<?php

function stats($result,$var,$message,$position) {
    global $bx, $t;
    $max = 1; 		// max is a number which gives the top 1!!
    $length = 300; 	// length is the maximal lenght of the image

	$bx->box_begin();
	$bx->box_title($t->translate($message));
	$bx->box_body_begin();

    echo "<table border=0 width=100% cellspacing=0>\n";
        
    while($row = mysql_fetch_array($result)) {
       $position +=1;
       if ( ($row[$var] > $max) ) {
	       $max = $row[$var];
       } 

       echo "<tr><td width=5% align=right>&nbsp;".$position.".</td>\n";
       echo "<td width=35%>&nbsp;<a href=\"appbyid.php?id=".$row["appid"]."\">$row[name]</A> (".typestr($row["type"]).")</td>\n";
       echo "<td width=1%>&nbsp;</td>\n";
       echo "<td width=59%><img src=\"images/leftbar.gif\" height=14 width=7 Alt=\"$row[name]\"><img src=\"images/mainbar.gif\" Alt=\"$row[name]\" height=14 width=", $row[$var] * $length / $max, "><img src=\"images/rightbar.gif\" height=14 width=7 Alt=\"$row[name]\">&nbsp; $row[$var]</td></tr>\n";
       echo "</td></tr>\n";
    }
    echo "</table>\n";
	$bx->box_body_end();
	$bx->box_end();
}

## stats_type($message,$type):
##
## where type can be: sections, categories and licenses

function stats_type($message, $type) {
    global $t, $bx, $db_name;
    $max = 10;		// max is a number to ensure the maximum lenght of the graph
    $length = 200; 	// length is the maximal lenght of the image

	$bx->box_begin();
	$bx->box_title($t->translate($message));
	$bx->box_body_begin();

    echo "<table border=0 width=100% cellspacing=0>\n";

    $max = 0.9*mysql_num_rows($result = mysql_db_query($db_name,"SELECT * FROM software"));

    for($i=0; $i<sizeof($$type); $i++) {

    switch($type) {

      case "sections":
	 $where = "section";
         echo "<tr><td width=47%>&nbsp;<a href=\"categories.php?section=".${$type}[$i]."\">".${$type}[$i]."</A>:</td>\n";
	 break;

      case "categories":
	 $sec_old = $sec;
         if ($i < 1) {$max = 0.2 * $max;}
         $sec = strtok(${$type}[$i], "/");
	 if ($sec != $sec_old) {
	    echo "</td></tr><tr><td><B>";
	    echo $sec;
  	    echo "</B></td></tr><tr bgcolor=\"".$GLOBALS["th_box_body_bgcolor"]."\"><tr><td>\n";
	 }
         ${$type}[$i] = strtok("."); 		
         echo "<tr><td width=47%>&nbsp;<a href=\"appbycat.php?section=".urlencode($sec)."&category=".urlencode(${$type}[$i])."\">".${$type}[$i]."</A>:</td>\n";
	 $where = "section='".$sec."' AND category";
	 break;

     case "licenses":         
       echo "<tr><td width=47%>&nbsp;<a href=\"lisence/".$licenses[$i]."\">".$licenses[$i]."</A>:</td>\n";
         $where = "license";
    }

    $result1 = mysql_db_query($db_name,"SELECT * FROM software WHERE $where='".${$type}[$i]."'");
	$count=mysql_num_rows($result1);

       echo "<td width=1%>&nbsp;</td>\n";
       echo "<td width=52%><img src=\"images/leftbar.gif\" height=14 width=7 Alt=\"${$type}[$i]\"><img src=\"images/mainbar.gif\" Alt=\"${$type}[$i]\" height=14 width=", $count * $length / $max, "><img src=\"images/rightbar.gif\" height=14 width=7 Alt=\"${$type}[$i]\">&nbsp; $count</td></tr>\n";
       echo "</td></tr>\n";
    }
    echo "</table>\n";
	$bx->box_body_end();
	$bx->box_end();
}

## stats_title($message):
##
## Displays the header of the table with the title given by $message

