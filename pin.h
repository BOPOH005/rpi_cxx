#pragma once
#include "bcm2835.h"
#include <cassert>

namespace rpi_cxx
{

enum class pinN
{
	p0,
	p1,
	p2,
	p3,
	p4,
	p5,
	p6,
	p7,
	p8,
	p9,
	p10,
	p11,
	p12,
	p13,
	p14,
	p15,
	p16,
	p17,
	p18,
	p19,
	p20,
	p21,
	p22,
	p23,
	p24,
	p25,
	p26,
	p27,
	p28,
	p29,
	p30,
	p31,
	p32,
	p33,
	p34,
	p35,
	p36,
	p37,
	p38,
	p39,
	p40,
	p41,
	p42,
	p43,
	p44,
	p45,
	p46,
	p47,
	p48,
	p49,
	p50,
	p51,
	p52,
	p53
};

template<pinN p>
class pin
{
public:
	pin():bcm(bcm2835::instance()) {};
	GPIO_REGS::pin_fun 		getFSEL()const;
	GPIO_REGS::output_set	getSET()const;
	GPIO_REGS::output_clr	getCLR()const;
	GPIO_REGS::pin_level	getLEV()const;
	GPIO_REGS::pin_event	getEDS()const;
	GPIO_REGS::red_status	getREN()const;
	GPIO_REGS::fed_status	getFEN()const;
	GPIO_REGS::hd_status	getHEN()const;
	GPIO_REGS::ld_status	getLEN()const;
	GPIO_REGS::ared_status	getAREN()const;
	GPIO_REGS::afed_status	getAFEN()const;
	GPIO_REGS::pud_clock	getPUDCLK()const;

