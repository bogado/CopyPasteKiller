CXXFLAGS += -I$(HOME)/usr/include -O0 -g -pg
LDFLAGS += -lmhash -L$(HOME)/usr/lib -L$(HOME)/usr/lib64 -pg

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

test: $(OBJS)
	g++ $(LDFLAGS) $^ -o $@

test.o: $(SRCS) $(wildcard *.h)


