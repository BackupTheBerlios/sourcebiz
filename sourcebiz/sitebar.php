<?php

######################################################################
# SourceBiz: Open Source Business
# ===============================
#
# Copyright (c) 2001-2003 by
#                Lutz Henckel (lutz.henckel@fokus.fraunhofer.de) and
#                Gregorio Robles (grex@scouts-es.org)
#
# BerliOS SourceBiz: http://sourcebiz.berlios.de
# BerliOS - The OpenSource Mediator: http://www.berlios.de
#
# This is the Netscape 6 sitebar of the system
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: sitebar.php,v 1.2 2003/02/25 11:45:44 helix Exp $
#
###################################################################### 

require("./include/prepend.php3");

page_open(array("sess" => "SourceBiz_Session"));
// Disabling cache
header("Cache-Control: no-cache, must-revalidate");     // HTTP/1.1
header("Pragma: no-cache"); 				// HTTP/1.0

require("./include/config.inc");
require("./include/newlib.inc");
require("./include/entlib.inc");
require("./include/conlib.inc");
require("./include/svclib.inc");
require("./include/prolib.inc");
require("./include/sollib.inc");
require("./include/cuslib.inc");
require("./include/cmtlib.inc");
require("./include/translation.inc");
require("./include/lang.inc");
require("./include/box.inc");

$t = new translation($la);
$db = new DB_SourceBiz;

$bx = new box("95%",$th_box_frame_color,0,$th_box_title_bgcolor,$th_box_title_font_color,$th_box_title_align,$th_box_body_bgcolor,$th_box_body_font_color,$th_box_body_align);
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<head>
   <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
   <meta http-equiv="expires" content="0">
   <meta http-equiv="Refresh" content="1200; URL=<?php echo $sys_url."sitebar.php"?>">
   <title><?php echo $sys_name;?> - <?php echo $t->translate($sys_title);?></title>
<link rel="stylesheet" type="text/css" href="style.php">
</head>
<body bgcolor="<?php echo $th_body_bgcolor;?>" topmargin="0" bottommargin="0" leftmargin="0" rightmargin="0" marginheight="0" marginwidth="0">

<!-- content -->

<p>&nbsp;
<?php
// Recent news
$bx->box_begin();
$bx->box_body_begin();
echo "<a href=\"$sys_url_title\" target=\"_content\"><img src=\"$sys_logo_small_image\" border=\"0\" height=\"$sys_logo_small_heigth\" width=\"$sys_logo_small_width\" ALT=\"$sys_logo_small_alt\"></a>";
$bx->box_body_end();
$bx->box_end();
$bx->box_begin();
$bx->box_title("<font size=\"1\">".$t->translate("News")."</font>");
$db->query("SELECT * FROM news WHERE news.status_new='A' ORDER BY news.modification_new DESC limit 10");
$bx->box_body_begin();
while($db->next_record()) {
  echo "<div class=newsind>&#149;&nbsp;";
  echo "<a href=\"".$sys_url."newbynewid.php?id=".$db->f("newid")."\" target=\"_content\">".$db->f("subject_new")."</a></div>\n";
}
$bx->box_body_end();
$bx->box_end();

// Enterprises
$bx->box_begin();
$bx->box_title("<font size=\"1\">".$t->translate("Enterprises")."</font>");

$num = 10;
$time = floor(time() / 60);
$db->query("SELECT COUNT(*) as cnt FROM enterprise WHERE enterprise.status='A'");
$db->next_record();
$entcnt = $db->f("cnt");
$blkcnt = floor($entcnt / $num);
if (($entcnt % $num) > 0) {
  $blkcnt += 1;
}
$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $num) - $num;
if (($offset + $num) >= $entcnt) {
  $offset = $entcnt - $num;
}

$db->query("SELECT * FROM enterprise WHERE enterprise.status='A' LIMIT $offset,$num");
$bx->box_body_begin();
while($db->next_record()) {
	echo "<div class=newsind>&#149;&nbsp;";
	echo "<a href=\"".$sys_url."entbyid.php?id=".$db->f("entid")."\" target=\"_content\">".$db->f("name")."</a></div>\n";
}
$bx->box_body_end();
$bx->box_end();

// Contacts
$bx->box_begin();
$bx->box_title("<font size=\"1\">".$t->translate("Contacts")."</font>");

$num = 10;
$time = floor(time() / 60);
$db->query("SELECT COUNT(*) as cnt FROM contact WHERE contact.status_con='A'");
$db->next_record();
$concnt = $db->f("cnt");
$blkcnt = floor($concnt / $num);
if (($concnt % $num) > 0) {
  $blkcnt += 1;
}
$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $num) - $num;
if (($offset + $num) >= $concnt) {
  $offset = $concnt - $num;
}

