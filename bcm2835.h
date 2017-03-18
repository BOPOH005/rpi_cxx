/*
 * bcm2835.h
 *
 *  Created on: 18.09.2016
 *      Author: bopoh
 */

#ifndef BCM2835_H_
#define BCM2835_H_

#include<memory>
#include<cstdint>

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

enum  mode
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

// enum  set
// {
// 	no_effect	=0x0,
// 	on			=0x1
// };

enum  level 
{
	low		=0x0,
	hight	=0x1
};

enum  event
{
	not_detected	=0x0,
	detected		=0x1
};

enum  status
{
	disable = 0x0,
	on 		= 0x1
};

enum pull
{
	off 		= 0x0, // disable pull-up/down
	down 		= 0x1, // Enable Pull Down control
	up 			= 0x2, // Enable Pull Up control 
	reserved	= 0x3  // Reserved
};

enum clock
{
	no_effect	= 0x0,
	assert		= 0x1
};

//#pragma pack(push,4)
struct   GPIO
{
	// typedef struct  
	// {
	// 	u_int64_t GPp1;
	// 	u_int64_t GPp2;
	// 	u_int64_t GPp3;
	// 	u_int32_t :32;
	// 	u_int64_t GPf;
	// 	u_int32_t :32;
	// 	u_int64_t GPCLR;
	// 	u_int32_t :32;
	// 	u_int64_t GPLEV;
	// 	u_int32_t :32;
	// 	u_int64_t GPEDS;
	// 	u_int32_t :32;
	// 	u_int64_t GPREN;
	// 	u_int32_t :32;
	// 	u_int64_t GPFEN;
	// 	u_int32_t :32;
	// 	u_int64_t GPHEN;
	// 	u_int32_t :32;
	// 	u_int64_t GPLEN;
	// 	u_int32_t :32;
	// 	u_int64_t GPAREN;
	// 	u_int32_t :32;
	// 	u_int64_t GPAFEN;
	// 	u_int32_t :32;
	// 	u_int32_t GPPUD;
	// 	u_int64_t GPPUDCLK;
	// 	u_int32_t :32;
	// 	u_int32_t :32;
	// 	u_int32_t :32;
	// 	u_int32_t :32;
	// } __attribute__((packed, aligned(4))) regs; 
	// regs REGS;
	// typedef struct 
	// { 
	union __attribute__((packed, aligned(4))) gpfsel
	{
		struct 
		{
			u_int64_t r0;
	 		u_int64_t r1;
		 	u_int64_t r2;
		} reg;	
		struct 
		{
			mode p0      : 3;
			mode p1      : 3;
			mode p2      : 3;
			mode p3      : 3;
			mode p4      : 3;
			mode p5      : 3;
			mode p6      : 3;
			mode p7      : 3;
			mode p8      : 3;
			mode p9      : 3;
			unsigned           : 2;
			mode p10      : 3;
			mode p11      : 3;
			mode p12      : 3;
			mode p13      : 3;
			mode p14      : 3;
			mode p15      : 3;
			mode p16      : 3;
			mode p17      : 3;
			mode p18      : 3;
			mode p19      : 3;
			unsigned            : 2;
			mode p20      : 3;
			mode p21      : 3;
			mode p22      : 3;
			mode p23      : 3;
			mode p24      : 3;
			mode p25      : 3;
			mode p26      : 3;
			mode p27      : 3;
			mode p28      : 3;
			mode p29      : 3;
			unsigned            : 2;
			mode p30      : 3;
			mode p31      : 3;
			mode p32      : 3;
			mode p33      : 3;
			mode p34      : 3;
			mode p35      : 3;
			mode p36      : 3;
			mode p37      : 3;
			mode p38      : 3;
			mode p39      : 3;
			unsigned            : 2;
			mode p40      : 3;
			mode p41      : 3;
			mode p42      : 3;
			mode p43      : 3;
			mode p44      : 3;
			mode p45      : 3;
			mode p46      : 3;
			mode p47      : 3;
			mode p48      : 3;
			mode p49      : 3;
			unsigned            : 2;
			mode p50      : 3;
			mode p51      : 3;
			mode p52      : 3;
			mode p53      : 3;
			unsigned            : 20;
		} fld;
	} GPFSEL;
	unsigned 			:32;
	union __attribute__((packed, aligned(4))) gpsetclr
	{
		u_int64_t reg;
		struct 
		{
			bool p0       : 1;
			bool p1       : 1;
			bool p2       : 1;
			bool p3       : 1;
			bool p4       : 1;
			bool p5       : 1;
			bool p6       : 1;
			bool p7       : 1;
			bool p8       : 1;
			bool p9       : 1;
			bool p10      : 1;
			bool p11      : 1;
			bool p12      : 1;
			bool p13      : 1;
			bool p14      : 1;
			bool p15      : 1;
			bool p16      : 1;
			bool p17      : 1;
			bool p18      : 1;
			bool p19      : 1;
			bool p20      : 1;
			bool p21      : 1;
			bool p22      : 1;
			bool p23      : 1;
			bool p24      : 1;
			bool p25      : 1;
			bool p26      : 1;
			bool p27      : 1;
			bool p28      : 1;
			bool p29      : 1;
			bool p30      : 1;
			bool p31      : 1;
			bool p32       : 1;
			bool p33       : 1;
			bool p34       : 1;
			bool p35       : 1;
			bool p36       : 1;
			bool p37       : 1;
			bool p38       : 1;
			bool p39       : 1;
			bool p40       : 1;
			bool p41       : 1;
			bool p42       : 1;
			bool p43       : 1;
			bool p44       : 1;
			bool p45       : 1;
			bool p46       : 1;
			bool p47       : 1;
			bool p48       : 1;
			bool p49       : 1;
			bool p50       : 1;
			bool p51       : 1;
			bool p52       : 1;
			bool p53       : 1;
			unsigned               : 10;
		}fld;
	} GPSET;
	unsigned			:32;
	gpsetclr	GPCLR;
	unsigned			:32;
	union __attribute__((packed, aligned(4))) gplev
	{
		u_int64_t reg;
		struct levels
		{
//#define level unsigned
			level p0       : 1;
			level p1       : 1;
			level p2       : 1;
			level p3       : 1;
			level p4       : 1;
			level p5       : 1;
			level p6       : 1;
			level p7       : 1;
			level p8       : 1;
			level p9       : 1;
			level p10      : 1;
			level p11      : 1;
			level p12      : 1;
			level p13      : 1;
			level p14      : 1;
			level p15      : 1;
			level p16      : 1;
			level p17      : 1;
			level p18      : 1;
			level p19      : 1;
			level p20      : 1;
			level p21      : 1;
			level p22      : 1;
			level p23      : 1;
			level p24      : 1;
			level p25      : 1;
			level p26      : 1;
			level p27      : 1;
			level p28      : 1;
			level p29      : 1;
			level p30      : 1;
			level p31      : 1;
			level p32       : 1;
			level p33       : 1;
			level p34       : 1;
			level p35       : 1;
			level p36       : 1;
			level p37       : 1;
			level p38       : 1;
			level p39       : 1;
			level p40       : 1;
			level p41       : 1;
			level p42       : 1;
			level p43       : 1;
			level p44       : 1;
			level p45       : 1;
			level p46       : 1;
			level p47       : 1;
			level p48       : 1;
			level p49       : 1;
			level p50       : 1;
			level p51       : 1;
			level p52       : 1;
			level p53       : 1;
			unsigned	          : 10;
//#undef level 
		} fld;
	} /*const*/ GPLEV;
	unsigned			:32;
	union __attribute__((packed, aligned(4))) gpeds
	{
		u_int64_t reg;
		struct 
		{
			event p0	:1;
			event p1	:1;
			event p2	:1;
			event p3	:1;
			event p4	:1;
			event p5	:1;
			event p6	:1;
			event p7	:1;
			event p8	:1;
			event p9	:1;
			event p10	:1;
			event p11	:1;
			event p12	:1;
			event p13	:1;
			event p14	:1;
			event p15	:1;
			event p16	:1;
			event p17	:1;
			event p18	:1;
			event p19	:1;
			event p20	:1;
			event p21	:1;
			event p22	:1;
			event p23	:1;
			event p24	:1;
			event p25	:1;
			event p26	:1;
			event p27	:1;
			event p28	:1;
			event p29	:1;
			event p30	:1;
			event p31	:1;
			event p32	:1;
			event p33	:1;
			event p34	:1;
			event p35	:1;
			event p36	:1;
			event p37	:1;
			event p38	:1;
			event p39	:1;
			event p40	:1;
			event p41	:1;
			event p42	:1;
			event p43	:1;
			event p44	:1;
			event p45	:1;
			event p46	:1;
			event p47	:1;
			event p48	:1;
			event p49	:1;
			event p50	:1;
			event p51	:1;
			event p52	:1;
			event p53	:1;
			unsigned		:10;
		} fld;		
	} GPEDS;
	unsigned			:32;
	union __attribute__((packed, aligned(4))) stats
	{
		u_int64_t reg;
		struct
		{
			status p0 : 1;
			status p1 : 1;
			status p2 : 1;
			status p3 : 1;
			status p4 : 1;
			status p5 : 1;
			status p6 : 1;
			status p7 : 1;
			status p8 : 1;
			status p9 : 1;
			status p10 : 1;
			status p11 : 1;
			status p12 : 1;
			status p13 : 1;
			status p14 : 1;
			status p15 : 1;
			status p16 : 1;
			status p17 : 1;
			status p18 : 1;
			status p19 : 1;
			status p20 : 1;
			status p21 : 1;
			status p22 : 1;
			status p23 : 1;
			status p24 : 1;
			status p25 : 1;
			status p26 : 1;
			status p27 : 1;
			status p28 : 1;
			status p29 : 1;
			status p30 : 1;
			status p31 : 1;
			status p32 : 1;
			status p33 : 1;
			status p34 : 1;
			status p35 : 1;
			status p36 : 1;
			status p37 : 1;
			status p38 : 1;
			status p39 : 1;
			status p40 : 1;
			status p41 : 1;
			status p42 : 1;
			status p43 : 1;
			status p44 : 1;
			status p45 : 1;
			status p46 : 1;
			status p47 : 1;
			status p48 : 1;
			status p49 : 1;
			status p50 : 1;
			status p51 : 1;
			status p52 : 1;
			status p53 : 1;
			unsigned : 10;
		} fld;
	} GPREN;
	unsigned			: 32;
	stats  GPFEN;
	unsigned			: 32;
	stats  GPHEN;
	unsigned			: 32;
	stats  GPLEN;
	unsigned			: 32;
	stats  GPAREN;
	unsigned			: 32;
	stats  GPAFEN;
	unsigned			: 32;
	union __attribute__((packed, aligned(4))) gppud
	{
		u_int32_t reg;
		struct //GPIO Pull-up/down Register (GPPUD) 
		{
			pull f		: 2;
			unsigned	: 30;
		} fld;
	} GPPUD;
	union __attribute__((packed, aligned(4))) gppudclk
	{
		u_int64_t reg;
		struct
		{
			clock p0 : 1;
			clock p1 : 1;
			clock p2 : 1;
			clock p3 : 1;
			clock p4 : 1;
			clock p5 : 1;
			clock p6 : 1;
			clock p7 : 1;
			clock p8 : 1;
			clock p9 : 1;
			clock p10 : 1;
			clock p11 : 1;
			clock p12 : 1;
			clock p13 : 1;
			clock p14 : 1;
			clock p15 : 1;
			clock p16 : 1;
			clock p17 : 1;
			clock p18 : 1;
			clock p19 : 1;
			clock p20 : 1;
			clock p21 : 1;
			clock p22 : 1;
			clock p23 : 1;
			clock p24 : 1;
			clock p25 : 1;
			clock p26 : 1;
			clock p27 : 1;
			clock p28 : 1;
			clock p29 : 1;
			clock p30 : 1;
			clock p31 : 1;
			clock p32 : 1;
			clock p33 : 1;
			clock p34 : 1;
			clock p35 : 1;
			clock p36 : 1;
			clock p37 : 1;
			clock p38 : 1;
			clock p39 : 1;
			clock p40 : 1;
			clock p41 : 1;
			clock p42 : 1;
			clock p43 : 1;
			clock p44 : 1;
			clock p45 : 1;
			clock p46 : 1;
			clock p47 : 1;
			clock p48 : 1;
			clock p49 : 1;
			clock p50 : 1;
			clock p51 : 1;
			clock p52 : 1;
			clock p53 : 1;
			unsigned : 10;
		} fld;
	} GPPUDCLK;
	unsigned			: 32;
	unsigned			: 32;
	unsigned			: 32;
	unsigned			: 32;
	//unsigned char	Test	: 4;
};
//#pragma push

class bcm2835 {
public:
	static bcm2835& instance();
	volatile GPIO& registers();
private:
	std::unique_ptr<int, 	fcloser>  	mem_fd_;
	std::unique_ptr<void, 	mcloser> 	p_map_;

	bcm2835();
};


} /* namespace rpi_cxx */

#endif /* BCM2835_H_ */
