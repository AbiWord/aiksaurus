dnl Usage: 
dnl   AIK_BZIP2_OPT(<optional>) where <optional> = "no"|"yes"
dnl 
dnl Defines:
dnl   aik_bzip2_opt=[yes|no|DIR]
dnl   aik_bzip2_cppflags
dnl   aik_bzip2_ldflags
dnl   aik_bzip2_libs
dnl 

# Check for optional bzip2

AC_DEFUN([AIK_BZIP2_OPT], [
	aik_bzip2_dir=""
	aik_bzip2_cppflags=""
	aik_bzip2_ldflags=""
	aik_bzip2_libs=""
	if [ test "x$1" = "xno" ]; then
		aik_bzip2_opt=required
	else
		aik_bzip2_opt=check
	fi
	
	AC_ARG_WITH(bzip2,[  --with-bzip2=DIR        BZip2 library in DIR],[
		if [ test "x$withval" = "xno" ]; then
			if [ test $aik_bzip2_opt = required ]; then
				AC_MSG_ERROR([* * * BZip2 library required to build AikSaurus * * *])
			fi
			aik_bzip2_opt=no
		elif [ test "x$withval" = "xyes" ]; then
			aik_bzip2_opt=required
		else
			aik_bzip2_opt=required
			aik_bzip2_dir="$withval"
			aik_bzip2_cppflags="-I$withval/include"
			aik_bzip2_ldflags="-L$withval/lib"
		fi
	])
	if [ test $aik_bzip2_opt != no ]; then
		_aik_bzip2_cppflags="$CPPFLAGS"
		_aik_bzip2_ldflags="$LDFLAGS"

		CPPFLAGS="$CPPFLAGS $aik_bzip2_cppflags"
		LDFLAGS="$LDFLAGS $aik_bzip2_ldflags"

		AC_CHECK_HEADER(bzlib.h,[
			AC_CHECK_LIB(bz2,BZ2_bzWrite,,[
				if [ test $aik_bzip2_opt = required ]; then
					AC_MSG_ERROR([* * * BZip2 library required to build AikSaurus * * *])
				fi
				AC_MSG_WARN([* * * Proceeding w/o bzip2 * * *])
				aik_bzip2_opt=no
			])
		],[	if [ test $aik_bzip2_opt = required ]; then
				AC_MSG_ERROR([* * * BZip2 library required to build AikSaurus * * *])
			fi
			aik_bzip2_opt=no
		])

		CPPFLAGS="$_aik_bzip2_cppflags"
		LDFLAGS="$_aik_bzip2_ldflags"
	fi
	if [ test $aik_bzip2_opt != no ]; then
		if [ test "x$aik_bzip2_dir" = "x" ]; then
			aik_bzip2_opt=yes
		else
			aik_bzip2_opt="$aik_bzip2_dir"
		fi
		aik_bzip2_libs="-lbz2"
	fi
])

dnl Usage: 
dnl   AIK_GLIB12_OPT(<micro-version>,<optional>) where <optional> = "no"|"yes"
dnl   AIK_GTK12(<micro-version>)
dnl 
dnl Defines:
dnl   aik_glib_opt=[yes|no|DIR]
dnl   aik_glib_config (if aik_glib_opt != no)
dnl   aik_gtk_config
dnl 

# Check for optional glib

