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

function phpAiksaur_popup()
{
    print "<script language=\"JavaScript1.1\">\n"
        . "<!--\n"
        . "    function launchThesaurus()\n"
        . "    {\n"
        . "        url = \"phpAiksaur_popup_frameset.php?lookup=\"\n"
        . "            + document.popupThesaurus.lookup.value;\n\n"
        . "        Pop = window.open(\n"
        . "                 url,\n"
        . "                 \"AikSaurus_PHP_Popup\",\n"
        . "                 \"toolbar=1,location=0,directories=0,status=0,menubar=0,\"\n"
        . "                 + \"resizable=1,scrollbars=1,width=480,height=340\"\n"
        . "        );\n"
        . "    }\n"
        . "// -->\n"
        . "</script>";
}

?>  
