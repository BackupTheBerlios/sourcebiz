<?php

function solform($db) {
    global $sess, $bx, $t;
	$bx->box_begin();
	$bx->box_title($t->translate("Solution")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->url("solins.php")."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Name")." (128):</td><td><input type=\"TEXT\" name=\"name_sol\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Description")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"description_sol\" wrap=\"virtual\"></textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_sol\" size=40 maxlength=255></td></tr>\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("entid")."\">\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function solshow($db,$admin) {
    global $sess, $t, $bx;
 	increasecnt($db->f("entid"),"sol_cnt");
	$bx->box_begin();
	$bx->box_title($t->translate("Solution").": ".$db->f("name_sol"));
	$bx->box_body_begin();
	if ($admin || $db->f("status_sol") == 'A') {
		echo "<p>".$db->f("description_sol")."\n";
		$homepage_sol = $db->f("homepage_sol");
		if (!empty($homepage_sol)) {
			echo "<p><b>Information:</b> <a href=\"".$db->f("homepage_sol")."\" target=_blank>".$db->f("homepage_sol")."</a>\n";
		}
	}
    echo "<p class=\"small\"><b>".$t->translate("of")."</b> <a href=\"".$sess->url("entbyid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$db->f("name")."</a>\n";
    $timestamp = mktimestamp($db->f("modification_sol"));
    echo "<br><b>".timestr($timestamp)."</b>\n";
	$bx->box_body_end();
	if ($admin || $db->f("status_sol") == 'D') {
		$bx->box_title_begin();
		if ($db->f("status_sol") == 'D') {
			if ($admin) {
				echo "<a href=\"".$sess->url("solupd.php").$sess->add_query(array("id" => $db->f("solid")))."\">";
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
		    echo "<b>".$t->translate("Update").":&nbsp;[&nbsp;<a href=\"".$sess->url("solupd.php").$sess->add_query(array("id" => $db->f("solid")))."\">".$t->translate("Solution")."</a>&nbsp;]</b>\n";
		}
		$bx->box_title_end();
	}
	$bx->box_end();
}

function solmod($db) {
   global $sess, $perm, $t, $bx;
	$bx->box_begin();
	$bx->box_title($t->translate("Solution")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->self_url()."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Name")." (128):</td><td><input type=\"TEXT\" name=\"name_sol\" size=40 maxlength=128 value=\"".$db->f("name_sol")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Description")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"description_sol\" wrap=\"virtual\">".$db->f("description_sol")."</textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_sol\" size=40 maxlength=255 value=\"".$db->f("homepage_sol")."\">&nbsp;[<a href=\"".$db->f("homepage_sol")."\" target=\"_blank\">".$t->translate("Check")."</a>]</td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Status")." :</td><td>";
	switch ($db->f("status_sol")) {
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
	if ($db->f("status_sol") == 'A') {
		echo "<option value=\"delete\"";
		echo ">".$t->translate("Delete")."\n";
	}
	if ($db->f("status_sol") == 'D') {
		echo "<option value=\"undelete\"";
		echo ">".$t->translate("Undelete")."\n";
	}
	if ($perm->have_perm("admin")) {
		echo "<option value=\"erase\"";
		echo ">".$t->translate("Erase")."\n";
	}
	echo "</select></td></tr>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("solid")."\">\n";
    echo "<input type=\"hidden\" name=\"status_sol\" value=\"".$db->f("status_sol")."\">\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function solbyentid($db,$entid) {
	global $t, $be, $auth, $perm;
	global $cnt,$prev_cnt,$next_cnt,$config_showfull_solperpage;

	if (!isset($cnt)) $cnt = 0;
	$prev_cnt = $cnt + $config_showfull_solperpage;
	if ($cnt >= $config_showfull_solperpage) $next_cnt = $cnt - $config_showfull_solperpage;
	else $next_cnt = 0;

	$query = solquery($entid);
	if (!$db->query($query)) {
		mysql_die($db);
	} else {
		if ($db->num_rows() > 0) {
			solsort($db,$entid);
			while ($db->next_record()) {
				increasecnt($db->f("entid"),"sol_cnt");
				solshow($db,admin($db));
			}
			solnav($db,$entid);
		} else {
			$errmsg = $t->translate("Solution")." ".$t->translate("for Enterprise")." (ID: $entid) ".$t->translate("does not exist").".";
			$be->box_full($t->translate("Attention!"), $errmsg);
		}
	}
}


function solbysolid($db,$solid) {
	global $t, $be, $auth, $perm;
	$columns = "*";
	$tables = "solutions,enterprise";
	$where = "solutions.solid='$solid' AND enterprise.entid=solutions.entid_sol";
	$group = "solutions.solid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"sol_cnt");
			solshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Solution")." (ID: $solid) ".$t->translate("does not exist").".");
		}
	}
}


