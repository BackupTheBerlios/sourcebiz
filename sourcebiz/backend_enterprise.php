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

header("Content-Type: text/xml");

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
echo "    <title>".htmlspecialchars($sys_name)." - Enterprises</title>\n";
echo "    <link>http:".$sys_url."</link>\n";
echo "    <description>".htmlspecialchars($sys_name." - ".$sys_title)."</description>\n";
echo "    <language>en-us</language>\n";

echo "  <image>\n";
echo "    <title>".htmlspecialchars($sys_name)."</title>\n";
echo "    <url>http:".$sys_url.$sys_logo_small_image."</url>\n";
echo "    <link>http:".$sys_url."</link>\n";
echo "    <description>".htmlspecialchars($sys_name." - ".$sys_title)."</description>\n";
echo "    <width>66</width>\n";
echo "    <height>73</height>\n";
echo "  </image>\n";

$db = new DB_SourceBiz;

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

$db->query("SELECT * FROM enterprise WHERE enterprise.status='A' LIMIT $offset,$blklen");
$i=0;
while($db->next_record()) {
  echo "  <item>\n";
  echo "    <title>".htmlspecialchars($db->f("name"))."</title>\n";
  echo "    <link>http:".$sys_url."entbyid.php?id=".$db->f("entid")."</link>\n";
  echo "  </item>\n";
  $i++;
}

echo "  </channel>\n";
echo "</rss>\n";
?>
