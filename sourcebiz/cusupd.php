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
# This is the customers administration file
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: cusupd.php,v 1.2 2003/02/25 11:45:44 helix Exp $
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
?>

<!-- content -->
<?
if (isset($id) ) {
	$columns = "*";
	$tables = "customers,enterprise";
	$where = "enterprise.entid = customers.entid_cus AND customers.cusid = '$id'";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
		mysql_die($db);
	} else {
		$db->next_record();
		if ($db->f("user") == $auth->auth["uname"] || $perm->have_perm("admin")) {
			if (!isset($action)) {
				cusmod($db);
			} else {
				$name_cus = trim($name_cus);
				$description_cus = trim($description_cus);
				$homepage_cus = trim($homepage_cus);
				if (!empty($homepage_cus) && !ereg("^http://", $homepage_cus)) {
					$homepage_cus = "http://".$homepage_cus;
				}
				$status_cus = trim($status_cus);
				if (!empty($name_cus)) {
				if (!empty($description_cus)) {

				$tables = "customers";
				$set = "name_cus='$name_cus',description_cus='$description_cus',homepage_cus='$homepage_cus'";
				$where = "cusid='$id'";
				switch ($action) {
				case "change":
					$set = $set.",status_cus='$status_cus'";
					break;
				case "delete":
					$set = $set.",status_cus='D'";
					break;
				case "undelete":
					$set = $set.",status_cus='A'";
					break;
				case "erase":
					break;
				default:
					$be->box_full($t->translate("Error"), $t->translate("No Action specified"));
					$set = $set.",status_cus='$status_cus'";
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
							$be->box_full($t->translate("Erase"), $t->translate("Customer is erased"));
						} else {
							entbycusid($db,$id);
							cusbycusid($db,$id);
						}
						if ($ml_notify) {
							$msg = "$action customer (ID: $id) by ".$auth->auth["uname"].".";
							mailuser("admin", "$action customer", $msg);
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
	$be->box_full($t->translate("Error"), $t->translate("No Customers ID specified"));
}	
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
