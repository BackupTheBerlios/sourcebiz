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
# Allows administrator to insert, rename and delete categories 
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: admcat.php,v 1.2 2003/02/25 11:45:44 helix Exp $
#
######################################################################  

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session",
                "auth" => "SourceBiz_Auth",
                "perm" => "SourceBiz_Perm"));

require("./include/header.inc");

$bx = new box("100%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
$bs = new box("100%",$th_strip_frame_color,$th_strip_frame_width,$th_strip_title_bgcolor,$th_strip_title_font_color,$th_strip_title_align,$th_strip_body_bgcolor,$th_strip_body_font_color,$th_strip_body_align);
?>

<!-- content -->
<?php
if ($perm->have_perm("admin")) {

  $bx->box_begin();
  $bx->box_title($t->translate("Category Administration for")." ".$t->translate($type));
  $bx->box_body_begin();

// Insert a new Category

  $bs->box_strip($t->translate("Insert a Category"));
  echo "<form action=\"".$sess->url("inscat.php")."\" method=\"POST\">\n";
  echo "<table border=0 cellspacing=0 cellpadding=3 width=100%>\n";
  echo "<tr><td align=right width=30%>".$t->translate("New Category")." (64):</td><td width=70%><input type=\"TEXT\" name=\"category\" size=40 maxlength=64>\n";
  echo "</td></tr>\n";
  echo "<tr><td>&nbsp;</td>\n";
  echo "<td><input type=\"submit\" value=\"".$t->translate("Insert")."\">";
  echo "<input type=\"hidden\" name=\"action\" value=\"ins\">";
  echo "<input type=\"hidden\" name=\"type\" value=\"$type\">";
  echo "</td></tr>\n";
  echo "</form>\n";
  echo "</table>\n";
  echo "<BR>\n";

// Rename a Category

  $bs->box_strip($t->translate("Rename a Category"));
  echo "<form action=\"".$sess->url("inscat.php")."\" method=\"POST\">\n";
  echo "<table border=0 cellspacing=0 cellpadding=3 width=100%>\n";
  echo "<tr><td align=right width=30%>".$t->translate("Category").":</td><td width=70%>\n";
  echo "<select name=\"category\">\n";
  select_cat($type,"");
  echo "</select></td></tr>\n";
  echo "<tr><td align=right>".$t->translate("New Category Name")." (64):</td><td><input type=\"TEXT\" name=\"new_category\" size=40 maxlength=64>\n";
  echo "</td></tr>\n";
  echo "<tr><td>&nbsp;</td>\n";
  echo "<td><input type=\"submit\" value=\"".$t->translate("Rename")."\">";
  echo "<input type=\"hidden\" name=\"action\" value=\"ren\">";
  echo "<input type=\"hidden\" name=\"type\" value=\"$type\">";
  echo "</td></tr>\n";
  echo "</form>\n";
  echo "</table>\n";
  echo "<BR>\n";

// Delete a Category

  $bs->box_strip($t->translate("Delete a Category"));
  echo "<form action=\"".$sess->url("inscat.php")."\" method=\"POST\">\n";
  echo "<table border=0 cellspacing=0 cellpadding=3 width=100%>\n";
  echo "<tr><td align=right width=30%>".$t->translate("Category").":</td><td width=70%>\n";
  echo "<select name=\"category\">\n";
  select_cat($type,"");
  echo "</select></td></tr>\n";
  echo "</td></tr>\n";
  echo "<tr><td>&nbsp;</td>\n";
  echo "<td><input type=\"submit\" value=\"".$t->translate("Delete")."\">";
  echo "<input type=\"hidden\" name=\"action\" value=\"del\">";
  echo "<input type=\"hidden\" name=\"type\" value=\"$type\">";
  echo "</td></tr>\n";
  echo "</form>\n";
  echo "</table>\n";
  $bx->box_body_end();
  $bx->box_end();

} else {
  $be->box_full($t->translate("Error"), $t->translate("Access denied").".");
}
?>
<!-- end content -->

<?php
require("./include/footer.inc");
page_close();
?>
