<?php

function newform($db) {
    global $sess, $bx, $t;
	$bx->box_begin();
	$bx->box_title($t->translate("News")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->url("newins.php")."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Subject")." (128):</td><td><input type=\"TEXT\" name=\"subject_new\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("News")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"text_new\" wrap=\"virtual\"></textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_new\" size=40 maxlength=255></td></tr>\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("entid")."\">\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function newshow($db,$admin) {
    global $sess, $t, $bx;
 	increasecnt($db->f("entid"),"new_cnt");
	$bx->box_begin();
	$bx->box_title($t->translate("News").": ".$db->f("subject_new"));
	$bx->box_body_begin();
	if ($admin || $db->f("status_new") == 'A') {
    echo "<p>".$db->f("text_new")."\n";
		$homepage_new = $db->f("homepage_new");
		if (!empty($homepage_new)) {
			echo "<p><b>Information:</b> <a href=\"".$db->f("homepage_new")."\" target=_blank>".$db->f("homepage_new")."</a>\n";
		}
	}
    echo "<p class=\"small\"><b>".$t->translate("of")."</b> <a href=\"".$sess->url("entbyid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$db->f("name")."</a>\n";
    $timestamp = mktimestamp($db->f("modification_new"));
    echo "<br><b>".timestr($timestamp)."</b>\n";
	$bx->box_body_end();
	if ($admin || $db->f("status_new") == 'D') {
		$bx->box_title_begin();
		if ($db->f("status_new") == 'D') {
			if ($admin) {
				echo "<a href=\"".$sess->url("newupd.php").$sess->add_query(array("id" => $db->f("newid")))."\">";
			}
			echo "<img src=\"images/editdelete.png\" border=0 alt=\"";
			if ($admin) {
				echo $t->translate("Undelete")."\"></a>\n";
			} else {
				echo $t->translate("Deleted")."\">\n";
			}
			echo "&nbsp;&nbsp;";
		}
		if ($admin) {
		    echo "<b>".$t->translate("Update").":&nbsp;[&nbsp;<a href=\"".$sess->url("newupd.php").$sess->add_query(array("id" => $db->f("newid")))."\">".$t->translate("News")."</a>&nbsp;]\n";
		}
		$bx->box_title_end();
	}
	$bx->box_end();
}

function newmod($db) {
   global $sess, $perm, $t, $bx;
	$bx->box_begin();
	$bx->box_title($t->translate("News of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->self_url()."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Subject")." (128):</td><td><input type=\"TEXT\" name=\"subject_new\" size=40 maxlength=128 value=\"".$db->f("subject_new")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("News")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"text_new\" wrap=\"virtual\">".$db->f("text_new")."</textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_new\" size=40 maxlength=255 value=\"".$db->f("homepage_new")."\">&nbsp;[<a href=\"".$db->f("homepage_new")."\" target=\"_blank\">".$t->translate("Check")."</a>]</td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Status")." :</td><td>";
	switch ($db->f("status_new")) {
	case 'A':
		echo $t->translate("active");
		break;
	case 'D':
		echo $t->translate("deleted");
		break;
	}
	echo "</td></tr>\n";
	echo "<tr><td align=right>".$t->translate("Action").":</td><td>\n";
	echo "<select name=\"action\">\n";
	echo "<option value=\"change\"";
	echo ">".$t->translate("Change")."\n";
	if ($db->f("status_new") == 'A') {
		echo "<option value=\"delete\"";
		echo ">".$t->translate("Delete")."\n";
	}
	if ($db->f("status_new") == 'D') {
		echo "<option value=\"undelete\"";
		echo ">".$t->translate("Undelete")."\n";
	}
	if ($perm->have_perm("admin")) {
		echo "<option value=\"erase\"";
		echo ">".$t->translate("Erase")."\n";
	}
	echo "</select></td></tr>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("newid")."\">\n";
    echo "<input type=\"hidden\" name=\"status_new\" value=\"".$db->f("status_new")."\">\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function newbyentid($db,$entid) {
	global $t, $be, $auth, $perm;
	global $cnt,$prev_cnt,$next_cnt,$config_showfull_newperpage;

	if (!isset($cnt)) $cnt = 0;
	$prev_cnt = $cnt + $config_showfull_newperpage;
	if ($cnt >= $config_showfull_newperpage) $next_cnt = $cnt - $config_showfull_newperpage;
	else $next_cnt = 0;

	$query = newquery($entid);
	if (!$db->query($query)) {
		mysql_die($db);
	} else {
		if ($db->num_rows() > 0) {
			newsort($db,$entid);
			while ($db->next_record()) {
				increasecnt($db->f("entid"),"new_cnt");
				newshow($db,admin($db));
			}
			newnav($db,$entid);
		} else {
			$errmsg = $t->translate("News")." ".$t->translate("for Enterprise")." (ID: $entid) ".$t->translate("does not exist").".";
			$be->box_full($t->translate("Attention!"), $errmsg);
		}
	}
}


function newbynewid($db,$newid) {
	global $t, $be, $auth, $perm;
	$columns = "*";
	$tables = "news,enterprise";
	$where = "news.newid='$newid' AND enterprise.entid=news.entid_new";
	$group = "news.newid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"new_cnt");
			newshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("News")." (ID: $conid) ".$t->translate("does not exist").".");
		}
	}
}


