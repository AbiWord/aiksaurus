AC_INIT([aiksaurus],[1.0],[http://aiksaurus.sourceforge.net/])
AC_CONFIG_SRCDIR([core/src/Aiksaurus.h])

# Aiksaurus, version 1.0

AIK_MAJOR_VERSION=1
AIK_MINOR_VERSION=0

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

AIK_MICRO_VERSION=0

AIK_INTERFACE_AGE=0
AIK_BINARY_AGE=0

AIKGTK_INTERFACE_AGE=0
AIKGTK_BINARY_AGE=0

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

LT_CURRENT=`expr $AIK_MICRO_VERSION - $AIK_INTERFACE_AGE`
LT_REVISION=$AIK_INTERFACE_AGE
LT_AGE=`expr $AIK_BINARY_AGE - $AIK_INTERFACE_AGE`

LT_AIK_VERSION_INFO="$LT_CURRENT:$LT_REVISION:$LT_AGE"

AC_SUBST(LT_AIK_VERSION_INFO)

LT_CURRENT=`expr $AIK_MICRO_VERSION - $AIKGTK_INTERFACE_AGE`
LT_REVISION=$AIKGTK_INTERFACE_AGE
LT_AGE=`expr $AIKGTK_BINARY_AGE - $AIKGTK_INTERFACE_AGE`

LT_AIKGTK_VERSION_INFO="$LT_CURRENT:$LT_REVISION:$LT_AGE"

AC_SUBST(LT_AIKGTK_VERSION_INFO)

# initialize automake
# 
AM_INIT_AUTOMAKE(aiksaurus,$AIKSAURUS_VERSION)

# Specify a configuration file
# 
AM_CONFIG_HEADER(config.h)

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

AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AM_PROG_LIBTOOL

AC_HEADER_STDC

AC_CHECK_FUNC(getenv)

# GTK+-2.0 front-end configuration
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
	PKG_CHECK_MODULES(GTK,[gtk+-2.0 >= 2.0.0],[
		aik_fe_gtk=yes
	],[	if test $aik_fe_gtk = yes; then
			AC_MSG_ERROR([gtk+-2.0 >= 2.0.0 required for GTK+ front-end])
		fi
		aik_fe_gtk=no
	])
fi
if test $aik_fe_gtk = yes; then
	GTK_DEFS="-DG_DISABLE_DEPRECATED -DGDK_DISABLE_DEPRECATED -DGDK_PIXBUF_DISABLE_DEPRECATED"
	GTK_DEFS="$GTK_DEFS -DGTK_DISABLE_DEPRECATED -DGNOME_DISABLE_DEPRECATED"
fi

AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)
AC_SUBST(GTK_DEFS)

AM_CONDITIONAL(AIK_FE_GTK,[test $aik_fe_gtk = yes])

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
	core/aiksaurus-1.0.pc
	core/Makefile
	core/src/Makefile
	core/data/Makefile
	gtk/gaiksaurus-1.0.pc
	gtk/Makefile
	gtk/src/Makefile
])
AC_OUTPUT

echo ""

if test $aik_fe_gtk = yes; then
	echo "building GTK+-2.0 front end"
else
	echo "not building GTK+-2.0 front end"
fi

echo ""
