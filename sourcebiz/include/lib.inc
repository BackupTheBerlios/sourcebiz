<?php

function mysql_die($db) {
    global $t,$be;
    $be->box_full($t->translate("Database Access failed"), $db->Errno." : ".$db->Error);
}

function mktimestamp($time) {
    $timestamp = mktime(substr($time,8,2),substr($time,10,2),substr($time,12,2),substr($time,4,2),substr($time,6,2),substr($time,0,4));
    return $timestamp;
}


function timestr($timestamp) {
    $time = strftime("%A, %e. %B %Y, %H:%M:%S %Z", $timestamp);
    return $time;
}

function timestr_short($timestamp){
    $time = strftime("%e. %b, %H:%M", $timestamp);
    return $time;
}

function inssec($string) {
    global $PHP_SELF, $bx, $t;
	$bx->box_begin();
	$bx->box_title($t->translate("Insert a Category"));
	$bx->box_body_begin();
    echo "<table border=0 align=center cellspacing=0 cellpadding=3 width=100%>\n";
    echo "<form action=\"inscat.php\" method=\"POST\">\n";

    if ($string == "yes") {
		// Inserting Sections and/or Categories
      echo "<tr><td align=right>".$t->translate("Section").":</td><td><b>".$GLOBALS["section"]."</b></td></tr>\n";
      echo "<input type=\"hidden\" name=\"section\" value=\"".$GLOBALS["section"]."\">\n";

    } else {
      echo "<tr><td align=right>".$t->translate("Section").":</td><td>\n";
      echo "<select name=\"section\">\n";
      sec($GLOBALS["section"]);     // We select the first one to avoid having a blank line
      echo "</select></td></tr>\n";
    }

    echo "<tr><td align=right>".$t->translate("Category")." (64):</td><td><input type=\"TEXT\" name=\"category\" size=40 maxlength=64></td></tr>\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Insert")."\"></td></tr>\n";
    echo "</form>\n";
    echo "</td></tr>\n";
    echo "</table>\n";
	$bx->box_body_end();
	$bx->box_end();
}

// 
//  select_form($table, $param, $sel)
//  Displays the different parameter values of a table as a select form
// 

function select_form($table,$param,$sel) {
    $dbsel = new DB_SourceBiz;
    if (!$dbsel->query("SELECT DISTINCT $param FROM $table ORDER BY $param ASC"))
    {
        mysql_die($dbsel);
    } else {
		$ret = "";
        while ($dbsel->next_record()) {
            $ret .= "<option";
            if ($dbsel->f($param) == $sel) {
                $ret .= " selected";
            }
            $ret .= ">".$dbsel->f($param)."\n";
        }
    }
    return $ret;
}

// 
//  select_cat($type)
//  Displays the different categories as a select form
// 

function select_cat($type,$sel) {
    $dbcat = new DB_SourceBiz;
    $columns = "*";
    $tables = "categories";
    $where = "type='$type'";
    $order = "category ASC";
    if (!$dbcat->query("SELECT DISTINCT $columns FROM $tables WHERE $where ORDER BY $order"))
    {
        mysql_die($dbcat);
    } else {
        while ($dbcat->next_record()) {
            echo "<option";
            if ($dbcat->f("category") == $sel) {
                echo " selected";
            }
            echo ">".$dbcat->f("category")."\n";
        }
    }
}

## show_more($iter,$maxiter,$url)
##
## shows 10 ents of the current iteraction $iter
## until it reaches the maximum number of iteractions $maxiter


function show_more($iter,$maxiter,$url) {

  $iter /=10;
  echo "<table border=0 width=600><tr>";
  echo "<td>&nbsp;</td>\n";
  echo "<td align=right>";

  $maxiter= Floor($maxiter);

  if ($iter > 3) {
      echo "<a href=\"".$url."iter=0\">&lt;&lt;</a>\n";
  }

  $number = $iter - 3;
  if ($number < 0) $number = 0;
  if ($iter > 2) {
    echo "<a href=\"".$url."iter=$number\">&lt;</a>\n";
  }

  switch ($iter) {
    case 0: $bias=0; break;
    case 1: $bias=1; break;
    case ($maxiter-1): if ($iter>3) {$bias=3;} else {$bias=2;} break;
    case ($maxiter): if ($iter>4) {$bias=4;} else {$bias=2;} break;
    default: $bias=2; break;
  }

  for($i=$iter-$bias;$i<$maxiter+1 && $i<($iter+5-$bias);$i++) {
    $number1 = $i*10 +1;
    $number2 = $number1 + 9;
    $number = strval($number1)."-".strval($number2);
    if ($i != $iter) echo "<a href=\"".$url."iter=$i\">&nbsp;$number</a>\n";
    else echo "<B>&nbsp;$number</B>\n"; 
   }

  $number = $iter + 5 - $bias;
  if ($number > $maxiter+$bias) $number =$maxiter+$bias;
  if ($iter < $maxiter-4+$bias) {
    echo "<a href=\"".$url."iter=$number\"> &gt;</a>\n";
  }

  $number = $iter + 10 - $bias;
  if ($number > $maxiter) $number = $maxiter;
  if ($iter < $maxiter-5 +$bias) {
    echo "<a href=\"".$url."iter=$number\"> &gt;&gt;</a>\n";
  }

   echo "</td>\n";
   echo "</tr></table><BR>";
}