$db->query("SELECT * FROM contact WHERE contact.status_con='A' LIMIT $offset,$num");
$bx->box_body_begin();
while($db->next_record()) {
	echo "<div class=newsind>&#149;&nbsp;";
	echo "<a href=\"".$sys_url."conbyconid.php?id=".$db->f("conid")."\" target=\"_content\">".$db->f("name_con")."</a></div>\n";
}
$bx->box_body_end();
$bx->box_end();

// Services
$bx->box_begin();
$bx->box_title("<font size=\"1\">".$t->translate("Services")."</font>");

$num = 10;
$time = floor(time() / 60);
$db->query("SELECT COUNT(*) as cnt FROM services WHERE services.status_svc='A'");
$db->next_record();
$svccnt = $db->f("cnt");
$blkcnt = floor($svccnt / $num);
if (($svccnt % $num) > 0) {
  $blkcnt += 1;
}
$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $num) - $num;
if (($offset + $num) >= $svccnt) {
  $offset = $svccnt - $num;
}

$db->query("SELECT * FROM services WHERE services.status_svc='A' LIMIT $offset,$num");
$bx->box_body_begin();
while($db->next_record()) {
	echo "<div class=newsind>&#149;&nbsp;";
	echo "<a href=\"".$sys_url."svcbysvcid.php?id=".$db->f("svcid")."\" target=\"_content\">".$db->f("name_svc")."</a></div>\n";
}
$bx->box_body_end();
$bx->box_end();

// Products
$bx->box_begin();
$bx->box_title("<font size=\"1\">".$t->translate("Products")."</font>");

$num = 10;
$time = floor(time() / 60);
$db->query("SELECT COUNT(*) as cnt FROM products WHERE products.status_pro='A'");
$db->next_record();
$procnt = $db->f("cnt");
$blkcnt = floor($procnt / $num);
if (($procnt % $num) > 0) {
  $blkcnt += 1;
}
$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $num) - $num;
if (($offset + $num) >= $procnt) {
  $offset = $procnt - $num;
}

$db->query("SELECT * FROM products WHERE products.status_pro='A' LIMIT $offset,$num");
$bx->box_body_begin();
while($db->next_record()) {
	echo "<div class=newsind>&#149;&nbsp;";
	echo "<a href=\"".$sys_url."probyproid.php?id=".$db->f("proid")."\" target=\"_content\">".$db->f("name_pro")."</a></div>\n";
}
$bx->box_body_end();
$bx->box_end();

// Solutions
$bx->box_begin();
$bx->box_title("<font size=\"1\">".$t->translate("Solutions")."</font>");

$num = 10;
$time = floor(time() / 60);
$db->query("SELECT COUNT(*) as cnt FROM solutions WHERE solutions.status_sol='A'");
$db->next_record();
$solcnt = $db->f("cnt");
$blkcnt = floor($solcnt / $num);
if (($solcnt % $num) > 0) {
  $blkcnt += 1;
}
$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $num) - $num;
if (($offset + $num) >= $solcnt) {
  $offset = $solcnt - $num;
}

$db->query("SELECT * FROM solutions WHERE solutions.status_sol='A' LIMIT $offset,$num");
$bx->box_body_begin();
while($db->next_record()) {
	echo "<div class=newsind>&#149;&nbsp;";
	echo "<a href=\"".$sys_url."solbysolid.php?id=".$db->f("solid")."\" target=\"_content\">".$db->f("name_sol")."</a></div>\n";
}
$bx->box_body_end();
$bx->box_end();

// Customers
$bx->box_begin();
$bx->box_title("<font size=\"1\">".$t->translate("Customers")."</font>");

$num = 10;
$time = floor(time() / 60);
$db->query("SELECT COUNT(*) as cnt FROM customers WHERE customers.status_cus='A'");
$db->next_record();
$cuscnt = $db->f("cnt");
$blkcnt = floor($cuscnt / $num);
if (($cuscnt % $num) > 0) {
  $blkcnt += 1;
}
$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $num) - $num;
if (($offset + $num) >= $cuscnt) {
  $offset = $cuscnt - $num;
}

$db->query("SELECT * FROM customers WHERE customers.status_cus='A' LIMIT $offset,$num");
$bx->box_body_begin();
while($db->next_record()) {
	echo "<div class=newsind>&#149;&nbsp;";
	echo "<a href=\"".$sys_url."cusbycusid.php?id=".$db->f("cusid")."\" target=\"_content\">".$db->f("name_cus")."</a></div>\n";
}
echo "<p><b><font size=\"1\"><a href=\"".$sys_url."\" target=\"_content\">more...</a></font></b>\n";
$bx->box_body_end();
$bx->box_end();

@page_close();
?>
