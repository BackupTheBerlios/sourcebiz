<?php

######################################################################
# SourceBiz: Open Source Business
# ===============================
#
# Copyright (c) 2001-2003 by
#                Lutz Henckel (lutz.henckel@fokus.fraunhofer.de)
#
# BerliOS SourceBiz: http://sourcebiz.berlios.de
# BerliOS - The OpenSource Mediator: http://www.berlios.de
#
# This file is usefull for administrating (registered) users
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id
#
######################################################################

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session",
                "auth" => "SourceBiz_Auth",
                "perm" => "SourceBiz_Perm"));

require("./include/header.inc");

$bx = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
?>

<!-- content -->
<?php
if ($perm->have_perm("admin")) {

###
### Submit Handler
###

## Get a database connection
$db = new DB_SourceBiz;

// Check if there was a submission
while (is_array($HTTP_POST_VARS) 
		  && list($key, $val) = each($HTTP_POST_VARS)) {
	switch ($key) {
		case "create": // Create a new user
			if (empty($username) || empty($password) || empty($email_usr)) { // Do we have all necessary data?
				$be->box_full($t->translate("Error"), $t->translate("Please enter")." <B>".$t->translate("Username")."</B>, <B>".$t->translate("Password")."</B> ".$t->translate("and")." <B>".$t->translate("E-Mail")."</B>!");
				break;
			}
         /* Does the user already exist?
	    NOTE: This should be a transaction, but it isn't... */
			$db->query("select * from auth_user where username='$username'");
			if ($db->nf()>0) {
				$be->box_full($t->translate("Error"), $t->translate("User")." <B>$username</B> ".$t->translate("already exists").".");
				break;
			}
			// Create a uid and insert the user...
			$u_id=md5(uniqid($hash_secret));
			$permlist = addslashes(implode($perms,","));
			$modification_usr = "NOW()";
			$creation_usr = "NOW()";
			$query = "insert into auth_user values('$u_id','$username','$password','$realname','$email_usr',$modification_usr,$creation_usr,'$permlist')";
			$db->query($query);
			if ($db->affected_rows() == 0) {
				$be->box_full($t->translate("Error"), "<b>".$t->translate("Database Access failed").":</b> $query");
				break;
			}
			$bx->box_full($t->translate("User Creation"), $t->translate("User")." \"$username\" ".$t->translate("created").".<BR>");
			break;

		case "u_edit": // Change user parameters
			if (empty($username) || empty($password) || empty($email_usr)) { // Do we have all necessary data?
				$be->box_full($t->translate("Error"), $t->translate("Please enter")." <B>".$t->translate("Username")."</B>, <B>".$t->translate("Password")."</B> ".$t->translate("and")." <B>".$t->translate("E-Mail")."</B>!");
				break;
			}
			// Update user information.
			$permlist = addslashes(implode($perms,","));
			$query = "update auth_user set username='$username', password='$password', realname='$realname', email_usr='$email_usr', modification_usr=NOW(), perms='$permlist' where user_id='$u_id'";
			$db->query($query);
			if ($db->affected_rows() == 0) {
				$be->box_full($t->translate("Error"), $t->translate("User Change failed").":<br>$query");
				break;
			}
			$bx->box_full($t->translate("User Change"), $t->translate("User")." <b>$username</b> ".$t->translate("is changed").".<br>");
			break;

		case "u_kill":
			// Delete that user.
			$query = "delete from auth_user where user_id='$u_id' and username='$username'";
			$db->query($query);
			if ($db->affected_rows() == 0) {
				$be->box_full($t->translate("Error"), $t->translate("User Deletion failed").":<br>$query");
				break;
			}
			$bx->box_full($t->translate("User Deletion"), $t->translate("User")." <b>$username</b> ".$t->translate("is deleted").".<BR>");
			break;

		default:
			break;
	}
}

/* Output user administration forms, including all updated
	information, if we come here after a submission...
*/

?>
<table border=0 cellspacing=0 cellpadding=0 bgcolor="<?php echo $th_box_frame_color;?>" align=center>
<tr>
<td>
<table border=0 align="center" cellspacing=1 cellpadding=3>
 <tr bgcolor="<?php echo $th_box_title_bgcolor;?>" valign=top align=left>
<?php
echo "  <th>".$t->translate("Username")."</th>";
echo "  <th>".$t->translate("Password")."</th>";
echo "  <th>".$t->translate("Realname")."</th>";
echo "  <th>".$t->translate("E-Mail")."</th>";
echo "  <th>".$t->translate("Modification")."</th>";
echo "  <th>".$t->translate("Creation")."</th>";
echo "  <th>".$t->translate("Permission")."</th>";
echo "  <th>".$t->translate("Action")."</th>";
?>
 </tr>
 <!-- create a new user -->
 <form method="post" action="<?php $sess->pself_url() ?>">
 <tr bgcolor="<?php echo $th_box_body_bgcolor;?>" valign=middle align=left>
  <td><input type="text" name="username" size=12 maxlength=32 value=""></td>
  <td><input type="text" name="password" size=12 maxlength=32 value=""></td>
  <td><input type="text" name="realname" size=12 maxlength=64 value=""></td>
  <td><input type="text" name="email_usr" size=12 maxlength=128 value=""></td>
  <td>&nbsp;</td>
  <td>&nbsp;</td>
  <td><?php print $perm->perm_sel("perms","user");?></td>
<?php
echo "  <td align=\"right\"><input type=\"submit\" name=\"create\" value=\"".$t->translate("Create User")."\"></td>\n";
?>
 </tr>
 </form>
<?php
  ## Traverse the result set
  $db->query("select * from auth_user order by username");
  while ($db->next_record()) {
?>
 <!-- existing user -->
 <form method="post" action="<?php $sess->pself_url() ?>">
 <tr bgcolor="<?php echo $th_box_body_bgcolor;?>" valign=middle align=left>
  <td><input type="text" name="username" size=12 maxlength=32 value="<?php $db->p("username") ?>"></td>
  <td><input type="text" name="password" size=12 maxlength=32 value="<?php $db->p("password") ?>"></td>
  <td><input type="text" name="realname" size=12 maxlength=64 value="<?php $db->p("realname") ?>"></td>
  <td><input type="text" name="email_usr" size=12 maxlength=32 value="<?php $db->p("email_usr") ?>"></td>
<?php
  $time = mktimestamp($db->f("modification_usr"));
  echo "  <td>".timestr($time)."</td>\n";
  $time = mktimestamp($db->f("creation_usr"));
  echo "  <td>".timestr($time)."</td>\n";
?>
  <td><?php print $perm->perm_sel("perms", $db->f("perms")) ?></td>
  <td align=right>
   <input type="hidden" name="u_id" value="<?php echo $db->p("user_id"); ?>">
<?php
  echo "   <input type=\"submit\" name=\"u_kill\" value=\"".$t->translate("Delete")."\">\n";
  echo "   <input type=\"submit\" name=\"u_edit\" value=\"".$t->translate("Change")."\">\n";
?>
  </td>
 </tr>
 </form>
<?php
  }
?>
</table>
</td>
</tr>
</table>
<?php
  } else {
	$be->box_full($t->translate("Error"), $t->translate("Access denied").".");
  }
?>

<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
