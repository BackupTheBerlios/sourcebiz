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
# This page lists the users registered in our system
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id
#
###################################################################### 

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session"));
if (isset($auth) && !empty($auth->auth["perm"])) {
  page_close();
  page_open(array("sess" => "SourceBiz_Session",
                  "auth" => "SourceBiz_Auth",
                  "perm" => "SourceBiz_Perm"));
}

require("./include/header.inc");

$bx = new box("100%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("80%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
$bs = new box("100%",$th_strip_frame_color,$th_strip_frame_width,$th_strip_title_bgcolor,$th_strip_title_font_color,$th_strip_title_align,$th_strip_body_bgcolor,$th_strip_body_font_color,$th_strip_body_align);
?>

<!-- content -->
<?php
$db = new DB_SourceBiz;
	if (!isset($by) || empty($by)) {
		$by = "%";
	}
	$alphabet = array ("A","B","C","D","E","F","G","H","I","J","K","L",
				"M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z");
	$msg = "[ ";
	while (list(, $ltr) = each($alphabet)) {
		$msg .= "<a href=\"".$sess->url(basename($PHP_SELF)).$sess->add_query(array("by" => $ltr."%"))."\">$ltr</a> | ";
    }
    $msg .= "<a href=\"".$sess->url(basename($PHP_SELF)).$sess->add_query(array("by" => "%"))."\">".$t->translate("All")."</a>&nbsp;]";
	$bs->box_strip($msg);
    $columns = "*";
    $tables = "auth_user";
	$where = "username LIKE '$by'";
	$order = "username ASC";
    if (!$db->query("SELECT $columns FROM $tables WHERE $where ORDER BY $order")) {
        mysql_die($db);
    } else {
		$bx->box_begin();
		$bystr = ereg_replace("%", "", $by);
		if ($bystr == "") $bystr = $t->translate("All");
		$bx->box_title($t->translate("Users").": ".$bystr);
		$bx->box_body_begin();
?>
<table border=0 align=center cellspacing=1 cellpadding=1 width=100%>
<?php
		echo "<tr><td><b>".$t->translate("No").".</b></td><td><b>#&nbsp;".$t->translate("Ent")."</b></td><td><b>".$t->translate("Username")."</b></td><td><b>".$t->translate("Realname")."</b></td><td><b>".$t->translate("E-Mail")."</b></td></tr>\n";
		$i = 1;
		while($db->next_record()) {
            $columns = "COUNT(*)";
            $tables = "enterprise";
            $where = "user=\"".$db->f("username")."\" AND status=\"A\"";
            $num = "";
			$dbn = new DB_SourceBiz;
            if ($dbn->query("SELECT $columns AS cnt FROM $tables WHERE $where")) {
                $dbn->next_record();
                $num = "[".sprintf("%03d",$dbn->f("cnt"))."]";
            }
            echo "<tr><td>".sprintf("%d",$i)."</td>\n";
			echo "<td><a href=\"".$sess->url("enterprises.php").$sess->add_query(array("by" => "filter","author" => $db->f("username")))."\">$num</a></td>\n";
			echo "<td>".$db->f("username")."</td>\n";
			echo "<td>".$db->f("realname")."</td>";
			echo "<td>&lt;<a href=\"mailto:".$db->f("email_usr")."\">".ereg_replace("@"," at ",htmlentities($db->f("email_usr")))."</a>&gt;</td>";
			echo "</tr>\n";
			$i++;
        }
		echo "</table>\n";
    }
	$bx->box_body_end();
	$bx->box_end();
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
