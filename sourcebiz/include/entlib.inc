<?php

function entform() {
    global $sess, $bx, $t;
	$bx->box_begin();
	$bx->box_title($t->translate("Insert Enterprise"));
	$bx->box_body_begin();
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right width=30%>".$t->translate("Enterprise Name")." (255):</td><td width=70%><b>".$GLOBALS["name"]."</b></td></tr>\n";
    echo "<form action=\"".$sess->url("entins.php")."\" ENCTYPE=\"multipart/form-data\" method=\"POST\">\n";
    echo "<input type=\"hidden\" name=\"name\" value=\"".$GLOBALS["name"]."\">\n";
	echo "<tr><td align=right>".$t->translate("Logofile")." (*):</td><td><input type=\"hidden\" name=\"MAX_FILE_SIZE\" value=\"100000\">\n";
	echo "<input name=\"logo\" type=\"file\"></td></tr>\n";
    echo "<tr><td align=right width=30%>".$t->translate("Homepage")." (255):</td><td width=70%><input type=\"TEXT\" name=\"homepage\" size=40 maxlength=255></td></tr>\n";
    echo "<tr><td align=right width=30%>".$t->translate("Short Profile")." (1000):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td width=70%><textarea cols=40 rows=20 name=\"short_profile\" maxlength=1000 wrap=\"virtual\"></textarea></td></tr>\n";
    echo "<tr><td align=right width=30%>&nbsp;</td><td width=70%><input type=\"Submit\" value=\"".$t->translate("Insert")."\"></td></tr>\n";
    echo "</form>\n";
    echo "</td></tr>\n";
    echo "</table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function entshow($db,$admin) {
    global $sess, $bx, $t;
	global $sys_logo_url, $sys_logo_dir, $config_maxwidth;

	$bx->box_begin();
	$bx->box_body_begin();
	$logo = $db->f("logo");
    if (!empty($logo) && ($admin || $db->f("status") == 'A')) {
		$logourl = $sys_logo_url.$db->f("entid")."ent_".rawurlencode(basename($logo));
		$logodir = $sys_logo_dir.$db->f("entid")."ent_".basename($logo);
		$size = GetImageSize($logodir);
		$width = $size[0];
		$height = $size[1];
		if ($width > $config_maxwidth) {
			$height = $height / $width * $config_maxwidth; 
			$width = $config_maxwidth;
		}
		echo "<a href=\"".$sess->url("redirect.php").$sess->add_query(array("id" => $db->f("entid"),"type" => "homepage_cnt","url" => $db->f("homepage")))."\" target=_blank><img src=\"".$logourl."\" width=\"".$width."\" height=\"".$height."\" border=\"0\"></a>";
	}
    echo "<p><b><a href=\"".$sess->url("redirect.php").$sess->add_query(array("id" => $db->f("entid"),"type" => "homepage_cnt","url" => $db->f("homepage")))."\" target=_blank>".$db->f("name")."</a></b>\n";
	if ($admin || $db->f("status") == 'A') {
	    echo "<p>".$db->f("short_profile")."\n";
    	echo "<p>\n";
		echo "<b>[&nbsp;<a href=\"".$sess->url("entbyid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Home")."</a>";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("prfbyentid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Profile")."</a>";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("conbyentid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Contact")."</a>";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("svcbyentid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Services")."</a>";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("probyentid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Products")."</a>";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("solbyentid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Solutions")."</a>";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("cusbyentid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Customers")."</a>";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("newbyentid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("News")."</a>";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("cmtbyentid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Comments")."</a>&nbsp;]</b>";
	}
    $timestamp = mktimestamp($db->f("modification"));
    echo "<p class=\"small\"><b>".$t->translate("by")." <a href=\"mailto:".$db->f("email_usr")."\">".$db->f("user")."</a> - ".timestr($timestamp)."</b>\n";
	$bx->box_body_end();
	$bx->box_title_begin();
	if ($admin || $db->f("status") == 'A') {
		echo "<img src=\"images/attention.png\" alt=\"".$t->translate("Attention")."\"><b>&nbsp;".$t->translate("Attention")."&nbsp;[".$db->f("sum_cnt")."]</b>\n";

		$dbcmt = new DB_SourceBiz;
		if ($admin) {
			$where = "";
		} else {
			$where = "AND status_cmt = 'A'";
		}
		$dbcmt->query("SELECT COUNT(*) AS cmtcnt FROM comments WHERE entid_cmt='".$db->f("entid")."' $where");
		$dbcmt->next_record();
		if ($dbcmt->f("cmtcnt") <= 0) {
			$num = "[0]";
		} else {
			$num = "[".$dbcmt->f("cmtcnt")."]";
		}

		echo "&nbsp;&nbsp;<a href=\"".$sess->url("cmtadd.php").$sess->add_query(array("id" => $db->f("entid")))."\"><b><img src=\"images/txt.png\" border=0 alt=\"".$t->translate("Add Comment")."\">&nbsp;".$t->translate("Add Comment")."</a>&nbsp;$num</b>\n";
		if ($admin) {
			echo "<br><b>".$t->translate("Update").":&nbsp;[&nbsp;<a href=\"".$sess->url("entupd.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Enterprise")."</a>&nbsp;]</b>\n";
		}
	}
	if ($db->f("status") == 'D') {
		echo "&nbsp;&nbsp;";
		if ($admin) {
			echo "<a href=\"".$sess->url("entupd.php").$sess->add_query(array("id" => $db->f("entid")))."\">";
		}
		echo "<img src=\"images/editdelete.png\" border=0 alt=\"";
		if ($admin) {
			echo $t->translate("Undelete")."\"></a>\n";
		} else {
			echo $t->translate("Deleted")."\">\n";
		}
	}
	if ($admin && $db->f("status") == 'A') {
		echo "<br><b>".$t->translate("Add").":&nbsp;[&nbsp;<a href=\"".$sess->url("prfadd.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Profile")."</a>\n";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("conadd.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Contact")."</a>\n";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("svcadd.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Service")."</a>\n";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("proadd.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Product")."</a>\n";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("soladd.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Solution")."</a>\n";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("cusadd.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("Customer")."</a>\n";
		echo "&nbsp;|&nbsp;<a href=\"".$sess->url("newadd.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$t->translate("News")."</a>&nbsp;]</b>\n";
	}
	$bx->box_title_end();
    $bx->box_end();
}


function entmod($db) {
    global $sess, $perm, $bx, $t;
	$bx->box_begin();
	$bx->box_title($t->translate("Update Enterprise"));
	$bx->box_body_begin();
    echo "<form action=\"".$sess->url("entupd.php")."\" ENCTYPE=\"multipart/form-data\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3 width=100%>\n";
    echo "<tr><td align=right width=30%>".$t->translate("Enterprise Name")." (255):</td><td width=70%><input type=\"TEXT\" name=\"name\" size=40 maxlength=255 value=\"".$db->f("name")."\"></td></tr>\n";
	$logo = $db->f("logo");
    echo "<input type=\"hidden\" name=\"clogo\" value=\"$logo\">\n";
	if (!empty($logo)) {
		echo "<tr><td align=right valign=top>".$t->translate("Current Logofile").":</td><td>$logo\n";
		echo "<br><input type=radio name=\"logoact\" value=\"keep\" checked> ".$t->translate("Keep")."\n";
		echo "<input type=radio name=\"logoact\" value=\"new\"> ".$t->translate("New")."\n";
		echo "<input type=radio name=\"logoact\" value=\"delete\"> ".$t->translate("Delete")."\n";
		echo "<td></tr>\n";
	} else {
	    echo "<input type=\"hidden\" name=\"logoact\" value=\"new\">\n";
	}
	echo "<tr><td align=right>".$t->translate("Logofile")." (*):</td><td><input type=\"hidden\" name=\"MAX_FILE_SIZE\" value=\"100000\">\n";
	echo "<input name=\"logo\" type=\"file\">\n";
	echo "</td></tr>\n";
    echo "<tr><td align=right width=30%>".$t->translate("Homepage")." (255):</td><td width=70%><input type=\"TEXT\" name=\"homepage\" size=40 maxlength=255 value=\"".$db->f("homepage")."\">&nbsp;[<a href=\"".$db->f("homepage")."\" target=\"_blank\">".$t->translate("Check")."</a>]</td></tr>\n";
    echo "<tr><td align=right width=30%>".$t->translate("Short Profile")." (1000):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td width=70%><textarea cols=40 rows=20 name=\"short_profile\" maxlength=1000 wrap=\"virtual\">".$db->f("short_profile")."</textarea></td></tr>\n";

	echo "<tr><td align=right width=30%>".$t->translate("Status").":</td><td width=70%>\n";
	switch ($db->f("status")) {
	case 'A':
		echo $t->translate("active")."\n";
		break;
	case 'D':
		echo $t->translate("deleted")."\n";
		break;
	}
	echo "</td></tr>\n";
	echo "<tr><td align=right width=30%>".$t->translate("Action").":</td><td width=70%>\n";
	echo "<select name=\"action\">\n";
	echo "<option value=\"change\"";
	echo ">".$t->translate("Change")."\n";
	if ($db->f("status") == 'A') {
		echo "<option value=\"delete\"";
		echo ">".$t->translate("Delete")."\n";
	}
	if ($db->f("status") == 'D') {
		echo "<option value=\"undelete\"";
		echo ">".$t->translate("Undelete")."\n";
	}
	if ($perm->have_perm("admin")) {
		echo "<option value=\"erase\"";
		echo ">".$t->translate("Erase")."\n";
	}
	echo "</select></td></tr>\n";
	echo "<tr><td align=right width=30%>&nbsp;</td><td width=70%><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td></tr>\n";

    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("entid")."\">\n";
    echo "<input type=\"hidden\" name=\"status\" value=\"".$db->f("status")."\">\n";
    echo "<input type=\"hidden\" name=\"modification\" value=\"".$db->f("modification")."\">\n";
    echo "</form>\n";
    echo "</td></tr>\n";
    echo "</table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function entbyentid($db,$id) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "enterprise,counter,auth_user";
	$where = "enterprise.entid='$id' AND enterprise.entid=counter.entid AND enterprise.user=auth_user.username";
	$group = "enterprise.entid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		increasecnt($id,"ent_cnt");
		$admin = 0;
		if ($db->next_record()) {
			if (isset($auth) && !empty($auth->auth["perm"]) && ($perm->have_perm("admin") || $db->f("user") == $auth->auth["uname"])) {
				$admin = 1;
			}
			entshow($db,$admin);
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Enterprise")." (ID: $id) ".$t->translate("does not exist").".");
		}
	}
}


