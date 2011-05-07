bin_PROGRAMS = cpkiller cpkiller_test
cpkiller_SOURCES = $(SRC) src/main.cpp

SRC = \
		src/file.cpp\
		src/file.h\
		src/filedb.cpp\
		src/filedb.h\
		src/line.cpp\
		src/line.h\
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
