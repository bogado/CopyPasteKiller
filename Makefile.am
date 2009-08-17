bin_PROGRAMS = cpkiller
cpkiller_SOURCES = \
		src/file.cpp\
		src/file.h\
		src/filedb.cpp\
		src/filedb.h\
		src/line.cpp\
		src/line.h\
		src/main.cpp\
		src/result.cpp\
		src/result.h\
		src/resultSet.h\
		src/simplifier.h

cpkiller_CPPFLAGS = -pthread ${BOOST_CPPFLAGS}
cpkiller_LDADD = ${BOOST_LDFLAGS} -lpthread
