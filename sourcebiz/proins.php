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
# This file shows the enterprise and the added products
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
require("./include/entlib.inc");
require("./include/prolib.inc");

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
	$category_pro = trim($category_pro);
	$name_pro = trim($name_pro);
	$description_pro = trim($description_pro);
	$homepage_pro = trim($homepage_pro);
	if (!empty($homepage_pro) && !ereg("^http://", $homepage_pro)) {
		$homepage_pro = "http://".$homepage_pro;
	}
	if (!empty($name_pro)) {
	if (!empty($description_pro)) {

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
					// Insert new products
					$tables = "products";
					$set = "entid_pro='$id',category_pro='$category_pro',name_pro='$name_pro',description_pro='$description_pro',homepage_pro='$homepage_pro',status_pro='A',modification_pro=NOW(),creation_pro=NOW()";
					if (!$db->query("INSERT $tables SET $set")) {
						mysql_die($db);
					}

					// Select and show new/updated enterprises with products
					entbyentid($db,$id);
					probyentid($db,$id);
					if ($ml_notify) {
						$msg = "insert product \"$name_pro\" by ".$auth->auth["uname"].".";
						mailuser("admin", "insert product", $msg);
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
