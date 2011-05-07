#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([CopyPasteKiller], [0.1], [victor@bogado.net])
m4_include([m4/bog_boost.m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign dist-bzip2 subdir-objects])
AC_CONFIG_SRCDIR([src/main.cpp])

# Checks for programs.
CXXFLAGS+="-std=c++0x"
AC_PROG_CXX

# Checks for libraries.
BG_BOOST_LIB([regex])
AC_CHECK_LIB([pthread], [pthread_cancel], 
[
	PTHREAD=-lpthread
],
[
	AC_MSG_ERROR([Could not find pthread], -1)
])
AC_CHECK_TOOL([GTEST_CONFIG],[gtest-config],[no])
GTEST_CPPFLAGS=`${GTEST_CONFIG} --cppflags`
GTEST_CXXFLAGS=`${GTEST_CONFIG} --cxxflags`
GTEST_LDFLAGS=`${GTEST_CONFIG} --ldflags`
GTEST_LIBS=`${GTEST_CONFIG} --libs`
AC_SUBST([GTEST_CPPFLAGS])
AC_SUBST([GTEST_CXXFLAGS])
AC_SUBST([GTEST_LDFLAGS])
AC_SUBST([GTEST_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_STAT

AC_CONFIG_FILES([
	Makefile
])
AC_OUTPUT
