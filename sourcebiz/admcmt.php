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
# This is the comment administration file
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
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
$bs = new box("100%",$th_strip_frame_color,$th_strip_frame_width,$th_strip_title_bgcolor,$th_strip_title_font_color,$th_strip_title_align,$th_strip_body_bgcolor,$th_strip_body_font_color,$th_strip_body_align);
?>

<!-- content -->
<?
if (($config_perm_admcmt != "all") && (!isset($perm) || !$perm->have_perm($config_perm_admcmt))) {
  $be->box_full($t->translate("Error"), $t->translate("Access denied"));
} else {
  if (!isset($by) || empty($by)) {
    $by = "";
  }
  $alphabet = array ("A","B","C","D","E","F","G","H","I","J","K","L",
				"M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z");
  $msg = $t->translate("Enterprise by").": [ ";
  while (list(, $ltr) = each($alphabet)) {
    $msg .= "<a href=\"".$sess->self_url().$sess->add_query(array("by" => $ltr))."\">$ltr</a>&nbsp;| ";
  }
  $msg .= "<a href=\"".$sess->self_url().$sess->add_query(array("by" => "%"))."\">".$t->translate("All")."</a>&nbsp;]";
  $bs->box_strip($msg);

  $by = $by."%";
  $db->query("SELECT enterprise.entid,name,cmtid,user_cmt,subject_cmt,status_cmt,creation_cmt FROM comments,enterprise WHERE enterprise.entid = comments.entid_cmt AND enterprise.name LIKE '$by' ORDER BY creation_cmt DESC");
  $bx->box_begin();
  $bx->box_title($t->translate("Comments"));
  $bx->box_body_begin();		

  echo "<table border=0 align=center cellspacing=1 cellpadding=1 width=100%>\n";
  echo "<tr><td><b>".$t->translate("No").".</b></td>\n";
  echo "<td><b>".$t->translate("Enterprise")."</b></td>\n";
  echo "<td><b>".$t->translate("Subject")."</b></td>\n";
  echo "<td><b>".$t->translate("Author")."</b></td>\n";
  echo "<td><b>".$t->translate("Posted on")."</b></td>\n";
  echo "<td><b>".$t->translate("Status")."</b></td>\n";
  echo "<td>&nbsp;</td>\n";
  echo "<td>&nbsp;</td></tr>\n";

  $i = 1;
  while($db->next_record()) {
    echo "<tr><td>$i</td>\n";
    echo "<td><a href=\"".$sess->url("cmtbyentid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$db->f("name")."</a></td>\n";
    echo "<td><a href=\"".$sess->url("cmtbycmtid.php").$sess->add_query(array("id" => $db->f("cmtid")))."\">".$db->f("subject_cmt")."</a></td>\n";
    echo "<td>".$db->f("user_cmt")."</td>\n";
    $timestamp = mktimestamp($db->f("creation_cmt"));
    echo "<td>".timestr_short($timestamp)."</td>\n";
    echo "<td>".$db->f("status_cmt")."</td>\n";

    echo "<td><form action=\"".$sess->url("cmtupd.php")."\" method=\"POST\">\n";
    echo "<input type=\"hidden\" name=\"modification\" value=\"".$db->f("creation_cmt")."\">\n";    
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("cmtid")."\">\n";
    echo "<input type=\"submit\"value=\"".$t->translate("Change")."\">\n";
    echo "</form></td>\n";

    echo "</tr>\n";
    $i++;
  }
  echo "</table>\n";
  $bx->box_body_end();
  $bx->box_end();
  echo "</table>\n";
}
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