function entbyprfid($db,$prfid) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "profile,enterprise,counter,auth_user";
	$where = "profile.prfid='$prfid' AND enterprise.entid=profile.entid_prf AND profile.entid_prf=counter.entid AND enterprise.user=auth_user.username";
	$group = "profile.prfid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"ent_cnt");
			entshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Contact")." (ID: $conid) ".$t->translate("does not exist").".");
		}
	}
}


function entbyconid($db,$conid) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "contact,enterprise,counter,auth_user";
	$where = "contact.conid='$conid' AND enterprise.entid=contact.entid_con AND contact.entid_con=counter.entid AND enterprise.user=auth_user.username";
	$group = "contact.conid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"ent_cnt");
			entshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Contact")." (ID: $conid) ".$t->translate("does not exist").".");
		}
	}
}


function entbysvcid($db,$svcid) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "services,enterprise,counter,auth_user";
	$where = "services.svcid='$svcid' AND enterprise.entid=services.entid_svc AND services.entid_svc=counter.entid AND enterprise.user=auth_user.username";
	$group = "services.svcid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"ent_cnt");
			entshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Service")." (ID: $svcid) ".$t->translate("does not exist").".");
		}
	}
}


function entbyproid($db,$proid) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "products,enterprise,counter,auth_user";
	$where = "products.proid='$proid' AND enterprise.entid=products.entid_pro AND products.entid_pro=counter.entid AND enterprise.user=auth_user.username";
	$group = "products.proid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"ent_cnt");
			entshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Product")." (ID: $proid) ".$t->translate("does not exist").".");
		}
	}
}


