<!-- BerliOS menu -->
<table BORDER=0 CELLSPACING=0 CELLPADDING=3 WIDTH="100%">
<tr BGCOLOR="<?php echo $th_navstrip_bgcolor;?>">
<td ALIGN=CENTER>
<span class="titlebar"><font color="<?php echo $th_navstrip_font_color;?>"><?php echo $sys_name?></font></span></td>
</tr>

<tr ALIGN=RIGHT BGCOLOR="<?php echo $th_nav_bgcolor;?>">
<td><a href="<?php $sess->purl("index.php") ?>" class="menus"><?php echo $t->translate("Home"); ?></a>
<br><a href="<?php $sess->purl("faq.php") ?>" class="menus"><?php echo $t->translate("Q&amp;A"); ?></a>

<br><br>

<?php
if (isset($auth) && !empty($auth->auth["perm"]) && !($logout) ) {
  if ($perm->have_perm("user") || $perm->have_perm("user_pending") || $perm->have_perm("editor") || $perm->have_perm("admin") || $perm->have_perm("anonymous")) {
?>
<a href="<?php $sess->purl("logout.php") ?>" class="menus"><?php echo $t->translate("Logout"); ?></a>
<?php
  }
} else {
?>
<a href="<?php $sess->purl("login.php") ?>" class="menus"><?php echo $t->translate("Login"); ?></a>
<?php
}
?>
<br><a href="<?php $sess->purl("register.php") ?>" class="menus"><?php echo $t->translate("New User"); ?></a>
<br><a href="<?php $sess->purl("remind.php") ?>" class="menus"><?php echo $t->translate("Forgot Password"); ?></a>
<?php
if (isset($auth) && !empty($auth->auth["perm"]) && !($logout)) {
	if (($perm->have_perm("user") || $perm->have_perm("user_pending") || $perm->have_perm("admin")) && !($perm->have_perm("anonymous"))) {
?>
<br><a href="<?php $sess->purl("chguser.php") ?>" class="menus"><?php echo $t->translate("Change User"); ?></a>
<?php
	}
}

if (($config_perm_users == "all") || (isset($perm) && $perm->have_perm($config_perm_users))  && !($logout)) {
?>
<br><a href="<?php $sess->purl("users.php") ?>" class="menus"><?php echo $t->translate("Users"); ?></a>
<?php
}
?>
<br>
<br><a href="<?php $sess->purl("enterprises.php") ?>" class="menus"><?php echo $t->translate("Enterprises"); ?></a>
<?php
if (isset($auth) && !empty($auth->auth["perm"]) && !($logout)) {
	if (($perm->have_perm("user") || $perm->have_perm("user_pending") || $perm->have_perm("admin")) && !($perm->have_perm("anonymous"))) {
echo "<br><a href=\"".$sess->url("entform.php")."\" class=\"menus\">".$t->translate("New Enterprise")."</a>\n";
echo "<br><a href=\"".$sess->url("enterprises.php").$sess->add_query(array("by" => "user"))."\" class=\"menus\">".$t->translate("Update Enterprise")."</a>\n";
}
}
?>
<br><a href="<?php $sess->purl("contacts.php"); ?>" class="menus"><?php echo $t->translate("Contacts"); ?></a>
<br><a href="<?php $sess->purl("services.php"); ?>" class="menus"><?php echo $t->translate("Services"); ?></a>
<br><a href="<?php $sess->purl("products.php"); ?>" class="menus"><?php echo $t->translate("Products"); ?></a>
<br><a href="<?php $sess->purl("solutions.php"); ?>" class="menus"><?php echo $t->translate("Solutions"); ?></a>
<br><a href="<?php $sess->purl("customers.php"); ?>" class="menus"><?php echo $t->translate("Customers"); ?></a>
<br><a href="<?php $sess->purl("news.php"); ?>" class="menus"><?php echo $t->translate("News"); ?></a>
<br><a href="<?php $sess->purl("comments.php"); ?>" class="menus"><?php echo $t->translate("Comments"); ?></a>
<br>
<br><a href="<?php $sess->purl("newsletter.php"); ?>" class="menus"><?php echo $t->translate("Newsletter"); ?></a>
<br><a href="<?php $sess->purl("backend.php"); ?>" class="menus"><?php echo $t->translate("Backend"); ?></a>

<!-- Statistics not yet implemented
<br><a href="<?php $sess->purl("stats.php").$sess->add_query(array("option" => "general")) ?>" class="menus"><?php echo $t->translate("Statistics"); ?></a>
-->

<?php
/*
// The credits have been moved to the footer
<br><a href="/html" class="menus"><?php echo $t->translate("About"); ?></a>
*/
?>
</td>
</tr>
</table>
<!-- end BerliOS menu -->
<!-- Admin menu -->
<?php

