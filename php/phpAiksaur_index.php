<!--

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

-->

<html>
<head>
<title>phpAiksaur Setup</title>
</head>
<body bgcolor="#ffffff" text="#000000">

<h1>Welcome to <font color="#009900">phpAiksaur</font></h1>
<hr size="1" noshade>
<h2>Running Tests on your Installation...</h2>
<p>You should see three <strong><font color="#009900">Goods</font></strong> here if your setup is correct.</p>
<blockquote>
<h3>Checking for PHP...</h3>
<!-- detect if php is being parsed
<?
$ok = "ok";
?>
-->
<form name="testform">
<input type="hidden" name="testphp" value="<? echo $ok; ?>"></input>
</form>
<blockquote>
<script language="JavaScript1.1">
<!--
    if (document.testform.testphp.value != "ok")
    {
        document.writeln("<p><b><font color=\"#ff0000\">ERROR:</font></b> PHP does not seem to be installed.</p>");
        document.writeln("<p>Make sure that your web server is set to interpret ");
        document.writeln("files with .php extensions as PHP scripts.</p>");
    }
    else
    {
        document.writeln("<p><b><font color=\"#009900\">Good</font>:</b> PHP seems to be installed correctly.</p>");
    }
// -->
</script>
<noscript>
<p><b><font color="#ff0000">ERROR:</font></b> Cannot check for PHP without JavaScript enabled.</p>
<p>PHP may or may not be installed correctly.</p>
</noscript>
</blockquote>

<h3>Checking for Correct EXEC_PATH...</h3>
<blockquote>
<?
include("phpAiksaur.php");
if (file_exists(EXEC_PATH))
{
    print "<p><b><font color=\"#009900\">Good</font>: </b> <code>" . EXEC_PATH . "</code> exists.</p>";
}
else
{
    $dir = $DOCUMENT_ROOT . substr($PHP_SELF, 1, strlen($PHP_SELF) - 1);
    $dir = substr($dir, 0, strrpos($dir, "/"));
    
    print "<p><b><font color=\"#ff0000\">ERROR</font>: </b> <code>" . EXEC_PATH . "</code> does not exist.</p>";
    print "<p>This indicates that either</p>";
    print "<ul><li>AikSaurus Core Libraries are not installed, or</li>";
    print "<li>phpAiksaur is not yet configured.</li></ul>";
    print "<p>Make sure that you have installed the AikSaurus Core Library. (";
    print "<a href=\"http://www.aiksaurus.com/install.php\">Instructions</a>)</p>";
    print "<p>If you already installed it, edit the file:</p><blockquote><code>";
    print "$dir/phpAiksuar.php</code></blockquote><p> ";
    print "and make sure that EXEC_PATH is correctly defined.";
    print " (<a href=\"http://www.aiksaurus.com/online/manual.php\">Help</a>)</p>";
}
?>
</blockquote>

<h3>Attempting to Do A Search...</h3>
<blockquote>
<?
    $thesaurus = new phpAiksaur;
    
    if ($thesaurus->doSearch("fool"))
    {
        print "<b><font color=\"#009900\">Good</font>: </b> Synonyms found successfully.";
    }
    else
    {
        if (strlen($thesaurus->getError()))
        {
            print "<p>This means that an internal error occured with the AikSaurus core.</p>";
        }

        else
        {
            print "<p>No synonyms were found, but no error was reported.</p>";
        }
        
        print "<p><b>This should not happen</b>.  Unless you were doing something that you ";
        print "know was strange (like messing around with thesaurus datafiles), ";
        print "you should probably <b>submit a bug report</b> to ";
        print "<a href=\"mailto:jared@aiksaurus.com\">jared@aiksaurus.com</a></p>";
    }
?>
</blockquote>

</blockquote>
<hr noshade size="1">

<h2>Test Drive!</h2>

<?
    include("phpAiksaur_popup.php");
    phpAiksaur_popup();
?>


<p>If the above tests passed, you can now try out your thesaurus.</p>

<p>You probably want to see 
<a href="http://www.aiksaurus.com/online/manual.php">The Manual</a> for instructions about 
customization and embedding with your site.
</p>

<blockquote>
    <h3>Popup Thesaurus</h3>
    <blockquote>
        <noscript>
        <p><b>NOTE:</b> this will not work because you do not have javascript enabled.</p>
        </noscript>
        <p>The popup thesaurus is intended mostly for web applications like web-based
        email, news authoring software, etc.</p>
        
        <form name="popupThesaurus" onSubmit="javascript:launchThesaurus()">
        <p><b>Test Drive Popup Thesaurus</b> <br> 
        <input type="text" name="lookup" size="20" />
        <input type="submit" value="Search">
        </form>

    </blockquote>
    <br>
    <h3>Embedded Thesaurus</h3>
    <blockquote>
        <p>The embedded thesaurus works without javascirpt and is intended for web 
        sites that want to provide thesuarus functionality.  It <b>looks plain now</b>
        but can integrate into your site's look easily.
        </p>

        <form name="embeddedThesaurus" method="post" action="phpAiksaur_embedded.php">
        <p><b>Test Drive Embedded Thesaurus</b> <br>
        <input type="text" name="lookup" size="20" />
        <input type="submit" value="Search">
        </form>
        
    </blockquote>
    
</blockquote>
<hr noshade size="1">


</body>
</html>