function stats_title($message) {
    global $t;
    echo "<center>\n";
    echo "<table width=600 border=0 cellspacing=0 cellpadding=0 bgcolor=\"".$GLOBALS["th_box_frame_color"]."\" align=center>\n";
    echo "<tr><td>\n";
    echo "<table width=100% border=0 cellspacing=1 cellpadding=3>\n";
    echo "<tr bgcolor=\"".$GLOBALS["th_box_title_bgcolor"]."\">\n";
    echo "<td><b>";
    	echo $t->translate($message);
    		echo "</b></td>\n";
    echo "</tr><tr bgcolor=\"".$GLOBALS["th_box_body_bgcolor"]."\"><td>\n";
    echo "<table border=0 width=100% cellspacing=0>\n";
}

## stats_subtitle($message):
##
## Displays a subtitle

function stats_subtitle_alt($message) {

    echo "<tr><td width=42% bgcolor=\"".$GLOBALS["th_box_title_bgcolor"]."\"><B>".$message."</B></td>\n";
    echo "<td width=1% bgcolor=\"".$GLOBALS["th_box_title_bgcolor"]."\">&nbsp;</td>";
    echo "<td width=6% bgcolor=\"".$GLOBALS["th_box_title_bgcolor"]."\">&nbsp;</td>";
    echo "<td width=44% bgcolor=\"".$GLOBALS["th_box_title_bgcolor"]."\">&nbsp;</td>";
    echo "<td width=7% bgcolor=\"".$GLOBALS["th_box_title_bgcolor"]."\">&nbsp;</td></tr>";
}

## stats_subtitle($message):
##
## Displays a subtitle

function stats_subtitle($message) {

    echo "<tr><td width=38% bgcolor=\"".$GLOBALS["th_box_title_bgcolor"]."\"><B>".$message."</B></td>\n";
    echo "<td bgcolor=\"".$GLOBALS["th_box_title_bgcolor"]."\">&nbsp;</td>";
    echo "<td bgcolor=\"".$GLOBALS["th_box_title_bgcolor"]."\">&nbsp;</td></tr>";
}


## stats_display($what,$count,$url):
##
## Displays the statistic graphically in one column
## $what is the string which gives the name
## $count gives the number of times it appears
## $url gives the corresponding url
## if $url = 0 then no url is displayed

function stats_display($what,$count,$url) {
    $max= 400;		// max is a number to ensure the maximum lenght of the graph
    $length = 575; 	// length is the maximal lenght of the image

    echo "<tr><td width=47%>&nbsp;<a href=\"".$url."\">".$what."</A>:</td>\n";
    echo "<td width=1%>&nbsp;</td>\n";
    echo "<td width=52%><img src=\"images/leftbar.gif\" height=14 width=7 Alt=\"${$type}[$i]\"><img src=\"images/mainbar.gif\" Alt=\"${$type}[$i]\" height=14 width=", $count * $length / $max, "><img src=\"images/rightbar.gif\" height=14 width=7 Alt=\"${$type}[$i]\">&nbsp; $count</td></tr>\n";
    echo "</FONT></td></tr>";
}

## stats_display_alt($what,$count,$url):
##
## Displays the statistic graphically in one column
## $what is the string which gives the name
## $count gives the number of times it appears
## $url gives the corresponding url

function stats_display_alt($what,$count,$url,$total) {

			// To avoid that by 100% the graph is too big
  if ($count/$total >= 0.95) {
    $total_normalize = 1.1 * $total;
  } else {
    $total_normalize = $total;
  }

  echo "<tr><td width=246>&nbsp;";
    if (strcmp($url,"0")) echo "<a href=\"".$url."\">";
       echo $what;
	 if (strcmp($url,"0")) echo "</A>:</td>\n";
  echo "<td width=6>&nbsp;</td>\n";
  echo "</td width=42><td>&nbsp; $count</td>\n";

  echo "<td><table width=264><TR><td><img src=\"images/leftbar.gif\" height=14 width=7 Alt=\"$what\"><img src=\"images/mainbar.gif\" Alt=\"$what\" height=14 width=", $count * 264 / $total_normalize, "><img src=\"images/rightbar.gif\" height=14 width=7 Alt=\"$what\"></td></tr></table>\n";


  echo "</td width=42><td>&nbsp;".(Floor(($count*100/$total)*10)/10)."%</td></tr>\n";
  echo "</FONT></td></tr>";
}

## stats_end():
##
## Finishes the table


function stats_end(){
    echo "</table>\n";
    echo "</TD></TR></TABLE>\n";
    echo "</TD></TR></TABLE></CENTER>\n";
    echo "<BR>\n";
}

?>
