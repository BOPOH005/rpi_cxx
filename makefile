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
GOOGLE_LIB=-L$(GOOGLE_PATH)/src/Default

COMPILER=$(C_PATH)/arm-linux-gnueabihf-g++
C_OPT=-std=c++1y -pthread $(C_INC) -O2 -g3 -Wall -c -fmessage-length=100 -MMD -MP 

LINKER=$(C_PATH)/arm-linux-gnueabihf-ar

all: work_dirs $(BIN)/unit_tests 

work_dirs:
	@if [ ! -d $(BIN) ] ; then mkdir -p $(BIN); fi 
	@if [ ! -d $(OBJ) ] ; then mkdir -p $(OBJ); fi 
	@if [ ! -d $(LIB) ] ; then mkdir -p $(LIB); fi 

clean:
	rm -rf $(OBJ) $(OBJ) $(LIB)

install:
#scp $(BIN)/unit_tests $(BIN)/l1_leg  pi@46.138.165.255:~/projects
	@echo '-> $(wildcard $(BIN)/*)'
	scp $(wildcard $(BIN)/*)  pi@46.138.165.255:~/projects

$(OBJ)/pin.o: pin.cpp		
	$(COMPILER) $(C_OPT) -MF$(OBJ)/pin.d -MT$(OBJ)/pin.d -o $@ $<

$(OBJ)/bcm2835.o: bcm2835.cpp		
	$(COMPILER) $(C_OPT) -MF$(OBJ)/bcm2835.d -MT$(OBJ)/bcm2835.d -o $@ $<
	
$(LIB)/librpi_cxx.a: $(OBJ)/pin.o $(OBJ)/bcm2835.o
	$(LINKER) -r $@ $^

$(OBJ)/Sources.o: ./unit_tests/Source.cpp
	$(COMPILER) $(C_OPT) $(GOOGLE_INC) -MF$(OBJ)/Sources.d -MT$(OBJ)/Sources.d -o $@ $<

$(BIN)/unit_tests: $(LIB)/librpi_cxx.a $(OBJ)/Sources.o
	$(COMPILER) -L$(LIB) $(C_LIB) $(GOOGLE_LIB) -o $@ $(OBJ)/Sources.o -lpthread -lgoogletest -lrpi_cxx

examples: $(BIN)/l1_leg

$(OBJ)/l1_leg.o: $(EXAMPLES)/l1_leg.cpp
	$(COMPILER) $(C_OPT) -I./ -MF$(OBJ)/l1_leg.d -MT$(OBJ)/l1_leg.d -o $@ $<

$(BIN)/l1_leg: $(OBJ)/l1_leg.o $(LIB)/librpi_cxx.a
	$(COMPILER) -L$(LIB) $(C_LIB) $(GOOGLE_LIB) -o $@ $< -lpthread -lrpi_cxx

include $(wildcard $(OBJ)/*.d)	