<?php

function proform($db) {
    global $sess, $bx, $t;
	$bx->box_begin();
	$bx->box_title($t->translate("Product")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->url("proins.php")."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Name")." (128):</td><td><input type=\"TEXT\" name=\"name_pro\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Category")." (64):</td>\n";
    echo "<td><select name=\"category_pro\">\n";
    select_cat("Products","");
    echo "</select></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Description")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"description_pro\" wrap=\"virtual\"></textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_pro\" size=40 maxlength=255></td></tr>\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("entid")."\">\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function proshow($db,$admin) {
    global $sess, $t, $bx;
 	increasecnt($db->f("entid"),"pro_cnt");
	$bx->box_begin();
	$bx->box_title($t->translate("Product").": ".$db->f("name_pro"));
	$bx->box_body_begin();
	if ($admin || $db->f("status_pro") == 'A') {
    	echo "<p>".$db->f("description_pro")."\n";
		$homepage_pro = $db->f("homepage_pro");
    	echo "<p><b>".$t->translate("Category").":</b> ".$db->f("category_pro")."\n";
		if (!empty($homepage_pro)) {
			echo "<br><b>".$t->translate("Information").":</b> <a href=\"".$db->f("homepage_pro")."\" target=_blank>".$db->f("homepage_pro")."</a>\n";
		}
	}
    echo "<p class=\"small\"><b>".$t->translate("of")."</b> <a href=\"".$sess->url("entbyid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$db->f("name")."</a>\n";
    $timestamp = mktimestamp($db->f("modification_pro"));
    echo "<br><b>".timestr($timestamp)."</b>\n";
	$bx->box_body_end();
	if ($admin || $db->f("status_pro") == 'D') {
		$bx->box_title_begin();
		if ($db->f("status_pro") == 'D') {
			if ($admin) {
				echo "<a href=\"".$sess->url("proupd.php").$sess->add_query(array("id" => $db->f("proid")))."\">";
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
		    echo "<b>".$t->translate("Update").":&nbsp;[&nbsp;<a href=\"".$sess->url("proupd.php").$sess->add_query(array("id" => $db->f("proid")))."\">".$t->translate("Product")."</a>&nbsp;]</b>\n";
		}
		$bx->box_title_end();
	}
	$bx->box_end();
}

function promod($db) {
   global $sess, $perm, $t, $bx;
	$bx->box_begin();
	$bx->box_title($t->translate("Product")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->self_url()."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Name")." (128):</td><td><input type=\"TEXT\" name=\"name_pro\" size=40 maxlength=128 value=\"".$db->f("name_pro")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Category")." (64):</td>\n";
    echo "<td><select name=\"category_pro\">\n";
    select_cat("Products",$db->f("category_pro"));
    echo "</select></td></tr>\n";
     echo "<tr><td align=right>".$t->translate("Description")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"description_pro\" wrap=\"virtual\">".$db->f("description_pro")."</textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_pro\" size=40 maxlength=255 value=\"".$db->f("homepage_pro")."\">&nbsp;[<a href=\"".$db->f("homepage_pro")."\" target=\"_blank\">".$t->translate("Check")."</a>]</td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Status")." :</td><td>";
	switch ($db->f("status_pro")) {
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
	if ($db->f("status_pro") == 'A') {
		echo "<option value=\"delete\"";
		echo ">".$t->translate("Delete")."\n";
	}
	if ($db->f("status_pro") == 'D') {
		echo "<option value=\"undelete\"";
		echo ">".$t->translate("Undelete")."\n";
	}
	if ($perm->have_perm("admin")) {
		echo "<option value=\"erase\"";
		echo ">".$t->translate("Erase")."\n";
	}
	echo "</select></td></tr>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("proid")."\">\n";
    echo "<input type=\"hidden\" name=\"status_pro\" value=\"".$db->f("status_pro")."\">\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function probyentid($db,$entid) {
	global $t, $be, $auth, $perm;
	global $cnt,$prev_cnt,$next_cnt,$config_showfull_properpage;

	if (!isset($cnt)) $cnt = 0;
	$prev_cnt = $cnt + $config_showfull_properpage;
	if ($cnt >= $config_showfull_properpage) $next_cnt = $cnt - $config_showfull_properpage;
	else $next_cnt = 0;

	$query = proquery($entid);
	if (!$db->query($query)) {
		mysql_die($db);
	} else {
		if ($db->num_rows() > 0) {
			prosort($db,$entid);
			while ($db->next_record()) {
				increasecnt($db->f("entid"),"pro_cnt");
				proshow($db,admin($db));
			}
			pronav($db,$entid);
		} else {
			$errmsg = $t->translate("Product")." ".$t->translate("for Enterprise")." (ID: $entid) ".$t->translate("does not exist").".";
			$be->box_full($t->translate("Attention!"), $errmsg);
		}
	}
}


function probyproid($db,$proid) {
	global $t, $be, $auth, $perm;
	$columns = "*";
	$tables = "products,enterprise";
	$where = "products.proid='$proid' AND enterprise.entid=products.entid_pro";
	$group = "products.proid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"pro_cnt");
			proshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Product")." (ID: $proid) ".$t->translate("does not exist").".");
		}
	}
}


