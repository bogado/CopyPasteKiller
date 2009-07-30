BOOST_LD_FLAGS ?= -lboost_regex-mt
BOOST_INCLUDE_DIR ?= /usr/include
BOOST_CPP_FLAGS ?= -I$(BOOST_INCLUDE_DIR) -I$(BOOST_INCLUDE_DIR)/boost/tr1/tr1 -DBOOST_TR1_DISABLE_INCLUDE_NEXT

CXXFLAGS += $(BOOST_CPP_FLAGS) -I$(HOME)/usr/include -O0 -g -Wall -Werror
LDFLAGS += -L$(HOME)/usr/lib -L$(HOME)/usr/lib64 $(BOOST_LD_FLAGS)

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

test: $(OBJS)
	g++  $^ -o $@ $(LDFLAGS)

test.o: $(SRCS) $(wildcard *.h)

clean:
	rm *.o test

