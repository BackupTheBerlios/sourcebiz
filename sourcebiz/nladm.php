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
# Administrating the daily/weekly newsletter
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: nladm.php,v 1.2 2003/02/25 11:45:44 helix Exp $
#
######################################################################

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session",
                "auth" => "SourceBiz_Auth",
                "perm" => "SourceBiz_Perm"));

require("./include/header.inc");

$bx = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("80%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
?>

<!-- content -->
<?php
if ($perm->have_perm("admin")) {
  $db = new DB_SourceBiz;

  if (!isset($period)) $period = "daily";
  if ($msg = nlmsg($period)) {
    $subj = "$sys_name $period newsletter for ".date("l dS of F Y");
    if (isset($send)) { // Send newsletter
      switch ($period) {
	case "weekly":
	  mail($ml_weeklynewstoaddr, $subj, $msg,
	  "From: $ml_newsfromaddr\nReply-To: $ml_newsreplyaddr\nX-Mailer: PHP");
	  $bx->box_full($t->translate("Weekly Newsletter"), $t->translate("Newsletter was sent at ").timestr(time()));
	  break;
        case "daily":
	default:
	  mail($ml_newstoaddr, $subj, $msg,
	  "From: $ml_newsfromaddr\nReply-To: $ml_newsreplyaddr\nX-Mailer: PHP");
	  $bx->box_full($t->translate("Daily Newsletter"), $t->translate("Newsletter was sent at ").timestr(time()));
	  break;
      }
    }
    $bx->box_full($subj, "<pre>\n".htmlentities($msg)."\n</pre>\n");
?>
<form method="get" action="<?php $sess->pself_url() ?>">
<?php
    echo "<input type=\"hidden\" name=\"period\" value=\"$period\">\n";
    echo "<center><p><input type=\"submit\" name=\"send\" value=\"".$t->translate("Send newsletter")."\"></center>\n";
    echo "</form>\n";
  } else {
    $be->box_full($t->translate("Error"), $t->translate("No Entry found").".");
  }
} else {
  $be->box_full($t->translate("Error"), $t->translate("Access denied").".");
}
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
