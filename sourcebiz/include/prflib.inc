<?php

function prfform($db) {
    global $sess, $bx, $t;
	$bx->box_begin();
	$bx->box_title($t->translate("Profile")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->url("prfins.php")."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Profile")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"profile_prf\" wrap=\"virtual\"></textarea></td></tr>\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("entid")."\">\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function prfshow($db,$admin) {
    global $sess, $t, $bx, $be;
 	increasecnt($db->f("entid"),"prf_cnt");
	$bx->box_begin();
	$bx->box_title($t->translate("Profile"));
	$bx->box_body_begin();
	if ($admin || $db->f("status_prf") == 'A') {
	    echo "<p>".$db->f("profile_prf")."\n";
	}
    $timestamp = mktimestamp($db->f("modification_prf"));
    echo "<p><b>".timestr($timestamp)."</b>\n";
	$bx->box_body_end();
	if ($admin || $db->f("status_prf") == 'D') {
		$bx->box_title_begin();
		if ($db->f("status_prf") == 'D') {
			if ($admin) {
				echo "<a href=\"".$sess->url("prfupd.php").$sess->add_query(array("id" => $db->f("prfid")))."\">";
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
		    echo "<b>".$t->translate("Update").":&nbsp;[&nbsp;<a href=\"".$sess->url("prfupd.php").$sess->add_query(array("id" => $db->f("prfid")))."\">".$t->translate("Profile")."</a>&nbsp;]</b>\n";
		}
		$bx->box_title_end();
	}
	$bx->box_end();
}

function prfmod($db) {
   global $sess, $perm, $t, $bx;
	$bx->box_begin();
	$bx->box_title($t->translate("Profile of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->url("prfupd.php")."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Profile")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"profile_prf\" wrap=\"virtual\">".$db->f("profile_prf")."</textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Status")." :</td><td>";
	switch ($db->f("status_prf")) {
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
	if ($db->f("status_prf") == 'A') {
		echo "<option value=\"delete\"";
		echo ">".$t->translate("Delete")."\n";
	}
	if ($db->f("status_prf") == 'D') {
		echo "<option value=\"undelete\"";
		echo ">".$t->translate("Undelete")."\n";
	}
	if ($perm->have_perm("admin")) {
		echo "<option value=\"erase\"";
		echo ">".$t->translate("Erase")."\n";
	}
	echo "</select></td></tr>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("prfid")."\">\n";
    echo "<input type=\"hidden\" name=\"status_prf\" value=\"".$db->f("status_prf")."\">\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function prfbyentid($db,$entid) {
	global $t, $be, $auth, $perm;
	$columns = "*";
	$tables = "profile,enterprise";
	$where = "entid_prf='$entid' AND enterprise.entid = profile.entid_prf";
	$order = "modification_prf DESC";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where ORDER BY $order")) {
		mysql_die($db);
	} else {
		if ($db->num_rows() > 0) {
			while ($db->next_record()) {
				increasecnt($db->f("entid"),"prf_cnt");
				prfshow($db,admin($db));
			}
		} else {
			$errmsg = $t->translate("Profile")." ".$t->translate("for Enterprise")." (ID: $entid) ".$t->translate("does not exist").".";
			$be->box_full($t->translate("Attention!"), $errmsg);
		}
	}
}


function prfbyprfid($db,$prfid) {
	global $t, $be, $auth, $perm;
	$columns = "*,SUM(ent_cnt+homepage_cnt+prf_cnt+con_cnt+svc_cnt+pro_cnt+sol_cnt+cus_cnt+new_cnt+cmt_cnt) AS sum_cnt";
	$tables = "profile,enterprise,counter";
	$where = "profile.prfid='$prfid' AND enterprise.entid=profile.entid_prf AND profile.entid_prf=counter.entid";
	$group = "profile.prfid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"prf_cnt");
			prfshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Profile")." (ID: $prfid) ".$t->translate("does not exist").".");
		}
	}
}

?>