AC_DEFUN([AIK_GLIB12_OPT], [	
	aik_glib_config=""
	if [ test "x$2" = "xyes" ]; then
		aik_glib_opt=check
	else
		aik_glib_opt=required
	fi
	AC_ARG_WITH(glib,[  --with-glib[=DIR]         Use glib (v1.2) [in DIR] ],[
		if [ test "x$withval" = "xno" ]; then
			if [ test $aik_glib_opt = required ]; then
				AC_MSG_ERROR([* * * glib-1.2 is not optional! * * *])
			fi
			aik_glib_opt=no
		elif [ test "x$withval" = "xyes" ]; then
			aik_glib_opt=required
			aik_glib_dir=""
		else
			aik_glib_opt=required
			aik_glib_dir="$withval"
		fi
	],[	aik_glib_dir=""
	])
	if [ test $aik_glib_opt != no ]; then
		if [ test "x$aik_glib_dir" = "x" ]; then
			AC_PATH_PROG(aik_glib_config,glib12-config, ,[$PATH])
		else
			AC_PATH_PROG(aik_glib_config,glib12-config, ,[$aik_glib_dir/bin:$PATH])
		fi
		if [ test "x$aik_glib_config" = "x" ]; then
			if [ test "x$aik_glib_dir" = "x" ]; then
				AC_PATH_PROG(aik_glib_config,glib-config, ,[$PATH])
			else
				AC_PATH_PROG(aik_glib_config,glib-config, ,[$aik_glib_dir/bin:$PATH])
			fi
		fi
		if [ test "x$aik_glib_config" = "x" ]; then
			if [ test $aik_glib_opt = required ]; then
				AC_MSG_ERROR([* * * unable to find glib12-config or glib-config in path! * * *])
			fi
			aik_glib_opt=no
		fi
	fi
	if [ test $aik_glib_opt != no ]; then
	        if [ $aik_glib_config --version > /dev/null 2>&1 ]; then
			aik_glib_opt_version=`$aik_glib_config --version`
			aik_glib_opt_major=`echo $aik_glib_opt_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
			aik_glib_opt_minor=`echo $aik_glib_opt_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
			aik_glib_opt_micro=`echo $aik_glib_opt_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

			aik_glib_opt_version=""
			if [ test $aik_glib_opt_major -eq 1 ]; then
				if [ test $aik_glib_opt_minor -eq 2 ]; then
					if [ test $aik_glib_opt_micro -ge "$1" ]; then
						aik_glib_opt_version="1.2.$aik_glib_opt_micro"
					fi
				fi
			fi
			if [ test "x$aik_glib_opt_version" = "x" ]; then
				if [ test $aik_glib_opt = required ]; then
					AC_MSG_ERROR([* * * glib version is incompatible! require at least "1.2.$1" * * *])
				fi
				aik_glib_opt=no
			fi
		else
			AC_MSG_WARN([* * * problem obtaining glib version... * * *])
			if [ test $aik_glib_opt = required ]; then
				AC_MSG_ERROR([* * * unable to determine glib version! * * *])
			fi
			aik_glib_opt=no
		fi
	fi
	if [ test $aik_glib_opt != no ]; then
		if [ test "x$aik_glib_dir" = "x" ]; then
			aik_glib_opt=yes
		else
			aik_glib_opt="$aik_glib_dir"
		fi
	fi
])

# Check for required gtk+

AC_DEFUN([AIK_GTK12], [	
	aik_gtk_config=""
	AC_ARG_WITH(gtk,[  --with-gtk[=DIR]          Use gtk+ (v1.2) [in DIR] ],[
		if [ test "x$withval" = "xno" ]; then
			AC_MSG_ERROR([* * * gtk-1.2 is not optional! * * *])
		elif [ test "x$withval" = "xyes" ]; then
			aik_gtk_dir=""
		else
			aik_gtk_dir="$withval"
		fi
	],[	aik_gtk_dir=""
	])
	if [ test "x$aik_gtk_dir" = "x" ]; then
		AC_PATH_PROG(aik_gtk_config,gtk12-config, ,[$PATH])
	else
		AC_PATH_PROG(aik_gtk_config,gtk12-config, ,[$aik_gtk_dir/bin:$PATH])
	fi
	if [ test "x$aik_gtk_config" = "x" ]; then
		if [ test "x$aik_gtk_dir" = "x" ]; then
			AC_PATH_PROG(aik_gtk_config,gtk-config, ,[$PATH])
		else
			AC_PATH_PROG(aik_gtk_config,gtk-config, ,[$aik_gtk_dir/bin:$PATH])
		fi
	fi
	if [ test "x$aik_gtk_config" = "x" ]; then
		AC_MSG_ERROR([* * * unable to find gtk12-config or gtk-config in path! * * *])
	fi
        if [ $aik_gtk_config --version > /dev/null 2>&1 ]; then
		aik_gtk_version=`$aik_gtk_config --version`
		aik_gtk_major=`echo $aik_gtk_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
		aik_gtk_minor=`echo $aik_gtk_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
		aik_gtk_micro=`echo $aik_gtk_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`

		aik_gtk_version=""
		if [ test $aik_gtk_major -eq 1 ]; then
			if [ test $aik_gtk_minor -eq 2 ]; then
				if [ test $aik_gtk_micro -ge "$1" ]; then
					aik_gtk_version="1.2.$aik_gtk_micro"
				fi
			fi
		fi
		if [ test "x$aik_gtk_version" = "x" ]; then
			AC_MSG_ERROR([* * * gtk version is incompatible! require at least "1.2.$1" * * *])
		fi
	else
		AC_MSG_ERROR([* * * unable to determine gtk version! * * *])
	fi
])
