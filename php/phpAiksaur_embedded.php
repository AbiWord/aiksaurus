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


// Define this as the path to your aiksaurus executable:
define(EXEC_PATH, "./CommandLineDemo");

// This path also needs to be correct.  Usually you just put
// phpAiksaurusClass.php in the same directory with this file.
include_once("phpAiksaur.php");






define(LINK_URL, $PHP_SELF . "?lookup=");

function makeLink($word)
{
    return "<a href=\"" . LINK_URL . rawurlencode($word) . "\">$word</a>";
}


function printResults($res, $title)
{
	if (count($res) == 0)
		return;

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

		print "<table border=\"0\" width=\"90%\" align=\"center\" cellpadding=\"5\">";
		print "<tr valign=\"top\">";
		print "<td width=\"20%\" bgcolor=\"#eeeeee\" valign=\"middle\" align=\"center\">";
		print "<big>" . count($res) . " $title</big>";
		print "</td><td width=\"20%\">";
		for($i = 0;$i < $stop1;++$i)
		{
			print makeLink($res[$i]) . "<br>";
		}
		print "</td><td width=\"20%\">";
		for(; $i < $stop2; ++$i)
		{
			print makeLink($res[$i]) . "<br>";
		}
		print "</td><td width=\"20%\">";
		for(; $i < $stop3; ++$i)
		{
			print makeLink($res[$i]) . "<br>";
		}
		print "</td><td width=\"20%\">";
		for(; $i < $stop4; ++$i)
		{
			print makeLink($res[$i]) . "<br>";
		}
		print "</td></tr></table><br>";
	}


$thesaurus = new phpAiksaur(EXEC_PATH);

if ($thesaurus->doSearch($lookup))
{
    print "<h2>Synonyms for ";
    print "<font color=\"#ff0000\">";
    print ucwords(strtolower($lookup));
    print "</font></h2>\n";

    
    printResults($thesaurus->getNouns(), "Nouns");
    printResults($thesaurus->getVerbs(), "Verbs");
    printResults($thesaurus->getAdjectives(), "Adjectives");
    printResults($thesaurus->getAdverbs(), "Adverbs");
    printResults($thesaurus->getOthers(), "Others");
    printResults($thesaurus->getUnknowns(), "Unknowns");
}


else
{
    print "<h2>No known synonyms for ";
    print "<font color=\"#ff0000\">";
    print ucwords(strtolower($lookup));
    print "</font></h2>\n";
   
    $similar = $thesaurus->getSimilar();
    
    print "<p>Alphabetically nearby known words:";
    print "<ul>";
    for($i = 0;$i < count($similar);++$i)
    {
        print "<li>" . makeLink($similar[$i]) . "</li>";
    }
    print "</ul>";
}

?>
