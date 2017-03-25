.PHONY: all clean install work_dirs

OBJ=./obj
BIN=./bin
LIB=./lib
EXAMPLES=./examples

C_PATH=../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
C_LIB_PATH=$(C_PATH)/lib/gcc/arm-linux-gnueabihf/4.8.3
C_LIB=-L$(C_LIB_PATH)
C_INC=-I$(C_LIB_PATH)/include

GOOGLE_PATH=../../googletest/googletest
GOOGLE_INC=-I$(GOOGLE_PATH)/include
#GOOGLE_LIB=-L$(GOOGLE_PATH)/src/Default

COMPILER=arm-linux-gnueabihf-g++
C_OPT=-std=c++1y -pthread $(C_INC) -O2 -g3 -Wall -c -fmessage-length=100 -MMD -MP 

LINKER=arm-linux-gnueabihf-ar

all: work_dirs $(BIN)/unit_tests 

work_dirs:
	@if [ ! -d $(BIN) ] ; then mkdir -p $(BIN); fi 
	@if [ ! -d $(OBJ) ] ; then mkdir -p $(OBJ); fi 
	@if [ ! -d $(LIB) ] ; then mkdir -p $(LIB); fi 

clean:
	rm -rf $(OBJ) $(OBJ) $(LIB) $(BIN)

install:
#scp $(BIN)/unit_tests $(BIN)/l1_leg  pi@46.138.165.255:~/projects
	scp $(wildcard $(BIN)/*)  pi@46.138.165.255:~/projects

include $(wildcard $(OBJ)/*.d)

$(OBJ)/pin.o: pin.cpp 
	$(COMPILER) $(C_OPT) -MF$(OBJ)/pin.d -MP -o $@ $<

$(OBJ)/bcm2835.o: bcm2835.cpp		
	$(COMPILER) $(C_OPT) -MF$(OBJ)/bcm2835.d -MT$(OBJ)/bcm2835.d -o $@ $<
	
$(LIB)/librpi_cxx.a: $(OBJ)/pin.o $(OBJ)/bcm2835.o
	$(LINKER) -r $@ $^

$(GOOGLE_PATH)/make/gtest.a:
	make -C $(GOOGLE_PATH)/make gtest.a CXX=$(COMPILER) AR=$(LINKER)

$(LIB)/libgtest.a: $(GOOGLE_PATH)/make/gtest.a
	cp $(GOOGLE_PATH)/make/gtest.a $@
	
$(OBJ)/Sources.o: ./unit_tests/Source.cpp
	$(COMPILER) $(C_OPT) $(GOOGLE_INC) -MF$(OBJ)/Sources.d -MP -o $@ $<

$(BIN)/unit_tests: $(LIB)/libgtest.a $(LIB)/librpi_cxx.a $(OBJ)/Sources.o
	$(COMPILER) -L$(LIB) $(C_LIB) -o $@ $(OBJ)/Sources.o -lpthread -lgtest -lrpi_cxx

EXAMPLES_OBJ=l1_leg l2_abuzzer l3_pbuzzer l4_tiltswitch l5_button

examples: work_dirs $(addprefix $(BIN)/, $(EXAMPLES_OBJ))

$(OBJ)/%.o: $(EXAMPLES)/%.cpp
	$(COMPILER) $(C_OPT) -I./ -MF$(@:.o=.d) -MP -o $@ $<

$(BIN)/%: $(OBJ)/%.o $(LIB)/librpi_cxx.a
	$(COMPILER) -L$(LIB) $(C_LIB) -o $@ $< -lpthread -lrpi_cxx
	