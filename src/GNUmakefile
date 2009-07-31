BOOST_LD_FLAGS ?= -lboost_regex-mt
BOOST_INCLUDE_DIR ?= /usr/include
BOOST_CPP_FLAGS ?= -I$(BOOST_INCLUDE_DIR) -I$(BOOST_INCLUDE_DIR)/boost/tr1/tr1 -DBOOST_TR1_DISABLE_INCLUDE_NEXT

DEBUG = -O0
RELEASE = -O2

CXXFLAGS += $(BOOST_CPP_FLAGS) -I$(HOME)/usr/include $(RELEASE) -g -Wall -Werror
LDFLAGS += -L$(HOME)/usr/lib -L$(HOME)/usr/lib64 $(BOOST_LD_FLAGS)

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

ALLDEPS = $(patsubst %.cpp,.%.cpp.dep, $(SRCS) )

test: $(OBJS)
	g++  $^ -o $@ $(LDFLAGS)

test.o: $(SRCS) $(wildcard *.h)

clean: dep-clean
	rm *.o test

dep-clean:
	rm -rf .*.dep

DODEP=@set -e; \
	echo Making depend of $<; \
	test -d $(dir $@) || mkdir -p $(dir $@); \
	rm -f $@; \
	tmp=`mktemp /tmp/$(TARGET_NAME)-dep.XXXXXX`; \
	$(CXX) -MM -I. $(CPPFLAGS) $< > $$tmp || { rm $$tmp; false; }; \
	v=$(TARGET_NAME)_version.h; \
	sed \
		-e "s|$$v||g" \
		-e 's|\($*\)\.o[ :]*|\1.o $@ : |g' < $$tmp > $@; \
	grep -q $$v $$tmp && printf "\n\n%s: $$v\n" `echo $*.o | sed -e "$$o2o"` >> $@; \
	rm -f $$tmp

.%.cpp.dep: %.cpp
	$(DODEP)

-include $(ALLDEPS)

