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
	struct 
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
	}		GPFSEL0;
	struct 
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
	}		GPFSEL1;
	struct 
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
	}		GPFSEL2;
	struct 
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
	}		GPFSEL3;
	struct 
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
	}		GPFSEL4;
	struct 
	{
		pin_fun FSEL50      : 3;
		pin_fun FSEL51      : 3;
		pin_fun FSEL52      : 3;
		pin_fun FSEL53      : 3;
		unsigned            : 20;
	}		GPFSEL5;
	unsigned			:32;
	typedef enum
	{
		noEffect=0x0,
		setOut	=0x1
	}	output_set;
	struct 
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
	}		GPSET0;
	struct 
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
	}		GPSET1;
	unsigned			:32;
	typedef enum
	{
		clearNoEffect=0x0,
		clearOut=0x1
	}	output_clr;
	struct 
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
	}		GPCLR0;
	struct 
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
	}		GPCLR1;
	unsigned			:32;
	typedef enum
	{
		low,
		hight
	}	pin_level;
	struct 
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
	}		GPLEV0;
	struct 
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
	}		GPLEV1;
	unsigned			:32;
	typedef enum
	{
		event_not_detected	=0x0,
		event_detected		=0x1
	}	pin_event;
	struct 
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
	}		GPEDS0;
	struct 
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
		pin_event EDS53	:1;
		unsigned		:10;
	}		GPEDS1;
	unsigned			:32;
	typedef enum
	{
		redDisable = 0x0,
		redOn = 0x1
	}	red_status;
	struct
	{
		red_status REN0 : 1;
		red_status REN1 : 1;
		red_status REN2 : 1;
		red_status REN3 : 1;
		red_status REN4 : 1;
		red_status REN5 : 1;
		red_status REN6 : 1;
		red_status REN7 : 1;
		red_status REN8 : 1;
		red_status REN9 : 1;
		red_status REN10 : 1;
		red_status REN11 : 1;
		red_status REN12 : 1;
		red_status REN13 : 1;
		red_status REN14 : 1;
		red_status REN15 : 1;
		red_status REN16 : 1;
		red_status REN17 : 1;
		red_status REN18 : 1;
		red_status REN19 : 1;
		red_status REN20 : 1;
		red_status REN21 : 1;
		red_status REN22 : 1;
		red_status REN23 : 1;
		red_status REN24 : 1;
		red_status REN25 : 1;
		red_status REN26 : 1;
		red_status REN27 : 1;
		red_status REN28 : 1;
		red_status REN29 : 1;
		red_status REN30 : 1;
		red_status REN31 : 1;
	}		GPREN0;
	struct
	{

		red_status REN32 : 1;
		red_status REN33 : 1;
		red_status REN34 : 1;
		red_status REN35 : 1;
		red_status REN36 : 1;
		red_status REN37 : 1;
		red_status REN38 : 1;
		red_status REN39 : 1;
		red_status REN40 : 1;
		red_status REN41 : 1;
		red_status REN42 : 1;
		red_status REN43 : 1;
		red_status REN44 : 1;
		red_status REN45 : 1;
		red_status REN46 : 1;
		red_status REN47 : 1;
		red_status REN48 : 1;
		red_status REN49 : 1;
		red_status REN50 : 1;
		red_status REN51 : 1;
		red_status REN52 : 1;
		red_status REN53 : 1;
		unsigned : 10;
	}		GPREN1;
	unsigned			: 32;
	typedef enum
	{
		fedDisable = 0x0,
		fedOn = 0x1
	}	fed_status;
	struct
	{
		fed_status FEN0 : 1;
		fed_status FEN1 : 1;
		fed_status FEN2 : 1;
		fed_status FEN3 : 1;
		fed_status FEN4 : 1;
		fed_status FEN5 : 1;
		fed_status FEN6 : 1;
		fed_status FEN7 : 1;
		fed_status FEN8 : 1;
		fed_status FEN9 : 1;
		fed_status FEN10 : 1;
		fed_status FEN11 : 1;
		fed_status FEN12 : 1;
		fed_status FEN13 : 1;
		fed_status FEN14 : 1;
		fed_status FEN15 : 1;
		fed_status FEN16 : 1;
		fed_status FEN17 : 1;
		fed_status FEN18 : 1;
		fed_status FEN19 : 1;
		fed_status FEN20 : 1;
		fed_status FEN21 : 1;
		fed_status FEN22 : 1;
		fed_status FEN23 : 1;
		fed_status FEN24 : 1;
		fed_status FEN25 : 1;
		fed_status FEN26 : 1;
		fed_status FEN27 : 1;
		fed_status FEN28 : 1;
		fed_status FEN29 : 1;
		fed_status FEN30 : 1;
		fed_status FEN31 : 1;
	}	    GPFEN0;
	struct
	{

		fed_status FEN32 : 1;
		fed_status FEN33 : 1;
		fed_status FEN34 : 1;
		fed_status FEN35 : 1;
		fed_status FEN36 : 1;
		fed_status FEN37 : 1;
		fed_status FEN38 : 1;
		fed_status FEN39 : 1;
		fed_status FEN40 : 1;
		fed_status FEN41 : 1;
		fed_status FEN42 : 1;
		fed_status FEN43 : 1;
		fed_status FEN44 : 1;
		fed_status FEN45 : 1;
		fed_status FEN46 : 1;
		fed_status FEN47 : 1;
		fed_status FEN48 : 1;
		fed_status FEN49 : 1;
		fed_status FEN50 : 1;
		fed_status FEN51 : 1;
		fed_status FEN52 : 1;
		fed_status FEN53 : 1;
		unsigned : 10;
	}	    GPFEN1;
	unsigned			: 32;
	typedef enum
	{
		hdDisable = 0x0,
		hdOn = 0x1
	}	hd_status;
	struct
	{
		hd_status HEN0 : 1;
		hd_status HEN1 : 1;
		hd_status HEN2 : 1;
		hd_status HEN3 : 1;
		hd_status HEN4 : 1;
		hd_status HEN5 : 1;
		hd_status HEN6 : 1;
		hd_status HEN7 : 1;
		hd_status HEN8 : 1;
		hd_status HEN9 : 1;
		hd_status HEN10 : 1;
		hd_status HEN11 : 1;
		hd_status HEN12 : 1;
		hd_status HEN13 : 1;
		hd_status HEN14 : 1;
		hd_status HEN15 : 1;
		hd_status HEN16 : 1;
		hd_status HEN17 : 1;
		hd_status HEN18 : 1;
		hd_status HEN19 : 1;
		hd_status HEN20 : 1;
		hd_status HEN21 : 1;
		hd_status HEN22 : 1;
		hd_status HEN23 : 1;
		hd_status HEN24 : 1;
		hd_status HEN25 : 1;
		hd_status HEN26 : 1;
		hd_status HEN27 : 1;
		hd_status HEN28 : 1;
		hd_status HEN29 : 1;
		hd_status HEN30 : 1;
		hd_status HEN31 : 1;
	}	    GPHEN0;
	struct
	{

		hd_status HEN32 : 1;
		hd_status HEN33 : 1;
		hd_status HEN34 : 1;
		hd_status HEN35 : 1;
		hd_status HEN36 : 1;
		hd_status HEN37 : 1;
		hd_status HEN38 : 1;
		hd_status HEN39 : 1;
		hd_status HEN40 : 1;
		hd_status HEN41 : 1;
		hd_status HEN42 : 1;
		hd_status HEN43 : 1;
		hd_status HEN44 : 1;
		hd_status HEN45 : 1;
		hd_status HEN46 : 1;
		hd_status HEN47 : 1;
		hd_status HEN48 : 1;
		hd_status HEN49 : 1;
		hd_status HEN50 : 1;
		hd_status HEN51 : 1;
		hd_status HEN52 : 1;
		hd_status HEN53 : 1;
		unsigned : 10;
	}	    GPHEN1;
	unsigned			: 32;
	typedef enum
	{
		ldDisable = 0x0,
		ldOn = 0x1
	} ld_status;
	struct
	{
		ld_status LEN0 : 1;
		ld_status LEN1 : 1;
		ld_status LEN2 : 1;
		ld_status LEN3 : 1;
		ld_status LEN4 : 1;
		ld_status LEN5 : 1;
		ld_status LEN6 : 1;
		ld_status LEN7 : 1;
		ld_status LEN8 : 1;
		ld_status LEN9 : 1;
		ld_status LEN10 : 1;
		ld_status LEN11 : 1;
		ld_status LEN12 : 1;
		ld_status LEN13 : 1;
		ld_status LEN14 : 1;
		ld_status LEN15 : 1;
		ld_status LEN16 : 1;
		ld_status LEN17 : 1;
		ld_status LEN18 : 1;
		ld_status LEN19 : 1;
		ld_status LEN20 : 1;
		ld_status LEN21 : 1;
		ld_status LEN22 : 1;
		ld_status LEN23 : 1;
		ld_status LEN24 : 1;
		ld_status LEN25 : 1;
		ld_status LEN26 : 1;
		ld_status LEN27 : 1;
		ld_status LEN28 : 1;
		ld_status LEN29 : 1;
		ld_status LEN30 : 1;
		ld_status LEN31 : 1;
	}	    GPLEN0;
	struct
	{

		ld_status LEN32 : 1;
		ld_status LEN33 : 1;
		ld_status LEN34 : 1;
		ld_status LEN35 : 1;
		ld_status LEN36 : 1;
		ld_status LEN37 : 1;
		ld_status LEN38 : 1;
		ld_status LEN39 : 1;
		ld_status LEN40 : 1;
		ld_status LEN41 : 1;
		ld_status LEN42 : 1;
		ld_status LEN43 : 1;
		ld_status LEN44 : 1;
		ld_status LEN45 : 1;
		ld_status LEN46 : 1;
		ld_status LEN47 : 1;
		ld_status LEN48 : 1;
		ld_status LEN49 : 1;
		ld_status LEN50 : 1;
		ld_status LEN51 : 1;
		ld_status LEN52 : 1;
		ld_status LEN53 : 1;
		unsigned : 10;
	}	    GPLEN1;
	unsigned			: 32;
	typedef enum
	{
		aredDisable = 0x0,
		aredOn = 0x1
	} ared_status;
	struct
	{
		ared_status AREN0 : 1;
		ared_status AREN1 : 1;
		ared_status AREN2 : 1;
		ared_status AREN3 : 1;
		ared_status AREN4 : 1;
		ared_status AREN5 : 1;
		ared_status AREN6 : 1;
		ared_status AREN7 : 1;
		ared_status AREN8 : 1;
		ared_status AREN9 : 1;
		ared_status AREN10 : 1;
		ared_status AREN11 : 1;
		ared_status AREN12 : 1;
		ared_status AREN13 : 1;
		ared_status AREN14 : 1;
		ared_status AREN15 : 1;
		ared_status AREN16 : 1;
		ared_status AREN17 : 1;
		ared_status AREN18 : 1;
		ared_status AREN19 : 1;
		ared_status AREN20 : 1;
		ared_status AREN21 : 1;
		ared_status AREN22 : 1;
		ared_status AREN23 : 1;
		ared_status AREN24 : 1;
		ared_status AREN25 : 1;
		ared_status AREN26 : 1;
		ared_status AREN27 : 1;
		ared_status AREN28 : 1;
		ared_status AREN29 : 1;
		ared_status AREN30 : 1;
		ared_status AREN31 : 1;
	}	    GPAREN0;
	struct
	{

		ared_status AREN32 : 1;
		ared_status AREN33 : 1;
		ared_status AREN34 : 1;
		ared_status AREN35 : 1;
		ared_status AREN36 : 1;
		ared_status AREN37 : 1;
		ared_status AREN38 : 1;
		ared_status AREN39 : 1;
		ared_status AREN40 : 1;
		ared_status AREN41 : 1;
		ared_status AREN42 : 1;
		ared_status AREN43 : 1;
		ared_status AREN44 : 1;
		ared_status AREN45 : 1;
		ared_status AREN46 : 1;
		ared_status AREN47 : 1;
		ared_status AREN48 : 1;
		ared_status AREN49 : 1;
		ared_status AREN50 : 1;
		ared_status AREN51 : 1;
		ared_status AREN52 : 1;
		ared_status AREN53 : 1;
		unsigned : 10;
	}	    GPAREN1;
	unsigned			: 32;
	typedef enum
	{
		afedDisable = 0x0,
		afedOn = 0x1
	} afed_status;
	struct
	{
		afed_status AFEN0 : 1;
		afed_status AFEN1 : 1;
		afed_status AFEN2 : 1;
		afed_status AFEN3 : 1;
		afed_status AFEN4 : 1;
		afed_status AFEN5 : 1;
		afed_status AFEN6 : 1;
		afed_status AFEN7 : 1;
		afed_status AFEN8 : 1;
		afed_status AFEN9 : 1;
		afed_status AFEN10 : 1;
		afed_status AFEN11 : 1;
		afed_status AFEN12 : 1;
		afed_status AFEN13 : 1;
		afed_status AFEN14 : 1;
		afed_status AFEN15 : 1;
		afed_status AFEN16 : 1;
		afed_status AFEN17 : 1;
		afed_status AFEN18 : 1;
		afed_status AFEN19 : 1;
		afed_status AFEN20 : 1;
		afed_status AFEN21 : 1;
		afed_status AFEN22 : 1;
		afed_status AFEN23 : 1;
		afed_status AFEN24 : 1;
		afed_status AFEN25 : 1;
		afed_status AFEN26 : 1;
		afed_status AFEN27 : 1;
		afed_status AFEN28 : 1;
		afed_status AFEN29 : 1;
		afed_status AFEN30 : 1;
		afed_status AFEN31 : 1;
	}	    GPAFEN0;
	struct
	{

		afed_status AFEN32 : 1;
		afed_status AFEN33 : 1;
		afed_status AFEN34 : 1;
		afed_status AFEN35 : 1;
		afed_status AFEN36 : 1;
		afed_status AFEN37 : 1;
		afed_status AFEN38 : 1;
		afed_status AFEN39 : 1;
		afed_status AFEN40 : 1;
		afed_status AFEN41 : 1;
		afed_status AFEN42 : 1;
		afed_status AFEN43 : 1;
		afed_status AFEN44 : 1;
		afed_status AFEN45 : 1;
		afed_status AFEN46 : 1;
		afed_status AFEN47 : 1;
		afed_status AFEN48 : 1;
		afed_status AFEN49 : 1;
		afed_status AFEN50 : 1;
		afed_status AFEN51 : 1;
		afed_status AFEN52 : 1;
		afed_status AFEN53 : 1;
		unsigned : 10;
	}		GPAFEN1;
	unsigned			: 32;
	typedef enum
	{
		pudOff = 0x0, // disable pull-up/down
		pudEnablePullDown = 0x1, // Enable Pull Down control
		pudEnablePullUp = 0x2, // Enable Pull Up control 
		pudReserved = 0x3  // Reserved
	} pin_pull_updown;
	struct //GPIO Pull-up/down Register (GPPUD) 
	{
		pin_pull_updown	PUD : 2;
		unsigned : 30;
	}		GPPUD;
	typedef enum
	{
		clockNoEffect = 0x0,
		clockAssertOnLine = 0x1
	} pud_clock;
	struct
	{
		pud_clock PUDCLK0 : 1;
		pud_clock PUDCLK1 : 1;
		pud_clock PUDCLK2 : 1;
		pud_clock PUDCLK3 : 1;
		pud_clock PUDCLK4 : 1;
		pud_clock PUDCLK5 : 1;
		pud_clock PUDCLK6 : 1;
		pud_clock PUDCLK7 : 1;
		pud_clock PUDCLK8 : 1;
		pud_clock PUDCLK9 : 1;
		pud_clock PUDCLK10 : 1;
		pud_clock PUDCLK11 : 1;
		pud_clock PUDCLK12 : 1;
		pud_clock PUDCLK13 : 1;
		pud_clock PUDCLK14 : 1;
		pud_clock PUDCLK15 : 1;
		pud_clock PUDCLK16 : 1;
		pud_clock PUDCLK17 : 1;
		pud_clock PUDCLK18 : 1;
		pud_clock PUDCLK19 : 1;
		pud_clock PUDCLK20 : 1;
		pud_clock PUDCLK21 : 1;
		pud_clock PUDCLK22 : 1;
		pud_clock PUDCLK23 : 1;
		pud_clock PUDCLK24 : 1;
		pud_clock PUDCLK25 : 1;
		pud_clock PUDCLK26 : 1;
		pud_clock PUDCLK27 : 1;
		pud_clock PUDCLK28 : 1;
		pud_clock PUDCLK29 : 1;
		pud_clock PUDCLK30 : 1;
		pud_clock PUDCLK31 : 1;
	}		GPPUDCLK0;
	struct
	{

		pud_clock PUDCLK32 : 1;
		pud_clock PUDCLK33 : 1;
		pud_clock PUDCLK34 : 1;
		pud_clock PUDCLK35 : 1;
		pud_clock PUDCLK36 : 1;
		pud_clock PUDCLK37 : 1;
		pud_clock PUDCLK38 : 1;
		pud_clock PUDCLK39 : 1;
		pud_clock PUDCLK40 : 1;
		pud_clock PUDCLK41 : 1;
		pud_clock PUDCLK42 : 1;
		pud_clock PUDCLK43 : 1;
		pud_clock PUDCLK44 : 1;
		pud_clock PUDCLK45 : 1;
		pud_clock PUDCLK46 : 1;
		pud_clock PUDCLK47 : 1;
		pud_clock PUDCLK48 : 1;
		pud_clock PUDCLK49 : 1;
		pud_clock PUDCLK50 : 1;
		pud_clock PUDCLK51 : 1;
		pud_clock PUDCLK52 : 1;
		pud_clock PUDCLK53 : 1;
		unsigned : 10;
	}		GPPUDCLK1;
	unsigned			: 32;
	unsigned			: 32;
	unsigned			: 32;
	unsigned			: 32;
	//unsigned char	Test	: 4;
};

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
