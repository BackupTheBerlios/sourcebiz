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
# This shows the recent news
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: index.php,v 1.2 2003/02/25 11:45:44 helix Exp $
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
require("./include/entlib.inc");
require("./include/newlib.inc");
require("./include/conlib.inc");
require("./include/svclib.inc");
require("./include/prolib.inc");
require("./include/sollib.inc");
require("./include/cuslib.inc");
require("./include/cmtlib.inc");

$bx = new box("100%",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
$be = new box("",$th_box_frame_color,$th_box_frame_width,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_error_font_color,$th_box_body_align);
$bs = new box("100%",$th_strip_frame_color,$th_strip_frame_width,$th_strip_title_bgcolor,$th_strip_title_font_color,$th_strip_title_align,$th_strip_body_bgcolor,$th_strip_body_font_color,$th_strip_body_align);
?>

<!-- content -->
<table BORDER=0 CELLSPACING=10 CELLPADDING=0 WIDTH="100%" >
<tr width=80% valign=top><td>
<?php

$bx->box_begin();
$title = $t->translate("Open Source Enterprises, Services, Products and Solutions");
$bx->box_title($title);
$text = "<ul>\n"
		."<li><b><a href=\"".$sess->url("enterprises.php")."\">".$t->translate("Enterprises")."</a></b>\n"
		."<br>".$t->translate("including Profile and Links to further Information")."\n"
		."<li><b><a href=\"".$sess->url("contacts.php")."\">".$t->translate("Contacts")."</a></b>\n"
		."<br>".$t->translate("including Address, Phone, Email, Homepage, etc.")."\n"
		."<li><b><a href=\"".$sess->url("services.php")."\">".$t->translate("Services")."</a></b>\n"
		."<br>".$t->translate("including Consulting, Education &amp; Training, Projects, Support, etc.")."\n"
		."<li><b><a href=\"".$sess->url("products.php")."\">".$t->translate("Products")."</a></b>\n"
		."<br>".$t->translate("including Software, Hardware, Books, Accessories, etc.")."\n"
		."<li><b><a href=\"".$sess->url("solutions.php")."\">".$t->translate("Solutions")."</a></b>\n"
		."<br>".$t->translate("created by Enterprises for Customers")."\n"
		."<li><b><a href=\"".$sess->url("customers.php")."\">".$t->translate("Customers")."</a></b>\n"
		."<br>".$t->translate("of Enterprises")."\n"
		."<li><b><a href=\"".$sess->url("news.php")."\">".$t->translate("News")."</a></b>\n"
		."<br>".$t->translate("provided by Enterprises")."\n"
		."<li><b><a href=\"".$sess->url("comments.php")."\">".$t->translate("Comments")."</a></b>\n"
		."<br>".$t->translate("about Enterprises by Users")."\n"
		."</ul>\n";
$bx->box_body($text);
$bx->box_end();

// News

$cnt = 0;
$query = newquery(0);
$db->query($query);

if ($db->num_rows() > 0) {
  while ($db->next_record()) {
    newshow($db,admin($db));
  }
}
?>

</td><td width=20%>
<?php

// Recent News at the right column

newidx($config_showidx_newperpage);
entidx($config_showidx_entperpage);
conidx($config_showidx_conperpage);
svcidx($config_showidx_svcperpage);
proidx($config_showidx_properpage);
solidx($config_showidx_solperpage);
cusidx($config_showidx_cusperpage);
cmtidx($config_showidx_cmtperpage);

?>
</td></tr>
</table>
<!-- end content -->

<?php
require("./include/footer.inc");
@page_close();
?>