function newidx($num) {
	global $sess, $t, $db, $bx;
    $columns = "*";
    $tables = "news";
    $where = "news.status_new='A'";
    $order = "news.modification_new DESC";
    $limit = "0,$num";
    if (!$db->query("SELECT $columns FROM $tables WHERE $where ORDER BY $order LIMIT $limit"))
    {
        mysql_die($db);
    } else {
        if ($db->num_rows() > 0) {
			$bx->box_begin();
			$bx->box_title_begin();
            echo "<center><b>".$t->translate("News")."</b></center></a>";
			$bx->box_title_end();
			$bx->box_body_begin();
            while($db->next_record()) {
				echo "<div class=newsind>&#149;&nbsp;";
                echo "<a href=\"".$sess->url("newbynewid.php").$sess->add_query(array("id" => $db->f("newid")))."\">".$db->f("subject_new")."</a></div>\n";
            }
			$bx->box_body_end();
			$bx->box_end();
        }
    }
}


function newquery($entid) {
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$subject,$text;
    global $auth, $logout, $bs, $config_showfull_newperpage;
	$columns = "*";
	$tables = "news,enterprise";
	$like = "";
	switch ($by) {
	case "subject":
		$order = "ORDER BY news.subject_new ASC";
		break;
	case "filter":
		$order = "";
		if (isset($enterprise) && !empty($enterprise)) {
			$like .= "AND enterprise.name LIKE '%$enterprise%'";
		}
		if (isset($subject) && !empty($subject)) {
			$like .= "AND news.subject_new LIKE '%$subject%'";
		}
		if (isset($text) && !empty($text)) {
			$like .= "AND news.text_new LIKE '%$text%'";
		}
		break;
	case "date":
	default:
		$order = "ORDER BY news.modification_new DESC";
		break;
	}
	$where = "enterprise.entid = news.entid_new $like";
	if (!isset($auth) || empty($auth->auth["perm"]) || $logout) {
		$where .= " AND news.status_new='A'";
	}
	if ($entid > 0) {
		$where = "news.entid_new='$entid' AND ".$where;
	}
	$limit = $cnt.",".$config_showfull_newperpage;
	return "SELECT $columns FROM $tables WHERE $where $order LIMIT $limit";
}


