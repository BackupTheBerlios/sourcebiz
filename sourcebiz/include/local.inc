<?php
/*
 * Session Management for PHP3
 *
 * Copyright (c) 1998-2000 NetUSE AG
 *                    Boris Erdmann, Kristian Koehntopp
 *
 * $Id: local.inc,v 1.1 2003/02/25 11:11:57 helix Exp $
 *
 */ 

######################################################################
# SourceBiz Database Configuration
#
# For using SourceBiz, you only have to fill in the appropriate
# parameters that fit your database
#
# The default (and recommended) configuration is the one with
# "sourcebiz" as the database name. Do better not change it ;-)
#
######################################################################

if ( file_exists( 'local_database.inc' ) ) {
  /** defines the DB_SourceBiz class **/
  include( 'local_database.inc' );
} else if ( file_exists( 'include/local_database.inc' ) ) {
  include( 'include/local_database.inc' );
} else {
  class DB_SourceBiz extends DB_Sql {
    var $Host      = "localhost";
    var $Database  = "sourcebiz";
    var $User      = "sourcebiz";
    var $Password  = "password";
  }
}

/*********************************************************************/
/* If you've finished configuring the Database, you can login as an  */
/* administrator. To do so, just launch your web browser pointing to */
/* http://yourdomain.com/login.php and login as the default admin    */
/* with user,editor,admin permissions.                               */
/*                                                                   */
/* At the prompt use the following ID to login (case sensitive):     */
/*                                                                   */
/*         Username: oldfish                                         */
/*         Password: oldfish                                         */
/*                                                                   */
/* Vert important:                                                   */
/* Be sure of inmediately changing the login & password by clicking  */
/* on User Admin. You'll notice this is quite easy to do ;-)         */
/*                                                                   */
/*               Thanks for having chosen SourceWell                 */
/*********************************************************************/


######################################################################
# SourceBiz Advanced Database Configuration
#
# If you've chosen "sourcebiz" as your database name, you don't
# need to worry about the rest of the file ;-)
#
# If you've chosen another database name, you'll have to change this
# file and config.inc in the pint "Database Name Config".
######################################################################

class SourceBiz_CT_Sql extends CT_Sql {
  var $database_class = "DB_SourceBiz";   ## Which database to connect...
  var $database_table = "active_sessions"; ## and find our session data in this table.
}

#class SourceBiz_CT_Split_Sql extends CT_Split_Sql {
#  var $database_class = "DB_SourceBiz";   ## Which database to connect...
#  var $database_table = "active_sessions_split"; ## and find our session data in this table.
#  var $split_length = 4096                 ## Split rows every 4096 bytes
#}

#class SourceBiz_CT_Shm extends CT_Shm {
#  var $max_sessions   = 500;               ## number of maximum sessions
#  var $shm_key        = 0x123754;          ## unique shm identifier
#  var $shm_size       = 64000;             ## size of segment
#}

#class SourceBiz_CT_Ldap extends CT_Ldap {
#   var $ldap_host = "localhost";
#   var $ldap_port = 389;
#   var $basedn    = "dc=your-domain, dc=com";
#   var $rootdn    = "cn=root, dc=your-domain, dc=com";
#   var $rootpw    = "secret";
#   var $objclass  = "phplibdata";
#}

#class SourceBiz_CT_Dbm extends CT_DBM {
#   var $dbm_file  = "must_exist.dbm";
#}

class SourceBiz_Session extends Session {
  var $classname = "SourceBiz_Session";

  var $cookiename     = "";                ## defaults to classname
  var $magic          = "Hocuspocus";      ## ID seed
  var $mode           = "cookie";          ## We propagate session IDs with cookies
#  var $mode = "get";
  var $fallback_mode  = "get";
  var $lifetime       = 0;                 ## 0 = do session cookies, else minutes
  var $that_class     = "SourceBiz_CT_Sql"; ## name of data storage container
  var $gc_probability = 5;  
}

class SourceBiz_User extends User {
  var $classname = "SourceBiz_User";

  var $magic          = "Abracadabra";     ## ID seed
  var $that_class     = "SourceBiz_CT_Sql"; ## data storage container
}

class SourceBiz_Auth extends Auth {
  var $classname      = "SourceBiz_Auth";

  var $lifetime       =  30;

  var $database_class = "DB_SourceBiz";
  var $database_table = "auth_user";
  
