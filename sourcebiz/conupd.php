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
# Update contact (by id) of an enterprise
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: conupd.php,v 1.2 2003/02/25 11:45:44 helix Exp $
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
?>

<!-- content -->
<?
if (isset($id) ) {
	$columns = "*";
	$tables = "contact,enterprise";
	$where = "enterprise.entid = contact.entid_con AND contact.conid = '$id'";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
		mysql_die($db);
	} else {
		$db->next_record();
		if ($db->f("user") == $auth->auth["uname"] || $perm->have_perm("admin")) {
			if (!isset($action)) {
				conmod($db);
			} else {
				$name_con = trim($name_con);
				$logo_con = trim($logo_con);
				$clogo_con = trim($clogo_con);
				$type_con = trim($type_con);
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
				$status_con = trim($status_con);
				if (!empty($name_con)) {

				switch ($logoact) {
				case "keep":
					$logofileset = ",logo_con='$clogo_con'";
					break;
				case "new":
					$logofileset = ",logo_con='$logo_con_name'";
					break;
				case "delete":
					$logofileset = ",logo_con=''";
					break;
				default:
					$logofileset = ",logo_con='$logo_con_name'";
				}

				$tables = "contact";

				$set = "name_con='$name_con'$logofileset,type_con='$type_con',description_con='$description_con',address_con='$address_con',country_con='$country_con',state_con='$state_con',city_con='$city_con',zip_con='$zip_con',phone_con='$phone_con',fax_con='$fax_con',email_con='$email_con',homepage_con='$homepage_con'";
				$where = "conid='$id'";
				switch ($action) {
				case "change":
					$set = $set.",status_con='$status_con'";
					break;
				case "delete":
					$set = $set.",status_con='D'";
					break;
				case "undelete":
					$set = $set.",status_con='A'";
					break;
				case "erase":
					break;
				default:
					$be->box_full($t->translate("Error"), $t->translate("No Action specified"));
					$set = $set.",status_con='$status_con'";
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
							$be->box_full($t->translate("Erase"), $t->translate("Contact is erased"));
						} else {
							if ($logoact == "new" && !empty($logo_con_name)) {
								if (!copy($logo_con, $sys_logo_dir.$db->f("conid")."con_".basename($logo_con_name))) {
									$be->box_full($t->translate("Error"), $t->translate("Unable to copy logofile to logo directory"));
								}
								@chmod($sys_logo_dir.$db->f("conid")."con_".basename($logo_con_name),0666);
							}
							entbyconid($db,$id);
							conbyconid($db,$id);
						}
						if ($ml_notify) {
							$msg = "$action contact (ID: $id) by ".$auth->auth["uname"].".";
							mailuser("admin", "$action contact", $msg);
						}
					}
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
	$be->box_full($t->translate("Error"), $t->translate("No Contact ID specified"));
}	
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
