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
# XML backend (RDF-type document) of the system
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id
#
###################################################################### 

require("./include/prepend.php3");

header("Content-Type: text/plain");

// Disabling cache
header("Cache-Control: no-cache, must-revalidate");     // HTTP/1.1
header("Pragma: no-cache");                             // HTTP/1.0

require("./include/config.inc");
require("./include/lib.inc");

echo "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n";
echo "<!DOCTYPE rss PUBLIC \"-//Netscape Communications//DTD RSS 0.91//EN\"\n";
echo "           \"http://my.netscape.com/publish/formats/rss-0.91.dtd\">\n";
echo "<rss version=\"0.91\">\n";

echo "  <channel>\n";
echo "    <title>".$sys_name."</title>\n";
echo "    <link>".$sys_url."</link>\n";
echo "    <description>".$sys_name." - ".$sys_title."</description>\n";
echo "    <language>en-us</language>\n";

echo "  <image>\n";
echo "    <title>".$sys_name."</title>\n";
echo "    <url>".$sys_url.$sys_logo_image."</url>\n";
echo "    <link>".$sys_url."</link>\n";
echo "    <description>".$sys_name." - ".$sys_title."</description>\n";
echo "    <width>66</width>\n";
echo "    <height>73</height>\n";
echo "  </image>\n";

echo "  <item>\n";
echo "    <title><b>News:</b></title>\n";
echo "    <link>".$sys_url."news.php</link>\n";
echo "  </item>\n";

$db = new DB_SourceBiz;
$db->query("SELECT * FROM news WHERE news.status_new='A' ORDER BY news.modification_new DESC limit 5");
$i=0;
while($db->next_record()) {
  echo "  <item>\n";
  echo "    <title>".$db->f("subject_new")."</title>\n";
  echo "    <link>".$sys_url."newbynewid.php?id=".$db->f("newid")."</link>\n";
  echo "  </item>\n";
  $i++;
}

$blklen = 5;
$time = floor(time() / 5);
$db->query("SELECT COUNT(*) as cnt FROM enterprise WHERE enterprise.status='A'");
$db->next_record();
$entcnt = $db->f("cnt");
$blkcnt = floor($entcnt / $blklen);
if (($entcnt % $blklen) > 0) {
  $blkcnt += 1;
}

$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $blklen) - $blklen;
if (($offset + $blklen) >= $entcnt) {
  $offset = $entcnt - $blklen;
}

echo "  <item>\n";
echo "    <title><b>Unternehmen:</b></title>\n";
echo "    <link>".$sys_url."enterprises.php</link>\n";
echo "  </item>\n";

$db->query("SELECT * FROM enterprise WHERE enterprise.status='A' LIMIT $offset,$blklen");
$i=0;
while($db->next_record()) {
  echo "  <item>\n";
  echo "    <title>".$db->f("name")."</title>\n";
  echo "    <link>".$sys_url."entbyid.php?id=".$db->f("entid")."</link>\n";
  echo "  </item>\n";
  $i++;
}

$blklen = 5;
$time = floor(time() / 5);
$db->query("SELECT COUNT(*) as cnt FROM contact WHERE contact.status_con='A'");
$db->next_record();
$entcnt = $db->f("cnt");
$blkcnt = floor($entcnt / $blklen);
if (($entcnt % $blklen) > 0) {
  $blkcnt += 1;
}

$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $blklen) - $blklen;
if (($offset + $blklen) >= $entcnt) {
  $offset = $entcnt - $blklen;
}

echo "  <item>\n";
echo "    <title><b>Kontakte:</b></title>\n";
echo "    <link>".$sys_url."contacts.php</link>\n";
echo "  </item>\n";

$db->query("SELECT * FROM contact WHERE contact.status_con='A' LIMIT $offset,$blklen");
$i=0;
while($db->next_record()) {
  echo "  <item>\n";
  echo "    <title>".$db->f("name_con")."</title>\n";
  echo "    <link>".$sys_url."conbyconid.php?id=".$db->f("conid")."</link>\n";
  echo "  </item>\n";
  $i++;
}

$blklen = 5;
$time = floor(time() / 5);
$db->query("SELECT COUNT(*) as cnt FROM services WHERE services.status_svc='A'");
$db->next_record();
$entcnt = $db->f("cnt");
$blkcnt = floor($entcnt / $blklen);
if (($entcnt % $blklen) > 0) {
  $blkcnt += 1;
}

