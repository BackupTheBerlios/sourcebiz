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
# Adding an enterprise
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

$bx = new box("100%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
?>

<!-- content -->
<?php
if ($perm->have_perm("user_pending")) {
	$be->box_full($t->translate("Error"), $t->translate("Access denied"));
	$auth->logout();
} else {
	if (isset($name) && !empty($name)) {
//
// Look if enterprise is already in table
//
		$name = trim($name);
		$columns = "*";
		$tables = "enterprise";
		$where = "name='$name'";
		if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
			mysql_die($db);
		} else {
//
// If enterprise in table show existing values to change
//
			if ($db->next_record()) {
				if (isset($auth) && !empty($auth->auth["perm"]) && ($perm->have_perm("admin") || $db->f("user") == $auth->auth["uname"])) {
					entmod($db);
				} else {
					$be->box_full($t->translate("Error"), $t->translate("Access denied")."<br>".$t->translate("An Enterprise with this name already exist"));
				}
//
// If enterprise is not in table, insert it
//
			} else {
				entform();
			}
		}
	} else {
		$be->box_full($t->translate("Error"), $t->translate("No Enterprise Name specified")."."
		."<br>".$t->translate("Please select")." <a href=\"".$sess->url("entform.php")."\">".$t->translate("New Enterprise")."</a>");
	}
}
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
