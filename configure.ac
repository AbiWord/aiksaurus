dnl Process this file with autoconf to produce a configure script.
AC_INIT([AikSaurus.cpp],0.11,[jared@aiksaurus.com])

dnl This next section is courtesy gtk+
dnl
# Making releases:
#   AIK_MICRO_VERSION += 1;
#   AIK_INTERFACE_AGE += 1;
#   AIK_BINARY_AGE += 1;
# if any functions have been added, set AIK_INTERFACE_AGE to 0.
# if backwards compatibility has been broken,
# set AIK_BINARY_AGE and AIK_INTERFACE_AGE to 0.
#
AIK_MAJOR_VERSION=0
AIK_MINOR_VERSION=11
AIK_MICRO_VERSION=1
AIK_INTERFACE_AGE=0
AIK_BINARY_AGE=0
AIK_VERSION=$AIK_MAJOR_VERSION.$AIK_MINOR_VERSION.$AIK_MICRO_VERSION

AC_SUBST(AIK_MAJOR_VERSION)
AC_SUBST(AIK_MINOR_VERSION)
AC_SUBST(AIK_MICRO_VERSION)
AC_SUBST(AIK_INTERFACE_AGE)
AC_SUBST(AIK_BINARY_AGE)
AC_SUBST(AIK_VERSION)

# libtool versioning
LT_RELEASE=$AIK_MAJOR_VERSION.$AIK_MINOR_VERSION
LT_CURRENT=`expr $AIK_MICRO_VERSION - $AIK_INTERFACE_AGE`
LT_REVISION=$AIK_INTERFACE_AGE
LT_AGE=`expr $AIK_BINARY_AGE - $AIK_INTERFACE_AGE`
AC_SUBST(LT_RELEASE)
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

# For automake.
VERSION=$AIK_VERSION
PACKAGE=AikSaurus

AM_INIT_AUTOMAKE($PACKAGE, $VERSION)

AM_CONFIG_HEADER(config.h)

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX

AC_MSG_CHECKING("whether $CXX accepts -Wall -pg -fprofile-arcs")
SAVE_CXXFLAGS=$CXXFLAGS
CXXFLAGS="-Wall -pg -fprofile-arcs $CXXFLAGS" 
AC_TRY_COMPILE(,,[
	AC_MSG_RESULT("yes")
],[	AC_MSG_RESULT("no")
	CXXFLAGS=$SAVE_CXXFLAGS
])

AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_INSTALL 

AC_ARG_PROGRAM 

AM_PROG_LIBTOOL

dnl Checks for header files.
AC_HEADER_STDC
 
dnl Checks for typedefs, structures, and compiler characteristics.
AM_C_PROTOTYPES 
AC_C_CONST
AC_C_INLINE

AIK_BZIP2_OPT(no)
AC_SUBST(aik_bzip2_cppflags)
AC_SUBST(aik_bzip2_ldflags)
AC_SUBST(aik_bzip2_libs)

AC_ARG_ENABLE(GTK,[  --enable-GTK            build GTK front end for AikSaurus (default: yes)],[
	if test "x$enableval" = "xno"; then
		aik_fe_gtk=no
	else
		aik_fe_gtk=yes
	fi
],[	aik_fe_gtk=yes
])

if test $aik_fe_gtk = yes; then
	AIK_GTK12(0)
	aik_gtk_cflags=`$aik_gtk_config --cflags`
	aik_gtk_libs=`$aik_gtk_config --libs`
	AC_SUBST(aik_gtk_cflags)
	AC_SUBST(aik_gtk_libs)
	AM_CONDITIONAL(AIK_BUILD_GTK,true)
fi

AC_CONFIG_FILES([
	Makefile
	data/Makefile
	gtk/Makefile
	aiksaurus.spec
])
AC_OUTPUT
