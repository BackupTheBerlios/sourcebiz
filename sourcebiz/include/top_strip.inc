<!-- top strip -->
<table BORDER=0 CELLSPACING=0 CELLPADDING=2 WIDTH="100%" BGCOLOR="<?php echo $th_navstrip_bgcolor;?>">
<tr>
<td width=45%><span class=maintitlebar>
<?php
$i = 0;
while (list($title, $url) = each($ts_array)) {
	if ($i > 0)
		echo "\n | ";
	echo "<b><a href=\"$url\" class=\"maintitlebar\">".$t->translate("$title")."</a></b>";
	$i++;
};
echo "\n</span></td><td width=55% align=right>\n";
if (isset($auth) && !empty($auth->auth["perm"])  && !($logout)) {
	echo "<FONT COLOR=\"".$th_nav_bgcolor."\">".$t->translate("Logged in")." <b>".$auth->auth["uname"]."</b> (<b>".$auth->auth["perm"]."</b>) / ".$t->translate("Expires")." <b>".timestr_short($auth->auth["exp"])."</b></FONT>";
} else {
	echo "<FONT COLOR=\"".$th_nav_bgcolor."\"><B>".$t->translate("Not Logged in")."</B></FONT>";
}
?>

</td>
</tr>

</table>
<!-- end top strip -->