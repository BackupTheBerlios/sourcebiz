<?php
switch($phrase) {
     case "Open Source Software Announcement &amp; Retrieval":  $tmp = "Open Source Software Announcement & Retrieval<BR>&nbsp;&nbsp;&nbsp; -> Italian is not yet supported, sorry :-( "; break;

// Im Default-Fall, lassen wir lieber das Englische...
// wer weiss, vielleicht hilft es mehr als "Error" zu sagen

     default: $tmp = "$phrase"; break;
}
?>
