#!/bin/sh

ACLOCAL=aclocal
AUTOHEADER=autoheader
AUTOMAKE=automake
AUTOCONF=autoconf
GNUM4=

echo -n "Locating GNU m4... "
for prog in $M4 gm4 gnum4 m4 ; do
  case `$prog --version 2>&1` in
    *GNU*) ok=yes
           GNUM4=$prog
	   echo "found: $GNUM4"
	   break ;;
    *) ;;
  esac
done
if test x$ok = xno ; then
    echo "not found."
fi

autoheader
 
# Generate the Makefiles and configure files
if ( aclocal --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building macros... "
	$ACLOCAL
	echo "done."
else
	echo "aclocal not found -- aborting"
	exit
fi

if ( $AUTOMAKE --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building Makefile templates... "
	$AUTOMAKE
	echo "done."
else
	echo "automake not found -- aborting"
	exit
fi

if ( $AUTOCONF --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building configure... "
	$AUTOCONF
	echo "done."
else
	echo "autoconf not found -- aborting"
	exit
fi

echo
echo 'run "./configure ; make"'
echo
