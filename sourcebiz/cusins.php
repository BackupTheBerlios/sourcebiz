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
# This file shows the enterprise and the added customers
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: cusins.php,v 1.2 2003/02/25 11:45:44 helix Exp $
#
######################################################################

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session",
                "auth" => "SourceBiz_Auth",
                "perm" => "SourceBiz_Perm"));

require("./include/header.inc");
require("./include/entlib.inc");
require("./include/cuslib.inc");

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
	$name_cus = trim($name_cus);
	$description_cus = trim($description_cus);
	$homepage_cus = trim($homepage_cus);
	if (!empty($homepage_cus) && !ereg("^http://", $homepage_cus)) {
		$homepage_cus = "http://".$homepage_cus;
	}
	if (!empty($name_cus)) {
	if (!empty($description_cus)) {

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
					// Insert new customers
					$tables = "customers";
    				$set = "entid_cus='$id',name_cus='$name_cus',description_cus='$description_cus',homepage_cus='$homepage_cus',status_cus='A',modification_cus=NOW(),creation_cus=NOW()";
					if (!$db->query("INSERT $tables SET $set")) {
						mysql_die($db);
					}

					// Select and show new/updated enterprises with customers
					entbyentid($db,$id);
					cusbyentid($db,$id);
					if ($ml_notify) {
						$msg = "insert customer \"$name_cus\" by ".$auth->auth["uname"].".";
						mailuser("admin", "insert customer", $msg);
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
		$be->box_full($t->translate("Error"), $t->translate("No Description specified"));
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
