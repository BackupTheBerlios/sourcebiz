<?php

######################################################################
# SourceBiz: Open Source Business
# ================================================
#
# Copyright (c) 2001-2003 by
#                Lutz Henckel (lutz.henckel@fokus.fraunhofer.de) and
#                Gregorio Robles (grex@scouts-es.org)
#
# BerliOS SourceBiz: http://sourcebiz.berlios.de
# BerliOS - The OpenSource Mediator: http://www.berlios.de
#
# Shows Frequently Asked Questions
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

$bx = new box("80%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("80%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
?>

<!-- content -->
<?php
$db->query("SELECT * FROM faq WHERE language='$la'");
if ($db->num_rows() > 0) {
while($db->next_record()) {
  $msg .= "<li><a href=#".$db->f("faqid").">".$db->f("question")."</a>";
}
$bx->box_full($t->translate("Frequently Asked Questions"), $msg);
$db->seek(0);
while($db->next_record()) {
  echo "<a name=".$db->f("faqid").">\n";
  $bx->box_full($t->translate("Question").": ".$db->f("question"), "<b>".$t->translate("Answer").":</b> ".$db->f("answer"));
}
} else {
  $be->box_full($t->translate("Error"), $t->translate("No Frequently Asked Questions exist"));
}
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
