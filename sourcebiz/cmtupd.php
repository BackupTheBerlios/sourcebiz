<?php

######################################################################
# SourceBiz: Open Source Business
# ================================================
#
# Copyright (c) 2001-2003 by
#                Lutz Henckel (lutz.henckel@fokus.fraunhofer.de)
#
# BerliOS SourceBiz: http://sourcewell.berlios.de
# BerliOS - The OpenSource Mediator: http://www.berlios.de
#
# Comment administration
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
require("./include/cmtlib.inc");

$bx = new box("100%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
?>

<!-- content -->
<?
if (isset($id) ) {
	$columns = "*";
	$tables = "comments,enterprise";
	$where = "enterprise.entid = comments.entid_cmt AND comments.cmtid = '$id'";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
		mysql_die($db);
	} else {
		$db->next_record();
		if ($db->f("user") == $auth->auth["uname"] || $perm->have_perm("admin")) {
			if (!isset($action)) {
				cmtmod($db);
			} else {
				$subject_cmt = trim($subject_cmt);
				$text_cmt = trim($text_cmt);
				$status_cmt = trim($status_cmt);
				if (!empty($subject_cmt)) {
				if (!empty($text_cmt)) {

				$tables = "comments";
				$set = "subject_cmt='$subject_cmt',text_cmt='$text_cmt',creation_cmt='$creation_cmt'";
				$where = "cmtid='$id'";
				switch ($action) {
				case "change":
					$set = $set.",status_cmt='$status_cmt'";
					break;
				case "delete":
					$set = $set.",status_cmt='D'";
					break;
				case "undelete":
					$set = $set.",status_cmt='A'";
					break;
				case "erase":
					break;
				default:
					$be->box_full($t->translate("Error"), $t->translate("No Action specified"));
					$set = $set.",status_cmt='$status_cmt'";
					break;
				}
				if ($action == "erase") {
					$query = "DELETE FROM $tables WHERE $where";
				} else {
					$query = "UPDATE $tables SET $set WHERE $where";
				}
				if ($action == "erase" && !$perm->have_perm("admin")) {
					$be->box_full($t->translate("Error"), $t->translate("Access denied"));
				} else {
					if (!$db->query($query)) {
						mysql_die($db);
					} else {
						if ($action == "erase") {
							$be->box_full($t->translate("Erase"), $t->translate("Comment is erased"));
						} else {
							entbycmtid($db,$id);
							cmtbycmtid($db,$id);
						}
						if ($ml_notify) {
							$msg = "$action comment (ID: $id) by ".$auth->auth["uname"].".";
							mailuser("admin", "$action comment", $msg);
						}
					}
				}
				} else {
					$be->box_full($t->translate("Error"), $t->translate("No Comment specified"));
				}
				} else {
					$be->box_full($t->translate("Error"), $t->translate("No Subject specified"));
				}
			}
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Access denied"));
		}	
	}
} else {
	$be->box_full($t->translate("Error"), $t->translate("No Comment ID specified"));
}	
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