function wrap($string,$width=75,$break=" ") {
	$out = "";
	$lin = "";
	$tok = strtok($string,$break);
	while ($tok) {
		if ((strlen($lin) + strlen($tok)) > $width) {
			$out .= $lin."\n";
			$lin = "";
		}
		if (strlen($lin) > 0)
			$lin .= " ";
		$lin .= $tok;
		$tok = strtok (" ");
	}
	$out .= $lin;
	return $out;
}

function typestr($type) {
	global $t;
	if ($type == "S")
		$str = $t->translate("Stable");
	if ($type == "D")
		$str = $t->translate("Development");
	return $str;
}

function admin($db) {
	global $auth, $perm;
	$admin = 0;
	if (isset($auth) && !empty($auth->auth["perm"]) && ($perm->have_perm("admin") || $db->f("user") == $auth->auth["uname"])) {
		$admin = 1;
	}
	return $admin;
}

function increasecnt($id, $type) {
	$dbcnt = new DB_SourceBiz;
	$columns = "*";
    $tables = "counter";
    $where = "entid='$id'";
    if (!$dbcnt->query("SELECT $columns FROM $tables WHERE $where")) {
        mysql_die($dbcnt);
    } else {
//
// If enterprise in table and first access today update counters
//
		$first = checkcnt($id, $GLOBALS[REMOTE_ADDR], $type);
        if ( $dbcnt->next_record() && $first) {
            $columns = $type;
            $tables = "counter";
            $counter = $dbcnt->f("$type") + 1;
            $set = "$type='$counter'";
            $where = "entid='$id'";
            if (!$dbcnt->query("UPDATE $tables SET $set WHERE $where")) {
				mysql_die($dbcnt);
			}
		}
	}
}

function checkcnt($id, $ipaddr, $type) {
	$dbchk = new DB_SourceBiz;
	$ret = 1;
//
// Delete all entries from yesterday
//
	$today = date("Y-m-d");
	$tables = "counter_check";
	$where = "DATE_FORMAT(creation_cnt,'%Y-%m-%d') != '$today'";
	if (!$dbchk->query("DELETE FROM $tables WHERE $where")) {
		mysql_die($dbchk);
	} else {
		$columns = "*";
		$where = "entid='$id' AND cnt_type='$type' AND ipaddr='$ipaddr'";
		if (!$dbchk->query("SELECT $columns FROM $tables WHERE $where")) {
			mysql_die($dbchk);
		} else {
//
// If remote host already accessed the ents link,
// don´t increase corresponding counter
//
			if ($dbchk->next_record()) {
				$ret = 0;
			} else {
// Include entry for remote host
				$set = "entid='$id',cnt_type='$type',ipaddr='$ipaddr'";
				if (!$dbchk->query("INSERT $tables SET $set")) {
					mysql_die($dbchk);
				}
			}
		}
	}
	return $ret;
}

