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
# This is the service administration file
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: svcupd.php,v 1.2 2003/02/25 11:45:44 helix Exp $
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
<?
if (isset($id) ) {
	$columns = "*";
	$tables = "services,enterprise";
	$where = "enterprise.entid = services.entid_svc AND services.svcid = '$id'";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
		mysql_die($db);
	} else {
		$db->next_record();
		if ($db->f("user") == $auth->auth["uname"] || $perm->have_perm("admin")) {
			if (!isset($action)) {
				svcmod($db);
			} else {
				$name_svc = trim($name_svc);
				$category_svc = trim($category_svc);
				$description_svc = trim($description_svc);
				$homepage_svc = trim($homepage_svc);
				if (!empty($homepage_svc) && !ereg("^http://", $homepage_svc)) {
					$homepage_svc = "http://".$homepage_svc;
				}
				$status_svc = trim($status_svc);
				if (!empty($name_svc)) {
				if (!empty($description_svc)) {

				$tables = "services";
				$set = "name_svc='$name_svc',category_svc='$category_svc',description_svc='$description_svc',homepage_svc='$homepage_svc'";
				$where = "svcid='$id'";
				switch ($action) {
				case "change":
					$set = $set.",status_svc='$status_svc'";
					break;
				case "delete":
					$set = $set.",status_svc='D'";
					break;
				case "undelete":
					$set = $set.",status_svc='A'";
					break;
				case "erase":
					break;
				default:
					$be->box_full($t->translate("Error"), $t->translate("No Action specified"));
					$set = $set.",status_svc='$status_svc'";
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
							$be->box_full($t->translate("Erase"), $t->translate("Service is erased"));
						} else {
							entbysvcid($db,$id);
							svcbysvcid($db,$id);
						}
						if ($ml_notify) {
							$msg = "$action service (ID: $id) by ".$auth->auth["uname"].".";
							mailuser("admin", "$action service", $msg);
						}
					}
				}
				} else {
					$be->box_full($t->translate("Error"), $t->translate("No Description specified"));
				}
				} else {
					$be->box_full($t->translate("Error"), $t->translate("No Name specified"));
				}
			}
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Access denied"));
		}
	}
} else {
	$be->box_full($t->translate("Error"), $t->translate("No Services ID specified"));
}	
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
