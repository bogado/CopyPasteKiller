bin_PROGRAMS = cpkiller cpkiller_test
cpkiller_SOURCES = $(SRC) src/main.cpp

SRC = \
		src/file.cpp\
		src/file.h\
		src/filedb.cpp\
		src/filedb.h\
		src/result.cpp\
		src/result.h\
		src/resultSet.h\
		src/simplifier.h

TEST_SRC = test/test.cpp

TESTS = cpkiller_test

cpkiller_CPPFLAGS = -pthread ${BOOST_CPPFLAGS}
cpkiller_LDADD = ${BOOST_LDFLAGS} -lpthread

cpkiller_test_SOURCES = \
		$(SRC) \
		$(TEST_SRC)

cpkiller_test_CPPFLAGS = $(cpkiller_CPFLAGS) $(GTEST_CPPFLAGS) -Isrc
cpkiller_test_CXXFLAGS = $(GTEST_CXXFLAGS) -DTEST_DIR="\"test/\""
cpkiller_test_LDFLAGS  = $(GTEST_LDFLAGS)
cpkiller_test_LDADD    = $(GTEST_LIBS) $(cpkiller_LDADD)