function nlmsg($period) {
  global $db;

  $msg = "";
  $lastday = time() - 7 * 24 * 60 * 60;

  switch ($period) {
    case "weekly":
      $where = "DATE_FORMAT(news.modification_new,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(news.modification_new,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
      break;
    case "daily":
    default:
      $where = "DATE_FORMAT(news.modification_new,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
      break;
  }

  $db->query("SELECT * FROM news,enterprise WHERE $where AND enterprise.entid=news.entid_new AND news.status_new='A' ORDER BY news.modification_new DESC"); 

  if ($db->num_rows() > 0) {

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   News Headlines\n";
  $msg .= "               ---------------------------------\n\n";
	
  $msg .= "Number of News: ".$db->num_rows()."\n\n";
  $i = 1;
  while($db->next_record()) {
    $msg .= "$i: ".$db->f("subject_new")."\n";
    $i++;
  }

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   News Details\n";
  $msg .= "               ---------------------------------\n";

  $db->seek(0);

  $i = 1;
  while ($db->next_record()) {
    $timestamp = mktimestamp($db->f("modification_new"));
    $msg .= "\nNews         : $i\n";
    $msg .= "Subject      : ".$db->f("subject_new")."\n";
    $msg .= "Date         : ".date("l, dS of F Y, H:i:s T", $timestamp)."\n";
    $msg .= "Text         : ".$db->f("text_new")."\n";
    if ($db->f("homepage_new") != "") {
    	$msg .= "Homepage     : ".$db->f("homepage_new")."\n";
	}
    $msg .= "Enterprise   : ".$db->f("name")."\n";
    $msg .= $GLOBALS["sys_name"]."    : ".$GLOBALS["sys_url"]."newbynewid.php?id=".$db->f("newid")."\n";
    $msg .= "\n               ---------------------------------\n";
    $i++;
  }

  }

  switch ($period) {
    case "weekly":
      $where = "DATE_FORMAT(enterprise.modification,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(enterprise.modification,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
      break;
    case "daily":
    default:
      $where = "DATE_FORMAT(enterprise.modification,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
      break;
  }

  $db->query("SELECT * FROM enterprise WHERE $where AND enterprise.status='A' ORDER BY enterprise.modification DESC"); 

  if ($db->num_rows() > 0) {

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Enterprise Headlines\n";
  $msg .= "               ---------------------------------\n\n";
	
  $msg .= "Number of Enterprises: ".$db->num_rows()."\n\n";
  $i = 1;
  while($db->next_record()) {
    $msg .= "$i: ".$db->f("name")."\n";
    $i++;
  }

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Enterprise Details\n";
  $msg .= "               ---------------------------------\n";

  $db->seek(0);

  $i = 1;
  while ($db->next_record()) {
    $timestamp = mktimestamp($db->f("modification"));
    $msg .= "\nEnterprise   : $i\n";
    $msg .= "Name         : ".$db->f("name")."\n";
    $msg .= "Date         : ".date("l, dS of F Y, H:i:s T", $timestamp)."\n";
    if ($db->f("homepage") != "") {
    	$msg .= "Homepage     : ".$db->f("homepage")."\n";
	}
    $msg .= $GLOBALS["sys_name"]."    : ".$GLOBALS["sys_url"]."entbyid.php?id=".$db->f("entid")."\n";
    $msg .= "\n               ---------------------------------\n";
    $i++;
  }

  }

  switch ($period) {
    case "weekly":
      $where = "DATE_FORMAT(contact.modification_con,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(contact.modification_con,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
      break;
    case "daily":
    default:
      $where = "DATE_FORMAT(contact.modification_con,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
      break;
  }

  $db->query("SELECT * FROM contact,enterprise WHERE $where AND enterprise.entid=contact.entid_con AND contact.status_con='A' ORDER BY contact.modification_con DESC"); 

  if ($db->num_rows() > 0) {

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Contact Headlines\n";
  $msg .= "               ---------------------------------\n\n";
	
  $msg .= "Number of Contacts: ".$db->num_rows()."\n\n";
  $i = 1;
  while($db->next_record()) {
    $msg .= "$i: ".$db->f("name_con")."\n";
    $i++;
  }

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Contact Details\n";
  $msg .= "               ---------------------------------\n";

  $db->seek(0);

  $i = 1;
  while ($db->next_record()) {
    $timestamp = mktimestamp($db->f("modification_con"));
    $msg .= "\nContact      : $i\n";
    $msg .= "Name         : ".$db->f("name_con")."\n";
    $msg .= "Date         : ".date("l, dS of F Y, H:i:s T", $timestamp)."\n";
    $msg .= "Type         : ".$db->f("type_con")."\n";
    if ($db->f("homepage_con") != "") {
    	$msg .= "Homepage     : ".$db->f("homepage_con")."\n";
	}
    $msg .= "Enterprise   : ".$db->f("name")."\n";
    $msg .= $GLOBALS["sys_name"]."    : ".$GLOBALS["sys_url"]."conbyconid.php?id=".$db->f("conid")."\n";
    $msg .= "\n               ---------------------------------\n";
    $i++;
  }

  }

  switch ($period) {
    case "weekly":
      $where = "DATE_FORMAT(services.modification_svc,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(services.modification_svc,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
      break;
    case "daily":
    default:
      $where = "DATE_FORMAT(services.modification_svc,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
      break;
  }

  $db->query("SELECT * FROM services,enterprise WHERE $where AND enterprise.entid=services.entid_svc AND services.status_svc='A' ORDER BY services.modification_svc DESC"); 

  if ($db->num_rows() > 0) {

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Service Headlines\n";
  $msg .= "               ---------------------------------\n\n";
	
  $msg .= "Number of Services: ".$db->num_rows()."\n\n";
  $i = 1;
  while($db->next_record()) {
    $msg .= "$i: ".$db->f("name_svc")."\n";
    $i++;
  }

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Service Details\n";
  $msg .= "               ---------------------------------\n";

  $db->seek(0);

  $i = 1;
  while ($db->next_record()) {
    $timestamp = mktimestamp($db->f("modification_svc"));
    $msg .= "\nService      : $i\n";
    $msg .= "Name         : ".$db->f("name_svc")."\n";
    $msg .= "Date         : ".date("l, dS of F Y, H:i:s T", $timestamp)."\n";
    $msg .= "Category     : ".$db->f("category_svc")."\n";
    if ($db->f("homepage_svc") != "") {
    	$msg .= "Homepage     : ".$db->f("homepage_svc")."\n";
	}
    $msg .= "Enterprise   : ".$db->f("name")."\n";
    $msg .= $GLOBALS["sys_name"]."    : ".$GLOBALS["sys_url"]."svcbysvcid.php?id=".$db->f("svcid")."\n";
    $msg .= "\n               ---------------------------------\n";
    $i++;
  }

  }

  switch ($period) {
    case "weekly":
      $where = "DATE_FORMAT(products.modification_pro,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(products.modification_pro,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
      break;
    case "daily":
    default:
      $where = "DATE_FORMAT(products.modification_pro,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
      break;
  }

  $db->query("SELECT * FROM products,enterprise WHERE $where AND enterprise.entid=products.entid_pro AND products.status_pro='A' ORDER BY products.modification_pro DESC"); 

  if ($db->num_rows() > 0) {

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Product Headlines\n";
  $msg .= "               ---------------------------------\n\n";
	
  $msg .= "Number of Products: ".$db->num_rows()."\n\n";
  $i = 1;
  while($db->next_record()) {
    $msg .= "$i: ".$db->f("name_pro")."\n";
    $i++;
  }

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Product Details\n";
  $msg .= "               ---------------------------------\n";

  $db->seek(0);

  $i = 1;
  while ($db->next_record()) {
    $timestamp = mktimestamp($db->f("modification_pro"));
    $msg .= "\nProduct      : $i\n";
    $msg .= "Name         : ".$db->f("name_pro")."\n";
    $msg .= "Date         : ".date("l, dS of F Y, H:i:s T", $timestamp)."\n";
    $msg .= "Category     : ".$db->f("category_pro")."\n";
    if ($db->f("homepage_pro") != "") {
    	$msg .= "Homepage     : ".$db->f("homepage_pro")."\n";
	}
    $msg .= "Enterprise   : ".$db->f("name")."\n";
    $msg .= $GLOBALS["sys_name"]."    : ".$GLOBALS["sys_url"]."probyproid.php?id=".$db->f("proid")."\n";
    $msg .= "\n               ---------------------------------\n";
    $i++;
  }

  }

  switch ($period) {
    case "weekly":
      $where = "DATE_FORMAT(solutions.modification_sol,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(solutions.modification_sol,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
      break;
    case "daily":
    default:
      $where = "DATE_FORMAT(solutions.modification_sol,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
      break;
  }

  $db->query("SELECT * FROM solutions,enterprise WHERE $where AND enterprise.entid=solutions.entid_sol AND solutions.status_sol='A' ORDER BY solutions.modification_sol DESC"); 

  if ($db->num_rows() > 0) {

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Solution Headlines\n";
  $msg .= "               ---------------------------------\n\n";
	
  $msg .= "Number of Solutions: ".$db->num_rows()."\n\n";
  $i = 1;
  while($db->next_record()) {
    $msg .= "$i: ".$db->f("name_sol")."\n";
    $i++;
  }

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Solution Details\n";
  $msg .= "               ---------------------------------\n";

  $db->seek(0);

  $i = 1;
  while ($db->next_record()) {
    $timestamp = mktimestamp($db->f("modification_sol"));
    $msg .= "\nSolution     : $i\n";
    $msg .= "Name         : ".$db->f("name_pro")."\n";
    $msg .= "Date         : ".date("l, dS of F Y, H:i:s T", $timestamp)."\n";
    if ($db->f("homepage_sol") != "") {
    	$msg .= "Homepage     : ".$db->f("homepage_sol")."\n";
	}
    $msg .= "Enterprise   : ".$db->f("name")."\n";
    $msg .= $GLOBALS["sys_name"]."    : ".$GLOBALS["sys_url"]."solbysolid.php?id=".$db->f("solid")."\n";
    $msg .= "\n               ---------------------------------\n";
    $i++;
  }

  }

  switch ($period) {
    case "weekly":
      $where = "DATE_FORMAT(customers.modification_cus,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(customers.modification_cus,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
      break;
    case "daily":
    default:
      $where = "DATE_FORMAT(customers.modification_cus,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
      break;
  }

  $db->query("SELECT * FROM customers,enterprise WHERE $where AND enterprise.entid=customers.entid_cus AND customers.status_cus='A' ORDER BY customers.modification_cus DESC"); 

  if ($db->num_rows() > 0) {

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Customer Headlines\n";
  $msg .= "               ---------------------------------\n\n";
	
  $msg .= "Number of Customers: ".$db->num_rows()."\n\n";
  $i = 1;
  while($db->next_record()) {
    $msg .= "$i: ".$db->f("name_cus")."\n";
    $i++;
  }

  $msg .= "\n               ---------------------------------\n";
  $msg .= "                   Customer Details\n";
  $msg .= "               ---------------------------------\n";

  $db->seek(0);

  $i = 1;
  while ($db->next_record()) {
    $timestamp = mktimestamp($db->f("modification_cus"));
    $msg .= "\nCustomer     : $i\n";
    $msg .= "Name         : ".$db->f("name_cus")."\n";
    $msg .= "Date         : ".date("l, dS of F Y, H:i:s T", $timestamp)."\n";
    if ($db->f("homepage_cus") != "") {
    	$msg .= "Homepage     : ".$db->f("homepage_cus")."\n";
	}
    $msg .= "Enterprise   : ".$db->f("name")."\n";
    $msg .= $GLOBALS["sys_name"]."    : ".$GLOBALS["sys_url"]."cusbycusid.php?id=".$db->f("cusid")."\n";
    $msg .= "\n               ---------------------------------\n";
    $i++;
  }

  }

  if (!empty($msg)) {
  $msg = $GLOBALS["sys_name"]." $period newsletter for ".date("l, dS of F Y, H:i:s T")."\n".$msg;
  $msg .= "\nYou get this ".$GLOBALS["sys_name"]." $period newsletter,"
  ."\nbecause you have subscribed to the mailing list ";

  switch ($period) {
    case "weekly":
      $msg .= "\n".$GLOBALS["ml_weeklynewstoaddr"]."."
      ."\nTo unsubscribe from this mailing list,"
      ."\nsend a message by email to"
      ."\n".$GLOBALS["ml_weeklynewsreqaddr"]
      ."\nwith \"unsubscribe <password>\" as subject or visit"
      ."\n".$GLOBALS["ml_weeklylisturl"];
      break;
    case "daily":
    default:
      $msg .= "\n".$GLOBALS["ml_newstoaddr"]."."
      ."\nTo unsubscribe from this mailing list,"
      ."\nsend a message by email to"
      ."\n".$GLOBALS["ml_newsreqaddr"]
      ."\nwith \"unsubscribe <password>\" as subject or visit"
      ."\n".$GLOBALS["ml_listurl"];
      break;
  }
  $msg .= "\nand follow the instructions there."
  ."\n\n - The ".$GLOBALS["sys_name"]." crew";
  }

  return $msg;
}

function mailuser($perms, $subj, $message) {
  global $t, $db;
  $db->query("SELECT email_usr FROM auth_user WHERE perms LIKE '%$perms%'");
  while($db->next_record()) {
    mail($db->f("email_usr"),"[".$GLOBALS["sys_name"]."] ".$subj,$message,"From: ".$GLOBALS["ml_fromaddr"]."\nReply-To: ".$GLOBALS["ml_replyaddr"]."\nX-Mailer: PHP");
  }
}

?>