if (
    (($config_perm_admuser == "all") ||
       ($config_perm_admlicens == "all") ||
       ($config_perm_admcomment == "all") ||
       ($config_perm_admsec == "all") ||
       ($config_perm_admcat == "all") ||
       ($config_perm_nladm == "all") ||
       ($config_perm_admfaq == "all"))
  || (isset($perm) &&
       (($perm->have_perm($config_perm_admuser)) ||
        ($perm->have_perm($config_perm_admlicens)) ||
        ($perm->have_perm($config_perm_admcomment)) ||
        ($perm->have_perm($config_perm_admsec)) ||
        ($perm->have_perm($config_perm_admcat)) ||
        ($perm->have_perm($config_perm_nladm)) ||
        ($perm->have_perm($config_perm_admfaq)) ))
  && !($logout)) {

?>
<table BORDER=0 CELLSPACING=0 CELLPADDING=3 WIDTH="100%">
<tr BGCOLOR="<?php echo $th_navstrip_bgcolor;?>">
<td ALIGN=CENTER><img SRC="http://www.berlios.de/images/blank.gif" height="1" width="135" border=0><br>
<span class="titlebar"><font color="<?php echo $th_navstrip_font_color;?>"><?php echo $t->translate("Administration"); ?></font></span></td>
</tr>

<tr ALIGN=RIGHT BGCOLOR="<?php echo $th_nav_bgcolor;?>">
<td>
<?php

  if (($config_perm_admuser == "all") || (isset($perm) && $perm->have_perm($config_perm_admuser))  && !($logout)) {
    $db->query("SELECT COUNT(*) FROM auth_user");
    $db->next_record();
    echo "<a href=\"".$sess->url("admuser.php")."\" class=\"menus\">".$t->translate("Users")." [".$db->f("COUNT(*)")."]</a>\n";
  }

  if (($config_perm_admcat == "all") || (isset($perm) && $perm->have_perm($config_perm_admcat))  && !($logout)) {
    $db->query("SELECT COUNT(*) FROM categories WHERE type='Contact'");
    $db->next_record();
    echo "<br><a href=\"".$sess->url("admcat.php").$sess->add_query(array("type" => "Contact"))."\" class=\"menus\">".$t->translate("Contact Categories")." [".$db->f("COUNT(*)")."]</a>\n";
    $db->query("SELECT COUNT(*) FROM categories WHERE type='Services'");
    $db->next_record();
    echo "<br><a href=\"".$sess->url("admcat.php").$sess->add_query(array("type" => "Services"))."\" class=\"menus\">".$t->translate("Service Categories")." [".$db->f("COUNT(*)")."]</a>\n";
    $db->query("SELECT COUNT(*) FROM categories WHERE type='Products'");
    $db->next_record();
    echo "<br><a href=\"".$sess->url("admcat.php").$sess->add_query(array("type" => "Products"))."\" class=\"menus\">".$t->translate("Product Categories")." [".$db->f("COUNT(*)")."]</a>\n";
  }

  if (($config_perm_admcmt == "all") || (isset($perm) && $perm->have_perm($config_perm_admcmt))  && !($logout)) {
    $db->query("SELECT COUNT(*) FROM comments");
    $db->next_record();
    echo "<br><a href=\"".$sess->url("admcmt.php")."\" class=\"menus\">".$t->translate("Comments")." [".$db->f("COUNT(*)")."]</a>\n";
  }

  if (($config_perm_admfaq == "all") || (isset($perm) && $perm->have_perm($config_perm_admfaq))  && !($logout)) {
    $db->query("SELECT COUNT(*) FROM faq WHERE language='$la'");
    $db->next_record();
    echo "<br><a href=\"".$sess->url("admfaq.php")."\" class=\"menus\">".$t->translate("Q&amp;A")." [".$db->f("COUNT(*)")."]</a>\n";
  }

  if (($config_perm_nladm == "all") || (isset($perm) && $perm->have_perm($config_perm_nladm))  && !($logout)) {
				// Daily Newsletter
    echo "<br><a href=\"".$sess->url("nladm.php").$sess->add_query(array("period" => "daily"))."\" class=\"menus\">".$t->translate("Daily Newsletter")."</a>\n";

    $where = "DATE_FORMAT(news.modification_new,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
    $db->query("SELECT COUNT(*) FROM news WHERE $where AND status_new='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("News")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(enterprise.modification,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
    $db->query("SELECT COUNT(*) FROM enterprise WHERE $where AND status='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Enterprise")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(contact.modification_con,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
    $db->query("SELECT COUNT(*) FROM contact WHERE $where AND status_con='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Contacts")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(services.modification_svc,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
    $db->query("SELECT COUNT(*) FROM services WHERE $where AND status_svc='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Services")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(products.modification_pro,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
    $db->query("SELECT COUNT(*) FROM products WHERE $where AND status_pro='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Products")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(solutions.modification_sol,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
    $db->query("SELECT COUNT(*) FROM solutions WHERE $where AND status_sol='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Solutions")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(customers.modification_cus,'%Y-%m-%d')=\"".date("Y-m-d")."\"";
    $db->query("SELECT COUNT(*) FROM customers WHERE $where AND status_cus='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Customers")." [".$db->f("COUNT(*)")."]\n";

				// Weekly Newsletter
    echo "<br><a href=\"".$sess->url("nladm.php").$sess->add_query(array("period" => "weekly"))."\" class=\"menus\">".$t->translate("Weekly Newsletter")."</a>\n";
    $lastday = time() - 7 * 24 * 60 * 60;

    $where = "DATE_FORMAT(news.modification_new,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(news.modification_new,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
    $db->query("SELECT COUNT(*) FROM news WHERE $where AND status_new='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("News")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(enterprise.modification,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(enterprise.modification,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
    $db->query("SELECT COUNT(*) FROM enterprise WHERE $where AND status='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Enterprise")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(contact.modification_con,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(contact.modification_con,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
    $db->query("SELECT COUNT(*) FROM contact WHERE $where AND status_con='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Contacts")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(services.modification_svc,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(services.modification_svc,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
    $db->query("SELECT COUNT(*) FROM services WHERE $where AND status_svc='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Services")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(products.modification_pro,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(products.modification_pro,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
    $db->query("SELECT COUNT(*) FROM products WHERE $where AND status_pro='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Products")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(solutions.modification_sol,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(solutions.modification_sol,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
    $db->query("SELECT COUNT(*) FROM solutions WHERE $where AND status_sol='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Solutions")." [".$db->f("COUNT(*)")."]\n";

    $where = "DATE_FORMAT(customers.modification_cus,'%Y-%m-%d')<=\"".date("Y-m-d")."\" AND DATE_FORMAT(customers.modification_cus,'%Y-%m-%d')>\"".date("Y-m-d",$lastday)."\"";
    $db->query("SELECT COUNT(*) FROM customers WHERE $where AND status_cus='A'"); 
    $db->next_record();
    echo "<br>- ".$t->translate("Customers")." [".$db->f("COUNT(*)")."]\n";

  }
?>
</td>
</tr>
</table>
<?php
}
?>
<!-- end Admin menu -->
<!-- Search menu -->
<table BORDER=0 CELLSPACING=0 CELLPADDING=3 WIDTH="100%">
<tr BGCOLOR="<?php echo $th_navstrip_bgcolor;?>">
<td ALIGN=CENTER><img SRC="http://www.berlios.de/images/blank.gif" height="1" width="135" border=0><br>
<span class="titlebar"><font color="<?php echo $th_navstrip_font_color;?>"><?php echo $t->translate("Search"); ?></font></span></td>
</tr>

<tr ALIGN=RIGHT BGCOLOR="<?php echo $th_nav_bgcolor;?>">
<td align=center>
<p>
<form action="<?php $sess->purl("enterprises.php"); ?>">
<input type="hidden" name="by" value="filter">
<input TYPE="text" SIZE="10" MAXLENGTH=255 NAME="name" VALUE="">
<?php
echo "<p><input TYPE=\"submit\" NAME=\"Search\" VALUE=\"".$t->translate("Search")."\">";
?>
</form>
</td>
</tr>
</table>
<!-- end Search menu -->
<!-- Language menu -->
<table BORDER=0 CELLSPACING=0 CELLPADDING=3 WIDTH="100%">
<tr BGCOLOR="<?php echo $th_navstrip_bgcolor;?>">
<td ALIGN=CENTER><img SRC="http://www.berlios.de/images/blank.gif" height="1" width="135" border=0><br>
<span class="titlebar"><font color="<?php echo $th_navstrip_font_color;?>"><?php echo $t->translate("Language");?></font></span></td>
</tr>

<tr ALIGN=RIGHT BGCOLOR="<?php echo $th_nav_bgcolor;?>">
<td align=center>
<p>
<form action="<?php $sess->pself_url()?>">
<?php
while (is_array($HTTP_GET_VARS) 
		&& list($key, $val) = each($HTTP_GET_VARS)) {
	if ($key != "lang" && $key != "go") {
		echo "<input TYPE=\"hidden\" NAME=\"$key\" VALUE=\"$val\">\n";
	}
}
?>
<select name="lang" size=1>
<?php
while (list(, $ln) = each($la_array)) {
	if ($la == $ln) {
		$sel = "selected";
	} else {
		$sel ="";
	}
	echo "<option value=\"$ln\" $sel>".$t->translate($ln)."\n";
}
?>
</select>
<?php
echo "<p><input TYPE=\"submit\" NAME=\"go\" VALUE=\"".$t->translate("Go")."\">";
?>
</form>
</td>
</tr>
</table>
<!-- end Language menu -->
<?php
if (ereg("Gecko", "$HTTP_USER_AGENT")) {
	echo "<p align=center><a href=\"javascript:addNetscapePanel();\"><img SRC=\"images/add-button.gif\" BORDER=0 height=45 width=100></a>\n";
}
echo "<p align=\"center\"><a href=\"http://developer.berlios.de\">
<img src=\"http://developer.berlios.de/bslogot.php?group_id=76&type=1\" width=\"124\" height=\"32\" border=\"0\" hspace=\"3\" vspace=\"3\" alt=\"BerliOS Logo\"><br>Developer</a>\n";
?>
