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
# XML backend (RDF-type document) for news
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
echo "    <title>".htmlspecialchars($sys_name)." - News</title>\n";
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
$db->query("SELECT * FROM news WHERE news.status_new='A' ORDER BY news.modification_new DESC limit 5");
$i=0;
while($db->next_record()) {
  echo "  <item>\n";
  echo "    <title>".htmlspecialchars($db->f("subject_new"))."</title>\n";
  echo "    <link>http:".$sys_url."newbynewid.php?id=".$db->f("newid")."</link>\n";
  echo "  </item>\n";
  $i++;
}

echo "  </channel>\n";
echo "</rss>\n";
?>
