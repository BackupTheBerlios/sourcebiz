<?php

function cusform($db) {
    global $sess, $bx, $t;
	$bx->box_begin();
	$bx->box_title($t->translate("Customer")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->url("cusins.php")."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Name")." (128):</td><td><input type=\"TEXT\" name=\"name_cus\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Description")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"description_cus\" wrap=\"virtual\"></textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_cus\" size=40 maxlength=255></td></tr>\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("entid")."\">\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function cusshow($db,$admin) {
    global $sess, $t, $bx;
 	increasecnt($db->f("entid"),"cus_cnt");
	$bx->box_begin();
	$bx->box_title($t->translate("Customer").": ".$db->f("name_cus"));
	$bx->box_body_begin();
	if ($admin || $db->f("status_cus") == 'A') {
    	echo "<p>".$db->f("description_cus")."\n";
		$homepage_cus = $db->f("homepage_cus");
		if (!empty($homepage_cus)) {
			echo "<p><b>".$t->translate("Homepage").":</b> <a href=\"".$db->f("homepage_cus")."\" target=_blank>".$db->f("homepage_cus")."</a>\n";
		}
	}
    echo "<p class=\"small\"><b>".$t->translate("of")."</b> <a href=\"".$sess->url("entbyid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$db->f("name")."</a>\n";
    $timestamp = mktimestamp($db->f("modification_cus"));
    echo "<br><b>".timestr($timestamp)."</b>\n";
	$bx->box_body_end();
	if ($admin || $db->f("status_cus") == 'D') {
		$bx->box_title_begin();
		if ($db->f("status_cus") == 'D') {
			if ($admin) {
				echo "<a href=\"".$sess->url("cusupd.php").$sess->add_query(array("id" => $db->f("cusid")))."\">";
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
		    echo "<b>".$t->translate("Update").":&nbsp;[&nbsp;<a href=\"".$sess->url("cusupd.php").$sess->add_query(array("id" => $db->f("cusid")))."\">".$t->translate("Customer")."</a>&nbsp;]</b>\n";
		}
		$bx->box_title_end();
	}
	$bx->box_end();
}

function cusmod($db) {
   global $sess, $perm, $t, $bx;
	$bx->box_begin();
	$bx->box_title($t->translate("Customer")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->self_url()."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Name")." (128):</td><td><input type=\"TEXT\" name=\"name_cus\" size=40 maxlength=128 value=\"".$db->f("name_cus")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Description")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"description_cus\" wrap=\"virtual\">".$db->f("description_cus")."</textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_cus\" size=40 maxlength=255 value=\"".$db->f("homepage_cus")."\">&nbsp;[<a href=\"".$db->f("homepage_cus")."\" target=\"_blank\">".$t->translate("Check")."</a>]</td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Status")." :</td><td>";
	switch ($db->f("status_cus")) {
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
	if ($db->f("status_cus") == 'A') {
		echo "<option value=\"delete\"";
		echo ">".$t->translate("Delete")."\n";
	}
	if ($db->f("status_cus") == 'D') {
		echo "<option value=\"undelete\"";
		echo ">".$t->translate("Undelete")."\n";
	}
	if ($perm->have_perm("admin")) {
		echo "<option value=\"erase\"";
		echo ">".$t->translate("Erase")."\n";
	}
	echo "</select></td></tr>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("cusid")."\">\n";
    echo "<input type=\"hidden\" name=\"status_cus\" value=\"".$db->f("status_cus")."\">\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function cusbyentid($db,$entid) {
	global $t, $be, $auth, $perm;
	global $cnt,$prev_cnt,$next_cnt,$config_showfull_cusperpage;

	if (!isset($cnt)) $cnt = 0;
	$prev_cnt = $cnt + $config_showfull_cusperpage;
	if ($cnt >= $config_showfull_cusperpage) $next_cnt = $cnt - $config_showfull_cusperpage;
	else $next_cnt = 0;

	$query = cusquery($entid);
	if (!$db->query($query)) {
		mysql_die($db);
	} else {
		if ($db->num_rows() > 0) {
			cussort($db,$entid);
			while ($db->next_record()) {
				increasecnt($db->f("entid"),"cus_cnt");
				cusshow($db,admin($db));
			}
			cusnav($db,$entid);
		} else {
			$errmsg = $t->translate("Customer")." ".$t->translate("for Enterprise")." (ID: $entid) ".$t->translate("does not exist").".";
			$be->box_full($t->translate("Attention!"), $errmsg);
		}
	}
}


function cusbycusid($db,$cusid) {
	global $t, $be, $auth, $perm;
	$columns = "*";
	$tables = "customers,enterprise";
	$where = "customers.cusid='$cusid' AND enterprise.entid=customers.entid_cus";
	$group = "customers.cusid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"cus_cnt");
			cusshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Customer")." (ID: $cusid) ".$t->translate("does not exist").".");
		}
	}
}


function cusidx($num) {
	global $sess, $t, $db, $bx;

    $tables = "customers";
    $where = "customers.status_cus='A'";

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
            echo "<center><b>".$t->translate("Customers")."</b></center></a>";
			$bx->box_title_end();
			$bx->box_body_begin();
            while($db->next_record()) {
				echo "<div class=newsind>&#149;&nbsp;";
                echo "<a href=\"".$sess->url("cusbycusid.php").$sess->add_query(array("id" => $db->f("cusid")))."\">".$db->f("name_cus")."</a></div>\n";
            }
			$bx->box_body_end();
			$bx->box_end();
        }
    }
}


function cusquery($entid) {
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$description;
    global $auth, $logout, $bs, $config_showfull_cusperpage;
	$columns = "*";
	$tables = "customers,enterprise";
	$like = "";
	switch ($by) {
	case "name":
		$order = "ORDER BY customers.name_cus ASC";
		break;			
	case "filter":
		$order = "";
		if (isset($enterprise) && !empty($enterprise)) {
			$like .= "AND enterprise.name LIKE '%$enterprise%'";
		}
		if (isset($name) && !empty($name)) {
			$like .= "AND customers.name_cus LIKE '%$name%'";
		}
		if (isset($description) && !empty($description)) {
			$like .= "AND customers.description_cus LIKE '%$description%'";
		}
		break;
	case "date":
	default:
		$order = "ORDER BY customers.modification_cus DESC";
		break;
	}
	$where = "enterprise.entid = customers.entid_cus $like";
	if (!isset($auth) || empty($auth->auth["perm"]) || $logout) {
		$where .= " AND customers.status_cus='A'";
	}
	if ($entid > 0) {
		$where = "customers.entid_cus='$entid' AND ".$where;
	}
	$limit = $cnt.",".$config_showfull_cusperpage;
	return "SELECT $columns FROM $tables WHERE $where $order LIMIT $limit";
}


function cussort($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_cusperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$description;
	if ($entid > 0) {
		$ref = "cusbyentid.php";
	} else {
		$ref = basename($PHP_SELF);
	}
	$sort = $t->translate("Customers")." ".$t->translate("sorted by").": ";
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


function cusnav($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_cusperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$description;
	if ($db->num_rows() > 0 && ($cnt > 0 || $db->num_rows() == $config_showfull_cusperpage)) {
		if ($entid > 0) {
			$ref = "cusbyentid.php";
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

		if ($db->num_rows() == $config_showfull_cusperpage) {
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
