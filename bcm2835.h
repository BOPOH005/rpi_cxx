/*
 * bcm2835.h
 *
 *  Created on: 18.09.2016
 *      Author: bopoh
 */

#ifndef BCM2835_H_
#define BCM2835_H_

#include<memory>

namespace rpi_cxx {

struct fcloser
{
	struct pointer {
		pointer() {}
		pointer(std::nullptr_t) {}
		pointer(int handle) : value_(handle) {}

		operator int() { return value_; }

		friend bool operator==(pointer lhs, pointer rhs) { return lhs.value_ == rhs.value_; }
		friend bool operator!=(pointer lhs, pointer rhs) { return !(lhs == rhs); }

		int value_ = -1;
	};

	void operator()(int p);
};

struct mcloser	{ void operator()(void* p);};

class pin
{
public:
	enum class pinNum
	{
		pin0,
		pin1,
		pin2,
		pin3,
		pin4,
		pin5,
		pin6,
		pin7,
		pin8,
		pin9,
		pin10,
		pin11,
		pin12,
		pin13,
		pin14,
		pin15,
		pin16,
		pin17,
		pin18,
		pin19,
		pin20,
		pin21,
		pin22,
		pin23,
		pin24,
		pin25,
		pin26,
		pin27,
		pin28,
		pin29,
		pin30,
		pin31,
		pin32,
		pin33,
		pin34,
		pin35,
		pin36,
		pin37,
		pin38,
		pin39,
		pin40,
		pin41,
		pin42,
		pin43,
		pin44,
		pin45,
		pin46,
		pin47,
		pin48,
		pin49,
		pin50,
		pin51,
		pin52,
		pin53
	};
	pin(pinNum p):pin_num(p){};
private:
	const pinNum	pin_num;
};

struct GPIO_REGS
{
typedef enum
{
	in	=0x0,
	out	=0x1,
	fun0=0x4,
	fun1=0x5,
	fun2=0x6,
	fun3=0x7,
	fun4=0x3,
	fun5=0x2
}pin_fun;

struct GPFSEL0
{
	pin_fun FSEL0      : 3;
    pin_fun FSEL1      : 3;
    pin_fun FSEL2      : 3;
    pin_fun FSEL3      : 3;
    pin_fun FSEL4      : 3;
    pin_fun FSEL5      : 3;
    pin_fun FSEL6      : 3;
    pin_fun FSEL7      : 3;
    pin_fun FSEL8      : 3;
    pin_fun FSEL9      : 3;
    unsigned           : 2;
}	gpfsel0;
struct GPFSEL1
{
    pin_fun FSEL10      : 3;
    pin_fun FSEL11      : 3;
    pin_fun FSEL12      : 3;
    pin_fun FSEL13      : 3;
    pin_fun FSEL14      : 3;
    pin_fun FSEL15      : 3;
    pin_fun FSEL16      : 3;
    pin_fun FSEL17      : 3;
    pin_fun FSEL18      : 3;
    pin_fun FSEL19      : 3;
    unsigned            : 2;
}	gpfsel1;
struct GPFSEL2
{
    pin_fun FSEL20      : 3;
    pin_fun FSEL21      : 3;
    pin_fun FSEL22      : 3;
    pin_fun FSEL23      : 3;
    pin_fun FSEL24      : 3;
    pin_fun FSEL25      : 3;
    pin_fun FSEL26      : 3;
    pin_fun FSEL27      : 3;
    pin_fun FSEL28      : 3;
    pin_fun FSEL29      : 3;
    unsigned            : 2;
}	gpfsel2;
struct GPFSEL3
{
    pin_fun FSEL30      : 3;
    pin_fun FSEL31      : 3;
    pin_fun FSEL32      : 3;
    pin_fun FSEL33      : 3;
    pin_fun FSEL34      : 3;
    pin_fun FSEL35      : 3;
    pin_fun FSEL36      : 3;
    pin_fun FSEL37      : 3;
    pin_fun FSEL38      : 3;
    pin_fun FSEL39      : 3;
    unsigned            : 2;
}	gpfsel3;
struct GPFSEL4
{
    pin_fun FSEL40      : 3;
    pin_fun FSEL41      : 3;
    pin_fun FSEL42      : 3;
    pin_fun FSEL43      : 3;
    pin_fun FSEL44      : 3;
    pin_fun FSEL45      : 3;
    pin_fun FSEL46      : 3;
    pin_fun FSEL47      : 3;
    pin_fun FSEL48      : 3;
    pin_fun FSEL49      : 3;
    unsigned            : 2;
}	gpfsel4;
struct GPFSEL5
{
    pin_fun FSEL50      : 3;
    pin_fun FSEL51      : 3;
    pin_fun FSEL52      : 3;
    pin_fun FSEL53      : 3;
    unsigned            : 20;
}	gpfsel5;
unsigned :32;

typedef enum
{
	noEffect=0x0,
	setOut	=0x1
}output_set;
struct GPSET0
{
    output_set SET0       : 1;
    output_set SET1       : 1;
    output_set SET2       : 1;
    output_set SET3       : 1;
    output_set SET4       : 1;
    output_set SET5       : 1;
    output_set SET6       : 1;
    output_set SET7       : 1;
    output_set SET8       : 1;
    output_set SET9       : 1;
    output_set SET10      : 1;
    output_set SET11      : 1;
    output_set SET12      : 1;
    output_set SET13      : 1;
    output_set SET14      : 1;
    output_set SET15      : 1;
    output_set SET16      : 1;
    output_set SET17      : 1;
    output_set SET18      : 1;
    output_set SET19      : 1;
    output_set SET20      : 1;
    output_set SET21      : 1;
    output_set SET22      : 1;
    output_set SET23      : 1;
    output_set SET24      : 1;
    output_set SET25      : 1;
    output_set SET26      : 1;
    output_set SET27      : 1;
    output_set SET28      : 1;
    output_set SET29      : 1;
    output_set SET30      : 1;
    output_set SET31      : 1;
}	gpset0;

struct GPSET1
{
    output_set SET32       : 1;
    output_set SET33       : 1;
    output_set SET34       : 1;
    output_set SET35       : 1;
    output_set SET36       : 1;
    output_set SET37       : 1;
    output_set SET38       : 1;
    output_set SET39       : 1;
    output_set SET40       : 1;
    output_set SET41       : 1;
    output_set SET42       : 1;
    output_set SET43       : 1;
    output_set SET44       : 1;
    output_set SET45       : 1;
    output_set SET46       : 1;
    output_set SET47       : 1;
    output_set SET48       : 1;
    output_set SET49       : 1;
    output_set SET50       : 1;
    output_set SET51       : 1;
    output_set SET52       : 1;
    output_set SET53       : 1;
    unsigned               : 10;
}	gpset1;
unsigned :32;
typedef enum
{
	noEffect=0x0,
	clearOut=0x1
}output_clr;

struct GPCLR0
{
    output_clr CLR0       : 1;
    output_clr CLR1       : 1;
    output_clr CLR2       : 1;
    output_clr CLR3       : 1;
    output_clr CLR4       : 1;
    output_clr CLR5       : 1;
    output_clr CLR6       : 1;
    output_clr CLR7       : 1;
    output_clr CLR8       : 1;
    output_clr CLR9       : 1;
    output_clr CLR10      : 1;
    output_clr CLR11      : 1;
    output_clr CLR12      : 1;
    output_clr CLR13      : 1;
    output_clr CLR14      : 1;
    output_clr CLR15      : 1;
    output_clr CLR16      : 1;
    output_clr CLR17      : 1;
    output_clr CLR18      : 1;
    output_clr CLR19      : 1;
    output_clr CLR20      : 1;
    output_clr CLR21      : 1;
    output_clr CLR22      : 1;
    output_clr CLR23      : 1;
    output_clr CLR24      : 1;
    output_clr CLR25      : 1;
    output_clr CLR26      : 1;
    output_clr CLR27      : 1;
    output_clr CLR28      : 1;
    output_clr CLR29      : 1;
    output_clr CLR30      : 1;
    output_clr CLR31      : 1;
}gpclr0;

struct GPCLR1
{
    output_clr CLR32       : 1;
    output_clr CLR33       : 1;
    output_clr CLR34       : 1;
    output_clr CLR35       : 1;
    output_clr CLR36       : 1;
    output_clr CLR37       : 1;
    output_clr CLR38       : 1;
    output_clr CLR39       : 1;
    output_clr CLR40       : 1;
    output_clr CLR41       : 1;
    output_clr CLR42       : 1;
    output_clr CLR43       : 1;
    output_clr CLR44       : 1;
    output_clr CLR45       : 1;
    output_clr CLR46       : 1;
    output_clr CLR47       : 1;
    output_clr CLR48       : 1;
    output_clr CLR49       : 1;
    output_clr CLR50       : 1;
    output_clr CLR51       : 1;
    output_clr CLR52       : 1;
    output_clr CLR53       : 1;
    unsigned               : 10;
}gpclr11;
unsigned :32;

typedef enum
{
	low,
	hight
} pin_level;

struct GPLEV0
{
    pin_level LEV0       : 1;
    pin_level LEV1       : 1;
    pin_level LEV2       : 1;
    pin_level LEV3       : 1;
    pin_level LEV4       : 1;
    pin_level LEV5       : 1;
    pin_level LEV6       : 1;
    pin_level LEV7       : 1;
    pin_level LEV8       : 1;
    pin_level LEV9       : 1;
    pin_level LEV10      : 1;
    pin_level LEV11      : 1;
    pin_level LEV12      : 1;
    pin_level LEV13      : 1;
    pin_level LEV14      : 1;
    pin_level LEV15      : 1;
    pin_level LEV16      : 1;
    pin_level LEV17      : 1;
    pin_level LEV18      : 1;
    pin_level LEV19      : 1;
    pin_level LEV20      : 1;
    pin_level LEV21      : 1;
    pin_level LEV22      : 1;
    pin_level LEV23      : 1;
    pin_level LEV24      : 1;
    pin_level LEV25      : 1;
    pin_level LEV26      : 1;
    pin_level LEV27      : 1;
    pin_level LEV28      : 1;
    pin_level LEV29      : 1;
    pin_level LEV30      : 1;
    pin_level LEV31      : 1;
}gplev0;

struct GPLEV1
{
    pin_level LEV32       : 1;
    pin_level LEV33       : 1;
    pin_level LEV34       : 1;
    pin_level LEV35       : 1;
    pin_level LEV36       : 1;
    pin_level LEV37       : 1;
    pin_level LEV38       : 1;
    pin_level LEV39       : 1;
    pin_level LEV40       : 1;
    pin_level LEV41       : 1;
    pin_level LEV42       : 1;
    pin_level LEV43       : 1;
    pin_level LEV44       : 1;
    pin_level LEV45       : 1;
    pin_level LEV46       : 1;
    pin_level LEV47       : 1;
    pin_level LEV48       : 1;
    pin_level LEV49       : 1;
    pin_level LEV50       : 1;
    pin_level LEV51       : 1;
    pin_level LEV52       : 1;
    pin_level LEV53       : 1;
    unsigned	          : 10;
}gplev1;

typedef enum
{
	event_not_detected	=0x0,
	event_detected		=0x1
}pin_event;

struct GPEDS0
{
	pin_event EDS0	:1;
	pin_event EDS1	:1;
	pin_event EDS2	:1;
	pin_event EDS3	:1;
	pin_event EDS4	:1;
	pin_event EDS5	:1;
	pin_event EDS6	:1;
	pin_event EDS7	:1;
	pin_event EDS8	:1;
	pin_event EDS9	:1;
	pin_event EDS10	:1;
	pin_event EDS11	:1;
	pin_event EDS12	:1;
	pin_event EDS13	:1;
	pin_event EDS14	:1;
	pin_event EDS15	:1;
	pin_event EDS16	:1;
	pin_event EDS17	:1;
	pin_event EDS18	:1;
	pin_event EDS19	:1;
	pin_event EDS20	:1;
	pin_event EDS21	:1;
	pin_event EDS22	:1;
	pin_event EDS23	:1;
	pin_event EDS24	:1;
	pin_event EDS25	:1;
	pin_event EDS26	:1;
	pin_event EDS27	:1;
	pin_event EDS28	:1;
	pin_event EDS29	:1;
	pin_event EDS30	:1;
	pin_event EDS31	:1;
}gpeds0;

struct GPEDS1
{
	pin_event EDS32	:1;
	pin_event EDS33	:1;
	pin_event EDS34	:1;
	pin_event EDS35	:1;
	pin_event EDS36	:1;
	pin_event EDS37	:1;
	pin_event EDS38	:1;
	pin_event EDS39	:1;
	pin_event EDS40	:1;
	pin_event EDS41	:1;
	pin_event EDS42	:1;
	pin_event EDS43	:1;
	pin_event EDS44	:1;
	pin_event EDS45	:1;
	pin_event EDS46	:1;
	pin_event EDS47	:1;
	pin_event EDS48	:1;
	pin_event EDS49	:1;
	pin_event EDS50	:1;
	pin_event EDS51	:1;
	pin_event EDS52	:1;
	pin_event EDS33	:1;
	unsigned		:10;
}gpeds1;
unsigned	:32;

};

class bcm2835 {
public:
	bcm2835();
	GPIO_REGS& get_Regs();
private:
	std::unique_ptr<int, 	fcloser>  	mem_fd_;
	std::unique_ptr<void, 	mcloser> 	p_map_;
};


} /* namespace rpi_cxx */

#endif /* BCM2835_H_ */
