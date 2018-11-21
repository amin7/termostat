#https://github.com/arduino/Arduino/blob/master/build/shared/manpage.adoc
#git repository https://github.com/google/googletest.git
INCLUDE_PATH_=../ 
INCLUDE_PATH_+= /cygdrive/c/Users/ominenko/.arduinocdt/libraries/ArduinoJson/6.5.0-beta/

INCLUDE_PATH =  $(addprefix -I ,$(INCLUDE_PATH_))
GTEST_DIR=/cygdrive/d/work/test/googletest/googletest/
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
 
CPPFLAGS += -isystem $(GTEST_DIR)/include

FLAGS_TEST=-DTEST -std=c++11 -g

CXXFLAGS += -g -Wall -Wextra -pthread
CXXFLAGS += -D _UNIT_TEST_ACTIVE_

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	CXXFLAGS += -std=c++11
endif


MKDIR_P = mkdir -p

LIB_TEST=

MODULES =  CTransformLine \
			CPresets
SOURCES =  $(addprefix ../,$(MODULES))
  
TESTS   =$(addsuffix _test,$(MODULES))

TESTS_CPP=$(addsuffix .cpp ,$(SOURCES) $(TESTS))

DEPEND_CPP = 

OBJ_DIR=./obj/
OBJS=$(subst .cpp,.o,$(TESTS_CPP) $(DEPEND_CPP))


default : all

$(OBJ_DIR)gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc -o $@

$(OBJ_DIR)gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc -o $@

$(OBJ_DIR)gtest.a : $(OBJ_DIR)gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)gtest_main.a : $(OBJ_DIR)gtest-all.o $(OBJ_DIR)gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
	

all : $(OBJS) $(GTEST_HEADERS) $(OBJ_DIR)gtest_main.a $(HELPER_OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LCFLAGS) $(wildcard $(OBJ_DIR)/*.o)  -lpthread -o $(OBJ_DIR)$@	
 
$(OBJS): ${OBJ_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDE_PATH) -c $(basename $@).cpp $(LCFLAGS) $(CSFLAFS) -lpthread $^ -o $(OBJ_DIR)$(notdir $@) -D TEST
	
clean :
	rm $(OBJ_DIR) -rf

$(OBJ_DIR):
	${MKDIR_P} ${OBJ_DIR}	
.PHONY: default all clean

#eof