	void setFSEL(GPIO_REGS::pin_fun);
	void setSET(GPIO_REGS::output_set);
	void setCLR(GPIO_REGS::output_clr);
	void setLEV(GPIO_REGS::pin_level);
	void setEDS(GPIO_REGS::pin_event);
	void setREN(GPIO_REGS::red_status);
	void setFEN(GPIO_REGS::fed_status);
	void setHEN(GPIO_REGS::hd_status);
	void setLEN(GPIO_REGS::ld_status);
	void setAREN(GPIO_REGS::ared_status);
	void setAFEN(GPIO_REGS::afed_status);
	void setPUDCLK(GPIO_REGS::pud_clock);
private:
	bcm2835&		bcm;
};

#define PIN_GET_FSEL(n) template<>GPIO_REGS::pin_fun pin<pinN::p##n>::getFSEL()const \
						{return bcm.registers().GPFSEL.FSEL##n;}
#define PIN_GET_SET(n) template<>GPIO_REGS::output_set pin<pinN::p##n>::getSET()const\
						{return bcm.registers().GPSET.SET##n;}
#define PIN_GET_CLR(n) template<>GPIO_REGS::output_clr pin<pinN::p##n>::getCLR()const\
						{return bcm.registers().GPCLR.CLR##n;}
#define PIN_GET_LEV(n) template<>GPIO_REGS::pin_level pin<pinN::p##n>::getLEV()const\
						{return bcm.registers().GPLEV.LEV##n;}
#define PIN_GET_EDS(n) template<>GPIO_REGS::pin_event pin<pinN::p##n>::getEDS()const\
						{return bcm.registers().GPEDS.EDS##n;}
#define PIN_GET_REN(n) template<>GPIO_REGS::red_status pin<pinN::p##n>::getREN()const\
						{return bcm.registers().GPREN.REN##n;}
#define PIN_GET_FEN(n) template<>GPIO_REGS::fed_status pin<pinN::p##n>::getFEN()const\
						{return bcm.registers().GPFEN.FEN##n;}
#define PIN_GET_HEN(n) template<>GPIO_REGS::hd_status pin<pinN::p##n>::getHEN()const\
						{return bcm.registers().GPHEN.HEN##n;}
#define PIN_GET_LEN(n) template<>GPIO_REGS::ld_status pin<pinN::p##n>::getLEN()const\
						{return bcm.registers().GPLEN.LEN##n;}
#define PIN_GET_AREN(n) template<>GPIO_REGS::ared_status pin<pinN::p##n>::getAREN()const\
						{return bcm.registers().GPAREN.AREN##n;}
#define PIN_GET_AFEN(n) template<>GPIO_REGS::afed_status pin<pinN::p##n>::getAFEN()const\
						{return bcm.registers().GPAFEN.AFEN##n;}
#define PIN_GET_PUDCLK(n) template<>GPIO_REGS::pud_clock pin<pinN::p##n>::getPUDCLK()const\
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

#define PIN_SET_FSEL(n) template<> void pin<pinN::p##n>::setFSEL(GPIO_REGS::pin_fun p) \
						{bcm.registers().GPFSEL.FSEL##n=p;}
#define PIN_SET_SET(n) template<> void pin<pinN::p##n>::setSET(GPIO_REGS::output_set p)\
						{bcm.registers().GPSET.SET##n=p;}
#define PIN_SET_CLR(n) template<> void pin<pinN::p##n>::setCLR(GPIO_REGS::output_clr p)\
						{bcm.registers().GPCLR.CLR##n=p;}
#define PIN_SET_LEV(n) template<> void pin<pinN::p##n>::setLEV(GPIO_REGS::pin_level p)\
						{bcm.registers().GPLEV.LEV##n=p;}
#define PIN_SET_EDS(n) template<> void pin<pinN::p##n>::setEDS(GPIO_REGS::pin_event p)\
						{bcm.registers().GPEDS.EDS##n=p;}
#define PIN_SET_REN(n) template<> void pin<pinN::p##n>::setREN(GPIO_REGS::red_status p)\
						{bcm.registers().GPREN.REN##n=p;}
#define PIN_SET_FEN(n) template<> void pin<pinN::p##n>::setFEN(GPIO_REGS::fed_status p)\
						{bcm.registers().GPFEN.FEN##n=p;}
#define PIN_SET_HEN(n) template<> void pin<pinN::p##n>::setHEN(GPIO_REGS::hd_status p)\
						{bcm.registers().GPHEN.HEN##n=p;}
#define PIN_SET_LEN(n) template<> void pin<pinN::p##n>::setLEN(GPIO_REGS::ld_status p)\
						{bcm.registers().GPLEN.LEN##n=p;}
#define PIN_SET_AREN(n) template<> void pin<pinN::p##n>::setAREN(GPIO_REGS::ared_status p)\
						{bcm.registers().GPAREN.AREN##n=p;}
#define PIN_SET_AFEN(n) template<> void pin<pinN::p##n>::setAFEN(GPIO_REGS::afed_status p)\
						{bcm.registers().GPAFEN.AFEN##n=p;}
#define PIN_SET_PUDCLK(n) template<> void pin<pinN::p##n>::setPUDCLK(GPIO_REGS::pud_clock p)\
						{bcm.registers().GPPUDCLK.PUDCLK##n=p;}

#define PIN_SET_ALL(n) PIN_SET_FSEL(n) PIN_SET_SET(n) PIN_SET_CLR(n) PIN_SET_LEV(n) PIN_SET_EDS(n) PIN_SET_REN(n) \
		PIN_SET_FEN(n) PIN_SET_HEN(n) PIN_SET_LEN(n) PIN_SET_AREN(n) PIN_SET_AFEN(n) PIN_SET_PUDCLK(n)

PIN_SET_ALL(0)  PIN_SET_ALL(1)  PIN_SET_ALL(2)  PIN_SET_ALL(3)  PIN_SET_ALL(4)  PIN_SET_ALL(5)  PIN_SET_ALL(6)  PIN_SET_ALL(7)
PIN_SET_ALL(8)  PIN_SET_ALL(9)  PIN_SET_ALL(10) PIN_SET_ALL(11) PIN_SET_ALL(12) PIN_SET_ALL(13) PIN_SET_ALL(14) PIN_SET_ALL(15)
PIN_SET_ALL(16) PIN_SET_ALL(17) PIN_SET_ALL(18) PIN_SET_ALL(19) PIN_SET_ALL(20) PIN_SET_ALL(21) PIN_SET_ALL(22) PIN_SET_ALL(23)
PIN_SET_ALL(24) PIN_SET_ALL(25) PIN_SET_ALL(26) PIN_SET_ALL(27) PIN_SET_ALL(28) PIN_SET_ALL(29) PIN_SET_ALL(30) PIN_SET_ALL(31)
PIN_SET_ALL(32) PIN_SET_ALL(33) PIN_SET_ALL(34) PIN_SET_ALL(35) PIN_SET_ALL(36) PIN_SET_ALL(37) PIN_SET_ALL(38) PIN_SET_ALL(39)
PIN_SET_ALL(40) PIN_SET_ALL(41) PIN_SET_ALL(42) PIN_SET_ALL(43) PIN_SET_ALL(44) PIN_SET_ALL(45) PIN_SET_ALL(46) PIN_SET_ALL(47)
PIN_SET_ALL(48) PIN_SET_ALL(49) PIN_SET_ALL(50) PIN_SET_ALL(51) PIN_SET_ALL(52) PIN_SET_ALL(53)

}