function entbysolid($db,$solid) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "solutions,enterprise,counter,auth_user";
	$where = "solutions.solid='$solid' AND enterprise.entid=solutions.entid_sol AND solutions.entid_sol=counter.entid AND enterprise.user=auth_user.username";
	$group = "solutions.solid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"ent_cnt");
			entshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Solution")." (ID: $solid) ".$t->translate("does not exist").".");
		}
	}
}


function entbycusid($db,$cusid) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "customers,enterprise,counter,auth_user";
	$where = "customers.cusid='$cusid' AND enterprise.entid=customers.entid_cus AND customers.entid_cus=counter.entid AND enterprise.user=auth_user.username";
	$group = "customers.cusid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"ent_cnt");
			entshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Customer")." (ID: $cusid) ".$t->translate("does not exist").".");
		}
	}
}


function entbynewid($db,$newid) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "news,enterprise,counter,auth_user";
	$where = "news.newid='$newid' AND enterprise.entid=news.entid_new AND news.entid_new=counter.entid AND enterprise.user=auth_user.username";
	$group = "news.newid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"ent_cnt");
			entshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("News")." (ID: $conid) ".$t->translate("does not exist").".");
		}
	}
}


function entbycmtid($db,$cmtid) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "comments,enterprise,counter,auth_user";
	$where = "comments.cmtid='$cmtid' AND enterprise.entid=comments.entid_cmt AND comments.entid_cmt=counter.entid AND enterprise.user=auth_user.username";
	$group = "comments.cmtid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"ent_cnt");
			entshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Comment")." (ID: $cmtid) ".$t->translate("does not exist").".");
		}
	}
}


