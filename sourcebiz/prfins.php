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
# This file shows the enterprise and the added profile
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: prfins.php,v 1.2 2003/02/25 11:45:44 helix Exp $
#
######################################################################

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session",
                "auth" => "SourceBiz_Auth",
                "perm" => "SourceBiz_Perm"));

require("./include/header.inc");
require("./include/entlib.inc");
require("./include/prflib.inc");

$bx = new box("100%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
$bs = new box("100%",$th_strip_frame_color,$th_strip_frame_width,$th_strip_title_bgcolor,$th_strip_title_font_color,$th_strip_title_align,$th_strip_body_bgcolor,$th_strip_body_font_color,$th_strip_body_align);
?>

<!-- content -->
<?php
if ($perm->have_perm("user_pending")) {
  $be->box_full($t->translate("Error"), $t->translate("Access denied"));
  $auth->logout();
} else {

  // If enterprise id specified
  if (isset($id)) {
  if (!empty($profile_prf)) {

	// Look if enterprise is in table
    $columns = "*";
    $tables = "enterprise";
    $where = "entid='$id'";
    if (!$db->query("SELECT $columns FROM $tables WHERE $where")) {
      mysql_die($db);
    } else {

	  // If enterprise in table
      if ($db->next_record()) {

        // If enterprise owner is logged in user
        if ($db->f("user") == $auth->auth["uname"] || $perm->have_perm("admin")) {

	      // Insert new profile
          $tables = "profile";
          $set = "entid_prf='$id',profile_prf='$profile_prf',status_prf='A',modification_prf=NOW(),creation_prf=NOW()";
          if (!$db->query("INSERT $tables SET $set")) {
            mysql_die($db);
          }

	      // Select and show new/updated enterprises with profile
          entbyentid($db,$id);
          prfbyentid($db,$id);
		  if ($ml_notify) {
		    $msg = "insert profile (ID: $id) by ".$auth->auth["uname"].".";
		    mailuser("admin", "insert profile", $msg);
		  }

        // If enterprise owner isn't logged in user
        } else {
          $be->box_full($t->translate("Error"), $t->translate("Access denied"));
        }

	  // If enterprise not in table
      } else {
        $be->box_full($t->translate("Error"), $t->translate("Enterprise")." (ID: $id) ".$t->translate("does not exist"));
      }
    }
  } else {
    $be->box_full($t->translate("Error"), $t->translate("No Profile specified"));
  }

  // If enterprise id not specified
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
