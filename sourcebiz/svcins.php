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
# This file shows the enterprise and the added services
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
require("./include/svclib.inc");

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
	$category_svc = trim($category_svc);
	$name_svc = trim($name_svc);
	$description_svc = trim($description_svc);
	$homepage_svc = trim($homepage_svc);
	if (!empty($homepage_svc) && !ereg("^http://", $homepage_svc)) {
		$homepage_svc = "http://".$homepage_svc;
	}
	if (!empty($name_svc)) {
	if (!empty($description_svc)) {

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

					// Insert new services
    				$tables = "services";
    				$set = "entid_svc='$id',category_svc='$category_svc',name_svc='$name_svc',description_svc='$description_svc',homepage_svc='$homepage_svc',status_svc='A',modification_svc=NOW(),creation_svc=NOW()";
    				if (!$db->query("INSERT $tables SET $set")) {
      					mysql_die($db);
    				}

					// Select and show new/updated enterprises with services
					entbyentid($db,$id);
					svcbyentid($db,$id);
					if ($ml_notify) {
						$msg = "insert service \"$name_svc\" by ".$auth->auth["uname"].".";
						mailuser("admin", "insert service", $msg);
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
