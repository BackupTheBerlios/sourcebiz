<?php

function conform($db) {
    global $sess, $db, $bx, $t;
	$bx->box_begin();
	$bx->box_title($t->translate("Contact")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->url("conins.php")."\" ENCTYPE=\"multipart/form-data\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Name")." (255):</td><td><input type=\"TEXT\" name=\"name_con\" value=\"".$db->f("name")."\" size=40 maxlength=255></td></tr>\n";
	echo "<tr><td align=right>".$t->translate("Logofile")." (*):</td><td><input type=\"hidden\" name=\"MAX_FILE_SIZE\" value=\"100000\">\n";
	echo "<input name=\"logo_con\" type=\"file\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Type")." (64):</td>\n";
    echo "<td><select name=\"type_con\">\n";
    select_cat("Contact","");
    echo "</select></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Description")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"description_con\" wrap=\"virtual\"></textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Address")." (255):</td><td><input type=\"TEXT\" name=\"address_con\" size=40 maxlength=255></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Country")." (128):</td><td><input type=\"TEXT\" name=\"country_con\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("State")." (128):</td><td><input type=\"TEXT\" name=\"state_con\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("City")." (128):</td><td><input type=\"TEXT\" name=\"city_con\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("ZIP")." (16):</td><td><input type=\"TEXT\" name=\"zip_con\" size=40 maxlength=16></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Phone")." (128):</td><td><input type=\"TEXT\" name=\"phone_con\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Fax")." (128):</td><td><input type=\"TEXT\" name=\"fax_con\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Email")." (128):</td><td><input type=\"TEXT\" name=\"email_con\" size=40 maxlength=128></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_con\" size=40 maxlength=255></td></tr>\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("entid")."\">\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function conshow($db,$admin) {
    global $sess, $t, $bx;
	global $sys_logo_url, $sys_logo_dir, $config_maxwidth;

 	increasecnt($db->f("entid"),"con_cnt");
	$bx->box_begin();
	$bx->box_title($t->translate("Contact"));
	$bx->box_body_begin();
	$logo = $db->f("logo_con");
    if (!empty($logo) && ($admin || $db->f("status") == 'A')) {
		$logourl = $sys_logo_url.$db->f("conid")."con_".rawurlencode(basename($logo));
		$logodir = $sys_logo_dir.$db->f("conid")."con_".basename($logo);
		$size = GetImageSize($logodir);
		$width = $size[0];
		$height = $size[1];
		if ($width > $config_maxwidth) {
			$height = $height / $width * $config_maxwidth; 
			$width = $config_maxwidth;
		}
    	echo "<a href=\"".$sess->url("redirect.php").$sess->add_query(array("id" => $db->f("entid"),"type" => "homepage_cnt","url" => $db->f("homepage_con")))."\" target=_blank><img src=\"".$logourl."\" width=\"".$width."\" height=\"".$height."\" border=\"0\"></a>\n";
	}
    echo "<p><b><a href=\"".$sess->url("redirect.php").$sess->add_query(array("id" => $db->f("entid"),"type" => "homepage_cnt","url" => $db->f("homepage_con")))."\" target=_blank>".$db->f("name_con")."</a></b>\n";
	if ($admin || $db->f("status_con") == 'A') {
	    echo "<table border=0 cellspacing=1 cellpadding=3 bgcolor=".$GLOBALS["th_box_body_bgcolor"].">\n";
		$type_con = $db->f("type_con");
		if (!empty($type_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("Type").":</b></td><td>".$db->f("type_con")."</td></tr>\n";
		}
		$description_con = $db->f("description_con");
		if (!empty($description_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("Description").":</b></td><td>".$db->f("description_con")."</td></tr>\n";
    	}
		$address_con = $db->f("address_con");
		if (!empty($address_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("Address").":</b></td><td>".$db->f("address_con")."</td></tr>\n";
    	}
		$country_con = $db->f("country_con");
		if (!empty($country_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("Country").":</b></td><td>".$db->f("country_con")."</td></tr>\n";
    	}
		$state_con = $db->f("state_con");
		if (!empty($state_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("State").":</b></td><td>".$db->f("state_con")."</td></tr>\n";
    	}
		$city_con = $db->f("city_con");
		if (!empty($city_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("City").":</b></td><td>".$db->f("city_con")."</td></tr>\n";
    	}
		$zip_con = $db->f("zip_con");
		if (!empty($zip_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("ZIP").":</b></td><td>".$db->f("zip_con")."</td></tr>\n";
    	}
		$phone_con = $db->f("phone_con");
		if (!empty($phone_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("Phone").":</b></td><td>".$db->f("phone_con")."</td></tr>\n";
    	}
		$fax_con = $db->f("fax_con");
		if (!empty($fax_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("Fax").":</b></td><td>".$db->f("fax_con")."</td></tr>\n";
    	}
		$email_con = $db->f("email_con");
		if (!empty($email_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("Email").":</b></td><td>&lt;<a href=\"mailto:".$db->f("email_con")."\">".ereg_replace("@"," at ",htmlentities($db->f("email_con")))."</a>&gt;</td></tr>\n";
		}
		$homepage_con = $db->f("homepage_con");
		if (!empty($homepage_con)) {
    		echo "<tr valign=top><td align=right><b>".$t->translate("Homepage").":</b></td><td>&lt;<a href=\"".$sess->url("redirect.php").$sess->add_query(array("id" => $db->f("entid"),"type" => "homepage_cnt","url" => $db->f("homepage_con")))."\" target=_blank>".$db->f("homepage_con")."</a>&gt;</td></tr>\n";
		}
	    echo "</table>\n";
	}
    echo "<p class=\"small\"><b>".$t->translate("of")."</b> <a href=\"".$sess->url("entbyid.php").$sess->add_query(array("id" => $db->f("entid")))."\">".$db->f("name")."</a>\n";
    $timestamp = mktimestamp($db->f("modification_con"));
    echo "<br><b>".timestr($timestamp)."</b>\n";
	$bx->box_body_end();
	if ($admin || $db->f("status_con") == 'D') {
		$bx->box_title_begin();
		if ($db->f("status_con") == 'D') {
			if ($admin) {
				echo "<a href=\"".$sess->url("conupd.php").$sess->add_query(array("id" => $db->f("conid")))."\">";
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
		    echo "<b>".$t->translate("Update").":&nbsp;[&nbsp;<a href=\"".$sess->url("conupd.php").$sess->add_query(array("id" => $db->f("conid")))."\">".$t->translate("Contact")."</a>&nbsp;]</b>\n";
		}
		$bx->box_title_end();
	}
	$bx->box_end();
}

function conmod($db) {
   global $sess, $perm, $t, $bx;
	$bx->box_begin();
	$bx->box_title($t->translate("Contact")." ".$t->translate("of")." \"".$db->f("name")."\"");
	$bx->box_body_begin();
    echo "<form action=\"".$sess->self_url()."\" ENCTYPE=\"multipart/form-data\" method=\"POST\">\n";
    echo "<table border=0 align=center cellspacing=0 cellpadding=3>\n";
    echo "<tr><td align=right>".$t->translate("Name")." (255):</td><td><input type=\"TEXT\" name=\"name_con\" size=40 maxlength=255 value=\"".$db->f("name_con")."\"></td></tr>\n";
	$logo_con = $db->f("logo_con");
    echo "<input type=\"hidden\" name=\"clogo_con\" value=\"$logo_con\">\n";
	if (!empty($logo_con)) {
		echo "<tr><td align=right valign=top>".$t->translate("Current Logofile").":</td><td>$logo_con\n";
		echo "<br><input type=radio name=\"logoact\" value=\"keep\" checked> ".$t->translate("Keep")."\n";
		echo "<input type=radio name=\"logoact\" value=\"new\"> ".$t->translate("New")."\n";
		echo "<input type=radio name=\"logoact\" value=\"delete\"> ".$t->translate("Delete")."\n";
		echo "<td></tr>\n";
	} else {
	    echo "<input type=\"hidden\" name=\"logoact\" value=\"new\">\n";
	}
	echo "<tr><td align=right>".$t->translate("Logofile")." (*):</td><td><input type=\"hidden\" name=\"MAX_FILE_SIZE\" value=\"100000\">\n";
	echo "<input name=\"logo_con\" type=\"file\" value=\"$logo_con\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Type")." (64):</td>\n";
    echo "<td><select name=\"type_con\">\n";
    select_cat("Contact",$db->f("type_con"));
    echo "</select></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Description")." (*):<br>".$t->translate("Use HTML for layout")."</td>\n";
	echo "<td><textarea cols=40 rows=20 name=\"description_con\" wrap=\"virtual\">".$db->f("description_con")."</textarea></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Address")." (255):</td><td><input type=\"TEXT\" name=\"address_con\" size=40 maxlength=255 value=\"".$db->f("address_con")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Country")." (128):</td><td><input type=\"TEXT\" name=\"country_con\" size=40 maxlength=128 value=\"".$db->f("country_con")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("State")." (128):</td><td><input type=\"TEXT\" name=\"state_con\" size=40 maxlength=128 value=\"".$db->f("state_con")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("City")." (128):</td><td><input type=\"TEXT\" name=\"city_con\" size=40 maxlength=128 value=\"".$db->f("city_con")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("ZIP")." (16):</td><td><input type=\"TEXT\" name=\"zip_con\" size=40 maxlength=16 value=\"".$db->f("zip_con")."\"</td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Phone")." (128):</td><td><input type=\"TEXT\" name=\"phone_con\" size=40 maxlength=128 value=\"".$db->f("phone_con")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Fax")." (128):</td><td><input type=\"TEXT\" name=\"fax_con\" size=40 maxlength=128 value=\"".$db->f("fax_con")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Email")." (128):</td><td><input type=\"TEXT\" name=\"email_con\" size=40 maxlength=128 value=\"".$db->f("email_con")."\"></td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Homepage")." (255):</td><td><input type=\"TEXT\" name=\"homepage_con\" size=40 maxlength=255 value=\"".$db->f("homepage_con")."\">&nbsp;[<a href=\"".$db->f("homepage_con")."\" target=\"_blank\">".$t->translate("Check")."</a>]</td></tr>\n";
    echo "<tr><td align=right>".$t->translate("Status")." :</td><td>";
	switch ($db->f("status_con")) {
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
	if ($db->f("status_con") == 'A') {
		echo "<option value=\"delete\"";
		echo ">".$t->translate("Delete")."\n";
	}
	if ($db->f("status_con") == 'D') {
		echo "<option value=\"undelete\"";
		echo ">".$t->translate("Undelete")."\n";
	}
	if ($perm->have_perm("admin")) {
		echo "<option value=\"erase\"";
		echo ">".$t->translate("Erase")."\n";
	}
	echo "</select></td></tr>\n";
    echo "<input type=\"hidden\" name=\"id\" value=\"".$db->f("conid")."\">\n";
    echo "<input type=\"hidden\" name=\"status_con\" value=\"".$db->f("status_con")."\">\n";
    echo "<tr><td align=right>&nbsp;</td><td><input type=\"Submit\" value=\"".$t->translate("Go")."\"></td>\n";
    echo "</form>\n";
    echo "</tr></table>\n";
	$bx->box_body_end();
	$bx->box_end();
}


function conbyentid($db,$entid) {
	global $t, $be, $auth, $perm;
	global $cnt,$prev_cnt,$next_cnt,$config_showfull_conperpage;

	if (!isset($cnt)) $cnt = 0;
	$prev_cnt = $cnt + $config_showfull_conperpage;
	if ($cnt >= $config_showfull_conperpage) $next_cnt = $cnt - $config_showfull_conperpage;
	else $next_cnt = 0;

	$query = conquery($entid);
	if (!$db->query($query)) {
		mysql_die($db);
	} else {
		if ($db->num_rows() > 0) {
			consort($db,$entid);
			while ($db->next_record()) {
				increasecnt($db->f("entid"),"con_cnt");
				conshow($db,admin($db));
			}
			connav($db,$entid);
		} else {
			$errmsg = $t->translate("Contact")." ".$t->translate("for Enterprise")." (ID: $entid) ".$t->translate("does not exist").".";
			$be->box_full($t->translate("Attention!"), $errmsg);
		}
	}
}


function conbyconid($db,$conid) {
	global $t, $be, $auth, $perm;
	$columns = "*";
	$tables = "contact,enterprise";
	$where = "contact.conid='$conid' AND enterprise.entid=contact.entid_con";
	$group = "contact.conid";
	if (!$db->query("SELECT $columns FROM $tables WHERE $where GROUP BY $group")) {
		mysql_die($db);
	} else {
		if ($db->next_record()) {
			increasecnt($db->f("entid"),"con_cnt");
			conshow($db,admin($db));
		} else {
			$be->box_full($t->translate("Error"), $t->translate("Contact")." (ID: $conid) ".$t->translate("does not exist").".");
		}
	}
}


function conidx($num) {
	global $sess, $t, $db, $bx;

    $tables = "contact";
    $where = "contact.status_con='A'";

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
            echo "<center><b>".$t->translate("Contacts")."</b></center></a>";
			$bx->box_title_end();
			$bx->box_body_begin();
            while($db->next_record()) {
				echo "<div class=newsind>&#149;&nbsp;";
                echo "<a href=\"".$sess->url("conbyconid.php").$sess->add_query(array("id" => $db->f("conid")))."\">".$db->f("name_con")."</a> (".$db->f("type_con").")</div>\n";
            }
			$bx->box_body_end();
			$bx->box_end();
        }
    }
}


function conquery($entid) {
    global $by,$cnt,$enterprise,$name,$type,$country,$state,$city,$zip;
    global $auth, $logout, $bs, $config_showfull_conperpage;
	$columns = "*";
	$tables = "contact,enterprise";
	$like = "";
	switch ($by) {
	case "name":
		$order = "ORDER BY contact.name_con ASC";
		break;			
	case "filter":
		$order = "";
		if (isset($enterprise) && !empty($enterprise)) {
			$like .= "AND enterprise.name LIKE '%$enterprise%'";
		}
		if (isset($name) && !empty($name)) {
			$like .= "AND contact.name_con LIKE '%$name%'";
		}
		if (isset($type) && !empty($type)) {
			$like .= "AND contact.type_con LIKE '$type'";
		}
		if (isset($country) && !empty($country)) {
			$like .= "AND contact.country_con LIKE '$country'";
		}
		if (isset($state) && !empty($state)) {
			$like .= "AND contact.state_con LIKE '$state'";
		}
		if (isset($city) && !empty($city)) {
			$like .= "AND contact.city_con LIKE '$city'";
		}
		if (isset($zip) && !empty($zip)) {
			$like .= "AND contact.zip_con LIKE '%$zip%'";
		}
		break;			
	case "date":
	default:
		$order = "ORDER BY contact.modification_con DESC";
		break;
	}
	$where = "enterprise.entid = contact.entid_con $like";
	if (!isset($auth) || empty($auth->auth["perm"]) || $logout) {
		$where .= " AND contact.status_con='A'";
	}
	if ($entid > 0) {
		$where = "contact.entid_con='$entid' AND ".$where;
	}
	$limit = $cnt.",".$config_showfull_conperpage;
	return "SELECT $columns FROM $tables WHERE $where $order LIMIT $limit";
}


function consort($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_conperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$type,$country,$state,$city,$zip;
	if ($entid > 0) {
		$ref = "conbyentid.php";
	} else {
		$ref = basename($PHP_SELF);
	}
	$sort = $t->translate("Contacts")." ".$t->translate("sorted by").": ";
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
		."<td><b>".$t->translate("Type")."</b></td>\n"
		."<td><b>".$t->translate("Country")."</b></td>\n"
		."</tr><tr>\n"
		."<td><input type=\"SUBMIT\" name=\"go\" value=\"".$t->translate("Go")."\"></td>\n";
		if ($entid <= 0) {
			$filter .= "<td><input type=\"TEXT\" name=\"enterprise\" value=\"$enterprise\" size=10 maxlength=255></td>\n";
		}
		$filter .= "<td><input type=\"TEXT\" name=\"name\" value=\"$name\" size=10 maxlength=255></td>\n"
		."<td><select name=\"type\">\n"
		."<option value=\"\">".$t->translate("All")."\n"
		.select_form('contact','type_con',$type)
		."</select></td>\n"
		."<td><select name=\"country\">\n"
		."<option value=\"\">".$t->translate("All")."\n"
		.select_form('contact','country_con',$country)
		."</select></td></tr>\n"
		."<tr><td></td>\n"
		."<td><b>".$t->translate("State")."</b></td>\n"
		."<td><b>".$t->translate("City")."</b></td>\n"
		."<td><b>".$t->translate("ZIP")."</b></td></tr>\n"
		."<tr><td></td>\n"
		."<td><select name=\"state\">\n"
		."<option value=\"\">".$t->translate("All")."\n"
		.select_form('contact','state_con',$state)
		."</select></td>\n"
		."<td><select name=\"city\">\n"
		."<option value=\"\">".$t->translate("All")."\n"
		.select_form('contact','city_con',$city)
		."</select></td>\n"
		."<td><input type=\"TEXT\" name=\"zip\" value=\"$zip\" size=10 maxlength=16></td>\n";
		if ($entid > 0) {
			$filter .= "<input type=\"hidden\" name=\"id\" value=\"$entid\">\n";
		}
		$filter .= "<input type=\"hidden\" name=\"by\" value=\"filter\">\n"
		."</form></tr></table>\n";
		$bs->box_strip($filter);
	}
}


function connav($db,$entid) {
	global $PHP_SELF,$sess,$t,$bs,$config_showfull_conperpage;
    global $by,$cnt,$prev_cnt,$next_cnt,$enterprise,$name,$type,$country,$state,$city,$zip;
	if ($db->num_rows() > 0 && ($cnt > 0 || $db->num_rows() == $config_showfull_conperpage)) {
		if ($entid > 0) {
			$ref = "conbyentid.php";
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
			$narray["type"] = $type;
			$narray["country"] = $country;
			$narray["state"] = $state;
			$narray["city"] = $city;
			$narray["zip"] = $zip;
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
		$tarray["type"] = $type;
		$tarray["country"] = $country;
		$tarray["state"] = $state;
		$tarray["city"] = $city;
		$tarray["zip"] = $zip;
		$nav .= $sess->add_query($tarray)."\">".$t->translate("Top")."</a>";

		if ($db->num_rows() == $config_showfull_conperpage) {
			$nav .= " | <a href=\"".$sess->url($ref);
			if ($entid > 0) {
				$parray["id"] = $entid;
			}
			$parray["cnt"] = $next_cnt;
			$parray["by"] = $by;
			$parray["enterprise"] = $enterprise;
			$parray["name"] = $name;
			$parray["type"] = $type;
			$parray["country"] = $country;
			$parray["state"] = $state;
			$parray["city"] = $city;
			$parray["zip"] = $zip;
			$nav .= $sess->add_query($parray)."\">".$t->translate("Next")."</a>&nbsp;&gt;";
		} else {
			$nav .= " | ".$t->translate("Next")."</a>&nbsp;&gt;";
		}

		$bs->box_strip($nav);
	}
}
?>
