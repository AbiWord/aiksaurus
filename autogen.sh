#!/bin/sh

libtoolize --version > /dev/null 2> /dev/null || {
    echo "error: libtoolize not found"
    exit 1
}
aclocal --version > /dev/null 2> /dev/null || {
    echo "error: aclocal not found"
    exit 1
}
automake --version > /dev/null 2> /dev/null || {
    echo "error: automake not found"
    exit 1
}
autoconf --version > /dev/null 2> /dev/null || {
    echo "error: autoconf not found"
    exit 1
}
autoheader --version > /dev/null 2> /dev/null || {
    echo "error: autoheader not found"
    exit 1
}

ah_version=x`autoheader --version 2> /dev/null | grep '2\.13'`
if test "$ah_version" != "x"; then
    AUTOHEADER_FLAGS="-l patches $AUTOHEADER_FLAGS"
fi

echo "Running: libtoolize --force --copy"
libtoolize --force --copy || {
    echo "error: libtoolize failed"
    exit 1
}
echo "Running: aclocal $ACLOCAL_FLAGS"
aclocal $ACLOCAL_FLAGS || {
    echo "error: aclocal failed"
    exit 1
}

echo "Checking for PKG_CHECK_MODULES..."

pkgcheckdef=`grep PKG_CHECK_MODULES aclocal.m4 | grep AC_DEFUN`
if test "x$pkgcheckdef" = "x"; then
  echo "Running aclocal -I ac-helpers/pkg-config $ACLOCAL_FLAGS"
  (aclocal -I ac-helpers/pkg-config $ACLOCAL_FLAGS 2>> autogen.err) || {
    echo "aclocal failed! Unable to continue."
    exit 1
  }
  pkgcheckdef=`grep PKG_CHECK_MODULES aclocal.m4 | grep AC_DEFUN`
  if test "x$pkgcheckdef" = "x"; then
    echo ""
    echo "error: PKG_CHECK_MODULES isn't defined"
    echo ""
    echo "   Either pkg.m4 wasn't in aclocal's search path or pkgconfig"
    echo "   (or pkgconfig-devel?) isn't installed."
    echo ""
    echo "   If pkg-config is installed in <prefix> then re-run autogen.sh:"
    echo ""
    echo "       ACLOCAL_FLAGS=\"-I <prefix>/share/aclocal\" ./autogen.sh"
    echo ""
    exit
  fi
fi

echo "Running: autoheader $AUTOHEADER_FLAGS"
autoheader $AUTOHEADER_FLAGS || {
    echo "error: autoheader failed"
    exit 1
}
echo "Running: automake --copy --add-missing --force-missing --foreign"
automake --copy --add-missing --force-missing --foreign || {
    echo "Running: automake --copy --add-missing --foreign"
    automake --copy --add-missing --foreign || {
        echo "error: automake failed"
        exit 1
    }
}
echo "Running: autoconf"
autoconf || {
    echo "error: autoconf failed"
    exit 1
}

intltoolize --force

echo "autogen.sh: configuration generated successfully"
