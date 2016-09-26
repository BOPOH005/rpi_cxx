#pragma once
#include "bcm2835.h"
//#include <cassert>

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
class pinregs
{
public:
	static pinregs<p> &instance();

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
	//bcm2835&		bcm;
	GPIO_REGS	&regs;

	pinregs():regs(bcm2835::instance().registers()) {};
};

template<pinN p>
class gpio_p
{
public:
							gpio_p() :_regs(pinregs<p>::instance()) {};
							gpio_p(GPIO_REGS::pin_fun f) :_regs(pinregs<p>::instance()) {mode(f)};
	pinregs<p>&				regs() { return _regs; }
	void					mode(GPIO_REGS::pin_fun f) {_regs.setFSEL(f);}
	void					write(GPIO_REGS::pin_level s) { s==GPIO_REGS::pin_level::hight?_regs.setSET(GPIO_REGS::output_set::setOut): _regs.setCLR(GPIO_REGS::output_clr::clearOut); }
	GPIO_REGS::pin_level	read()const { return _regs.getLEV(); }
private:
	static pinregs<p> &_regs;
};

#define DEF53(macro) 	macro(0)  macro(1)  macro(2)  macro(3)  macro(4)  macro(5)  macro(6)  macro(7) \
						macro(8)  macro(9)  macro(10) macro(11) macro(12) macro(13) macro(14) macro(15)\
						macro(16) macro(17) macro(18) macro(19) macro(20) macro(21) macro(22) macro(23)\
						macro(24) macro(25) macro(26) macro(27) macro(28) macro(29) macro(30) macro(31)\
						macro(32) macro(33) macro(34) macro(35) macro(36) macro(37) macro(38) macro(39)\
						macro(40) macro(41) macro(42) macro(43) macro(44) macro(45) macro(46) macro(47)\
						macro(48) macro(49) macro(50) macro(51) macro(52) macro(53)


class pin
{
public:
	pin(pinN p);
	void setFSEL(GPIO_REGS::pin_fun f);

private:
	const pinN	pn;
};

}
