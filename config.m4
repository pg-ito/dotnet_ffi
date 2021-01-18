dnl config.m4 for extension dotnet_ffi

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([dotnet_ffi],
dnl   [for dotnet_ffi support],
dnl   [AS_HELP_STRING([--with-dotnet_ffi],
dnl     [Include dotnet_ffi support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([dotnet_ffi],
  [whether to enable dotnet_ffi support],
  [AS_HELP_STRING([--enable-dotnet_ffi],
    [Enable dotnet_ffi support])],
  [no])

if test "$PHP_DOTNET_FFI" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, DOTNET_FFI_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-dotnet_ffi -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/dotnet_ffi.h"  # you most likely want to change this
  dnl if test -r $PHP_DOTNET_FFI/$SEARCH_FOR; then # path given as parameter
  dnl   DOTNET_FFI_DIR=$PHP_DOTNET_FFI
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for dotnet_ffi files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DOTNET_FFI_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DOTNET_FFI_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the dotnet_ffi distribution])
  dnl fi

  AC_MSG_CHECKING( phpdotnetffivariableis $PHP_DOTNET_FFI)
  dnl  SEARCH_PATH="./ /usr/local /usr /usr/local/lib /usr/lib"     # you might want to change this
  SEARCH_PATH="./ "     # search only in current dir.
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



  dnl Remove this code block if the library supports pkg-config.
  dnl --with-dotnet_ffi -> add include path
  dnl PHP_ADD_INCLUDE($DOTNET_FFI_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-dotnet_ffi -> check for lib and symbol presence
  dnl LIBNAME=DOTNET_FFI # you may want to change this
  dnl LIBSYMBOL=DOTNET_FFI # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_DOTNET_FFI_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your dotnet_ffi library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DOTNET_FFI_DIR/$PHP_LIBDIR, DOTNET_FFI_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DOTNET_FFI_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your dotnet_ffi library.])
  dnl ],[
  dnl   -L$DOTNET_FFI_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DOTNET_FFI_SHARED_LIBADD)

  AC_MSG_CHECKING(phplibdir $DOTNET_FFI_DIR/$PHP_LIBDIR)

  dnl PHP_ADD_LIBRARY_WITH_PATH("coreclr_ctlpp", $DOTNET_FFI_DIR/coreclrhost, DOTNET_FFI_SHARED_LIBADD)
  dnl PHP_SUBST(DOTNET_FFI_SHARED_LIBADD)

  dnl static link coreclrhost/libcoreclr_ctlpp.a
  PHP_ADD_LIBRARY_WITH_PATH("coreclr_ctlpp", $DOTNET_FFI_DIR/coreclrhost, EXTRA_LDFLAGS)

  echo -e "\ncflags $CFLAGS"
  echo "cxxflags $CXXFLAGS"
  dnl In case of no dependencies
  AC_DEFINE(HAVE_DOTNET_FFI, 1, [ Have dotnet_ffi support ])

  PHP_NEW_EXTENSION(dotnet_ffi, dotnet_ffi.c, $ext_shared)
fi