function delprf($entid) {
	$dbprf = new DB_SourceBiz;
	$tables = "profile";
	$set = "status_prf='D'";
	$where = "entid_prf='$entid'";
	$dbprf->query("UPDATE $tables SET $set WHERE $where");
}


function delcon($entid) {
	$dbcon = new DB_SourceBiz;
	$tables = "contact";
	$set = "status_con='D'";
	$where = "entid_con='$entid'";
	$dbcon->query("UPDATE $tables SET $set WHERE $where");
}


function delsvc($entid) {
	$dbsvc = new DB_SourceBiz;
	$tables = "services";
	$set = "status_svc='D'";
	$where = "entid_svc='$entid'";
	$dbsvc->query("UPDATE $tables SET $set WHERE $where");
}


function delpro($entid) {
	$dbpro = new DB_SourceBiz;
	$tables = "products";
	$set = "status_pro='D'";
	$where = "entid_pro='$entid'";
	$dbpro->query("UPDATE $tables SET $set WHERE $where");
}


function delsol($entid) {
	$dbcus = new DB_SourceBiz;
	$tables = "solutions";
	$set = "status_sol='D'";
	$where = "entid_sol='$entid'";
	$dbcus->query("UPDATE $tables SET $set WHERE $where");
}


function delcus($entid) {
	$dbcus = new DB_SourceBiz;
	$tables = "customers";
	$set = "status_cus='D'";
	$where = "entid_cus='$entid'";
	$dbcus->query("UPDATE $tables SET $set WHERE $where");
}


function delnew($entid) {
	$dbnew = new DB_SourceBiz;
	$tables = "news";
	$set = "status_new='D'";
	$where = "entid_new='$entid'";
	$dbnew->query("UPDATE $tables SET $set WHERE $where");
}


function delcmt($entid) {
	$dbcmt = new DB_SourceBiz;
	$tables = "comments";
	$set = "status_cmt='D'";
	$where = "entid_cmt='$entid'";
	$dbcmt->query("UPDATE $tables SET $set WHERE $where");
}


function eraprf($entid) {
	$dbprf = new DB_SourceBiz;
	$tables = "profile";
	$where = "entid_prf='$entid'";
	$dbprf->query("DELETE FROM $tables WHERE $where");
}


