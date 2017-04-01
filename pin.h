#pragma once
#include "bcm2835.h"
#include<chrono>
#include<thread>

namespace rpi_cxx
{

enum /*class*/ pinN
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
class gpio_regs
{
public:
	static gpio_regs<p> &instance();

	mode 	getFSEL()const;
	level	getLEV()const;
	event	getEDS()const;
	status	getREN()const;
	status	getFEN()const;
	status	getHEN()const;
	status	getLEN()const;
	status	getAREN()const;
	status	getAFEN()const;
	clock	getPUDCLK()const;

	void setFSEL(mode);
	void setSET();
	void setCLR();
	void setEDS(event);
	void setREN(status);
	void setFEN(status);
	void setHEN(status);
	void setLEN(status);
	void setAREN(status);
	void setAFEN(status);
	void setPUDCLK(clock);

	volatile GPIO	&regs_;

	gpio_regs():regs_(bcm2835::instance().registers()) {};
};   


template<pinN p>  
class gpio_p
{
public:
					gpio_p() :_regs(gpio_regs<p>::instance()) {}
					gpio_p(mode f) :_regs(gpio_regs<p>::instance()) {setmode(f);}
	void			setmode(mode f){_regs.setFSEL(f);}
	gpio_regs<p>&	regs() { return _regs; }
	void			write(level s) { s==level::hight?_regs.setSET(): _regs.setCLR(); }
	gpio_p<p>& 		operator=(level s){write(s);return *this;}
					operator level() const { return read(); }
	
	template<class _P=std::chrono::milliseconds>
	gpio_p<p>& 		operator<<(std::pair<level, _P> s)
					{
						write(s.first);
						std::this_thread::sleep_for(s.second);
						return *this;
					} 		
	level			read()const { return _regs.getLEV(); }
	void			gentone(float freq);
	
	GPIO::gppudclk& add2reg(GPIO::gppudclk& r);
	GPIO::gpsetclr& add2reg(GPIO::gpsetclr& r);
private:
	gpio_regs<p> &_regs;
};



#define DEF53(macro) 	macro(0)  macro(1)  macro(2)  macro(3)  macro(4)  macro(5)  macro(6)  macro(7) \
						macro(8)  macro(9)  macro(10) macro(11) macro(12) macro(13) macro(14) macro(15)\
						macro(16) macro(17) macro(18) macro(19) macro(20) macro(21) macro(22) macro(23)\
						macro(24) macro(25) macro(26) macro(27) macro(28) macro(29) macro(30) macro(31)\
						macro(32) macro(33) macro(34) macro(35) macro(36) macro(37) macro(38) macro(39)\
						macro(40) macro(41) macro(42) macro(43) macro(44) macro(45) macro(46) macro(47)\
						macro(48) macro(49) macro(50) macro(51) macro(52) macro(53)

#define __CLOSE_DEF__

class gpio_pin
{
public:
					gpio_pin(pinN p);
					gpio_pin(pinN p, mode);
	void			setmode(mode);
	void			write(level s);
	level			read()const;
	void			gentone(float freq);
private:
	const pinN	pn_;
};
}
