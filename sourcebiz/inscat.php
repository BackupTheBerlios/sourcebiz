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
# Inserts a category
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: inscat.php,v 1.2 2003/02/25 11:45:44 helix Exp $
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
	if (isset($category) && !empty($category)) {
		$dbcat = new DB_SourceBiz;

		// Look if Category is already in table
   		$columns = "*";
		$tables = "categories";
		$where = "type='$type' AND category='$category'";
		if (!$dbcat->query("SELECT $columns FROM $tables WHERE $where")) {
			mysql_die($dbcat);
		} else {
			switch ($action) {
			case "ins":
				if ($dbcat->num_rows() > 0) {
					$be->box_full($t->translate("Error"), $t->translate("Category")." $category ".$t->translate("already exists"));
				} else {
					$set = "type='$type',category='$category'";
					if (!$dbcat->query("INSERT $tables SET $set")) {
          				mysql_die($dbcat);
					} else {
						$bx->box_full($t->translate("Administration"),$t->translate("Category")." $category ".$t->translate("has been added"));
					}
				}
				break;
			case "ren":
				if ($dbcat->num_rows() < 1) {
					$be->box_full($t->translate("Error"), $t->translate("Category")." $category ".$t->translate("does not exist"));
				} else {
					$set = "category='$new_category'";
					$where = "type='$type' AND category='$category'";
					if (!$dbcat->query("UPDATE $tables SET $set WHERE $where")) {
          				mysql_die($dbcat);
					} else {
						$bx->box_full($t->translate("Administration"),$t->translate("Category")." $category ".$t->translate("has been renamed to")." $new_category");
					}
				}
				break;
			case "del":
				if ($dbcat->num_rows() < 1) {
					$be->box_full($t->translate("Error"), $t->translate("Category")." $category ".$t->translate("does not exist"));
				} else {
					$where = "type='$type' AND category='$category'";
					if (!$dbcat->query("DELETE FROM $tables WHERE $where")) {
          				mysql_die($dbcat);
					} else {
						$bx->box_full($t->translate("Administration"),$t->translate("Category")." $category ".$t->translate("has been deleted"));
					}
				}
				break;
			default:
			}
		}
	} else {
		$be->box_full($t->translate("Error"),$t->translate("Parameter missing"));
	}
} else {
	$be->box_full($t->translate("Error"),$t->translate("Access denied"));
}
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
