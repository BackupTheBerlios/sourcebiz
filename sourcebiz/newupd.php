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
# This is the news administration file
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
require("./include/newlib.inc");

$bx = new box("100%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
?>

<!-- content -->
<?
if (isset($id) ) {
	$columns = "*";
	$tables = "news,enterprise";
	$where = "enterprise.entid = news.entid_new AND news.newid = '$id'";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
		mysql_die($db);
	} else {
		$db->next_record();
		if ($db->f("user") == $auth->auth["uname"] || $perm->have_perm("admin")) {
			if (!isset($action)) {
				newmod($db);
			} else {
				$subject_new = trim($subject_new);
				$text_new = trim($text_new);
				$homepage_new = trim($homepage_new);
				if (!empty($homepage_new) && !ereg("^http://", $homepage_new)) {
					$homepage_new = "http://".$homepage_new;
				}
				$status_new = trim($status_new);
				if (!empty($subject_new)) {
				if (!empty($text_new)) {

				$tables = "news";
				$set = "subject_new='$subject_new',text_new='$text_new',homepage_new='$homepage_new'";
				$where = "newid='$id'";
				switch ($action) {
				case "change":
					$set = $set.",status_new='$status_new'";
					break;
				case "delete":
					$set = $set.",status_new='D'";
					break;
				case "undelete":
					$set = $set.",status_new='A'";
					break;
				case "erase":
					break;
				default:
					$be->box_full($t->translate("Error"), $t->translate("No Action specified"));
					$set = $set.",status_new='$status_new'";
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
							$be->box_full($t->translate("Erase"), $t->translate("News is erased"));
						} else {
							entbynewid($db,$id);
							newbynewid($db,$id);
						}
						if ($ml_notify) {
							$msg = "$action news (ID: $id) by ".$auth->auth["uname"].".";
							mailuser("admin", "$action news", $msg);
						}
					}
				}
				} else {
					$be->box_full($t->translate("Error"), $t->translate("No News specified"));
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
	$be->box_full($t->translate("Error"), $t->translate("No News ID specified"));
}	
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