function eracon($entid) {
	$dbcon = new DB_SourceBiz;
	$tables = "contact";
	$where = "entid_con='$entid'";
	$dbcon->query("DELETE FROM $tables WHERE $where");
}


function erasvc($entid) {
	$dbsvc = new DB_SourceBiz;
	$tables = "services";
	$where = "entid_svc='$entid'";
	$dbsvc->query("DELETE FROM $tables WHERE $where");
}


function erapro($entid) {
	$dbpro = new DB_SourceBiz;
	$tables = "products";
	$where = "entid_pro='$entid'";
	$dbpro->query("DELETE FROM $tables WHERE $where");
}


function erasol($entid) {
	$dbpro = new DB_SourceBiz;
	$tables = "solutions";
	$where = "entid_sol='$entid'";
	$dbpro->query("DELETE FROM $tables WHERE $where");
}


function eracus($entid) {
	$dbcus = new DB_SourceBiz;
	$tables = "customers";
	$where = "entid_cus='$entid'";
	$dbcus->query("DELETE FROM $tables WHERE $where");
}


function eranew($entid) {
	$dbnew = new DB_SourceBiz;
	$tables = "news";
	$where = "entid_new='$entid'";
	$dbnew->query("DELETE FROM $tables WHERE $where");
}


function eracmt($entid) {
	$dbcmt = new DB_SourceBiz;
	$tables = "comments";
	$where = "entid_cmt='$entid'";
	$dbcmt->query("DELETE FROM $tables WHERE $where");
}


function eracnt($entid) {
	$dbcnt = new DB_SourceBiz;
	$tables = "counter";
	$where = "entid='$entid'";
	$dbcnt->query("DELETE FROM $tables WHERE $where");
}


