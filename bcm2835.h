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

#ifdef __GNUC__
enum /*class*/ mode /* : u_char*/ // warning gcc bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51242
#else
enum class mode : u_char
#endif
{
	in	=0b000,
	out	=0b001,
	fun0=0b100,
	fun1=0b101,
	fun2=0b110,
	fun3=0b111,
	fun4=0b011,
	fun5=0b010
};

enum class output: bool
{
	no_effect=0x0,
	set		=0x1
};

enum class level: bool
{
	low		=0x0,
	hight	=0x1
};

enum class event: bool
{
	not_detected	=0x0,
	detected		=0x1
};

enum class status: bool
{
	disable = 0x0,
	on 		= 0x1
};

#ifdef __GNUC__
enum /*class*/ pull /*:u_char*/ // warning gcc bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51242
#else
enum class pull :u_char
#endif
{
	off 		= 0x0, // disable pull-up/down
	down 		= 0x1, // Enable Pull Down control
	up 			= 0x2, // Enable Pull Up control 
	reserved	= 0x3  // Reserved
};

enum class clock: bool
{
	no_effect	= 0x0,
	assert		= 0x1
};

// #ifdef __GNUC__
// #define mode u_char
// #define pull u_char
// #endif

struct GPIO_REGS
{
	struct 
	{
		mode FSEL0      : 3;
		mode FSEL1      : 3;
		mode FSEL2      : 3;
		mode FSEL3      : 3;
		mode FSEL4      : 3;
		mode FSEL5      : 3;
		mode FSEL6      : 3;
		mode FSEL7      : 3;
		mode FSEL8      : 3;
		mode FSEL9      : 3;
		unsigned           : 2;
		mode FSEL10      : 3;
		mode FSEL11      : 3;
		mode FSEL12      : 3;
		mode FSEL13      : 3;
		mode FSEL14      : 3;
		mode FSEL15      : 3;
		mode FSEL16      : 3;
		mode FSEL17      : 3;
		mode FSEL18      : 3;
		mode FSEL19      : 3;
		unsigned            : 2;
		mode FSEL20      : 3;
		mode FSEL21      : 3;
		mode FSEL22      : 3;
		mode FSEL23      : 3;
		mode FSEL24      : 3;
		mode FSEL25      : 3;
		mode FSEL26      : 3;
		mode FSEL27      : 3;
		mode FSEL28      : 3;
		mode FSEL29      : 3;
		unsigned            : 2;
		mode FSEL30      : 3;
		mode FSEL31      : 3;
		mode FSEL32      : 3;
		mode FSEL33      : 3;
		mode FSEL34      : 3;
		mode FSEL35      : 3;
		mode FSEL36      : 3;
		mode FSEL37      : 3;
		mode FSEL38      : 3;
		mode FSEL39      : 3;
		unsigned            : 2;
		mode FSEL40      : 3;
		mode FSEL41      : 3;
		mode FSEL42      : 3;
		mode FSEL43      : 3;
		mode FSEL44      : 3;
		mode FSEL45      : 3;
		mode FSEL46      : 3;
		mode FSEL47      : 3;
		mode FSEL48      : 3;
		mode FSEL49      : 3;
		unsigned            : 2;
		mode FSEL50      : 3;
		mode FSEL51      : 3;
		mode FSEL52      : 3;
		mode FSEL53      : 3;
		unsigned            : 20;
	}		GPFSEL;
	unsigned			:32;
	struct 
	{
		output SET0       : 1;
		output SET1       : 1;
		output SET2       : 1;
		output SET3       : 1;
		output SET4       : 1;
		output SET5       : 1;
		output SET6       : 1;
		output SET7       : 1;
		output SET8       : 1;
		output SET9       : 1;
		output SET10      : 1;
		output SET11      : 1;
		output SET12      : 1;
		output SET13      : 1;
		output SET14      : 1;
		output SET15      : 1;
		output SET16      : 1;
		output SET17      : 1;
		output SET18      : 1;
		output SET19      : 1;
		output SET20      : 1;
		output SET21      : 1;
		output SET22      : 1;
		output SET23      : 1;
		output SET24      : 1;
		output SET25      : 1;
		output SET26      : 1;
		output SET27      : 1;
		output SET28      : 1;
		output SET29      : 1;
		output SET30      : 1;
		output SET31      : 1;
		output SET32       : 1;
		output SET33       : 1;
		output SET34       : 1;
		output SET35       : 1;
		output SET36       : 1;
		output SET37       : 1;
		output SET38       : 1;
		output SET39       : 1;
		output SET40       : 1;
		output SET41       : 1;
		output SET42       : 1;
		output SET43       : 1;
		output SET44       : 1;
		output SET45       : 1;
		output SET46       : 1;
		output SET47       : 1;
		output SET48       : 1;
		output SET49       : 1;
		output SET50       : 1;
		output SET51       : 1;
		output SET52       : 1;
		output SET53       : 1;
		unsigned               : 10;
	}		GPSET;
	unsigned			:32;
	struct 
	{
		output CLR0       : 1;
		output CLR1       : 1;
		output CLR2       : 1;
		output CLR3       : 1;
		output CLR4       : 1;
		output CLR5       : 1;
		output CLR6       : 1;
		output CLR7       : 1;
		output CLR8       : 1;
		output CLR9       : 1;
		output CLR10      : 1;
		output CLR11      : 1;
		output CLR12      : 1;
		output CLR13      : 1;
		output CLR14      : 1;
		output CLR15      : 1;
		output CLR16      : 1;
		output CLR17      : 1;
		output CLR18      : 1;
		output CLR19      : 1;
		output CLR20      : 1;
		output CLR21      : 1;
		output CLR22      : 1;
		output CLR23      : 1;
		output CLR24      : 1;
		output CLR25      : 1;
		output CLR26      : 1;
		output CLR27      : 1;
		output CLR28      : 1;
		output CLR29      : 1;
		output CLR30      : 1;
		output CLR31      : 1;
		output CLR32       : 1;
		output CLR33       : 1;
		output CLR34       : 1;
		output CLR35       : 1;
		output CLR36       : 1;
		output CLR37       : 1;
		output CLR38       : 1;
		output CLR39       : 1;
		output CLR40       : 1;
		output CLR41       : 1;
		output CLR42       : 1;
		output CLR43       : 1;
		output CLR44       : 1;
		output CLR45       : 1;
		output CLR46       : 1;
		output CLR47       : 1;
		output CLR48       : 1;
		output CLR49       : 1;
		output CLR50       : 1;
		output CLR51       : 1;
		output CLR52       : 1;
		output CLR53       : 1;
		unsigned               : 10;
	}		GPCLR;
	unsigned			:32;
	struct 
	{
		level LEV0       : 1;
		level LEV1       : 1;
		level LEV2       : 1;
		level LEV3       : 1;
		level LEV4       : 1;
		level LEV5       : 1;
		level LEV6       : 1;
		level LEV7       : 1;
		level LEV8       : 1;
		level LEV9       : 1;
		level LEV10      : 1;
		level LEV11      : 1;
		level LEV12      : 1;
		level LEV13      : 1;
		level LEV14      : 1;
		level LEV15      : 1;
		level LEV16      : 1;
		level LEV17      : 1;
		level LEV18      : 1;
		level LEV19      : 1;
		level LEV20      : 1;
		level LEV21      : 1;
		level LEV22      : 1;
		level LEV23      : 1;
		level LEV24      : 1;
		level LEV25      : 1;
		level LEV26      : 1;
		level LEV27      : 1;
		level LEV28      : 1;
		level LEV29      : 1;
		level LEV30      : 1;
		level LEV31      : 1;
		level LEV32       : 1;
		level LEV33       : 1;
		level LEV34       : 1;
		level LEV35       : 1;
		level LEV36       : 1;
		level LEV37       : 1;
		level LEV38       : 1;
		level LEV39       : 1;
		level LEV40       : 1;
		level LEV41       : 1;
		level LEV42       : 1;
		level LEV43       : 1;
		level LEV44       : 1;
		level LEV45       : 1;
		level LEV46       : 1;
		level LEV47       : 1;
		level LEV48       : 1;
		level LEV49       : 1;
		level LEV50       : 1;
		level LEV51       : 1;
		level LEV52       : 1;
		level LEV53       : 1;
		unsigned	          : 10;
	}		GPLEV;
	unsigned			:32;
	struct 
	{
		event EDS0	:1;
		event EDS1	:1;
		event EDS2	:1;
		event EDS3	:1;
		event EDS4	:1;
		event EDS5	:1;
		event EDS6	:1;
		event EDS7	:1;
		event EDS8	:1;
		event EDS9	:1;
		event EDS10	:1;
		event EDS11	:1;
		event EDS12	:1;
		event EDS13	:1;
		event EDS14	:1;
		event EDS15	:1;
		event EDS16	:1;
		event EDS17	:1;
		event EDS18	:1;
		event EDS19	:1;
		event EDS20	:1;
		event EDS21	:1;
		event EDS22	:1;
		event EDS23	:1;
		event EDS24	:1;
		event EDS25	:1;
		event EDS26	:1;
		event EDS27	:1;
		event EDS28	:1;
		event EDS29	:1;
		event EDS30	:1;
		event EDS31	:1;
		event EDS32	:1;
		event EDS33	:1;
		event EDS34	:1;
		event EDS35	:1;
		event EDS36	:1;
		event EDS37	:1;
		event EDS38	:1;
		event EDS39	:1;
		event EDS40	:1;
		event EDS41	:1;
		event EDS42	:1;
		event EDS43	:1;
		event EDS44	:1;
		event EDS45	:1;
		event EDS46	:1;
		event EDS47	:1;
		event EDS48	:1;
		event EDS49	:1;
		event EDS50	:1;
		event EDS51	:1;
		event EDS52	:1;
		event EDS53	:1;
		unsigned		:10;
	}		GPEDS;
	unsigned			:32;
	struct
	{
		status REN0 : 1;
		status REN1 : 1;
		status REN2 : 1;
		status REN3 : 1;
		status REN4 : 1;
		status REN5 : 1;
		status REN6 : 1;
		status REN7 : 1;
		status REN8 : 1;
		status REN9 : 1;
		status REN10 : 1;
		status REN11 : 1;
		status REN12 : 1;
		status REN13 : 1;
		status REN14 : 1;
		status REN15 : 1;
		status REN16 : 1;
		status REN17 : 1;
		status REN18 : 1;
		status REN19 : 1;
		status REN20 : 1;
		status REN21 : 1;
		status REN22 : 1;
		status REN23 : 1;
		status REN24 : 1;
		status REN25 : 1;
		status REN26 : 1;
		status REN27 : 1;
		status REN28 : 1;
		status REN29 : 1;
		status REN30 : 1;
		status REN31 : 1;
		status REN32 : 1;
		status REN33 : 1;
		status REN34 : 1;
		status REN35 : 1;
		status REN36 : 1;
		status REN37 : 1;
		status REN38 : 1;
		status REN39 : 1;
		status REN40 : 1;
		status REN41 : 1;
		status REN42 : 1;
		status REN43 : 1;
		status REN44 : 1;
		status REN45 : 1;
		status REN46 : 1;
		status REN47 : 1;
		status REN48 : 1;
		status REN49 : 1;
		status REN50 : 1;
		status REN51 : 1;
		status REN52 : 1;
		status REN53 : 1;
		unsigned : 10;
	}		GPREN;
	unsigned			: 32;
	struct
	{
		status FEN0 : 1;
		status FEN1 : 1;
		status FEN2 : 1;
		status FEN3 : 1;
		status FEN4 : 1;
		status FEN5 : 1;
		status FEN6 : 1;
		status FEN7 : 1;
		status FEN8 : 1;
		status FEN9 : 1;
		status FEN10 : 1;
		status FEN11 : 1;
		status FEN12 : 1;
		status FEN13 : 1;
		status FEN14 : 1;
		status FEN15 : 1;
		status FEN16 : 1;
		status FEN17 : 1;
		status FEN18 : 1;
		status FEN19 : 1;
		status FEN20 : 1;
		status FEN21 : 1;
		status FEN22 : 1;
		status FEN23 : 1;
		status FEN24 : 1;
		status FEN25 : 1;
		status FEN26 : 1;
		status FEN27 : 1;
		status FEN28 : 1;
		status FEN29 : 1;
		status FEN30 : 1;
		status FEN31 : 1;
		status FEN32 : 1;
		status FEN33 : 1;
		status FEN34 : 1;
		status FEN35 : 1;
		status FEN36 : 1;
		status FEN37 : 1;
		status FEN38 : 1;
		status FEN39 : 1;
		status FEN40 : 1;
		status FEN41 : 1;
		status FEN42 : 1;
		status FEN43 : 1;
		status FEN44 : 1;
		status FEN45 : 1;
		status FEN46 : 1;
		status FEN47 : 1;
		status FEN48 : 1;
		status FEN49 : 1;
		status FEN50 : 1;
		status FEN51 : 1;
		status FEN52 : 1;
		status FEN53 : 1;
		unsigned : 10;
	}	    GPFEN;
	unsigned			: 32;
	struct
	{
		status HEN0 : 1;
		status HEN1 : 1;
		status HEN2 : 1;
		status HEN3 : 1;
		status HEN4 : 1;
		status HEN5 : 1;
		status HEN6 : 1;
		status HEN7 : 1;
		status HEN8 : 1;
		status HEN9 : 1;
		status HEN10 : 1;
		status HEN11 : 1;
		status HEN12 : 1;
		status HEN13 : 1;
		status HEN14 : 1;
		status HEN15 : 1;
		status HEN16 : 1;
		status HEN17 : 1;
		status HEN18 : 1;
		status HEN19 : 1;
		status HEN20 : 1;
		status HEN21 : 1;
		status HEN22 : 1;
		status HEN23 : 1;
		status HEN24 : 1;
		status HEN25 : 1;
		status HEN26 : 1;
		status HEN27 : 1;
		status HEN28 : 1;
		status HEN29 : 1;
		status HEN30 : 1;
		status HEN31 : 1;
		status HEN32 : 1;
		status HEN33 : 1;
		status HEN34 : 1;
		status HEN35 : 1;
		status HEN36 : 1;
		status HEN37 : 1;
		status HEN38 : 1;
		status HEN39 : 1;
		status HEN40 : 1;
		status HEN41 : 1;
		status HEN42 : 1;
		status HEN43 : 1;
		status HEN44 : 1;
		status HEN45 : 1;
		status HEN46 : 1;
		status HEN47 : 1;
		status HEN48 : 1;
		status HEN49 : 1;
		status HEN50 : 1;
		status HEN51 : 1;
		status HEN52 : 1;
		status HEN53 : 1;
		unsigned : 10;
	}	    GPHEN;
	unsigned			: 32;
	struct
	{
		status LEN0 : 1;
		status LEN1 : 1;
		status LEN2 : 1;
		status LEN3 : 1;
		status LEN4 : 1;
		status LEN5 : 1;
		status LEN6 : 1;
		status LEN7 : 1;
		status LEN8 : 1;
		status LEN9 : 1;
		status LEN10 : 1;
		status LEN11 : 1;
		status LEN12 : 1;
		status LEN13 : 1;
		status LEN14 : 1;
		status LEN15 : 1;
		status LEN16 : 1;
		status LEN17 : 1;
		status LEN18 : 1;
		status LEN19 : 1;
		status LEN20 : 1;
		status LEN21 : 1;
		status LEN22 : 1;
		status LEN23 : 1;
		status LEN24 : 1;
		status LEN25 : 1;
		status LEN26 : 1;
		status LEN27 : 1;
		status LEN28 : 1;
		status LEN29 : 1;
		status LEN30 : 1;
		status LEN31 : 1;
		status LEN32 : 1;
		status LEN33 : 1;
		status LEN34 : 1;
		status LEN35 : 1;
		status LEN36 : 1;
		status LEN37 : 1;
		status LEN38 : 1;
		status LEN39 : 1;
		status LEN40 : 1;
		status LEN41 : 1;
		status LEN42 : 1;
		status LEN43 : 1;
		status LEN44 : 1;
		status LEN45 : 1;
		status LEN46 : 1;
		status LEN47 : 1;
		status LEN48 : 1;
		status LEN49 : 1;
		status LEN50 : 1;
		status LEN51 : 1;
		status LEN52 : 1;
		status LEN53 : 1;
		unsigned : 10;
	}	    GPLEN;
	unsigned			: 32;
	struct
	{
		status AREN0 : 1;
		status AREN1 : 1;
		status AREN2 : 1;
		status AREN3 : 1;
		status AREN4 : 1;
		status AREN5 : 1;
		status AREN6 : 1;
		status AREN7 : 1;
		status AREN8 : 1;
		status AREN9 : 1;
		status AREN10 : 1;
		status AREN11 : 1;
		status AREN12 : 1;
		status AREN13 : 1;
		status AREN14 : 1;
		status AREN15 : 1;
		status AREN16 : 1;
		status AREN17 : 1;
		status AREN18 : 1;
		status AREN19 : 1;
		status AREN20 : 1;
		status AREN21 : 1;
		status AREN22 : 1;
		status AREN23 : 1;
		status AREN24 : 1;
		status AREN25 : 1;
		status AREN26 : 1;
		status AREN27 : 1;
		status AREN28 : 1;
		status AREN29 : 1;
		status AREN30 : 1;
		status AREN31 : 1;
		status AREN32 : 1;
		status AREN33 : 1;
		status AREN34 : 1;
		status AREN35 : 1;
		status AREN36 : 1;
		status AREN37 : 1;
		status AREN38 : 1;
		status AREN39 : 1;
		status AREN40 : 1;
		status AREN41 : 1;
		status AREN42 : 1;
		status AREN43 : 1;
		status AREN44 : 1;
		status AREN45 : 1;
		status AREN46 : 1;
		status AREN47 : 1;
		status AREN48 : 1;
		status AREN49 : 1;
		status AREN50 : 1;
		status AREN51 : 1;
		status AREN52 : 1;
		status AREN53 : 1;
		unsigned : 10;
	}	    GPAREN;
	unsigned			: 32;
	struct
	{
		status AFEN0 : 1;
		status AFEN1 : 1;
		status AFEN2 : 1;
		status AFEN3 : 1;
		status AFEN4 : 1;
		status AFEN5 : 1;
		status AFEN6 : 1;
		status AFEN7 : 1;
		status AFEN8 : 1;
		status AFEN9 : 1;
		status AFEN10 : 1;
		status AFEN11 : 1;
		status AFEN12 : 1;
		status AFEN13 : 1;
		status AFEN14 : 1;
		status AFEN15 : 1;
		status AFEN16 : 1;
		status AFEN17 : 1;
		status AFEN18 : 1;
		status AFEN19 : 1;
		status AFEN20 : 1;
		status AFEN21 : 1;
		status AFEN22 : 1;
		status AFEN23 : 1;
		status AFEN24 : 1;
		status AFEN25 : 1;
		status AFEN26 : 1;
		status AFEN27 : 1;
		status AFEN28 : 1;
		status AFEN29 : 1;
		status AFEN30 : 1;
		status AFEN31 : 1;
		status AFEN32 : 1;
		status AFEN33 : 1;
		status AFEN34 : 1;
		status AFEN35 : 1;
		status AFEN36 : 1;
		status AFEN37 : 1;
		status AFEN38 : 1;
		status AFEN39 : 1;
		status AFEN40 : 1;
		status AFEN41 : 1;
		status AFEN42 : 1;
		status AFEN43 : 1;
		status AFEN44 : 1;
		status AFEN45 : 1;
		status AFEN46 : 1;
		status AFEN47 : 1;
		status AFEN48 : 1;
		status AFEN49 : 1;
		status AFEN50 : 1;
		status AFEN51 : 1;
		status AFEN52 : 1;
		status AFEN53 : 1;
		unsigned : 10;
	}		GPAFEN;
	unsigned			: 32;
	struct //GPIO Pull-up/down Register (GPPUD) 
	{
		pull	PUD : 2;
		unsigned : 30;
	}		GPPUD;
	struct
	{
		clock PUDCLK0 : 1;
		clock PUDCLK1 : 1;
		clock PUDCLK2 : 1;
		clock PUDCLK3 : 1;
		clock PUDCLK4 : 1;
		clock PUDCLK5 : 1;
		clock PUDCLK6 : 1;
		clock PUDCLK7 : 1;
		clock PUDCLK8 : 1;
		clock PUDCLK9 : 1;
		clock PUDCLK10 : 1;
		clock PUDCLK11 : 1;
		clock PUDCLK12 : 1;
		clock PUDCLK13 : 1;
		clock PUDCLK14 : 1;
		clock PUDCLK15 : 1;
		clock PUDCLK16 : 1;
		clock PUDCLK17 : 1;
		clock PUDCLK18 : 1;
		clock PUDCLK19 : 1;
		clock PUDCLK20 : 1;
		clock PUDCLK21 : 1;
		clock PUDCLK22 : 1;
		clock PUDCLK23 : 1;
		clock PUDCLK24 : 1;
		clock PUDCLK25 : 1;
		clock PUDCLK26 : 1;
		clock PUDCLK27 : 1;
		clock PUDCLK28 : 1;
		clock PUDCLK29 : 1;
		clock PUDCLK30 : 1;
		clock PUDCLK31 : 1;
		clock PUDCLK32 : 1;
		clock PUDCLK33 : 1;
		clock PUDCLK34 : 1;
		clock PUDCLK35 : 1;
		clock PUDCLK36 : 1;
		clock PUDCLK37 : 1;
		clock PUDCLK38 : 1;
		clock PUDCLK39 : 1;
		clock PUDCLK40 : 1;
		clock PUDCLK41 : 1;
		clock PUDCLK42 : 1;
		clock PUDCLK43 : 1;
		clock PUDCLK44 : 1;
		clock PUDCLK45 : 1;
		clock PUDCLK46 : 1;
		clock PUDCLK47 : 1;
		clock PUDCLK48 : 1;
		clock PUDCLK49 : 1;
		clock PUDCLK50 : 1;
		clock PUDCLK51 : 1;
		clock PUDCLK52 : 1;
		clock PUDCLK53 : 1;
		unsigned : 10;
	}		GPPUDCLK;
	unsigned			: 32;
	unsigned			: 32;
	unsigned			: 32;
	unsigned			: 32;
	//unsigned char	Test	: 4;
};

#ifdef __GNUC__
#undef mode
#undef pull 
#endif


class bcm2835 {
public:
	static bcm2835& instance();
	GPIO_REGS& registers();
private:
	std::unique_ptr<int, 	fcloser>  	mem_fd_;
	std::unique_ptr<void, 	mcloser> 	p_map_;

	bcm2835();
};


} /* namespace rpi_cxx */

#endif /* BCM2835_H_ */
