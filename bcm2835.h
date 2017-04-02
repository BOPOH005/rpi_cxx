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

// Компилятор gcc не корретно обрабатывает конструкции:
// enum class level: bool в битовом поле
// при чтении выдает "погоду" в значении hight
enum level
{
	low		=0x0,
	hight	=0x1
};

enum set
{
	//uncheck	=0x0,
	on	=0x1
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
			set p0       : 1;
			set p1       : 1;
			set p2       : 1;
			set p3       : 1;
			set p4       : 1;
			set p5       : 1;
			set p6       : 1;
			set p7       : 1;
			set p8       : 1;
			set p9       : 1;
			set p10      : 1;
			set p11      : 1;
			set p12      : 1;
			set p13      : 1;
			set p14      : 1;
			set p15      : 1;
			set p16      : 1;
			set p17      : 1;
			set p18      : 1;
			set p19      : 1;
			set p20      : 1;
			set p21      : 1;
			set p22      : 1;
			set p23      : 1;
			set p24      : 1;
			set p25      : 1;
			set p26      : 1;
			set p27      : 1;
			set p28      : 1;
			set p29      : 1;
			set p30      : 1;
			set p31      : 1;
			set p32       : 1;
			set p33       : 1;
			set p34       : 1;
			set p35       : 1;
			set p36       : 1;
			set p37       : 1;
			set p38       : 1;
			set p39       : 1;
			set p40       : 1;
			set p41       : 1;
			set p42       : 1;
			set p43       : 1;
			set p44       : 1;
			set p45       : 1;
			set p46       : 1;
			set p47       : 1;
			set p48       : 1;
			set p49       : 1;
			set p50       : 1;
			set p51       : 1;
			set p52       : 1;
			set p53       : 1;
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
	union __attribute__((packed, aligned(4))) gplev
	{
		u_int64_t reg;
		struct gplevbits
		{
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
			unsigned               : 10;
		}fld;
		gplev(){reg=0;}
	} const GPLEV;
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
