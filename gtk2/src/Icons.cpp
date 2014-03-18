/*
 * AiksaurusGTK - A GTK interface to the AikSaurus library
 * Copyright (C) 2001 by Jared Davis
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include "Icons.h"

namespace AiksaurusGTK_impl
{
    namespace Icons
    {

        const char *backNormal[] =
        {
            "20 16 5 1",
            "a c #4a484a",
            "# c #737573",
            "c c #a4a1a4",
            "b c #cdcacd",
            ". c None",
            "....................",
            "....................",
            "....................",
            "........#a..........",
            ".......#ba..........",
            "......#bba#####a....",
            ".....#bbccccccca....",
            "....#bbcccccccca....",
            "....a#ccccccccca....",
            ".....a#c#######a....",
            "......a##aaaaaaa....",
            ".......a#a..........",
            "........aa..........",
            "....................",
            "....................",
            "...................."
        };


        const char *backHover[] = 
        {
            "20 16 6 1",
            "a c #005d00",
            "# c #009900",
            "c c #00ce00",
            "b c #00ff00",
            "d c #31ce00",
            ". c None",
            "....................",
            "....................",
            "....................",
            "........#a..........",
            ".......#ba..........",
            "......#bba#####a....",
            ".....#bbccccccca....",
            "....#bbcddddddca....",
            "....a#ccccccccca....",
            ".....a#c#######a....",
            "......a##aaaaaaa....",
            ".......a#a..........",
            "........aa..........",
            "....................",
            "....................",
            "...................."
        };


        const char *forwardNormal[] = 
        {
            "20 16 5 1",
            "c c #4a484a",
            "# c #737573",
            "b c #a4a1a4",
            "a c #cdcacd",
            ". c None",
            "....................",
            "....................",
            "....................",
            "..........##........",
            "..........#a#.......",
            "....#######ab#......",
            "....#aaaaaaaab#.....",
            "....#abbbbbbbbb#....",
            "....#abbbbbbbb#c....",
            "....########b#c.....",
            "....ccccccc##c......",
            "..........c#c.......",
            "..........cc........",
            "....................",
            "....................",
            "...................."
        };


        const char *forwardHover[] = 
        {
            "20 16 6 1",
            "d c #005d00",
            "# c #009900",
            "b c #00ce00",
            "a c #00ff00",
            "c c #31ce00",
            ". c None",
            "....................",
            "....................",
            "....................",
            "..........##........",
            "..........#a#.......",
            "....#######ab#......",
            "....#aaaaaaaab#.....",
            "....#accccccbbb#....",
            "....#abbbbbbbb#d....",
            "....########b#d.....",
            "....ddddddd##d......",
            "..........d#d.......",
            "..........dd........",
            "....................",
            "....................",
            "...................."
        };


        const char *searchNormal[] = 
        {
            "61 16 6 1",
            "d c #000000",
            "a c #4a484a",
            "# c #737573",
            "c c #a4a1a4",
            "b c #cdcacd",
            ". c None",
            ".............................................................",
            "............#####a...........................................",
            "............#bcc#a...........................................",
            "............#bcc#a...................................dd......",
            "............#bcc#a....ddddd..........................dd......",
            "......#a....#bcc#a...dd..............................dd......",
            ".....#ba....#bcc#a...dd......dddd...dddd..dd.d..dddd.ddddd...",
            "....#bba#####bcc#a...ddddd..dd..dd.....dd.dddd.dd....dd..dd..",
            "...#bbcccccccccc#a....ddddd.dddddd..ddddd.dd...dd....dd..dd..",
            "..#bbccccccccccc#a.......dd.dd.....dd..dd.dd...dd....dd..dd..",
            "..a#cccccccccccc#a.......dd.dd.....dd..dd.dd...dd....dd..dd..",
            "...a#c###########a...ddddd...ddddd..ddddd.dd....dddd.dd..dd..",
            "....a##aaaaaaaaaaa...........................................",
            ".....a#a.....................................................",
            "......aa.....................................................",
            "............................................................."
        };


        const char *searchHover[] = 
        {
            "61 16 7 1",
            "d c #000000",
            "a c #005d00",
            "# c #009900",
            "c c #00ce00",
            "b c #00ff00",
            "e c #31ce00",
            ". c None",
            ".............................................................",
            "............#####a...........................................",
            "............#bcc#a...........................................",
            "............#bcc#a...................................dd......",
            "............#bcc#a....ddddd..........................dd......",
            "......#a....#bcc#a...dd..............................dd......",
            ".....#ba....#bcc#a...dd......dddd...dddd..dd.d..dddd.ddddd...",
            "....#bba#####bcc#a...ddddd..dd..dd.....dd.dddd.dd....dd..dd..",
            "...#bbcccccccccc#a....ddddd.dddddd..ddddd.dd...dd....dd..dd..",
            "..#bbceeeeeecccc#a.......dd.dd.....dd..dd.dd...dd....dd..dd..",
            "..a#cccccccccccc#a.......dd.dd.....dd..dd.dd...dd....dd..dd..",
            "...a#c###########a...ddddd...ddddd..ddddd.dd....dddd.dd..dd..",
            "....a##aaaaaaaaaaa...........................................",
            ".....a#a.....................................................",
            "......aa.....................................................",
            "............................................................."
        };

    }
}
