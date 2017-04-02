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

enum pull
{
	off 		= 0x0, // disable pull-up/down
	down 		= 0x1, // Enable Pull Down control
	up 			= 0x2, // Enable Pull Up control 
	reserved	= 0x3  // Reserved
};


//#pragma pack(push,4)
struct   GPIO
{
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
	union __attribute__((packed, aligned(4))) gpset
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
		gpset(){reg=0;}
		gpset(const gpset& r){reg=r.reg;}
		template<class _T>
		gpset& operator<<(_T pin){ pin.add2reg(*this); return *this;}
	} GPSET;
	unsigned			:32;
	gpset	GPCLR;
	unsigned			:32;
	gpset const GPLEV;
	unsigned			:32;
	gpset	GPEDS;
	unsigned			:32;
	gpset 	GPREN;
	unsigned			: 32;
	gpset  	GPFEN;
	unsigned			: 32;
	gpset  	GPHEN;
	unsigned			: 32;
	gpset  	GPLEN;
	unsigned			: 32;
	gpset  	GPAREN;
	unsigned			: 32;
	gpset  	GPAFEN;
	unsigned			: 32;
	union __attribute__((packed, aligned(4))) gppud
	{
		u_int32_t reg;
		struct //GPIO Pull-up/down Register (GPPUD) 
		{
			pull f		: 2;
			unsigned	: 30;
		} fld;
	} 			GPPUD;
	gpset 	GPPUDCLK;
	unsigned			: 32;
	unsigned			: 32;
	unsigned			: 32;
	unsigned			: 32;
	//unsigned char	Test	: 4;
};
//#pragma push

enum class level 
{
	low		=0x0,
	hight	=0x1
};

class bcm2835 {
public:
	static bcm2835& instance();
	volatile GPIO& registers();

	// void	setmode(mode m, const GPIO::gpfsel& reg);
	void	pullupdown(pull f, const GPIO::gpset& reg);
	void	setlevel(level l, const GPIO::gpset& reg);

private:
	std::unique_ptr<int, 	fcloser>  	mem_fd_;
	std::unique_ptr<void, 	mcloser> 	p_map_;

	bcm2835();
};


} /* namespace rpi_cxx */

#endif /* BCM2835_H_ */
