<?
    include("../format.php");
    printHeader("phpAiksaur: Installation");
?>

<h2>phpAiksaur Installation</h2>

<p>This guide will take you through installing phpAiksaur on your computer.
</p>

<h3>0. Install Web Server</h3>
<p>If you do not already have a PHP-enabled web server, you will need
to get one.  I think 
that just about any version of PHP 3 or 4 should work, but have only tested
AikSaurus with PHP 4.  Please let me know of successes or failures that you
may encounter.  If you don't have such a server, here are links to   
<a href="http://www.apache.org/">Apache</a> and 
<a href="http://www.php.net/">PHP</a>.
</p>

<h3>1. Install AikSaurus Core Libraries</h3>

<p>Now you need to <a href="/install.php">install the core library</a>
on to your web server.  Once you have installed the library, you should have a 
new program named <strong>CommandLineDemo</strong>.  Be sure to mark down where 
this program is because we will need it in a few minutes.
</p>


<h3>2. Download phpAiksaur</h3>

<p>At this point, you should <a href="source.php">download phpAiksaur</a>
and extract it to somewhere that is accessible on your web server.  For 
the rest of this document, I will assume you have extracted it so that 
it lives in:
</p>
<blockquote>
<code>http://www,your-domain.com/aiksaurus/</code>
</blockquote>

<p>You don't need to do anything else, just extract the files and you'll
be fine.
</p>

<h3>3. Configure phpAiksaur</h3>

<p>The first thing we need to do is tell phpAiksaur where to find the 
<b>CommandLineDemo</b> program that you downloaded a few minutes ago.
</p>

<p>To do this, you should edit the file <b>phpAiksaur.php</b> and change
the line that says:
</p>

<blockquote>
<code>define(EXEC_PATH, "./CommandLineDemo");</code>
</blockquote>

<p>To match your system.</p>

<p><strong>NOTE</strong>: Due to the peculiarities of autoconf/automake, the 
<b>CommandLineDemo</b> program that gets created in the main directory is actually
just a shell script that points to <code>./libs/CommandLineDemo</code>.  If you are going to
move the CommandLineDemo somewhere else, say, into <code>your-domain.com/aiksaurus</code>,
you will need to move the program that is in <code>./libs</code> instead of the shell 
script.
</p>

<p>Example: if you built AikSaurus in <code>/home/jared/AikSaurus-0.XX</code>, you will
want to run the following commands:</p>
<blockquote>
<code>
$ cd /home/jared/AikSaurus-0.XX<br>
$ [./configure; make; make install]<br>
$ cd .libs<br>
$ mv CommandLineDemo /path/to/phpAiksaur/
</code></blockquote>

<p>And that's all the configuration you should have to do.</p>

<h3>4.  Testing</h3>

<p>Now it's just a matter of testing out your installation.  You should be 
able to just point your web browser at: <code>
<blockquote>
<code>http://www.your-server.com/aiksaurus/index.php</code>
</blockquote>
<p>You should now be seeing a simple page that lets you test your installation.
Go ahead and make sure everything works, then customize to your heart's 
content.
</p>

<h3>If you need help</h3>

<p>If you run into problems not covered here or have any questions, go ahead
and email me at <a href="mailto:jared@aiksaurus.com">jared@aiksaurus.com</a>.
</p>

<?
    printFooter();
?>