  function auth_loginform() {
    global $sess;
    global $_PHPLIB;

    include("loginform.ihtml");
  }
  
  function auth_validatelogin() {
    global $username, $password;

    if(isset($username)) {
      $this->auth["uname"]=$username;        ## This provides access for "loginform.ihtml"
    }
    
    
    $uid = false;
    
    $this->db->query(sprintf("select user_id, perms ".
                             "        from %s ".
                             "       where username = '%s' ".
                             "         and password = '%s'",
                          $this->database_table,
                          addslashes($username),
                          addslashes($password)));

    while($this->db->next_record()) {
      $uid = $this->db->f("user_id");
      $this->auth["perm"] = $this->db->f("perms");
    }
    return $uid;
  }
}

class SourceBiz_Default_Auth extends SourceBiz_Auth {
  var $classname = "SourceBiz_Default_Auth";
  
  var $nobody    = true;
}

class SourceBiz_Challenge_Auth extends Auth {
  var $classname      = "SourceBiz_Challenge_Auth";

  var $lifetime       =  1;

  var $magic          = "Simsalabim";  ## Challenge seed
  var $database_class = "DB_SourceBiz";
  var $database_table = "auth_user";

  function auth_loginform() {
    global $sess;
    global $challenge;
    global $_PHPLIB;
    
    $challenge = md5(uniqid($this->magic));
    $sess->register("challenge");
    
    include($_PHPLIB["libdir"] . "crloginform.ihtml");
  }
  
  function auth_validatelogin() {
    global $username, $password, $challenge, $response;

    if(isset($username)) {
      $this->auth["uname"]=$username;        ## This provides access for "loginform.ihtml"
    }
    $this->db->query(sprintf("select user_id,perms,password ".
                "from %s where username = '%s'",
                          $this->database_table,
                          addslashes($username)));

    while($this->db->next_record()) {
      $uid   = $this->db->f("user_id");
      $perm  = $this->db->f("perms");
      $pass  = $this->db->f("password");
    }
    $exspected_response = md5("$username:$pass:$challenge");

    ## True when JS is disabled
    if ($response == "") {
      if ($password != $pass) {
        return false;
      } else {
        $this->auth["perm"] = $perm;
        return $uid;
      }
    }
    
    ## Response is set, JS is enabled
    if ($exspected_response != $response) {
      return false;
    } else {
      $this->auth["perm"] = $perm;
      return $uid;
    }
  }
}

##
## SourceBiz_Challenge_Crypt_Auth: Keep passwords in md5 hashes rather 
##                           than cleartext in database
## Author: Jim Zajkowski <jim@jimz.com>

class SourceBiz_Challenge_Crypt_Auth extends Auth {
  var $classname      = "SourceBiz_Challenge_Crypt_Auth";

  var $lifetime       =  1;

  var $magic          = "Frobozzica";  ## Challenge seed
  var $database_class = "DB_SourceBiz";
  var $database_table = "auth_user_md5";

  function auth_loginform() {
    global $sess;
    global $challenge;
    
    $challenge = md5(uniqid($this->magic));
    $sess->register("challenge");
    
    include("crcloginform.ihtml");
  }
  
  function auth_validatelogin() {
    global $username, $password, $challenge, $response;

    $this->auth["uname"]=$username;        ## This provides access for "loginform.ihtml"
    
    $this->db->query(sprintf("select user_id,perms,password ".
                "from %s where username = '%s'",
                          $this->database_table,
                          addslashes($username)));

    while($this->db->next_record()) {
      $uid   = $this->db->f("user_id");
      $perm  = $this->db->f("perms");
      $pass  = $this->db->f("password");   ## Password is stored as a md5 hash
    }
    $exspected_response = md5("$username:$pass:$challenge");

    ## True when JS is disabled
    if ($response == "") {
      if (md5($password) != $pass) {       ## md5 hash for non-JavaScript browsers
        return false;
      } else {
        $this->auth["perm"] = $perm;
        return $uid;
      }
    }
    
    ## Response is set, JS is enabled
    if ($exspected_response != $response) {
      return false;
    } else {
      $this->auth["perm"] = $perm;
      return $uid;
    }
  }
}

class SourceBiz_Perm extends Perm {
  var $classname = "SourceBiz_Perm";
  
