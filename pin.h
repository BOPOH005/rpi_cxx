#pragma once
#include "bcm2835.h"
#include <cassert>

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
//struct pin_regs
//{
//	GPIO_REGS::pin_fun		&FSEL;
//	GPIO_REGS::output_set	&SET;
//	GPIO_REGS::output_clr	&CLR;
//	GPIO_REGS::pin_level	&LEV;
//	GPIO_REGS::pin_event	&EDS;
//	GPIO_REGS::red_status	&REN;
//	GPIO_REGS::fed_status	&FEN;
//	GPIO_REGS::hd_status	&HEN;
//	GPIO_REGS::ld_status	&LEN;
//	GPIO_REGS::ared_status	&AREN;
//	GPIO_REGS::afed_status	&AFEN;
//	GPIO_REGS::pud_clock	&PUDCLK;
//};

template<pinNum p>
class pin
{
public:
	pin():bcm(bcm2835::instance()) {};
	GPIO_REGS::pin_fun 		getFSEL();
	GPIO_REGS::output_set	getSET();
	GPIO_REGS::output_clr	getCLR();
	GPIO_REGS::pin_level	getLEV();
	GPIO_REGS::pin_event	getEDS();
	GPIO_REGS::red_status	getREN();
	GPIO_REGS::fed_status	getFEN();
	GPIO_REGS::hd_status	getHEN();
	GPIO_REGS::ld_status	getLEN();
	GPIO_REGS::ared_status	getAREN();
	GPIO_REGS::afed_status	getAFEN();
	GPIO_REGS::pud_clock	getPUDCLK();

private:
	bcm2835&		bcm;
};

#define PIN_GET_FSEL(n) template<>GPIO_REGS::pin_fun pin<pinNum::pin##n>::getFSEL() \
						{return bcm.registers().GPFSEL.FSEL##n;}
#define PIN_GET_SET(n) template<>GPIO_REGS::output_set pin<pinNum::pin##n>::getSET() \
						{return bcm.registers().GPSET.SET##n;}
#define PIN_GET_CLR(n) template<>GPIO_REGS::output_clr pin<pinNum::pin##n>::getCLR() \
						{return bcm.registers().GPCLR.CLR##n;}
#define PIN_GET_LEV(n) template<>GPIO_REGS::pin_level pin<pinNum::pin##n>::getLEV() \
						{return bcm.registers().GPLEV.LEV##n;}
#define PIN_GET_EDS(n) template<>GPIO_REGS::pin_event pin<pinNum::pin##n>::getEDS() \
						{return bcm.registers().GPEDS.EDS##n;}
#define PIN_GET_REN(n) template<>GPIO_REGS::red_status pin<pinNum::pin##n>::getREN() \
						{return bcm.registers().GPREN.REN##n;}
#define PIN_GET_FEN(n) template<>GPIO_REGS::fed_status pin<pinNum::pin##n>::getFEN() \
						{return bcm.registers().GPFEN.FEN##n;}
#define PIN_GET_HEN(n) template<>GPIO_REGS::hd_status pin<pinNum::pin##n>::getHEN() \
						{return bcm.registers().GPHEN.HEN##n;}
#define PIN_GET_LEN(n) template<>GPIO_REGS::ld_status pin<pinNum::pin##n>::getLEN() \
						{return bcm.registers().GPLEN.LEN##n;}
#define PIN_GET_AREN(n) template<>GPIO_REGS::ared_status pin<pinNum::pin##n>::getAREN() \
						{return bcm.registers().GPAREN.AREN##n;}
#define PIN_GET_AFEN(n) template<>GPIO_REGS::afed_status pin<pinNum::pin##n>::getAFEN() \
						{return bcm.registers().GPAFEN.AFEN##n;}
#define PIN_GET_PUDCLK(n) template<>GPIO_REGS::pud_clock pin<pinNum::pin##n>::getPUDCLK() \
						{return bcm.registers().GPPUDCLK.PUDCLK##n;}

#define PIN_GET_ALL(n) PIN_GET_FSEL(n) PIN_GET_SET(n) PIN_GET_CLR(n) PIN_GET_LEV(n) PIN_GET_EDS(n) PIN_GET_REN(n) \
		PIN_GET_FEN(n) PIN_GET_HEN(n) PIN_GET_LEN(n) PIN_GET_AREN(n) PIN_GET_AFEN(n) PIN_GET_PUDCLK(n)

PIN_GET_ALL(0)  PIN_GET_ALL(1)  PIN_GET_ALL(2)  PIN_GET_ALL(3)  PIN_GET_ALL(4)  PIN_GET_ALL(5)  PIN_GET_ALL(6)  PIN_GET_ALL(7)
PIN_GET_ALL(8)  PIN_GET_ALL(9)  PIN_GET_ALL(10) PIN_GET_ALL(11) PIN_GET_ALL(12) PIN_GET_ALL(13) PIN_GET_ALL(14) PIN_GET_ALL(15)
PIN_GET_ALL(16) PIN_GET_ALL(17) PIN_GET_ALL(18) PIN_GET_ALL(19) PIN_GET_ALL(20) PIN_GET_ALL(21) PIN_GET_ALL(22) PIN_GET_ALL(23)
PIN_GET_ALL(24) PIN_GET_ALL(25) PIN_GET_ALL(26) PIN_GET_ALL(27) PIN_GET_ALL(28) PIN_GET_ALL(29) PIN_GET_ALL(30) PIN_GET_ALL(31)
PIN_GET_ALL(32) PIN_GET_ALL(33) PIN_GET_ALL(34) PIN_GET_ALL(35) PIN_GET_ALL(36) PIN_GET_ALL(37) PIN_GET_ALL(38) PIN_GET_ALL(39)
PIN_GET_ALL(40) PIN_GET_ALL(41) PIN_GET_ALL(42) PIN_GET_ALL(43) PIN_GET_ALL(44) PIN_GET_ALL(45) PIN_GET_ALL(46) PIN_GET_ALL(47)
PIN_GET_ALL(48) PIN_GET_ALL(49) PIN_GET_ALL(50) PIN_GET_ALL(51) PIN_GET_ALL(52) PIN_GET_ALL(53)
}
