#pragma once
#include "bcm2835.h"

namespace rpi_cxx
{

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
struct pin_regs
{
	GPIO_REGS::pin_fun		&FSEL;	
	GPIO_REGS::output_set	&SET;
	GPIO_REGS::output_clr	&CLR;
	GPIO_REGS::pin_level	&LEV;
	GPIO_REGS::pin_event	&EDS;
	GPIO_REGS::red_status	&REN;
	GPIO_REGS::fed_status	&FEN;
	GPIO_REGS::hd_status	&HEN;
	GPIO_REGS::ld_status	&LEN;
	GPIO_REGS::ared_status	&AREN;
	GPIO_REGS::afed_status	&AFEN;
	GPIO_REGS::pud_clock	&PUDCLK;
};

class pin
{
public:
	pin(pinNum p) :pin_num(p),bcm(bcm2835::instance()) {};
	pin_regs& registers();
private:
	const pinNum	pin_num;
	bcm2835&		bcm;
};

}