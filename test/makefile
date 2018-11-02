#https://github.com/arduino/Arduino/blob/master/build/shared/manpage.adoc
PROJECT_FOLDER=$(pwd)
PROJECT_NAME=clock.ino
PROJECT=$(PROJECT_FOLDER)$(PROJECT_NAME)
SLOEBER_PATH=/home/ominenko/work/ides/sloeber/arduinoPlugin/packages/esp8266/hardware/esp8266/2.3.0/cores/esp8266/

INCLUDE_PATH_= ../../libraries/ArduinoJson/src \
			 $(SLOEBER_PATH)

INCLUDE_PATH =  $(addprefix -I ,$(INCLUDE_PATH_))
GTEST_DIR=/cygdrive/d/work/test/googletest/googletest/
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
 
#FLAGS="-v"
FLAGS_TEST=-DTEST -std=c++11 -g
LIB_TEST=

MODULES =  CPresets
SOURCES =  $(addprefix ../,$(MODULES))
  
TESTS   =$(addsuffix _test,$(MODULES))

ALL_SRC=$(addsuffix .cpp ,$(SOURCES) $(TESTS))

DEPEND = CObserver
DEPEND_SRC  =$(addsuffix .cpp,$(DEPEND))

OUT_DIR=./obj/
#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
MD := mkdir -p
RM := rm
CC := g++

all: clean tests
clean:
	@echo "clean"
	$(RM) -rf $(OUT_DIR)
dirs:
		$(MD) $(OUT_DIR) -p		
gtest.o:  dirs
	$(CC) -isystem ${GTEST_DIR}/include -I${GTEST_DIR}  -pthread -c ${GTEST_DIR}/src/gtest-all.cc -o $(OUT_DIR)gtest-all.o
	ar -rv $(OUT_DIR)libgtest.a $(OUT_DIR)gtest-all.o
	
tests: dirs gtest.o
	 $(CC) $(ALL_SRC) $(GTEST_DIR)/src/gtest_main.cc $(FLAGS_TEST) $(LIB_TEST) $(INCLUDE_PATH) -isystem ${GTEST_DIR}/include -pthread $(OUT_DIR)libgtest.a -o $(OUT_DIR)test_all.o		
list: 
	@echo "test list [" $(SOURCES) "]"
.PHONY: all upload clean tests dirs $(SOURCES)
