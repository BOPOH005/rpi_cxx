#pragma once
#include "bcm2835.h"
#include<chrono>
#include<thread>

namespace rpi_cxx
{
typedef  uint8_t pinN;

template<pinN p>
class gpio_regs
{
public:
	static gpio_regs<p> &instance();

	mode 	getFSEL()const;
	level	getLEV()const;
	set		getEDS()const;
	set 	getREN()const;
	set 	getFEN()const;
	set 	getHEN()const;
	set 	getLEN()const;
	set 	getAREN()const;
	set 	getAFEN()const;
	set 	getPUDCLK()const;

	void setFSEL(mode);
	void setSET();
	void setCLR();
	void setEDS(set );
	void setREN(set );
	void setFEN(set );
	void setHEN(set );
	void setLEN(set );
	void setAREN(set );
	void setAFEN(set );
	void setPUDCLK(set );

	volatile GPIO	&regs_;

	gpio_regs():regs_(bcm2835::instance().registers()) {};
};   


template<pinN p>  
class gpio
{
public:
					gpio() :_regs(gpio_regs<p>::instance()) {}
					gpio(mode f) :_regs(gpio_regs<p>::instance()) {setmode(f);}
	void			setmode(mode f){if(f!=mode::in)_regs.setFSEL(mode::in);_regs.setFSEL(f);}
	gpio_regs<p>&	regs() { return _regs; }
	void			write(level s) { s==level::hight?_regs.setSET(): _regs.setCLR(); }
	gpio<p>& 		operator=(level s){write(s);return *this;}
					operator level() const { return read(); }
	
	template<class _P=std::chrono::milliseconds>
	gpio<p>& 		operator<<(std::pair<level, _P> s)
					{
						write(s.first);
						std::this_thread::sleep_for(s.second);
						return *this;
					} 		
	level			read()const { return _regs.getLEV(); }
	void			gentone(float freq);
	
	GPIO::gpset& add2reg(GPIO::gpset& r);
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