function newsort($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_newperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$subject,$text;
	if ($entid > 0) {
		$ref = "newbyentid.php";
	} else {
		$ref = basename($PHP_SELF);
	}
	$sort = $t->translate("News")." ".$t->translate("sorted by").": ";
	if (!empty($by) && $by != "date") {
		$sort .= "<a href=\"".$sess->url($ref);
		if ($entid > 0) {
			$darray["id"] = $entid;
		}
		$darray["by"] = "date";
		$sort .= $sess->add_query($darray)."\">".$t->translate("Date")."</a>";
	} else {
		$sort .= $t->translate("Date");
	}
	$sort .= " | ";
	if ($by != "subject") {
		$sort .= "<a href=\"".$sess->url($ref);
		if ($entid > 0) {
			$sarray["id"] = $entid;
		}
		$sarray["by"] = "subject";
		$sort .= $sess->add_query($sarray)."\">".$t->translate("Subject")."</a>";
	} else {
		$sort .= "".$t->translate("Subject");
	}
	$sort .= " | ";
	if ($by != "filter") {
		$sort .= "<a href=\"".$sess->url($ref);
		if ($entid > 0) {
			$farray["id"] = $entid;
		}
		$farray["by"] = "filter";
		$sort .= $sess->add_query($farray)."\">".$t->translate("Filter")."</a>\n";
	} else {
		$sort .= $t->translate("Filter")."\n";
	}
	$bs->box_strip($sort);

	if ($by == "filter") {
		$filter = "<table border=0 align=center cellspacing=0 cellpadding=3><tr>\n"
		."<form action=\"".$sess->url($ref)."\" method=\"POST\">\n"
		."<td><b>".$t->translate("Filter").":</b></td>\n";
		if ($entid <= 0) {
			$filter .= "<td><b>".$t->translate("Enterprise")."</b></td>\n";
		}
		$filter .= "<td><b>".$t->translate("Subject")."</b></td>\n"
		."<td><b>".$t->translate("Text")."</b></td>\n"
		."</tr><tr>\n"
		."<td><input type=\"SUBMIT\" name=\"go\" value=\"".$t->translate("Go")."\"></td>\n";
		if ($entid <= 0) {
			$filter .= "<td><input type=\"TEXT\" name=\"enterprise\" value=\"$enterprise\" size=10 maxlength=255></td>\n";
		}
		$filter .= "<td><input type=\"TEXT\" name=\"subject\" value=\"$subject\" size=10 maxlength=255></td>\n"
		."<td><input type=\"TEXT\" name=\"text\" value=\"$text\" size=10 maxlength=255></td>\n";
		if ($entid > 0) {
			$filter .= "<input type=\"hidden\" name=\"id\" value=\"$entid\">\n";
		}
		$filter .= "<input type=\"hidden\" name=\"by\" value=\"filter\">\n"
		."</form></tr></table>\n";
		$bs->box_strip($filter);
	}
}


function newnav($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_newperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$subject,$text;
	if ($db->num_rows() > 0 && ($cnt > 0 || $db->num_rows() == $config_showfull_newperpage)) {
		if ($entid > 0) {
			$ref = "newbyentid.php";
		} else {
			$ref = basename($PHP_SELF);
		}

		if ($cnt > 0) {
			$nav = "&lt;&nbsp;<a href=\"".$sess->url($ref);
			if ($entid > 0) {
				$narray["id"] = $entid;
			}
			$narray["cnt"] = $prev_cnt;
			$narray["by"] = $by;
			$narray["enterprise"] = $enterprise;
			$narray["subject"] = $subject;
			$narray["text"] = $text;
			$nav .= $sess->add_query($narray)."\">".$t->translate("Previous")."</a>";
		} else {
			$nav = "&lt;&nbsp;".$t->translate("Previous");
		}

		$nav .= " | <a href=\"".$sess->url($ref);
		if ($entid > 0) {
			$tarray["id"] = $entid;
		}
		$tarray["by"] = $by;
		$tarray["enterprise"] = $enterprise;
		$tarray["subject"] = $subject;
		$tarray["text"] = $text;
		$nav .= $sess->add_query($tarray)."\">".$t->translate("Top")."</a>";

		if ($db->num_rows() == $config_showfull_newperpage) {
			$nav .= " | <a href=\"".$sess->url($ref);
			if ($entid > 0) {
				$parray["id"] = $entid;
			}
			$parray["cnt"] = $next_cnt;
			$parray["by"] = $by;
			$parray["enterprise"] = $enterprise;
			$parray["subject"] = $subject;
			$parray["text"] = $text;
			$nav .= $sess->add_query($parray)."\">".$t->translate("Next")."</a>&nbsp;&gt;";
		} else {
			$nav .= " | ".$t->translate("Next")."&nbsp;&gt;";
		}

		$bs->box_strip($nav);
	}
}
?>
