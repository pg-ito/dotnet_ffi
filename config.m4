dnl $Id$
dnl config.m4 for extension dotnet_ffi

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(dotnet_ffi, for dotnet_ffi support,
dnl Make sure that the comment is aligned:
dnl [  --with-dotnet_ffi             Include dotnet_ffi support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(dotnet_ffi, whether to enable dotnet_ffi support,
dnl Make sure that the comment is aligned:
[  --enable-dotnet_ffi           Enable dotnet_ffi support])

AC_MSG_CHECKING( phpdotnetffivariableis $PHP_DOTNET_FFI)
if test "$PHP_DOTNET_FFI" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=`$PKG_CONFIG foo --cflags`
  dnl     LIBFOO_LIBDIR=`$PKG_CONFIG foo --libs`
  dnl     LIBFOO_VERSON=`$PKG_CONFIG foo --modversion`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, DOTNET_FFI_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-dotnet_ffi -> check with-path
  dnl  SEARCH_PATH="./ /usr/local /usr /usr/local/lib /usr/lib"     # you might want to change this
  SEARCH_PATH="./"     # search only in current dir.
  SEARCH_FOR="coreclrhost/coreclrhost.h"  # you most likely want to change this
  if test -r $PHP_DOTNET_FFI/$SEARCH_FOR; then # path given as parameter
    DOTNET_FFI_DIR=$PHP_DOTNET_FFI
  else # search default path list
    AC_MSG_CHECKING([for dotnet_ffi files in default path])
    for i in $SEARCH_PATH ; do
    AC_MSG_CHECKING(searching $i)
      if test -r $i/$SEARCH_FOR; then
        DOTNET_FFI_DIR=$i
        AC_MSG_RESULT(found in $i)
        PHP_ADD_INCLUDE($i)
      fi
    done
  fi
  
  if test -z "$DOTNET_FFI_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the dotnet_ffi distribution])
  fi

  dnl # --with-dotnet_ffi -> add include path
  dnl PHP_ADD_INCLUDE($DOTNET_FFI_DIR/include)

  dnl # --with-dotnet_ffi -> check for lib and symbol presence
  dnl LIBNAME=dotnet_ffi # you may want to change this
  dnl LIBSYMBOL=dotnet_ffi # you most likely want to change this 
  
  dnl $LIBNAME=libcoreclr_ctlpp
  dnl AC_MSG_CHECKING(libname $LIBNAME)
  dnl PHP_CHECK_LIBRARY(libcoreclr_ctlpp,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DOTNET_FFI_DIR/$PHP_LIBDIR, DOTNET_FFI_SHARED_LIBADD)
dnl 
  dnl   AC_DEFINE(HAVE_DOTNET_FFILIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong dotnet_ffi lib version or lib not found])
  dnl ],[
  dnl   -L$DOTNET_FFI_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl 
  dnl PHP_SUBST(DOTNET_FFI_SHARED_LIBADD)
  AC_MSG_CHECKING(phplibdir $DOTNET_FFI_DIR/$PHP_LIBDIR)

  PHP_ADD_LIBRARY_WITH_PATH("coreclr_ctlpp", $DOTNET_FFI_DIR/coreclrhost, DOTNET_FFI_SHARED_LIBADD)
  PHP_SUBST(DOTNET_FFI_SHARED_LIBADD)
  PHP_NEW_EXTENSION(dotnet_ffi, dotnet_ffi.c, $ext_shared)
fi
