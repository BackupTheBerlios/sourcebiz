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
# Registration form for the daily/weekly newsletter
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id
#
######################################################################

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session"));
if (isset($auth) && !empty($auth->auth["perm"])) {
  page_close();
  page_open(array("sess" => "SourceBiz_Session",
                  "auth" => "SourceBiz_Auth",
                  "perm" => "SourceBiz_Perm"));
}

require("./include/header.inc");

$bx = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$bi = new box("80%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("80%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
?>

<!-- content -->
<?php

###
### Submit Handler
###

## Get a database connection
$db = new DB_SourceBiz;

// Check if there was a submission
$subs = 0;
while (is_array($HTTP_POST_VARS) 
       && list($key, $val) = each($HTTP_POST_VARS)) {
    switch ($key) {
    case "subscribe": // sunscribe newsletter
		$email_usr = trim($email_usr);
		$password = trim($password);
		$cpassword = trim($cpassword);
        if (empty($email_usr) || empty($password)  || empty($cpassword)) { // Do we have all necessary data?
            $be->box_full($t->translate("Error"), $t->translate("Please enter")." <b>".$t->translate("Username")."</b>, <b>".$t->translate("Password")."</b> ".$t->translate("and")." <b>".$t->translate("E-Mail")."</b>!");
            break;
        }
        if (strcmp($password,$cpassword)) { // password are identical?
            $be->box_full($t->translate("Error"), $t->translate("The passwords are not identical").". ".$t->translate("Please try again")."!");
            break;
        }
        // send mail
        $message = "";
		if ($period == "daily") { // Daily Newsletter
			mail($ml_newsreqaddr,"subscribe $password",$message,"From: $email_usr\nReply-To: $email_usr\nX-Mailer: PHP");
			$msg = $t->translate("Congratulations")."! "
				  .$t->translate("You have subscribed to $sys_name daily Newsletter")."."
				  ."<p>".$t->translate("You are now being sent a confirmation email to verify your email address").".";
			$bi->box_full($t->translate("Subscribe daily Newsletter"), $msg);
		} else { // Weekly Newsletter
			mail($ml_weeklynewsreqaddr,"subscribe $password",$message,"From: $email_usr\nReply-To: $email_usr\nX-Mailer: PHP");
			$msg = $t->translate("Congratulations")."! "
				  .$t->translate("You have subscribed to $sys_name weekly Newsletter")."."
				  ."<p>".$t->translate("You are now being sent a confirmation email to verify your email address").".";
			$bi->box_full($t->translate("Subscribe weekly Newsletter"), $msg);
		}
        $subs = 1;
        break;
    default:
        break;
    }
}

if (!$subs) {
	$bx->box_begin();
	$bx->box_title($t->translate("Subscribe Newsletter"));
	$bx->box_body_begin();
?>
<table border=0 cellspacing=0 cellpadding=3>
<tr>
<!-- create a new user -->
<form method="post" action="<?php $sess->pself_url() ?>">
<td align=right><?php echo $t->translate("E-Mail") ?>:</td><td><input type="text" name="email_usr" size=20 maxlength=128 value=""></td>
</tr>
<tr valign=middle align=left>
<td align=right><?php echo $t->translate("Password") ?>:</td><td><input type="password" name="password" size=20 maxlength=32 value=""></td>
</tr>
<tr valign=middle align=left>
<td align=right><?php echo $t->translate("Confirm Password") ?>:</td><td><input type="password" name="cpassword" size=20 maxlength=32 value=""></td>
</tr>
<tr valign=middle align=left>
<td></td><td>
<input type=radio name="period" value="daily" checked> <?php echo $t->translate("daily");?>&nbsp;
<input type=radio name="period" value="weekly"> <?php echo $t->translate("weekly");?>
</td></tr>
<tr valign=middle align=left>
<td></td>
<?php
echo "<td><input type=\"submit\" name=\"subscribe\" value=\"".$t->translate("Subscribe")."\">";
?>
</td>
</tr>
</form>
</table>
<?php
	$bx->box_body_end();
	$bx->box_end();
}
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
