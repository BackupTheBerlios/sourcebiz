<?php

######################################################################
# SourceBiz: Open Source Business
# ================================================
#
# Copyright (c) 2001-2003 by
#                Lutz Henckel (lutz.henckel@fokus.faunhofer.de)
#
# BerliOS SourceBiz: http://sourcebiz.berlios.de
# BerliOS - The OpenSource Mediator: http://www.berlios.de
#
# Library with the functions for comments
#
# This program is free software. You can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 or later of the GPL.
#
# $Id
#
######################################################################

function cmtform($db) {
    global $sess, $bx, $t;
 	increasecnt($db->f("entid"),"cmt_cnt");
	$bx->box_begin();
	$bx->box_title($t->translate("Comment")." ".$t->translate("about")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->url("cmtins.php")."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Subject")." (128):</td><td><input type=\"TEXT\" name=\"subject_cmt\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Comment")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=7 name=\"text_cmt\" wrap=\"virtual\" maxlength=255></textarea></td></tr>\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("entid")."\">\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function cmtshow($db,$admin) {
    global $sess, $t, $bx;
 	increasecnt($db->f("entid"),"cmt_cnt");
	$bx->box_begin();
	$bx->box_title($t->translate("Comment").": ".$db->f("subject_cmt"));
	$bx->box_body_begin();
	if ($admin || $db->f("status_cmt") == 'A') {
	    echo $db->f("text_cmt")."\n";
	}
    echo "<p class=\"small\"><b>".$t->translate("about")."</b> <a href=\"".$sess->url("entbyid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$db->f("name")."</a>\n";
    $timestamp = mktimestamp($db->f("creation_cmt"));
    echo "<br><b>".$t->translate("by")." <a href=\"mailto:".$db->f("email_usr")."\">".$db->f("user_cmt")."</a> - ".timestr($timestamp)."</b>\n";
	$bx->box_body_end();
	if ($admin || $db->f("status_cmt") == 'D') {
		$bx->box_title_begin();
		if ($db->f("status_cmt") == 'D') {
			if ($admin) {
				echo "<a href=\"".$sess->url("cmtupd.php").$sess->add_query(array("id" => $db->f("cmtid")))."\">";
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
		    echo "<b>".$t->translate("Update").":&nbsp;[&nbsp;<a href=\"".$sess->url("cmtupd.php").$sess->add_query(array("id" => $db->f("cmtid")))."\">".$t->translate("Comment")."</a>&nbsp;]</b>\n";
		}
		$bx->box_title_end();
	}
	$bx->box_end();
}

function cmtmod($db) {
   global $sess, $perm, $t, $bx;
	$bx->box_begin();
	$bx->box_title($t->translate("Comment")." ".$t->translate("about")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->self_url()."\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Subject")." (128):</td><td><input type=\"TEXT\" name=\"subject_cmt\" size=40 maxlength=128 value=\"".$db->f("subject_cmt")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Comment")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=7 name=\"text_cmt\" wrap=\"virtual\" maxlength=255>".$db->f("text_cmt")."</textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Status")." :</td><td>";
	switch ($db->f("status_cmt")) {
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
	if ($db->f("status_cmt") == 'A') {
		echo "<option value=\"delete\"";
		echo ">".$t->translate("Delete")."\n";
	}
	if ($db->f("status_cmt") == 'D') {
		echo "<option value=\"undelete\"";
		echo ">".$t->translate("Undelete")."\n";
	}
	if ($perm->have_perm("admin")) {
		echo "<option value=\"erase\"";
		echo ">".$t->translate("Erase")."\n";
	}
	echo "</select></td></tr>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("cmtid")."\">\n";
    echo "<input type=\"hidden\" name=\"status_cmt\" value=\"".$db->f("status_cmt")."\">\n";
    echo "<input type=\"hidden\" name=\"creation_cmt\" value=\"".$db->f("creation_cmt")."\">\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function cmtbyentid($db,$entid) {
	global $t, $be, $auth, $perm;
	global $cnt,$prev_cnt,$next_cnt,$config_showfull_cmtperpage;

	if (!isset($cnt)) $cnt = 0;
	$prev_cnt = $cnt + $config_showfull_cmtperpage;
	if ($cnt >= $config_showfull_cmtperpage) $next_cnt = $cnt - $config_showfull_cmtperpage;
	else $next_cnt = 0;

	$query = cmtquery($entid);
	if (!$db->query($query)) {
		mysql_die($db);
	} else {
		if ($db->num_rows() > 0) {
			cmtsort($db,$entid);
			while ($db->next_record()) {
				increasecnt($db->f("entid"),"cmt_cnt");
				cmtshow($db,admin($db));
			}
			cmtnav($db,$entid);
		} else {
			$errmsg = $t->translate("Comment")." ".$t->translate("for Enterprise")." (ID: $entid) ".$t->translate("does not exist").".";
			$be->box_full($t->translate("Attention!"), $errmsg);
		}
	}
}


function cmtbycmtid($db,$cmtid) {
	global $t, $be, $auth, $perm;
	$columns = "*";
	$tables = "comments,enterprise,auth_user";
	$where = "comments.cmtid='$cmtid' AND enterprise.entid=comments.entid_cmt AND enterprise.user=auth_user.username";
	$group = "comments.cmtid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"cmt_cnt");
			cmtshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Comment")." (ID: $cmtid) ".$t->translate("does not exist").".");
		}
	}
}