  var $permissions = array(
                            "user_pending" => 1,
                            "user"       => 2,
                            "editor"     => 4,
                            "supervisor" => 8,
                            "admin"      => 16
                          );

  function perm_invalid($does_have, $must_have) {
    global $perm, $auth, $sess;
    global $_PHPLIB;
    
    include($_PHPLIB["libdir"] . "perminvalid.ihtml");
  }
}

## Domaines by  Country

// (ordered by importance)

    $domain_country[1][0] = "com";	$domain_country[1][1] = "Commercial (.com)";
    $domain_country[2][0] = "org";	$domain_country[2][1] = "Organization (.org)";
    $domain_country[3][0] = "net";	$domain_country[3][1] = "Network (.net)";
    $domain_country[4][0] = "de";	$domain_country[4][1] = "Germany (.de)";
    $domain_country[5][0] = "fr";	$domain_country[5][1] = "France (.fr)";
    $domain_country[6][0] = "edu";	$domain_country[6][1] = "Educational (.edu)";
    $domain_country[7][0] = "uk";	$domain_country[7][1] = "United Kingdom (.uk)";
    $domain_country[8][0] = "it";	$domain_country[8][1] = "Italy (.it)";
    $domain_country[9][0] = "se";	$domain_country[9][1] = "Sweden (.se)";
    $domain_country[10][0] = "nl";	$domain_country[10][1] = "The Netherlands (.nl)";
    $domain_country[11][0] = "be";	$domain_country[11][1] = "Belgium (.be)";
    $domain_country[12][0] = "es";	$domain_country[12][1] = "Spain (.es)";
    $domain_country[13][0] = "nu";	$domain_country[13][1] = "Niue (.nu)";
    $domain_country[14][0] = "ca";	$domain_country[14][1] = "Canada (.ca)";
    $domain_country[15][0] = "jp";	$domain_country[15][1] = "Japan (.jp)";
    $domain_country[16][0] = "cz";	$domain_country[16][1] = "Czech Republik (.cz)";
    $domain_country[17][0] = "ru";	$domain_country[17][1] = "Russian Federation (.ru)";
    $domain_country[21][0] = "no";	$domain_country[21][1] = "Norway (.no)";
    $domain_country[24][0] = "at";	$domain_country[24][1] = "Austria (at.)";

// In alfabetical order
    $domain_country[25][0] = "ac";	$domain_country[25][1] = "Ascension Island (.ac)";
    $domain_country[26][0] = "ad";	$domain_country[26][1] = "Andorra (.ad)";
    $domain_country[27][0] = "ae";	$domain_country[27][1] = "United Arab Emirates (.ae)";
    $domain_country[28][0] = "af";	$domain_country[28][1] = "Afghanistan (.af)";
    $domain_country[29][0] = "ag";	$domain_country[29][1] = "Antigua and Barbuda (.ag)";
    $domain_country[30][0] = "ai";	$domain_country[30][1] = "Anguilla (.ai)";
    $domain_country[31][0] = "al";	$domain_country[31][1] = "Albania (.al)";
    $domain_country[32][0] = "am";	$domain_country[32][1] = "Armenia (.am)";
    $domain_country[33][0] = "an";	$domain_country[33][1] = "Netherlands Antilles (.an)";
    $domain_country[34][0] = "ao";	$domain_country[34][1] = "Angola (.ao)";
    $domain_country[35][0] = "aq";	$domain_country[35][1] = "Antartica (.aq)";
    $domain_country[36][0] = "ar";	$domain_country[36][1] = "Argentina (.ar)";
    $domain_country[37][0] = "as";	$domain_country[37][1] = "American Samoa (.as)";
    $domain_country[38][0] = "au";	$domain_country[38][1] = "Australia (.au)";
    $domain_country[39][0] = "aw";	$domain_country[39][1] = "Aruba (.aw)";
    $domain_country[40][0] = "az";	$domain_country[40][1] = "Azerbaijan (.az)";
    $domain_country[41][0] = "ba";	$domain_country[41][1] = "Bosnia and Herzegovina (.ba)";
    $domain_country[42][0] = "bb";	$domain_country[42][1] = "Barbados (.bb)";
    $domain_country[43][0] = "bd";	$domain_country[43][1] = "Bangladesh (.bd)";

