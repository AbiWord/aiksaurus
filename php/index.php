<?
/*
 * AikSaurus Online - A Web Interface to the AikSaurus Thesaurus Library
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
?>

<?

include("../format.php");
printHeader("phpAiksaur");

if (!empty($lookup))
{
    include("phpAiksaur_embedded.php");
    printFooter();
    exit;
}

?>

<h2><a href="popsaurus.png">
<img class="ss" src="popsaurus_thumb.png" align="right" width="250" height="212" border="1">
</a>
phpAiksaur: A PHP Thesaurus</h2>

<h3>Information</h3>

<p>phpAiksaur is a PHP interface to the Aiksaurus thesaurus library.
It is free, open-source software released under the 
<a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public License</a>.
</p>

<p>phpAiksaur is <strong>easy to embed</strong> and customize in your web 
site or web application.  It should be easy to integrate with open 
source web email clients, news authoring programs, and so forth.  
</p>

<h3>Versions</h3>

<p>phpAiksaur includes two interfaces that you can choose from, and a core
php class if you'd rather write your own.
</p>

<p><strong>Web sites</strong> probably want to use the 
<strong>embedded</strong> version. (<a href="index.php?lookup=ashen">demo</a>) 
</p>
<ul>
 <li>No JavaScript required</li>
 <li>Can take on the appearance of your web site</li>
 <li>Meant to function like a regular part of your site</li>
</ul>

<?
include("phpAiksaur_popup.php");
phpAiksaur_popup();
?>

<form name="popupThesaurus">
<input type="hidden" name="lookup" value="ashen" />
</form>

<p><strong>Web applications</strong> probably want to use the 
<strong>popup</strong> version. (<a href="javascript:launchThesaurus()">demo</a>)
</p>
<ul>
 <li>Requires JavaScript on client's browser</li>
 <li>Pops up he term into a new, tight window</li>
 <li>Doesn't take user away from what they were doing</li>
 <li>Ideal for web based email/authoring software</li>
</ul>
    
<?
    printFooter();
?>
