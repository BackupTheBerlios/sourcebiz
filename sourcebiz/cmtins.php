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
# This file shows the enterprise and the inserted comment
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: cmtins.php,v 1.2 2003/02/25 11:45:44 helix Exp $
#
######################################################################

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session",
                "auth" => "SourceBiz_Auth",
                "perm" => "SourceBiz_Perm"));

require("./include/header.inc");
require("./include/entlib.inc");
require("./include/cmtlib.inc");

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
	$subject_cmt = trim($subject_cmt);
	$text_cmt = trim($text_cmt);
	if (!empty($subject_cmt)) {
	if (!empty($text_cmt)) {

		// Look if enterprise is in table
    	$columns = "*";
    	$tables = "enterprise";
    	$where = "entid='$id'";
    	if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
      		mysql_die($db);
    	} else {

			// If enterprise in table
			if ($db->next_record()) {

				// Insert new comment
				$tables = "comments";
				$set = "entid_cmt='$id',user_cmt='".$auth->auth["uname"]."',subject_cmt='$subject_cmt',text_cmt='$text_cmt',status_cmt='A',creation_cmt=NOW()";
				if (!$db->query("INSERT $tables SET $set")) {
					mysql_die($db);
				}

				// Select and show new/updated enterprises with comments
				entbyentid($db,$id);
				cmtbyentid($db,$id);
				if ($ml_notify) {
					$msg = "insert comment \"$subject_cmt\" by ".$auth->auth["uname"].".";
					mailuser("admin", "insert comment", $msg);
				}

			// If enterprise is not in table
			} else {
				$be->box_full($t->translate("Error"), $t->translate("Enterprise")." (ID: $id) ".$t->translate("does not exist").".");
      		}
		}
	} else {
		$be->box_full($t->translate("Error"), $t->translate("No Comment specified"));
	}
	} else {
		$be->box_full($t->translate("Error"), $t->translate("No Subject specified"));
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