$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $blklen) - $blklen;
if (($offset + $blklen) >= $entcnt) {
  $offset = $entcnt - $blklen;
}

echo "  <item>\n";
echo "    <title><b>Dienste:</b></title>\n";
echo "    <link>".$sys_url."services.php</link>\n";
echo "  </item>\n";

$db->query("SELECT * FROM services WHERE services.status_svc='A' LIMIT $offset,$blklen");
$i=0;
while($db->next_record()) {
  echo "  <item>\n";
  echo "    <title>".$db->f("name_svc")."</title>\n";
  echo "    <link>".$sys_url."svcbysvcid.php?id=".$db->f("svcid")."</link>\n";
  echo "  </item>\n";
  $i++;
}

$blklen = 5;
$time = floor(time() / 5);
$db->query("SELECT COUNT(*) as cnt FROM products WHERE products.status_pro='A'");
$db->next_record();
$entcnt = $db->f("cnt");
$blkcnt = floor($entcnt / $blklen);
if (($entcnt % $blklen) > 0) {
  $blkcnt += 1;
}

$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $blklen) - $blklen;
if (($offset + $blklen) >= $entcnt) {
  $offset = $entcnt - $blklen;
}

echo "  <item>\n";
echo "    <title><b>Produkte:</b></title>\n";
echo "    <link>".$sys_url."products.php</link>\n";
echo "  </item>\n";

$db->query("SELECT * FROM products WHERE products.status_pro='A' LIMIT $offset,$blklen");
$i=0;
while($db->next_record()) {
  echo "  <item>\n";
  echo "    <title>".$db->f("name_pro")."</title>\n";
  echo "    <link>".$sys_url."probyproid.php?id=".$db->f("proid")."</link>\n";
  echo "  </item>\n";
  $i++;
}

$blklen = 5;
$time = floor(time() / 5);
$db->query("SELECT COUNT(*) as cnt FROM solutions WHERE solutions.status_sol='A'");
$db->next_record();
$entcnt = $db->f("cnt");
$blkcnt = floor($entcnt / $blklen);
if (($entcnt % $blklen) > 0) {
  $blkcnt += 1;
}

$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $blklen) - $blklen;
if (($offset + $blklen) >= $entcnt) {
  $offset = $entcnt - $blklen;
}

echo "  <item>\n";
echo "    <title><b>Lösungen:</b></title>\n";
echo "    <link>".$sys_url."solutions.php</link>\n";
echo "  </item>\n";

$db->query("SELECT * FROM solutions WHERE solutions.status_sol='A' LIMIT $offset,$blklen");
$i=0;
while($db->next_record()) {
  echo "  <item>\n";
  echo "    <title>".$db->f("name_sol")."</title>\n";
  echo "    <link>".$sys_url."solbysolid.php?id=".$db->f("solid")."</link>\n";
  echo "  </item>\n";
  $i++;
}

$blklen = 5;
$time = floor(time() / 5);
$db->query("SELECT COUNT(*) as cnt FROM customers WHERE customers.status_cus='A'");
$db->next_record();
$entcnt = $db->f("cnt");
$blkcnt = floor($entcnt / $blklen);
if (($entcnt % $blklen) > 0) {
  $blkcnt += 1;
}

$offset = $time % $blkcnt;
if ($offset == 0) $offset = $blkcnt;
$offset = ($offset * $blklen) - $blklen;
if (($offset + $blklen) >= $entcnt) {
  $offset = $entcnt - $blklen;
}

echo "  <item>\n";
echo "    <title><b>Kunden:</b></title>\n";
echo "    <link>".$sys_url."customers.php</link>\n";
echo "  </item>\n";

$db->query("SELECT * FROM customers WHERE customers.status_cus='A' LIMIT $offset,$blklen");
$i=0;
while($db->next_record()) {
  echo "  <item>\n";
  echo "    <title>".$db->f("name_cus")."</title>\n";
  echo "    <link>".$sys_url."cusbycusid.php?id=".$db->f("cusid")."</link>\n";
  echo "  </item>\n";
  $i++;
}

echo "  </channel>\n";
echo "</rss>\n";
?>