function entidx($num) {
	global $sess, $t, $db, $bx;

    $tables = "enterprise";
    $where = "enterprise.status='A'";

	$time = floor(time() / 60);
	$db->query("SELECT COUNT(*) as cnt FROM $tables WHERE $where");
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

    $columns = "*";
    $limit = "$offset,$num";
    if (!$db->query("SELECT $columns FROM $tables WHERE $where LIMIT $limit"))
    {
        mysql_die($db);
    } else {
        if ($db->num_rows() > 0) {
			$bx->box_begin();
			$bx->box_title_begin();
            echo "<center><b>".$t->translate("Enterprises")."</b></center></a>";
			$bx->box_title_end();
			$bx->box_body_begin();
            while($db->next_record()) {
				echo "<div class=newsind>&#149;&nbsp;";
                echo "<a href=\"".$sess->url("entbyid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$db->f("name")."</a></div>\n";
            }
			$bx->box_body_end();
			$bx->box_end();
        }
    }
}


function entquery() {
    global $by,$cnt,$prev_cnt,$next_cnt,$name,$short_profile,$author;
    global $auth, $logout, $bs, $config_showfull_entperpage;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "enterprise,counter,auth_user";
	$like = "";
	$where = "counter.entid=enterprise.entid";
	switch ($by) {
	case "name":
		$order = "ORDER BY enterprise.name ASC";
		break;			
	case "attention":
		$order = "ORDER BY sum_cnt DESC";
		break;
	case "filter":
		if (isset($name) && !empty($name)) {
			$like .= "AND enterprise.name LIKE '%$name%'";
		}
		if (isset($short_profile) && !empty($short_profile)) {
			$like .= "AND enterprise.short_profile LIKE '%$short_profile%'";
		}
		if (isset($author) && !empty($author)) {
			$where .= " AND enterprise.user LIKE '%$author%'";
		}
		break;		
	case "user":
		if (isset($auth)) {
			$where .= " AND enterprise.user='".$auth->auth["uname"]."'";
		}
		break;
	case "date":
	default:
		$order = "ORDER BY enterprise.modification DESC";
		break;
	}
	if (!isset($auth) || empty($auth->auth["perm"]) || $logout) {
		$where .= " AND enterprise.status = 'A'";
	}
	$where .= " AND auth_user.username = enterprise.user";
	$where .= " $like GROUP BY enterprise.entid";
	$limit = $cnt.",".$config_showfull_entperpage;
	return "SELECT $columns FROM $tables WHERE $where $order LIMIT $limit";
}


function entsort($db) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_entperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$name,$short_profile,$author;
	$ref = basename($PHP_SELF);
	$sort = $t->translate("Enterprises")." ".$t->translate("sorted by").": ";
	if (!empty($by) && $by != "date") {
		$sort .= "<a href=\"".$sess->url($ref).$sess->add_query(array("by" => "date"))."\">".$t->translate("Date")."</a>";
	} else {
		$sort .= $t->translate("Date");
	}
	$sort .= " | ";
	if ($by != "name") {
		$sort .= "<a href=\"".$sess->url($ref).$sess->add_query(array("by" => "name"))."\">".$t->translate("Name")."</a>";
	} else {
		$sort .= "".$t->translate("Name");
	}
	$sort .= " | ";
	if ($by != "attention") {
		$sort .= "<a href=\"".$sess->url($ref).$sess->add_query(array("by" => "attention"))."\">".$t->translate("Attention")."</a>";
	} else {
		$sort .= "".$t->translate("Attention");
	}
	$sort .= " | ";
	if ($by != "filter") {
		$sort .= "<a href=\"".$sess->url($ref).$sess->add_query(array("by" => "filter"))."\">".$t->translate("Filter")."</a>\n";
	} else {
		$sort .= $t->translate("Filter")."\n";
	}
	$bs->box_strip($sort);

	if ($by == "filter") {
		$filter = "<table border=0 align=center cellspacing=0 cellpadding=3><tr>\n"
		."<form action=\"".$sess->url($ref)."\" method=\"POST\">\n"
		."<td><b>".$t->translate("Filter").":</b></td>\n"
		."<td><b>".$t->translate("Name")."</b></td>\n"
		."<td><b>".$t->translate("Short Profile")."</b></td>\n"
		."<td><b>".$t->translate("Author")."</b></td>\n"
		."</tr><tr>\n"
		."<td><input type=\"SUBMIT\" name=\"go\" value=\"".$t->translate("Go")."\"></td>\n"
		."<td><input type=\"TEXT\" name=\"name\" value=\"$name\" size=10 maxlength=255></td>\n"
		."<td><input type=\"TEXT\" name=\"short_profile\" value=\"$short_profile\" size=10 maxlength=255></td>\n"
		."<td><input type=\"TEXT\" name=\"author\" value=\"$author\" size=10 maxlength=16></td>\n"
		."<input type=\"hidden\" name=\"by\" value=\"filter\">\n"
		."</form></tr></table>\n";
		$bs->box_strip($filter);
	}
}


function entnav($db) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_entperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$name,$short_profile,$author;
	if ($db->num_rows() > 0) {
		$ref = basename($PHP_SELF);

		if ($cnt > 0) {
			$nav = "&lt;&nbsp;<a href=\"".$sess->url($ref).$sess->add_query(array("cnt" => $prev_cnt,"by" => $by,"name" => $name,"short_profile" => $short_profile,"author" => $author))."\">".$t->translate("Previous")."</a>";
		} else {
			$nav = "&lt;&nbsp;".$t->translate("Previous");
		}

		$nav .= " | <a href=\"".$sess->url($ref).$sess->add_query(array("by" => $by,"name" => $name,"short_profile" => $short_profile,"author" => $author))."\">".$t->translate("Top")."</a>";

		if ($db->num_rows() == $config_showfull_entperpage) {
			$nav .= " | <a href=\"".$sess->url($ref).$sess->add_query(array("cnt" => $next_cnt,"by" => $by,"name" => $name,"short_profile" => $short_profile,"author" => $author))."\">".$t->translate("Next")."</a>&nbsp;&gt;";
		} else {
			$nav .= " | ".$t->translate("Next")."&nbsp;&gt;";
		}

		$bs->box_strip($nav);
	}
}
?>