function solidx($num) {
	global $sess, $t, $db, $bx, $config_showshort_solperpage;

    $tables = "solutions";
    $where = "solutions.status_sol='A'";

	$time = floor(time() / 60);
	$db->query("SELECT COUNT(*) as cnt FROM $tables WHERE $where");
	$db->next_record();
	$entcnt = $db->f("cnt");
	$blkcnt = floor($entcnt / $num);
	if (($entcnt % $num) > 0) $blkcnt += 1;
	$offset = $time % $blkcnt;
	if ($offset == 0) $offset = $blkcnt;
	$offset = ($offset * $num) - $num;
	if (($offset + $num) >= $entcnt) {
		$offset = $entcnt - $num;
		if ($offset < 0) $offset = 0;
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
            echo "<center><b>".$t->translate("Solutions")."</b></center></a>";
			$bx->box_title_end();
			$bx->box_body_begin();
            while($db->next_record()) {
				echo "<div class=newsind>&#149;&nbsp;";
                echo "<a href=\"".$sess->url("solbysolid.php").$sess->add_query(array("id" => $db->f("solid")))."\">".$db->f("name_sol")."</a></div>\n";
            }
			$bx->box_body_end();
			$bx->box_end();
        }
    }
}


function solquery($entid) {
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$description;
    global $auth, $logout, $bs, $config_showfull_solperpage;
	$columns = "*";
	$tables = "solutions,enterprise";
	$like = "";
	switch ($by) {
	case "name":
		$order = "ORDER BY solutions.name_sol ASC";
		break;			
	case "filter":
		$order = "";
		if (isset($enterprise) && !empty($enterprise)) {
			$like .= "AND enterprise.name LIKE '%$enterprise%'";
		}
		if (isset($name) && !empty($name)) {
			$like .= "AND solutions.name_sol LIKE '%$name%'";
		}
		if (isset($description) && !empty($description)) {
			$like .= "AND solutions.description_sol LIKE '%$description%'";
		}
		break;
	case "date":
	default:
		$order = "ORDER BY solutions.modification_sol DESC";
		break;
	}
	$where = "enterprise.entid = solutions.entid_sol $like";
	if (!isset($auth) || empty($auth->auth["perm"]) || $logout) {
		$where .= " AND solutions.status_sol='A'";
	}
	if ($entid > 0) {
		$where = "solutions.entid_sol='$entid' AND ".$where;
	}
	$limit = $cnt.",".$config_showfull_solperpage;
	return "SELECT $columns FROM $tables WHERE $where $order LIMIT $limit";
}


function solsort($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_solperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$description;
	if ($entid > 0) {
		$ref = "solbyentid.php";
	} else {
		$ref = basename($PHP_SELF);
	}
	$sort = $t->translate("Solutions")." ".$t->translate("sorted by").": ";
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
	if ($by != "name") {
		$sort .= "<a href=\"".$sess->url($ref);
		if ($entid > 0) {
			$narray["id"] = $entid;
		}
		$narray["by"] = "name";
		$sort .= $sess->add_query($narray)."\">".$t->translate("Name")."</a>";
	} else {
		$sort .= "".$t->translate("Name");
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
		$filter .= "<td><b>".$t->translate("Name")."</b></td>\n"
		."<td><b>".$t->translate("Description")."</b></td>\n"
		."</tr><tr>\n"
		."<td><input type=\"SUBMIT\" name=\"go\" value=\"".$t->translate("Go")."\"></td>\n";
		if ($entid <= 0) {
			$filter .= "<td><input type=\"TEXT\" name=\"enterprise\" value=\"$enterprise\" size=10 maxlength=255></td>\n";
		}
		$filter .= "<td><input type=\"TEXT\" name=\"name\" value=\"$name\" size=10 maxlength=255></td>\n"
		."<td><input type=\"TEXT\" name=\"description\" value=\"$description\" size=10 maxlength=255></td>\n";
		if ($entid > 0) {
			$filter .= "<input type=\"hidden\" name=\"id\" value=\"$entid\">\n";
		}
		$filter .= "<input type=\"hidden\" name=\"by\" value=\"filter\">\n"
		."</form></tr></table>\n";
		$bs->box_strip($filter);
	}
}


function solnav($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_solperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$description;
	if ($db->num_rows() > 0 && ($cnt > 0 || $db->num_rows() == $config_showfull_solperpage)) {
		if ($entid > 0) {
			$ref = "solbyentid.php";
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
			$narray["name"] = $name;
			$narray["description"] = $description;
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
		$tarray["name"] = $name;
		$tarray["description"] = $description;
		$nav .= $sess->add_query($tarray)."\">".$t->translate("Top")."</a>";

		if ($db->num_rows() == $config_showfull_solperpage) {
			$nav .= " | <a href=\"".$sess->url($ref);
			if ($entid > 0) {
				$parray["id"] = $entid;
			}
			$parray["cnt"] = $next_cnt;
			$parray["by"] = $by;
			$parray["enterprise"] = $enterprise;
			$parray["name"] = $name;
			$parray["description"] = $description;
			$nav .= $sess->add_query($parray)."\">".$t->translate("Next")."</a>&nbsp;&gt;";
		} else {
			$nav .= " | ".$t->translate("Next")."&nbsp;&gt;";
		}

		$bs->box_strip($nav);
	}
}
?>
