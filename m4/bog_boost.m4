# macro baseada no AX_BOOST_BASE:
# LICENSE
#
#   Copyright (c) 2008 Thomas Porschberg <thomas@randspringer.de>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([BG_BOOST_BASE],
[
AC_ARG_WITH([boost],
	AS_HELP_STRING([--with-boost@<:@=DIR@:>@], [use boost (default is yes) - it is possible to specify the root directory for boost (optional)]),
	[
    if test "$withval" = "no"; then
		want_boost="no"
    elif test "$withval" = "yes"; then
        want_boost="yes"
        ac_boost_path=""
    else
	    want_boost="yes"
        ac_boost_path="$withval"
	fi
    ],
    [want_boost="yes"])


AC_ARG_WITH([boost-libdir],
        AS_HELP_STRING([--with-boost-libdir=LIB_DIR],
        [Force given directory for boost libraries. Note that this will overwrite library path detection, so use this parameter only if default library detection fails and you know exactly where your boost libraries are located.]),
        [
        if test -d $withval
        then
                ac_boost_lib_path="$withval"
        else
                AC_MSG_ERROR(--with-boost-libdir expected directory name)
        fi
        ],
        [ac_boost_lib_path=""]
)

if test "x$want_boost" = "xyes"; then
	boost_lib_version_req=ifelse([$1], ,1.20.0,$1)
	boost_lib_version_req_shorten=`expr $boost_lib_version_req : '\([[0-9]]*\.[[0-9]]*\)'`
	boost_lib_version_req_major=`expr $boost_lib_version_req : '\([[0-9]]*\)'`
	boost_lib_version_req_minor=`expr $boost_lib_version_req : '[[0-9]]*\.\([[0-9]]*\)'`
	boost_lib_version_req_sub_minor=`expr $boost_lib_version_req : '[[0-9]]*\.[[0-9]]*\.\([[0-9]]*\)'`
	if test "x$boost_lib_version_req_sub_minor" = "x" ; then
		boost_lib_version_req_sub_minor="0"
    	fi
	WANT_BOOST_VERSION=`expr $boost_lib_version_req_major \* 100000 \+  $boost_lib_version_req_minor \* 100 \+ $boost_lib_version_req_sub_minor`
	AC_MSG_CHECKING(for boostlib >= $boost_lib_version_req)
	succeeded=no

	dnl first we check the system location for boost libraries
	dnl this location ist chosen if boost libraries are installed with the --layout=system option
	dnl or if you install boost with RPM
	if test "$ac_boost_path" != ""; then
		BOOST_LIB="$ac_boost_path/lib"
		BOOST_INC="$ac_boost_path/include/"
	else
		for ac_boost_path_tmp in /usr /usr/local /opt /opt/local ; do
			if test -d "$ac_boost_path_tmp/include/boost" && test -r "$ac_boost_path_tmp/include/boost"; then
				for ac_lib_path_tmp in lib lib64; do
					if test -d $ac_boost_path_tmp/$ac_lib_path_tmp; then 
						BOOST_LIB="$ac_boost_path_tmp/$ac_lib_path_tmp"
					fi
				done
				BOOST_INC="$ac_boost_path_tmp/include"
				break;
			fi
		done
	fi

    dnl overwrite ld flags if we have required special directory with
    dnl --with-boost-libdir parameter
    if test "$ac_boost_lib_path" != ""; then
       BOOST_LIB="$ac_boost_lib_path"
    fi

	CPPFLAGS_SAVED="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS -I$BOOST_INC"
	export CPPFLAGS

	LDFLAGS_SAVED="$LDFLAGS"
	LDFLAGS="$LDFLAGS -L$BOOST_LIB"
	export LDFLAGS

	AC_LANG_PUSH(C++)
     	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
	@%:@include <boost/version.hpp>
	]], [[
	#if BOOST_VERSION >= $WANT_BOOST_VERSION
	// Everything is okay
	#else
	#  error Boost version is too old
	#endif
	]])],[
        AC_MSG_RESULT(yes)
	succeeded=yes
	found_system=yes
       	],[
       	])
	AC_LANG_POP([C++])

	dnl if we found no boost with system layout we search for boost libraries
	dnl built and installed without the --layout=system option or for a staged(not installed) version
	if test "x$succeeded" != "xyes"; then
		_version=0
		if test "$ac_boost_path" != ""; then
			if test -d "$ac_boost_path" && test -r "$ac_boost_path"; then
				for i in `ls -d $ac_boost_path/include/boost-* 2>/dev/null`; do
					_version_tmp=`echo $i | sed "s#$ac_boost_path##" | sed 's/\/include\/boost-//' | sed 's/_/./'`
					V_CHECK=`expr $_version_tmp \> $_version`
					if test "$V_CHECK" = "1" ; then
						_version=$_version_tmp
					fi
					VERSION_UNDERSCORE=`echo $_version | sed 's/\./_/'`
					BOOST_INC="$ac_boost_path/include/boost-$VERSION_UNDERSCORE"
				done
			fi
		else
			for ac_boost_path in /usr /usr/local /opt /opt/local ; do
				if test -d "$ac_boost_path" && test -r "$ac_boost_path"; then
					for i in `ls -d $ac_boost_path/include/boost-* 2>/dev/null`; do
						_version_tmp=`echo $i | sed "s#$ac_boost_path##" | sed 's/\/include\/boost-//' | sed 's/_/./'`
						V_CHECK=`expr $_version_tmp \> $_version`
						if test "$V_CHECK" = "1" ; then
							_version=$_version_tmp
	               					best_path=$ac_boost_path
						fi
					done
				fi
			done

			VERSION_UNDERSCORE=`echo $_version | sed 's/\./_/'`
			BOOST_INC="$best_path/include/boost-$VERSION_UNDERSCORE"
            if test "$ac_boost_lib_path" = ""
            then
               BOOST_LIB="$best_path/lib"
            fi

	    		if test "x$BOOST_ROOT" != "x"; then
				if test -d "$BOOST_ROOT" && test -r "$BOOST_ROOT" && test -d "$BOOST_ROOT/stage/lib" && test -r "$BOOST_ROOT/stage/lib"; then
					version_dir=`expr //$BOOST_ROOT : '.*/\(.*\)'`
					stage_version=`echo $version_dir | sed 's/boost_//' | sed 's/_/./g'`
			        	stage_version_shorten=`expr $stage_version : '\([[0-9]]*\.[[0-9]]*\)'`
					V_CHECK=`expr $stage_version_shorten \>\= $_version`
                    if test "$V_CHECK" = "1" -a "$ac_boost_lib_path" = "" ; then
						AC_MSG_NOTICE(We will use a staged boost library from $BOOST_ROOT)
						BOOST_INC="$BOOST_ROOT"
						BOOST_LIB="$BOOST_ROOT/stage/lib"
					fi
				fi
	    		fi
		fi

		CPPFLAGS="$CPPFLAGS -I$BOOST_INC"
		export CPPFLAGS
		LDFLAGS="$LDFLAGS -L$BOOST_LIB"
		export LDFLAGS

		AC_LANG_PUSH(C++)
	     	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
		@%:@include <boost/version.hpp>
		]], [[
		#if BOOST_VERSION >= $WANT_BOOST_VERSION
		// Everything is okay
		#else
		#  error Boost version is too old
		#endif
		]])],[
        	AC_MSG_RESULT(yes)
		succeeded=yes
		found_system=yes
       		],[
	       	])
		AC_LANG_POP([C++])
	fi

	if test "$succeeded" != "yes" ; then
		if test "$_version" = "0" ; then
			AC_MSG_ERROR([[We could not detect the boost libraries (version $boost_lib_version_req_shorten or higher). If you have a staged boost library (still not installed) please specify \$BOOST_ROOT in your environment and do not give a PATH to --with-boost option.  If you are sure you have boost installed, then check your version number looking in <boost/version.hpp>. See http://randspringer.de/boost for more documentation.]])
		else
			AC_MSG_NOTICE([Your boost libraries seems to old (version $_version).])
		fi
	else
		AC_SUBST(BOOST_INC)
		AC_SUBST(BOOST_LIB)
		AC_DEFINE(HAVE_BOOST,,[define if the Boost library is available])
	fi

	CPPFLAGS="$CPPFLAGS_SAVED"
	LDFLAGS="$LDFLAGS_SAVED"
fi

])

AC_DEFUN([BG_BOOST_LIB],
[
	BG_BOOST_BASE
	if test "a$BOOST_LDFLAGS" == "a"; then
 		BOOST_LDFLAGS=-L${BOOST_LIB}
	fi

	AC_ARG_WITH([boost-static],
		AS_HELP_STRING([--with-boost-static],
			[Use the static version of boost, if available]),
		[
		stat_lib=$(ls $BOOST_LIB/libboost_$1-*.a  $BOOST_LIB/libboost_$1.a 2>/dev/null | head -1)
		if test -e "$stat_lib"; then 
			BOOST_LDFLAGS=$BOOST_LDFLAGS\ $stat_lib
		fi
		],
		[
		dyn_lib=$(ls $BOOST_LIB/libboost_$1-*.so $BOOST_LIB/libboost_$1.so 2>/dev/null | head -1)
		if test -e "$dyn_lib"; then
			lib=`echo $dyn_lib | sed 's/.*\(boost.*\).so/\1/'`
			BOOST_LDFLAGS=$BOOST_LDFLAGS\ -l$lib
		fi
	])
	AC_SUBST(BOOST_LDFLAGS)
])

AC_DEFUN([BG_BOOST_TR1],
[
	BG_BOOST_BASE([1.34])
	BG_BOOST_LIB([regex])
	BOOST_CPPFLAGS="-I$BOOST_INC/boost/tr1/tr1 -I$BOOST_INC"
	AC_LANG_PUSH(C++)

	CPPFLAGS_SAVED="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
	export CPPFLAGS

	LDFLAGS_SAVED="$LDFLAGS"
	LDFLAGS="$LDFLAGS $BOOST_LDFLAGS"
	export LDFLAGS

	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#include <regexp>

main()
{
	std::tr1::regexp a;
}
		]])],
		[],[
			BOOST_CPPFLAGS="$BOOST_CPPFLAGS -DBOOST_TR1_DISABLE_INCLUDE_NEXT"
	]);

	export CPPFLAGS="$CPPFLAGS_SAVED"
	export LDFLAGS="$LDFLAGS_SAVED"

	AC_SUBST(BOOST_CPPFLAGS)
])