/*
    $domain_country[44][0] = "";	$domain_country[44][1] = "";
    $domain_country[45][0] = "";	$domain_country[45][1] = "";
    $domain_country[46][0] = "";	$domain_country[46][1] = "";
    $domain_country[47][0] = "";	$domain_country[47][1] = "";
    $domain_country[48][0] = "";	$domain_country[48][1] = "";
    $domain_country[49][0] = "";	$domain_country[49][1] = "";
    $domain_country[50][0] = "";	$domain_country[50][1] = "";
    $domain_country[51][0] = "";	$domain_country[51][1] = "";
    $domain_country[52][0] = "";	$domain_country[52][1] = "";
    $domain_country[53][0] = "";	$domain_country[53][1] = "";
    $domain_country[54][0] = "";	$domain_country[54][1] = "";
    $domain_country[55][0] = "";	$domain_country[55][1] = "";
    $domain_country[56][0] = "";	$domain_country[56][1] = "";
    $domain_country[57][0] = "";	$domain_country[57][1] = "";
    $domain_country[58][0] = "";	$domain_country[58][1] = "";
    $domain_country[59][0] = "";	$domain_country[59][1] = "";
    $domain_country[60][0] = "";	$domain_country[60][1] = "";
    $domain_country[61][0] = "";	$domain_country[61][1] = "";
    $domain_country[62][0] = "";	$domain_country[62][1] = "";
    $domain_country[63][0] = "";	$domain_country[63][1] = "";
    $domain_country[64][0] = "";	$domain_country[64][1] = "";
    $domain_country[65][0] = "";	$domain_country[65][1] = "";
    $domain_country[66][0] = "";	$domain_country[66][1] = "";
    $domain_country[67][0] = "";	$domain_country[67][1] = "";
    $domain_country[68][0] = "";	$domain_country[68][1] = "";
    $domain_country[69][0] = "";	$domain_country[69][1] = "";
    $domain_country[70][0] = "";	$domain_country[70][1] = "";
    $domain_country[71][0] = "";	$domain_country[71][1] = "";
    $domain_country[72][0] = "";	$domain_country[72][1] = "";
    $domain_country[73][0] = "";	$domain_country[73][1] = "";
    $domain_country[74][0] = "";	$domain_country[74][1] = "";
    $domain_country[75][0] = "";	$domain_country[75][1] = "";
    $domain_country[76][0] = "";	$domain_country[76][1] = "";
    $domain_country[77][0] = "";	$domain_country[77][1] = "";
    $domain_country[78][0] = "";	$domain_country[78][1] = "";
    $domain_country[79][0] = "";	$domain_country[79][1] = "";
    $domain_country[80][0] = "";	$domain_country[80][1] = "";
    $domain_country[81][0] = "";	$domain_country[81][1] = "";
    $domain_country[82][0] = "";	$domain_country[82][1] = "";
    $domain_country[83][0] = "";	$domain_country[83][1] = "";
    $domain_country[84][0] = "";	$domain_country[84][1] = "";
    $domain_country[85][0] = "";	$domain_country[85][1] = "";
    $domain_country[86][0] = "";	$domain_country[86][1] = "";
    $domain_country[87][0] = "";	$domain_country[87][1] = "";
    $domain_country[88][0] = "";	$domain_country[88][1] = "";
    $domain_country[89][0] = "";	$domain_country[89][1] = "";
    $domain_country[90][0] = "";	$domain_country[90][1] = "";
    $domain_country[91][0] = "";	$domain_country[91][1] = "";
    $domain_country[92][0] = "";	$domain_country[92][1] = "";
    $domain_country[93][0] = "";	$domain_country[93][1] = "";
    $domain_country[94][0] = "";	$domain_country[94][1] = "";
    $domain_country[95][0] = "";	$domain_country[95][1] = "";
    $domain_country[96][0] = "";	$domain_country[96][1] = "";
    $domain_country[97][0] = "";	$domain_country[97][1] = "";
    $domain_country[98][0] = "";	$domain_country[98][1] = "";
    $domain_country[99][0] = "";	$domain_country[99][1] = "";
    $domain_country[100][0] = "";	$domain_country[100][1] = "";
    $domain_country[101][0] = "";	$domain_country[101][1] = "";
    $domain_country[102][0] = "";	$domain_country[102][1] = "";
    $domain_country[103][0] = "";	$domain_country[103][1] = "";
    $domain_country[104][0] = "";	$domain_country[104][1] = "";
    $domain_country[105][0] = "";	$domain_country[105][1] = "";
    $domain_country[106][0] = "";	$domain_country[106][1] = "";
    $domain_country[107][0] = "";	$domain_country[107][1] = "";
    $domain_country[108][0] = "";	$domain_country[108][1] = "";
    $domain_country[109][0] = "";	$domain_country[109][1] = "";
    $domain_country[110][0] = "";	$domain_country[110][1] = "";
    $domain_country[111][0] = "";	$domain_country[111][1] = "";
    $domain_country[112][0] = "";	$domain_country[112][1] = "";
    $domain_country[113][0] = "";	$domain_country[113][1] = "";
    $domain_country[114][0] = "";	$domain_country[114][1] = "";
    $domain_country[115][0] = "";	$domain_country[115][1] = "";
    $domain_country[116][0] = "";	$domain_country[116][1] = "";
    $domain_country[117][0] = "";	$domain_country[117][1] = "";
    $domain_country[118][0] = "";	$domain_country[118][1] = "";
    $domain_country[119][0] = "";	$domain_country[119][1] = "";
    $domain_country[120][0] = "";	$domain_country[120][1] = "";
    $domain_country[121][0] = "";	$domain_country[121][1] = "";
    $domain_country[122][0] = "";	$domain_country[122][1] = "";
    $domain_country[123][0] = "";	$domain_country[123][1] = "";
    $domain_country[124][0] = "";	$domain_country[124][1] = "";
    $domain_country[125][0] = "";	$domain_country[125][1] = "";
    $domain_country[126][0] = "";	$domain_country[126][1] = "";
    $domain_country[127][0] = "";	$domain_country[127][1] = "";
    $domain_country[128][0] = "";	$domain_country[128][1] = "";
    $domain_country[129][0] = "";	$domain_country[129][1] = "";
    $domain_country[130][0] = "";	$domain_country[130][1] = "";
    $domain_country[131][0] = "";	$domain_country[131][1] = "";
    $domain_country[132][0] = "";	$domain_country[132][1] = "";
    $domain_country[133][0] = "";	$domain_country[133][1] = "";
    $domain_country[134][0] = "";	$domain_country[134][1] = "";
    $domain_country[135][0] = "";	$domain_country[135][1] = "";
    $domain_country[136][0] = "";	$domain_country[136][1] = "";
    $domain_country[137][0] = "";	$domain_country[137][1] = "";
    $domain_country[138][0] = "";	$domain_country[138][1] = "";
    $domain_country[139][0] = "";	$domain_country[139][1] = "";
    $domain_country[140][0] = "";	$domain_country[140][1] = "";
    $domain_country[141][0] = "";	$domain_country[141][1] = "";
    $domain_country[142][0] = "";	$domain_country[142][1] = "";
    $domain_country[143][0] = "";	$domain_country[143][1] = "";
    $domain_country[144][0] = "";	$domain_country[144][1] = "";
    $domain_country[145][0] = "";	$domain_country[145][1] = "";
    $domain_country[146][0] = "";	$domain_country[146][1] = "";
    $domain_country[147][0] = "";	$domain_country[147][1] = "";
    $domain_country[148][0] = "";	$domain_country[148][1] = "";
    $domain_country[149][0] = "";	$domain_country[149][1] = "";
    $domain_country[150][0] = "";	$domain_country[150][1] = "";
    $domain_country[151][0] = "";	$domain_country[151][1] = "";
    $domain_country[152][0] = "";	$domain_country[152][1] = "";
    $domain_country[153][0] = "";	$domain_country[153][1] = "";
    $domain_country[154][0] = "";	$domain_country[154][1] = "";
    $domain_country[155][0] = "";	$domain_country[155][1] = "";
    $domain_country[156][0] = "";	$domain_country[156][1] = "";
    $domain_country[157][0] = "";	$domain_country[157][1] = "";
    $domain_country[158][0] = "";	$domain_country[158][1] = "";
    $domain_country[159][0] = "";	$domain_country[159][1] = "";
    $domain_country[160][0] = "";	$domain_country[160][1] = "";
    $domain_country[161][0] = "";	$domain_country[161][1] = "";
    $domain_country[162][0] = "";	$domain_country[162][1] = "";
    $domain_country[163][0] = "";	$domain_country[163][1] = "";
    $domain_country[164][0] = "";	$domain_country[164][1] = "";
    $domain_country[165][0] = "";	$domain_country[165][1] = "";
    $domain_country[166][0] = "";	$domain_country[166][1] = "";
    $domain_country[167][0] = "";	$domain_country[167][1] = "";
    $domain_country[168][0] = "";	$domain_country[168][1] = "";
    $domain_country[169][0] = "";	$domain_country[169][1] = "";
    $domain_country[170][0] = "";	$domain_country[170][1] = "";
    $domain_country[171][0] = "";	$domain_country[171][1] = "";
    $domain_country[172][0] = "";	$domain_country[172][1] = "";
    $domain_country[173][0] = "";	$domain_country[173][1] = "";
    $domain_country[174][0] = "";	$domain_country[174][1] = "";
    $domain_country[175][0] = "";	$domain_country[175][1] = "";
    $domain_country[176][0] = "";	$domain_country[176][1] = "";
    $domain_country[177][0] = "";	$domain_country[177][1] = "";
    $domain_country[178][0] = "";	$domain_country[178][1] = "";
    $domain_country[179][0] = "";	$domain_country[179][1] = "";
    $domain_country[180][0] = "";	$domain_country[180][1] = "";
    $domain_country[181][0] = "";	$domain_country[181][1] = "";
    $domain_country[182][0] = "";	$domain_country[182][1] = "";
    $domain_country[183][0] = "";	$domain_country[183][1] = "";
    $domain_country[184][0] = "";	$domain_country[184][1] = "";
    $domain_country[185][0] = "";	$domain_country[185][1] = "";
    $domain_country[186][0] = "";	$domain_country[186][1] = "";
    $domain_country[187][0] = "";	$domain_country[187][1] = "";
    $domain_country[188][0] = "";	$domain_country[188][1] = "";
    $domain_country[189][0] = "";	$domain_country[189][1] = "";
    $domain_country[190][0] = "";	$domain_country[190][1] = "";
    $domain_country[191][0] = "";	$domain_country[191][1] = "";
    $domain_country[192][0] = "";	$domain_country[192][1] = "";
    $domain_country[193][0] = "";	$domain_country[193][1] = "";
    $domain_country[194][0] = "";	$domain_country[194][1] = "";
    $domain_country[195][0] = "";	$domain_country[195][1] = "";
    $domain_country[196][0] = "";	$domain_country[196][1] = "";
    $domain_country[197][0] = "";	$domain_country[197][1] = "";
    $domain_country[198][0] = "";	$domain_country[198][1] = "";
    $domain_country[199][0] = "";	$domain_country[199][1] = "";
    $domain_country[200][0] = "";	$domain_country[200][1] = "";
    $domain_country[201][0] = "";	$domain_country[201][1] = "";
    $domain_country[202][0] = "";	$domain_country[202][1] = "";
    $domain_country[203][0] = "";	$domain_country[203][1] = "";
    $domain_country[204][0] = "";	$domain_country[204][1] = "";
    $domain_country[205][0] = "";	$domain_country[205][1] = "";
    $domain_country[206][0] = "";	$domain_country[206][1] = "";
    $domain_country[207][0] = "";	$domain_country[207][1] = "";
    $domain_country[208][0] = "";	$domain_country[208][1] = "";
    $domain_country[209][0] = "";	$domain_country[209][1] = "";
    $domain_country[210][0] = "";	$domain_country[210][1] = "";
    $domain_country[211][0] = "";	$domain_country[211][1] = "";
    $domain_country[212][0] = "";	$domain_country[212][1] = "";
    $domain_country[213][0] = "";	$domain_country[213][1] = "";
    $domain_country[214][0] = "";	$domain_country[214][1] = "";
    $domain_country[215][0] = "";	$domain_country[215][1] = "";
    $domain_country[216][0] = "";	$domain_country[216][1] = "";
    $domain_country[217][0] = "";	$domain_country[217][1] = "";
    $domain_country[218][0] = "";	$domain_country[218][1] = "";
    $domain_country[219][0] = "";	$domain_country[219][1] = "";
    $domain_country[220][0] = "";	$domain_country[220][1] = "";
    $domain_country[221][0] = "";	$domain_country[221][1] = "";
    $domain_country[222][0] = "";	$domain_country[222][1] = "";
    $domain_country[223][0] = "";	$domain_country[223][1] = "";
    $domain_country[224][0] = "";	$domain_country[224][1] = "";
    $domain_country[225][0] = "";	$domain_country[225][1] = "";
    $domain_country[226][0] = "";	$domain_country[226][1] = "";
    $domain_country[227][0] = "";	$domain_country[227][1] = "";
    $domain_country[228][0] = "";	$domain_country[228][1] = "";
    $domain_country[229][0] = "";	$domain_country[229][1] = "";
    $domain_country[230][0] = "";	$domain_country[230][1] = "";
    $domain_country[231][0] = "";	$domain_country[231][1] = "";
    $domain_country[232][0] = "";	$domain_country[232][1] = "";
    $domain_country[233][0] = "";	$domain_country[233][1] = "";
    $domain_country[234][0] = "";	$domain_country[234][1] = "";
    $domain_country[235][0] = "";	$domain_country[235][1] = "";
    $domain_country[236][0] = "";	$domain_country[236][1] = "";
    $domain_country[237][0] = "";	$domain_country[237][1] = "";
    $domain_country[238][0] = "";	$domain_country[238][1] = "";
    $domain_country[239][0] = "";	$domain_country[239][1] = "";
    $domain_country[240][0] = "";	$domain_country[240][1] = "";
    $domain_country[241][0] = "";	$domain_country[241][1] = "";
    $domain_country[242][0] = "";	$domain_country[242][1] = "";
    $domain_country[243][0] = "";	$domain_country[243][1] = "";
    $domain_country[244][0] = "";	$domain_country[244][1] = "";
    $domain_country[245][0] = "";	$domain_country[245][1] = "";
    $domain_country[246][0] = "";	$domain_country[246][1] = "";
    $domain_country[247][0] = "";	$domain_country[247][1] = "";
    $domain_country[248][0] = "";	$domain_country[248][1] = "";
    $domain_country[249][0] = "";	$domain_country[249][1] = "";
    $domain_country[250][0] = "";	$domain_country[250][1] = "";
    $domain_country[251][0] = "";	$domain_country[251][1] = "";
    $domain_country[252][0] = "";	$domain_country[252][1] = "";
    $domain_country[253][0] = "";	$domain_country[253][1] = "";
    $domain_country[254][0] = "";	$domain_country[254][1] = "";
*/

