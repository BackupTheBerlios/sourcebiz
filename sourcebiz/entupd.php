<?php

######################################################################
# SourceBiz: Open Source Business
# ===============================
#
# Copyright (c) 2001-2003 by
#                Lutz Henckel (lutz.henckel@fokus.fraunhofer.de)
#
# BerliOS SourceBiz: http://sourcebiz.berlios.de
# BerliOS - The OpenSource Mediator: http://www.berlios.de
#
# Update an enterprise entry.
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: entupd.php,v 1.2 2003/02/25 11:45:44 helix Exp $
#
######################################################################

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session",
                "auth" => "SourceBiz_Auth",
                "perm" => "SourceBiz_Perm"));

require("./include/header.inc");
require("./include/entlib.inc");

$bx = new box("100%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
?>

<!-- content -->
<?php
if ($perm->have_perm("user_pending")) {
    $be->box_full($t->translate("Error"), $t->translate("Access denied"));
    $auth->logout();
} else {
if (isset($id) ) {
	$columns = "*";
	$tables = "enterprise";
	$where = "enterprise.entid = '$id'";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
		mysql_die($db);
	} else {
		$db->next_record();
		if ($db->f("user") == $auth->auth["uname"] || $perm->have_perm("admin")) {
			if (!isset($action)) {
				entmod($db);
			} else {
				$name = trim($name);
				$logo = trim($logo);
				$homepage = trim($homepage);
				if (!empty($homepage) && !ereg("^http://", $homepage)) {
					$homepage = "http://".$homepage;
				}
				$short_profile = trim($short_profile);
				$status = trim($status);
				if (!empty($name)) {
				if (!empty($short_profile)) {

				switch ($logoact) {
				case "keep":
					$logofileset = ",logo='$clogo'";
					break;
				case "new":
					$logofileset = ",logo='$logo_name'";
					break;
				case "delete":
					$logofileset = ",logo=''";
					break;
				default:
					$logofileset = ",logo='$logo_name'";
				}

				$tables = "enterprise";
				$set = "name='$name'$logofileset,homepage='$homepage',short_profile='$short_profile'";
				switch ($action) {
				case "change":
					$set = $set.",status='$status'";
					break;
				case "delete":
					$set = $set.",status='D'";
					delprf($id);
					delcon($id);
					delsvc($id);
					delpro($id);
					delsol($id);
					delcus($id);
					delnew($id);
					delcmt($id);
					break;
				case "undelete":
					$set = $set.",status='A'";
					break;
				case "erase":
					break;
				default:
					$be->box_full($t->translate("Error"), $t->translate("No Action specified"));
					$set = $set.",status='$status'";
					break;
				}
				$where = "entid='$id'";
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
							eraprf($id);
							eracon($id);
							erasvc($id);
							erapro($id);
							erasol($id);
							eracus($id);
							eranew($id);
							eracmt($id);
							eracnt($id);
							$be->box_full($t->translate("Erase"), $t->translate("Enterprise is erased"));
						} else {
							if ($logoact == "new" && !empty($logo_name)) {
								if (!copy($logo, $sys_logo_dir.$db->f("entid")."ent_".basename($logo_name))) {
									$be->box_full($t->translate("Error"), $t->translate("Unable to copy logofile to logo directory"));
								}
								@chmod($sys_logo_dir.$db->f("entid")."ent_".basename($logo_name),0666);
							}
							entbyentid($db,$id);
						}
					}
				}
				} else {
					$be->box_full($t->translate("Error"), $t->translate("No Short Profile specified"));
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
	$be->box_full($t->translate("Error"), $t->translate("No Enterprise ID specified"));
}	
}
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
