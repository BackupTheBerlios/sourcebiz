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
# This file is used to keep track of all the statistics
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

require("./include/config.inc");
require("./include/lib.inc");

//
// increase counter
//
increasecnt($id,$type);
//
// Redirect to URL
//
?>
<HTML>
<HEAD>
   <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
   <META HTTP-EQUIV="refresh" CONTENT="0;url=<?php echo "$url"; ?>">
   <META NAME="GENERATOR" CONTENT="Mozilla/4.05 [en] (X11; I; SunOS 5.6 sun4m) [Netscape]">
   <META NAME="robots" CONTENT="noindex">
   <TITLE>Page redirected to ...</TITLE>
<LINK rel="stylesheet" type="text/css" href="style.php">
</HEAD>
<BODY>
</BODY>
</HTML>
<?php
page_close();
?>
