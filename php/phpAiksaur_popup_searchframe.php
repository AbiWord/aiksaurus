<?
/*
 * phpAiksaur - A Web Interface to the AikSaurus Thesaurus Library
 * Copyright (C) 2001 by Jared Davis 
 *
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version. 
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details. 
 *
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. 
 */


// Set the title of your window here.
define(TITLE, "Thesaurus: Synonyms for " . ucwords(strtolower($lookup)));


// This path also needs to be correct.  Usually you just put
// phpAiksaurusClass.php in the same directory with this file.
include_once("phpAiksaur.php");


// Define this so that words will be hyperlinks.
define(LINK_URL, $PHP_SELF . "?lookup=");


function makeLink($word)
{
    return "<a href=\"" . LINK_URL . rawurlencode($word) . "\">$word</a>";
}


function printResults($res, $title)
{
	if (count($res) == 0)
		return;
    
    usort($res, strcasecmp);

	switch(  count($res) % 4  )
	{
		case 0:
			case 3:
				$stop1 = count($res) / 4;
				$stop2 = 2 * $stop1;
				$stop3 = 3 * $stop1;
				$stop4 = count($res);
			break;
			
			case 1:
				$stop1 = (count($res) / 4);
				$stop2 = $stop1 + count($res) / 4;
				$stop3 = $stop2 + count($res) / 4;
				$stop4 = count($res);
			break;

			case 2:
				$stop1 = count($res) / 4;
				$stop2 = 1 + $stop1 + count($res) / 4;
				$stop3 = $stop2 + count($res) / 4;
				$stop4 = count($res);
			break;
		}

		print "<table border=\"0\" width=\"100%\" align=\"center\" cellspacing=\"0\" cellpadding=\"5\">";
		print "<tr valign=\"top\">";
		print "<td colspan=\"4\" width=\"100%\" bgcolor=\"#eeeeee\">";
		print "<big>" . count($res) . " $title</big>";
		print "</td></tr><tr><td width=\"20%\" valign=\"top\">";
		for($i = 0;$i < $stop1;++$i)
		{
			print makeLink($res[$i]) . "<br>";
		}
		print "</td><td width=\"20%\" valign=\"top\">";
		for(; $i < $stop2; ++$i)
		{
			print makeLink($res[$i]) . "<br>";
		}
		print "</td><td width=\"20%\" valign=\"top\">";
		for(; $i < $stop3; ++$i)
		{
			print makeLink($res[$i]) . "<br>";
		}
		print "</td><td width=\"20%\" valign=\"top\">";
		for(; $i < $stop4; ++$i)
		{
			print makeLink($res[$i]) . "<br>";
		}
		print "</td></tr></table><br>";
	}
?>

<html>
<head>
<title><? print TITLE; ?></title>
<style>
<!--
body {
    margin-left: 0px;
    margin-right: 0px;
    margin-top: 0px;
    margin-bottom: 0px;
}
-->
</style>
</head>
<body bgcolor="#ffffff" text="#000000">

<form name="NewSearch" method="post" action="<? print $PHP_SELF; ?>">
<table bgcolor="#fffff0" border="0" width="100%" height="45">
<tr><td width="100%">
<big> &nbsp;  
<? 
    $thesaurus = new phpAiksaur;
    $synonyms = $thesaurus->doSearch($lookup);
    print (($synonyms) ? ("Synonyms for ") : ("Synonyms for "));
    print "<font color=\"#ff0000\">" . ucwords(strtolower($lookup)) . "</font>\n";
?>
</big>
</td>
<td align="right">
<nobr>Look up:</nobr> 
</td><td>
<nobr>
<input type="text" name="lookup" size="15" />
<input type="submit" value="Go" />
&nbsp; </nobr></td></tr>
</table>

<script language="JavaScript1.1">
<!--
    document.NewSearch.lookup.focus();
// -->
</script>


<?

if ($synonyms)
{
    printResults($thesaurus->getNouns(), "Nouns");
    printResults($thesaurus->getVerbs(), "Verbs");
    printResults($thesaurus->getAdjectives(), "Adjectives");
    printResults($thesaurus->getAdverbs(), "Adverbs");
    printResults($thesaurus->getOthers(), "Others");
    printResults($thesaurus->getUnknowns(), "Unknowns");
}


else
{
    $similar = $thesaurus->getSimilar();
    
    print "<p> &nbsp; <strong>No Synonyms Found.</strong><br />";
    print " &nbsp; Alphabetically nearby known words:</p>";
    print "<table border=\"0\" width=\"100%\">";
    print "<tr><td width=\"50%\">";
    print "<ul>";
    for($i = 0;$i < count($similar) / 2;++$i)
    {
        print "<li>" . makeLink($similar[$i]) . "</li>";
    }
    print "</ul>";
    print "</td><td width=\"50%\">";
    print "<ul>";
    for(;$i < count($similar);++$i)
    {
        print "<li>" . makeLink($similar[$i]) . "</li>";
    }
    print "</ul>";
    print "</td></tr>";
    print "</table>";
}

?>
</form>
</body>
</html>

