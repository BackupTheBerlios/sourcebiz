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
# This file inserts an applications
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: entins.php,v 1.2 2003/02/25 11:45:44 helix Exp $
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
	$status = 'A';

	$name = trim($name);
	$homepage = trim($homepage);
	if (!empty($homepage) && !ereg("^http://", $homepage)) {
		$homepage = "http://".$homepage;
	}
	$short_profile = trim($short_profile);
	if (!empty($name)) {
	if (!empty($short_profile)) {
		$tables = "enterprise";
		$columns = "*";
		$where = "name='$name'";
		if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
			mysql_die($db);
		} else {

			// If enterprise already exists
			if ($db->num_rows() > 0) {
				$be->box_full($t->translate("Error"), $t->translate("Enterprise")." $name ".$t->translate("already exists"));

			// If a new enterprise
			} else {
        		$set = "name='$name',logo='$logo_name',short_profile='$short_profile',homepage='$homepage',status='$status',user='".$auth->auth["uname"]."',modification=NOW(),creation=NOW()";
        		if (!$db->query("INSERT $tables SET $set")) {
					mysql_die($db);
        		} else {

					// Get new enterprise
            		if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
                		mysql_die($db);
            		} else {
						$db->next_record();

						// Move uploaded logo to logo directory
						if (!empty($logo_name)) {
							$to = $sys_logo_dir.$db->f("entid")."ent_".basename($logo_name);
							if (!copy($logo,$to)) {
								$be->box_full($t->translate("Error"), $t->translate("Unable to copy logofile to logo directory"));
							}
							if (!chmod($to,0666)) {
								$be->box_full($t->translate("Error"), $t->translate("Unable to change logofile mode"));
							}
						}

						// Insert new counters
						$dbcnt = new DB_SourceBiz;
                		$tables = "counter";
	        			$set = "entid=".$db->f("entid");
						if (!$dbcnt->query("INSERT $tables SET $set")) {
                    		mysql_die($dbcnt);
						} else {

							// Select and show new enterprise with counters
							entbyentid($db,$db->f("entid"));
							if ($ml_notify) {
								$msg = "insert enterprise $name by ".$auth->auth["uname"].".";
								mailuser("admin", "insert enterprise", $msg);
							}
						}
					}
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
?>
<!-- end content -->

<?php
require("./include/footer.inc");
@page_close();
?>
