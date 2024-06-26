.PHONY: all clean install work_dirs
 
 RPI_HOST=bopoh.ddns.net


ifeq ($(OS),Windows_NT)
OBJ=obj
BIN=bin
LIB=lib
EXAMPLES=examples

	C_PATH=C:\SysGCC\Raspberry\arm-linux-gnueabihf
	C_LIB=-L$(C_PATH)\sysroot\usr\lib\arm-linux-gnueabihf
	C_INC=-I$(C_PATH)\sysroot\usr\include\c++\8
	GOOGLE_PATH=..\googletest\googletest

work_dirs: 
	if not exist $(BIN) mkdir $(BIN)
	if not exist $(OBJ) mkdir $(OBJ)
	if not exist $(LIB) mkdir $(LIB)

$(LIB)/libgtest.a: $(GOOGLE_PATH)/make/libgtest.a
	copy  $(subst /,\,$<) $(subst /,\,$@)

else

OBJ=./obj
BIN=./bin
LIB=./lib
EXAMPLES=./examples

	C_PATH=~/Projects/raspberry/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf
	C_LIB_PATH=$(C_PATH)/arm-linux-gnueabihf/sysroot/usr/lib
	C_LIB=-L$(C_LIB_PATH)
	C_INC=-I$(C_PATH)/arm-linux-gnueabihf/include/c++/4.9.3
	GOOGLE_PATH=../../googletest/googletest

$(LIB)/libgtest.a: $(GOOGLE_PATH)/make/libgtest.a
	cp $(GOOGLE_PATH)/make/gtest.a $@

endif

install: 
	scp -Cpr $(BIN)  pi@$(RPI_HOST):~/

GOOGLE_INC=-I$(GOOGLE_PATH)/include

COMPILER=arm-linux-gnueabihf-g++
C_OPT=-std=c++17 -pthread $(C_INC) -O2 -Wall -c -fmessage-length=100 -MMD -MP 

LINKER=arm-linux-gnueabihf-ar

all: work_dirs $(BIN)/unit_tests 

clean: 
	if exist $(LIB) rmdir /S/Q $(LIB)
	if exist $(OBJ) rmdir /S/Q $(OBJ)
	if exist $(BIN) rmdir /S/Q $(BIN)
	
include $(wildcard $(OBJ)/*.d)

$(OBJ)/%.o: ./%.cpp
	$(COMPILER) $(C_OPT) -MF$(@:.o=.d) -MT$(@:.o=.d) -o $@ ./$<
	
$(LIB)/librpi_cxx.a: $(OBJ)/pin.o $(OBJ)/bcm2835.o $(OBJ)/pwm.o
	$(LINKER) -r $@ $^

$(GOOGLE_PATH)/make/libgtest.a:
	make -C $(GOOGLE_PATH)/make libgtest.a CXX=$(COMPILER) AR=$(LINKER)
	
$(OBJ)/%.o: ./unit_tests/%.cpp
	$(COMPILER) $(C_OPT) $(GOOGLE_INC) -MF$(@:.o=.d) -MP -o $@ ./$<

TEST_CPP = $(notdir $(wildcard ./unit_tests/*.cpp))
TEST_OBJ = $(addprefix $(OBJ)/, $(TEST_CPP:.cpp=.o))

$(BIN)/unit_tests: $(LIB)/libgtest.a $(LIB)/librpi_cxx.a $(TEST_OBJ)
	$(COMPILER) -L$(LIB) $(C_LIB) -o $@ $(TEST_OBJ) -lpthread -lgtest -lrpi_cxx

EXAMPLES_OBJ= l1_leg l2_abuzzer l3_pbuzzer l4_tiltswitch l5_button l6_relay l7_flowing_lights l8_breathing_led l8_1_breathing_led l18_thermistor

examples: work_dirs $(addprefix $(BIN)/, $(EXAMPLES_OBJ))

$(OBJ)/%.o: $(EXAMPLES)/%.cpp
	$(COMPILER) $(C_OPT)  -MF$(@:.o=.d) -o $@ $<

$(BIN)/%: $(OBJ)/%.o $(LIB)/librpi_cxx.a
	$(COMPILER) -L$(LIB) $(C_LIB) -o $@ $< -lpthread -lrpi_cxx
	