.PHONY: all clean

C_PATH=../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
C_LIB_PATH=$(C_PATH)/lib/gcc/arm-linux-gnueabihf/4.8.3
C_LIB=-L$(C_LIB_PATH)
C_INC=-I$(C_LIB_PATH)/include

GOOGLE_PATH=../../googletest/googletest
GOOGLE_INC=-I$(GOOGLE_PATH)/include
GOOGLE_LIB=-L$(GOOGLE_PATH)/src/Default

COMPILER=$(C_PATH)/arm-linux-gnueabihf-g++
C_OPT=-std=c++1y -pthread $(C_INC) -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP 

LINKER=$(C_PATH)/arm-linux-gnueabihf-ar

all: rpi_cxx

clean:
	rm -rf out/*.*

rpi_cxx.o: rpi_cxx.cpp		
	$(COMPILER) $(C_OPT) -MFout/rpi_cxx.d -MTout/rpi_cxx.d -o out/rpi_cxx.o rpi_cxx.cpp

pin.o: pin.cpp		
	$(COMPILER) $(C_OPT) -MFout/pin.d -MTout/pin.d -o out/pin.o pin.cpp

rpi_cxx: rpi_cxx.o pin.o
	$(LINKER) -r "out/librpi_cxx.a" out/rpi_cxx.o out/pin.o

unit_tests.o:
	$(COMPILER) $(C_OPT) $(GOOGLE_INC) -MFout/Sources.d -MTout/Sources.d -o ./out/Sources.o ./unit_tests/Source.cpp

unit_tests: rpi_cxx unit_tests.o
	$(COMPILER) -L./out $(C_LIB) $(GOOGLE_LIB) -o "out/unit_tests" ./out/Sources.o -lpthread -lgoogletest -lrpi_cxx