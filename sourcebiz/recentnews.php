<?php

######################################################################
# SourceBiz: Open Source Business
# =============================================
#
# Copyright (c) 2001-2003 by
#                Lutz Henckel (lutz.henckel@fokus.fraunhofer.de) and
#                Gregorio Robles (grex@scouts-es.org)
#
# BerliOS SourceBiz: http://sourcebiz.berlios.de
# BerliOS - The OpenSource Mediator: http://www.berlios.de
#
# This is the text backend of the system
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id: recentnews.php,v 1.2 2003/02/25 11:45:44 helix Exp $
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
header("Content-Type: text/plain");

// Disabling cache
header("Cache-Control: no-cache, must-revalidate");     // HTTP/1.1
header("Pragma: no-cache");                             // HTTP/1.0

require("./include/config.inc");
require("./include/lib.inc");

$db = new DB_SourceBiz;
$db->query("SELECT * FROM news WHERE news.status_new='A' ORDER BY news.modification_new DESC limit 10");
$i=0;
while($db->next_record()) {
  echo $db->f("subject_new")."\n";
  $timestamp = mktimestamp($db->f("modification_new"));
  echo timestr($timestamp)."\n";
  echo $sys_url."newbynewid.php?id=".$db->f("newid")."\n";
  $i++;
} 

@page_close();
?>
