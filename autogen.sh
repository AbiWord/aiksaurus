#!/bin/sh
# Run this to generate all the initial makefiles, etc.

if test "x$SHELL" = "x"; then
	SHELL=/bin/sh
fi

$SHELL libtoolize --help > /dev/null 2> /dev/null || { echo "Unable to run libtoolize"; exit 1; }
$SHELL autoconf   --help > /dev/null 2> /dev/null || { echo "Unable to run autoconf";   exit 1; }
$SHELL automake   --help > /dev/null 2> /dev/null || { echo "Unable to run automake";   exit 1; }

echo "Running: libtoolize --force --copy"
$SHELL libtoolize --force --copy || {
	echo "**Error**: libtoolize failed.";
	exit 1;
}

echo "Running: aclocal"
$SHELL aclocal || {
	echo "**Error**: aclocal failed.";
	exit 1;
}

echo "Running: autoheader"
$SHELL autoheader || {
	echo "**Error**: autoheader failed.";
	exit 1;
}

echo "Running: automake -a --foreign"
$SHELL automake -a --foreign || {
	echo "**Error**: automake failed.";
	exit 1;
}

echo "Running: autoconf"
$SHELL autoconf || {
	echo "**Error**: autoconf failed.";
	exit 1;
}
