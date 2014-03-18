# Aiksaurus, version 1.2.3

m4_define([aiksaurus_version_major],[1])
m4_define([aiksaurus_version_minor],[2])
m4_define([aiksaurus_version_micro],[2])
m4_define(
    [aiksaurus_version],
    [aiksaurus_version_major.aiksaurus_version_minor.aiksaurus_version_micro])
AC_INIT([aiksaurus],[aiksaurus_version],[http://aiksaurus.sourceforge.net/])
AC_CONFIG_SRCDIR([base/Aiksaurus.h])

AIK_MAJOR_VERSION=aiksaurus_version_major
AIK_MINOR_VERSION=aiksaurus_version_minor

# ========================================================================
# IMPORTANT: Making Releases
# 
#   AIK_MICRO_VERSION += 1;
#   AIK_INTERFACE_AGE += 1;
#   AIK_BINARY_AGE += 1;
# 
# if any functions have been added, set AIK_INTERFACE_AGE to 0.
# if backwards compatibility has been broken,
# set AIK_BINARY_AGE and AIK_INTERFACE_AGE to 0.
# 
# similarly for AIKGTK_BINARY_AGE and AIKGTK_INTERFACE_AGE:

AIK_MICRO_VERSION=aiksaurus_version_micro

AIK_INTERFACE_AGE=1
AIK_BINARY_AGE=1

AIKGTK_INTERFACE_AGE=1
AIKGTK_BINARY_AGE=1

# release number, for spec file

AIKSAURUS_RELEASE=1

# 
# ========================================================================

AIKSAURUS_VERSION=$AIK_MAJOR_VERSION.$AIK_MINOR_VERSION.$AIK_MICRO_VERSION

# spec file substitutions
# 
AC_SUBST(AIKSAURUS_VERSION)
AC_SUBST(AIKSAURUS_RELEASE)

# libtool versioning
# 
LT_RELEASE=$AIK_MAJOR_VERSION.$AIK_MINOR_VERSION

AC_SUBST(LT_RELEASE)

CURRENT=`expr $AIK_MICRO_VERSION - $AIK_INTERFACE_AGE`
REVISION=$AIK_INTERFACE_AGE
AGE=`expr $AIK_BINARY_AGE - $AIK_INTERFACE_AGE`

LT_AIK_VERSION_INFO="$CURRENT:$REVISION:$AGE"

AC_SUBST(LT_AIK_VERSION_INFO)

CURRENT=`expr $AIK_MICRO_VERSION - $AIKGTK_INTERFACE_AGE`
REVISION=$AIKGTK_INTERFACE_AGE
AGE=`expr $AIKGTK_BINARY_AGE - $AIKGTK_INTERFACE_AGE`

LT_AIKGTK_VERSION_INFO="$CURRENT:$REVISION:$AGE"

AC_SUBST(LT_AIKGTK_VERSION_INFO)

# initialize automake
#
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE
m4_ifndef([AM_SILENT_RULES], [m4_define([AM_SILENT_RULES],[])])
AM_SILENT_RULES([yes])

# Specify a configuration file
# 
AC_CONFIG_HEADERS(config.h)

AH_TOP([
#ifndef AIKSAURUS_CONFIG_H
#define AIKSAURUS_CONFIG_H
])

# ========================================================================

AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET


LT_PREREQ([2.2.6])
# Make --disable-static the default
LT_INIT([disable-static])

IT_PROG_INTLTOOL([0.50.0])

AC_HEADER_STDC

AC_CHECK_FUNC(getenv)

# GTK+-3.0 front-end configuration
# 
aik_fe_gtk=check

AC_ARG_WITH(gtk,[  --with-gtk              build gtk front-end],[
	if test "$withval" = "no"; then
		aik_fe_gtk=no
	else
		aik_fe_gtk=yes
	fi
])

GTK_CFLAGS=""
GTK_LIBS=""
GTK_DEFS=""

if test $aik_fe_gtk != no; then
	PKG_CHECK_MODULES(GTK,[gtk+-3.0 >= 3.0.0],[
		aik_fe_gtk=yes
	],[	if test $aik_fe_gtk = yes; then
			AC_MSG_ERROR([gtk+-3.0 >= 3.0.0 required for GTK+-3.0 front-end])
		fi
		aik_fe_gtk=no
	])
fi

dnl if test $aik_fe_gtk = yes; then
dnl	GTK_DEFS="-DG_DISABLE_DEPRECATED -DGDK_DISABLE_DEPRECATED -DGDK_PIXBUF_DISABLE_DEPRECATED"
dnl	GTK_DEFS="$GTK_DEFS -DGTK_DISABLE_DEPRECATED -DGNOME_DISABLE_DEPRECATED"
dnl fi

AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)
AC_SUBST(GTK_DEFS)

AM_CONDITIONAL(AIK_FE_GTK,[test $aik_fe_gtk = yes])

# GTK+-2.0 front-end configuration
# 
aik_fe_gtk2=check

AC_ARG_WITH(gtk2,[  --with-gtk2              build gtk2 front-end],[
	if test "$withval" = "no"; then
		aik_fe_gtk2=no
	else
		aik_fe_gtk2=yes
	fi
])

GTK2_CFLAGS=""
GTK2_LIBS=""
GTK2_DEFS=""

if test $aik_fe_gtk2 != no; then
	PKG_CHECK_MODULES(GTK2,[gtk+-2.0 >= 2.0.0],[
		aik_fe_gtk2=yes
	],[	if test $aik_fe_gtk2 = yes; then
			AC_MSG_ERROR([gtk+-2.0 >= 2.0.0 required for GTK+-2.0 front-end])
		fi
		aik_fe_gtk2=no
	])
fi

dnl if test $aik_fe_gtk2 = yes; then
dnl	GTK_DEFS="-DG_DISABLE_DEPRECATED -DGDK_DISABLE_DEPRECATED -DGDK_PIXBUF_DISABLE_DEPRECATED"
dnl	GTK_DEFS="$GTK_DEFS -DGTK_DISABLE_DEPRECATED -DGNOME_DISABLE_DEPRECATED"
dnl fi

AC_SUBST(GTK2_CFLAGS)
AC_SUBST(GTK2_LIBS)
AC_SUBST(GTK2_DEFS)

AM_CONDITIONAL(AIK_FE_GTK2,[test $aik_fe_gtk2 = yes])

dnl ===========================================================================

#AC_CANONICAL_HOST

AC_MSG_CHECKING([for some Win32 platform])
case "$host" in
  *-*-mingw*|*-*-cygwin*)
    platform_win32=yes
    ;;
  *)
    platform_win32=no
    ;;
esac
AC_MSG_RESULT([$platform_win32])
AM_CONDITIONAL(PLATFORM_WIN32, test "$platform_win32" = "yes")

# ========================================================================

AH_BOTTOM([

#endif /* ! AIKSAURUS_CONFIG_H */
])

AC_CONFIG_FILES([
	aiksaurus.spec
	Makefile
	base/aiksaurus-1.0.pc
	base/Makefile
	gtk/aiksaurusgtk3-1.0.pc
	gtk/Makefile
	gtk/src/Makefile
	gtk2/gaiksaurus-1.0.pc
	gtk2/Makefile
	gtk2/src/Makefile
	data/Makefile
    gaiksaurus.desktop.in
    po/Makefile.in
])
AC_OUTPUT

echo ""

if test $aik_fe_gtk = yes; then
	echo "building GTK+-3.0 front end"
else
	echo "not building GTK+-3.0 front end"
fi

if test $aik_fe_gtk2 = yes; then
	echo "building GTK+-2.0 front end"
else
	echo "not building GTK+-2.0 front end"
fi

echo ""