function proidx($num) {
	global $sess, $t, $db, $bx;

    $tables = "products";
    $where = "products.status_pro='A'";

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
            echo "<center><b>".$t->translate("Products")."</b></center></a>";
			$bx->box_title_end();
			$bx->box_body_begin();
            while($db->next_record()) {
				echo "<div class=newsind>&#149;&nbsp;";
                echo "<a href=\"".$sess->url("probyproid.php").$sess->add_query(array("id" => $db->f("proid")))."\">".$db->f("name_pro")."</a> (".$db->f("category_pro").")</div>\n";
            }
			$bx->box_body_end();
			$bx->box_end();
        }
    }
}


function proquery($entid) {
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$category,$description;
    global $auth, $logout, $bs, $config_showfull_properpage;
	$columns = "*";
	$tables = "products,enterprise";
	$like = "";
	switch ($by) {
	case "name":
		$order = "ORDER BY products.name_pro ASC";
		break;			
	case "filter":
		$order = "";
		if (isset($enterprise) && !empty($enterprise)) {
			$like .= "AND enterprise.name LIKE '%$enterprise%'";
		}
		if (isset($name) && !empty($name)) {
			$like .= "AND products.name_pro LIKE '%$name%'";
		}
		if (isset($category) && !empty($category)) {
			$like .= "AND products.category_pro LIKE '$category'";
		}
		if (isset($description) && !empty($description)) {
			$like .= "AND products.description_pro LIKE '%$description%'";
		}
		break;
	case "date":
	default:
		$order = "ORDER BY products.modification_pro DESC";
		break;
	}
	$where = "enterprise.entid = products.entid_pro $like";
	if (!isset($auth) || empty($auth->auth["perm"]) || $logout) {
		$where .= " AND products.status_pro='A'";
	}
	if ($entid > 0) {
		$where = "products.entid_pro='$entid' AND ".$where;
	}
	$limit = $cnt.",".$config_showfull_properpage;
	return "SELECT $columns FROM $tables WHERE $where $order LIMIT $limit";
}


function prosort($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_properpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$category,$description;
	if ($entid > 0) {
		$ref = "probyentid.php";
	} else {
		$ref = basename($PHP_SELF);
	}
	$sort = $t->translate("Products")." ".$t->translate("sorted by").": ";
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
		."<td><b>".$t->translate("Category")."</b></td>\n"
		."<td><b>".$t->translate("Description")."</b></td>\n"
		."</tr><tr>\n"
		."<td><input type=\"SUBMIT\" name=\"go\" value=\"".$t->translate("Go")."\"></td>\n";
		if ($entid <= 0) {
			$filter .= "<td><input type=\"TEXT\" name=\"enterprise\" value=\"$enterprise\" size=10 maxlength=255></td>\n";
		}
		$filter .= "<td><input type=\"TEXT\" name=\"name\" value=\"$name\" size=10 maxlength=255></td>\n"
		."<td><select name=\"category\">\n"
		."<option value=\"\">".$t->translate("All")."\n"
		.select_form('products','category_pro',$category)
		."</select></td>\n"
		."<td><input type=\"TEXT\" name=\"description\" value=\"$description\" size=10 maxlength=255></td>\n";
		if ($entid > 0) {
			$filter .= "<input type=\"hidden\" name=\"id\" value=\"$entid\">\n";
		}
		$filter .= "<input type=\"hidden\" name=\"by\" value=\"filter\">\n"
		."</form></tr></table>\n";
		$bs->box_strip($filter);
	}
}


function pronav($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_properpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$category,$description;
	if ($db->num_rows() > 0 && ($cnt > 0 || $db->num_rows() == $config_showfull_properpage)) {
		if ($entid > 0) {
			$ref = "probyentid.php";
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
			$narray["category"] = $category;
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
		$tarray["category"] = $category;
		$tarray["description"] = $description;
		$nav .= $sess->add_query($tarray)."\">".$t->translate("Top")."</a>";

		if ($db->num_rows() == $config_showfull_properpage) {
			$nav .= " | <a href=\"".$sess->url($ref);
			if ($entid > 0) {
				$parray["id"] = $entid;
			}
			$parray["cnt"] = $next_cnt;
			$parray["by"] = $by;
			$parray["enterprise"] = $enterprise;
			$parray["name"] = $name;
			$parray["category"] = $category;
			$parray["description"] = $description;
			$nav .= $sess->add_query($parray)."\">".$t->translate("Next")."</a>&nbsp;&gt;";
		} else {
			$nav .= " | ".$t->translate("Next")."&nbsp;&gt;";
		}

		$bs->box_strip($nav);
	}
}
?>
