<?php

######################################################################
# SourceBiz: Open Source Business
# ================================================
#
# Copyright (c) 2001-2003 by
#                Lutz Henckel (lutz.henckel@fokus.fraunhofer.de)
#
# BerliOS SourceBiz: http://sourcebiz.berlios.de
# BerliOS - The OpenSource Mediator: http://www.berlios.de
#
# This file shows the enterprise and the added contact
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: conins.php,v 1.2 2003/02/25 11:45:44 helix Exp $
#
######################################################################

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session",
                "auth" => "SourceBiz_Auth",
                "perm" => "SourceBiz_Perm"));

require("./include/header.inc");
require("./include/entlib.inc");
require("./include/conlib.inc");

$bx = new box("100%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
$bs = new box("100%",$th_strip_frame_color,$th_strip_frame_width,$th_strip_title_bgcolor,$th_strip_title_font_color,$th_strip_title_align,$th_strip_body_bgcolor,$th_strip_body_font_color,$th_strip_body_align);
?>

<!-- content -->
<?php
if ($perm->have_perm("user_pending")) {
	$be->box_full($t->translate("Error"), $t->translate("Access denied"));
	$auth->logout();
} else {
	if (isset($id)) {
	if (!empty($name_con)) {

		// Look if enterprise is in table
    	$columns = "*";
    	$tables = "enterprise";
    	$where = "entid='$id'";
    	if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
      		mysql_die($db);
    	} else {

			// If enterprise in table
			if ($db->next_record()) {
				if ($db->f("user") == $auth->auth["uname"] || $perm->have_perm("admin")) {

					$name_con = trim($name_con);
					$logo_con_name = trim($logo_con_name);
					$description_con = trim($description_con);
					$address_con = trim($address_con);
					$country_con = trim($country_con);
					$state_con = trim($state_con);
					$city_con = trim($city_con);
					$zip_con = trim($zip_con);
					$phone_con = trim($phone_con);
					$fax_con = trim($fax_con);
					$email_con = trim($email_con);
					$homepage_con = trim($homepage_con);
					if (!empty($homepage_con) && !ereg("^http://", $homepage_con)) {
						$homepage_con = "http://".$homepage_con;
					}

					// Insert new contact
    				$tables = "contact";
    				$set = "entid_con='$id',name_con='$name_con',logo_con='$logo_con_name',type_con='$type_con',description_con='$description_con',address_con='$address_con',country_con='$country_con',state_con='$state_con',city_con='$city_con',zip_con='$zip_con',phone_con='$phone_con',fax_con='$fax_con',email_con='$email_con',homepage_con='$homepage_con',status_con='A',modification_con=NOW(),creation_con=NOW()";
    				if (!$db->query("INSERT $tables SET $set")) {
      					mysql_die($db);
    				}

					// Get new contact
					$columns = "*";
            		$where = "entid_con='$id' AND name_con='$name_con'";
            		if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
                		mysql_die($db);
            		} else {
						$db->next_record();
						if (!empty($logo_con_name)) {
							if (!copy($logo_con, $sys_logo_dir.$db->f("conid")."con_".basename($logo_con_name))) {
								$be->box_full($t->translate("Error"), $t->translate("Unable to copy logofile to logo directory"));
							}
							if (!chmod($sys_logo_dir.$db->f("conid")."con_".basename($logo_con_name),0666)) {
								$be->box_full($t->translate("Error"), $t->translate("Unable to change logofile mode"));
							}
						}

						// Show enterprise with new contact
						entbyentid($db,$id);
						conbyentid($db,$id);
						if ($ml_notify) {
							$msg = "insert contact \"$name_con\" by ".$auth->auth["uname"].".";
							mailuser("admin", "insert contact", $msg);
						}
					}
        		} else {
          			$be->box_full($t->translate("Error"), $t->translate("Access denied"));
				}

			// If enterprise is not in table
			} else {
				$be->box_full($t->translate("Error"), $t->translate("Enterprise")." (ID: $id) ".$t->translate("does not exist").".");
      		}
		}
	} else {
		$be->box_full($t->translate("Error"), $t->translate("No Name specified"));
	}
  	} else {
    	$be->box_full($t->translate("Error"), $t->translate("No Enterprise ID specified"));
  	}
}
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
