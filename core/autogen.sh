#!/bin/sh

libtoolize --force --copy
 
# Generate the Makefiles and configure files
if ( aclocal --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building macros... "
	aclocal $ACLOCAL_FLAGS
	echo "done."
else
	echo "aclocal not found -- aborting"
	exit
fi

if ( automake --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building Makefile templates... "
	automake -a --foreign || automake
	echo "done."
else
	echo "automake not found -- aborting"
	exit
fi

autoheader

if ( autoconf --version ) </dev/null > /dev/null 2>&1; then
	echo -n "Building configure... "
	autoconf
	echo "done."
else
	echo "autoconf not found -- aborting"
	exit
fi

echo
echo 'run "./configure ; make"'
echo