##
## SourceBiz_Menu may extend Menu.
## If you name this class differently, you must also
## rename its constructor function - this is a PHP language 
## design stupidity.
##
## To use this, you must enable the require statement for
## menu.inc in prepend.php3.
##

# class SourceBiz_Menu extends Menu {
#   var $classname = "SourceBiz_Menu";
#
#   # Map of PHP_SELF URL strings to menu positions
#   var $urlmap = array(
#     "/menu/index.php"   => "",
#     "/menu/item1.php"   => "/1",
#     "/menu/item11.php"  => "/1/1",
#     "/menu/item12.php"  => "/1/2",
#     "/menu/item13.php"  => "/1/3",
#     "/menu/item2.php"   => "/2",
#     "/menu/item21.php"  => "/2/1",
#     "/menu/item22.php"  => "/2/2",
#     "/menu/item221.php" => "/2/2/1",
#     "/menu/item222.php" => "/2/2/2",
#     "/menu/item23.php"  => "/2/3",
#     "/menu/item24.php"  => "/2/4"
#   );
#   
#   # Information about each menu item
#   var $item = array(
#     ""      => array("title" => "Main"),
#     "/1"    => array("title" => "Text 1"),
#     "/1/1"  => array("title" => "Text 1.1"),
#     "/1/2"  => array("title" => "Text 1.2"),
#     "/1/3"  => array("title" => "Text 1.3"),
#     "/2"    => array("title" => "Text 2"),
#     "/2/1"  => array("title" => "Text 2.1"),
#     "/2/2"  => array("title" => "Text 2.2"),
#     "/2/2/1"=> array("title" => "Text 2.2.1"),
#     "/2/2/2"=> array("title" => "Text 2.2.2"),
#     "/2/3"  => array("title" => "Text 2.3"),
#     "/2/4"  => array("title" => "Text 2.4")
#   );
#   
#   function SourceBiz_Menu() {
#     $this->setup();
#   }
# }

?>
