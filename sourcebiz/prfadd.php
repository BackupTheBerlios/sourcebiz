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
# This file contains the form for adding a profile of an enterprise
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
require("./include/prflib.inc");

$bx = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
?>

<!-- content -->
<?php
if ($perm->have_perm("user_pending")) {
  $be->box_full($t->translate("Error"), $t->translate("Access denied"));
  $auth->logout();
} else {

  // If enterprise id specified
  if (isset($id)) {

	// Look if enterprise is already in table
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

	      // Look if profile is already in table
          $dbprf = new DB_SourceBiz;
          $columns = "*";
          $tables = "profile,enterprise";
          $where = "entid_prf='$id' AND enterprise.entid = profile.entid_prf";
          if ($dbprf->query("SELECT $columns FROM $tables WHERE $where")) {

	        // If profile in table
            if ($dbprf->next_record()) {

              // Modify existing profile
              prfmod($dbprf);
            } else {

              // Insert new profile
              prfform($db);
            }
          } else {
            mysql_die($db);
          }

        } else {
          $be->box_full($t->translate("Error"), $t->translate("Access denied").".");
        }

	  // If enterprise not in table
      } else {
        $be->box_full($t->translate("Error"), $t->translate("Enterprise")." (ID: $id) ".$t->translate("does not exist").".");
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