function cmtidx($num) {
	global $sess, $t, $db, $bx;
    $columns = "*";
    $tables = "comments";
    $where = "comments.status_cmt='A'";
    $order = "comments.creation_cmt DESC";
    $limit = "0,".$num;
    if (!$db->query("SELECT $columns FROM $tables WHERE $where ORDER BY $order LIMIT $limit"))
    {
        mysql_die($db);
    } else {
        if ($db->num_rows() > 0) {
			$bx->box_begin();
			$bx->box_title_begin();
            echo "<center><b>".$t->translate("Comments")."</b></center></a>";
			$bx->box_title_end();
			$bx->box_body_begin();
            while($db->next_record()) {
				echo "<div class=newsind>&#149;&nbsp;";
                echo "<a href=\"".$sess->url("cmtbycmtid.php").$sess->add_query(array("id" => $db->f("cmtid")))."\">".$db->f("subject_cmt")."</a></div>\n";
            }
			$bx->box_body_end();
			$bx->box_end();
        }
    }
}


function cmtquery($entid) {
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$subject,$text,$author;
    global $auth, $logout, $bs, $config_showfull_cmtperpage;

	$columns = "*";
	$tables = "comments,enterprise,auth_user";
	switch ($by) {
	case "subject":
		$order = "ORDER BY comments.subject_cmt ASC";
		break;			
	case "filter":
		$order = "";
		if (isset($enterprise) && !empty($enterprise)) {
			$like .= "AND enterprise.name LIKE '%$enterprise%'";
		}
		if (isset($subject) && !empty($subject)) {
			$like .= "AND comments.subject_cmt LIKE '%$subject%'";
		}
		if (isset($text) && !empty($text)) {
			$like .= "AND comments.text_cmt LIKE '%$text%'";
		}
		if (isset($author) && !empty($author)) {
			$like .= "AND comments.user_cmt LIKE '%$author%'";
		}
		break;
	case "date":
	default:
		$order = "ORDER BY comments.creation_cmt DESC";
		break;
	}
	$where = "enterprise.entid=comments.entid_cmt AND enterprise.user=auth_user.username $like";
	if (!isset($auth) || empty($auth->auth["perm"]) || $logout) {
		$where .= " AND comments.status_cmt='A'";
	}
	if ($entid > 0) {
		$where = "comments.entid_cmt='$entid' AND ".$where;
	}
	$limit = $cnt.",".$config_showfull_cmtperpage;
	return "SELECT $columns FROM $tables WHERE $where $order LIMIT $limit";
}


function cmtsort($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_cmtperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$subject,$text,$author;
	if ($entid > 0) {
		$ref = "cmtbyentid.php";
	} else {
		$ref = basename($PHP_SELF);
	}
	$sort = $t->translate("Comments")." ".$t->translate("sorted by").": ";
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
		."<td><b>".$t->translate("Author")."</b></td>\n"
		."</tr><tr>\n"
		."<td><input type=\"SUBMIT\" name=\"go\" value=\"".$t->translate("Go")."\"></td>\n";
		if ($entid <= 0) {
			$filter .= "<td><input type=\"TEXT\" name=\"enterprise\" value=\"$enterprise\" size=10 maxlength=255></td>\n";
		}
		$filter .= "<td><input type=\"TEXT\" name=\"subject\" value=\"$subject\" size=10 maxlength=128></td>\n"
		."<td><input type=\"TEXT\" name=\"text\" value=\"$text\" size=10 maxlength=255></td>\n"
		."<td><input type=\"TEXT\" name=\"author\" value=\"$author\" size=10 maxlength=16></td>\n";
		if ($entid > 0) {
			$filter .= "<input type=\"hidden\" name=\"id\" value=\"$entid\">\n";
		}
		$filter .= "<input type=\"hidden\" name=\"by\" value=\"filter\">\n"
		."</form></tr></table>\n";
		$bs->box_strip($filter);
	}
}


function cmtnav($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_cmtperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$subject,$text,$author;
	if ($db->num_rows() > 0 && ($cnt > 0 || $db->num_rows() == $config_showfull_cmtperpage)) {
		if ($entid > 0) {
			$ref = "cmtbyentid.php";
		} else {
			$ref = basename($PHP_SELF);
		}
		if ($db->num_rows() == $config_showfull_cmtperpage) {
			$nav = "&lt;&nbsp;<a href=\"".$sess->url($ref);
			if ($entid > 0) {
				$parray["id"] = $entid;
			}
			$parray["cnt"] = $prev_cnt;
			$parray["by"] = $by;
			$parray["enterprise"] = $enterprise;
			$parray["subject"] = $subject;
			$parray["text"] = $text;
			$parray["author"] = $author;
			$nav .= $sess->add_query($parray)."\">".$t->translate("Previous")."</a>";
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
		$tarray["author"] = $author;
		$nav .= $sess->add_query($tarray)."\">".$t->translate("Top")."</a>";

		if ($cnt > 0) {
			$nav .= " | <a href=\"".$sess->url($ref);
			if ($entid > 0) {
				$narray["id"] = $entid;
			}
			$narray["cnt"] = $next_cnt;
			$narray["by"] = $by;
			$narray["enterprise"] = $enterprise;
			$narray["subject"] = $subject;
			$narray["text"] = $text;
			$narray["author"] = $author;
			$nav .= $sess->add_query($narray)."\">".$t->translate("Next")."</a>&nbsp;&gt;";
		} else {
			$nav .= " | ".$t->translate("Next")."&nbsp;&gt;";
		}
		$bs->box_strip($nav);
	}
}
?>
