CXXFLAGS += -I$(HOME)/usr/include -O3 -g
LDFLAGS += -L$(HOME)/usr/lib -L$(HOME)/usr/lib64

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

test: $(OBJS)
	g++ $(LDFLAGS) $^ -o $@

test.o: $(SRCS) $(wildcard *.h)

clean:
	rm *.o test

