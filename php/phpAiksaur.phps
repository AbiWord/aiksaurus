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

# 
# EXEC_PATH
# ---------
#   Define this to be the path to your AikSaurus CommandLineDemo program.
#
#   For example:
#       /usr/local/apache/htdocs/aiksaurus/CommandLineDemo
#
#   You should really use an absolute path here.
#
define(EXEC_PATH, "./CommandLineDemo");


class phpAiksaur 
{
    var $d_word;
    var $d_similar;
    var $d_error;
    
    var $d_synonyms;
    var $d_nouns;
    var $d_verbs;
    var $d_adjectives;
    var $d_adverbs;
    var $d_others;
    var $d_unknowns;
    
    // getSynonyms: returns an array of all synonyms.
    function getSynonyms()
    {
        return $this->d_synonyms;
    }

    // getNouns: returns an array of all nouns.
    function getNouns()
    {
        return $this->d_nouns;
    }
    
    // getVerbs: returns an array of all verbs.
    function getVerbs()
    {
        return $this->d_verbs;
    }

    // getAdjectives: returns an array of all adjectives.
    function getAdjectives()
    {
        return $this->d_adjectives;
    }

    // getAdverbs: returns an array of all adverbs.
    function getAdverbs()
    {
        return $this->d_adverbs;
    }

    // getOthers: returns an array of all words of other classification.
    function getOthers()
    {
        return $this->d_others;
    }

    // getUnknowns: returns an array of words of unknown classification.
    function getUnknowns()
    {
        return $this->d_unknowns;
    }
    
    // getSimilar: returns an array of alphabetically nearby words.
    function getSimilar()
    {
        return $this->d_similar;
    }

    // getCount: returns number of synonyms found for word.
    function getCount()
    {
        return count($this->d_synonyms);
    }
    
    // getWord: returns current word being searched for.
    function getWord()
    {
        return $this->d_word;
    }
       
    // getError: returns error description from core library if error occured.
    function getError()
    {
        return $this->d_error;
    }
    
    // doSearch: returns TRUE if word found, FALSE if word not found.
    function doSearch($word)
    {
        $this->d_word = $word;
	    $this->d_synonyms = $this->d_similar =
        $this->d_nouns = $this->d_verbs = $this->d_adjectives =
        $this->d_adverbs = $this->d_others = $this->d_unknown = array();    
        $this->d_error = 0;
        
        $command = EXEC_PATH . " \"$word\"";
        exec($command, $res);

        if (ereg("^Error", $res[0])) // error with thesaurus program.
        {
            print "<h3>Internal Aiksaurus Error</h3>";
            print "<pre>";
            for($i = 0;$i < count($res);++$i)
            {
                $this->d_error .= $res[$i];
                print $res[$i];
            }
            print "</pre>";
            return false;
        }
        
		if (!ereg("^Not found", $res[0])) // synonyms were found.
		{
		    for($i = 0;$i < count($res);++$i)
		    {
			    $word = substr($res[$i], 7, strlen($res[$i]) - 7);
                $this->d_synonyms[] = $word;

                if ($res[$i][0] == 'N')
				    $this->d_nouns[] = $word;

			    if ($res[$i][1] == 'V')
				    $this->d_verbs[] = $word;

	    		if ($res[$i][2] == 'J')
		    		$this->d_adjectives[] = $word;

		    	if ($res[$i][3] == 'D')
			    	$this->d_adverbs[] = $word;

		    	if ($res[$i][4] == 'O')
			    	$this->d_others[] = $word;

    			if ($res[$i][5] == 'U')
	    			$this->d_unknowns[] = $word;
            }

            return true;
		}

        else // no synonyms found.
        {
            for($i = 1;$i < count($res);++$i)
            {
                $this->d_similar[] = htmlentities(trim($res[$i]));
            }

            return false;
        }
    }
};


?>
