#include "pin.h"
#include <cassert>
#include<chrono>
#include<thread>
#include<atomic>
#include<algorithm>
#include <iostream>

using namespace std::this_thread;
using namespace std::chrono;

namespace rpi_cxx {


template<pinN p>
gpio_regs<p> &gpio_regs<p>::instance()
{
	static gpio_regs<p> r;
	return r;
}

#define PIN_GET_FSEL(n) template<>mode gpio_regs<n>::getFSEL()const \
						{return regs_.GPFSEL.fld.p##n;}
#define PIN_GET_LEV(n) template<>level gpio_regs<n>::getLEV()const\
						{return (regs_.GPLEV.fld.p##n?level::hight:level::low);}
#define PIN_GET_EDS(n) template<> bool gpio_regs<n>::getEDS()const\
						{return regs_.GPEDS.fld.p##n;}
#define PIN_GET_REN(n) template<> bool gpio_regs<n>::getREN()const\
						{return regs_.GPREN.fld.p##n;}
#define PIN_GET_FEN(n) template<> bool gpio_regs<n>::getFEN()const\
						{return regs_.GPFEN.fld.p##n;}
#define PIN_GET_HEN(n) template<>bool gpio_regs<n>::getHEN()const\
						{return regs_.GPHEN.fld.p##n;}
#define PIN_GET_LEN(n) template<>bool gpio_regs<n>::getLEN()const\
						{return regs_.GPLEN.fld.p##n;}
#define PIN_GET_AREN(n) template<>bool gpio_regs<n>::getAREN()const\
						{return regs_.GPAREN.fld.p##n;}
#define PIN_GET_AFEN(n) template<>bool gpio_regs<n>::getAFEN()const\
						{return regs_.GPAFEN.fld.p##n;}
#define PIN_GET_PUDCLK(n) template<>bool gpio_regs<n>::getPUDCLK()const\
						{return regs_.GPPUDCLK.fld.p##n;}

#define PIN_GET_ALL(n) PIN_GET_FSEL(n) PIN_GET_LEV(n) PIN_GET_EDS(n) PIN_GET_REN(n) \
		PIN_GET_FEN(n) PIN_GET_HEN(n) PIN_GET_LEN(n) PIN_GET_AREN(n) PIN_GET_AFEN(n) \
		PIN_GET_PUDCLK(n)

#define PIN_SET_FSEL(n) template<> void gpio_regs<n>::setFSEL(mode p) \
						{regs_.GPFSEL.fld.p##n=p;}
#define PIN_SET_SET(n) template<> void gpio_regs<n>::setSET()\
						{GPIO::gpset set; set.fld.p##n=true; regs_.GPSET.reg=set.reg;}
#define PIN_SET_CLR(n) template<> void gpio_regs<n>::setCLR()\
						{GPIO::gpset clr; clr.fld.p##n=true; regs_.GPCLR.reg=clr.reg;}
#define PIN_SET_EDS(n) template<> void gpio_regs<n>::setEDS( bool p)\
						{regs_.GPEDS.fld.p##n=p;}
#define PIN_SET_REN(n) template<> void gpio_regs<n>::setREN( bool p)\
						{regs_.GPREN.fld.p##n=p;}
#define PIN_SET_FEN(n) template<> void gpio_regs<n>::setFEN( bool p)\
						{regs_.GPFEN.fld.p##n=p;}
#define PIN_SET_HEN(n) template<> void gpio_regs<n>::setHEN( bool p)\
						{regs_.GPHEN.fld.p##n=p;}
#define PIN_SET_LEN(n) template<> void gpio_regs<n>::setLEN( bool p)\
						{regs_.GPLEN.fld.p##n=p;}
#define PIN_SET_AREN(n) template<> void gpio_regs<n>::setAREN( bool p)\
						{regs_.GPAREN.fld.p##n=p;}
#define PIN_SET_AFEN(n) template<> void gpio_regs<n>::setAFEN( bool p)\
						{regs_.GPAFEN.fld.p##n=p;}
#define PIN_SET_PUDCLK(n) template<> void gpio_regs<n>::setPUDCLK( bool p)\
						{regs_.GPPUDCLK.fld.p##n=p;}


#define PIN_SET_ALL(n) PIN_SET_FSEL(n) PIN_SET_SET(n) PIN_SET_CLR(n) PIN_SET_EDS(n) PIN_SET_REN(n) \
		PIN_SET_FEN(n) PIN_SET_HEN(n) PIN_SET_LEN(n) PIN_SET_AREN(n) PIN_SET_AFEN(n) PIN_SET_PUDCLK(n)

#define ADD_2_gpset(n) template<> GPIO::gpset& gpio<n>::add2reg(GPIO::gpset& r){r.fld.p##n=true; return r;}

DEF53(PIN_GET_ALL)
DEF53(PIN_SET_ALL)
DEF53(ADD_2_gpset)

#define __ALL_5__

template<pinN n>
void gpio<n>::gentone(float gz)
{
	static std::atomic<unsigned> period;
	const static float max_gz=float(std::micro::den/2);
	if(!period.exchange((unsigned)(gz?(max_gz/std::min(gz, max_gz)):0)))
	{
		std::thread t([this]()
		{
			setmode(out);
			auto l=read();
			while(period.load())
			{
				write(l=(l==level::hight?level::low:level::hight));
				sleep_for(microseconds(period));
			}
			write(level::low);
		});
		t.detach();
	}
	if(!period.load())sleep_for(duration_values<microseconds>::zero());
}



gpio_pin::gpio_pin(pinN p) :pn_(p)
{

}

gpio_pin::gpio_pin(pinN p, mode f) :pn_(p)
{
	setmode(f);
}

void gpio_pin::setmode(mode f)
{
	switch(pn_)
	{
#define CASE_SETMODE(n) case n : {static gpio<n> p##n; p##n.setmode(f); return;}
	DEF53(CASE_SETMODE)
	};
}

void gpio_pin::write(level l)
{
	switch(pn_)
	{
#define CASE_WRITE(n) case n : {static gpio<n> p##n; p##n.write(l); return;}
	DEF53(CASE_WRITE)
	};
}

level gpio_pin::read()const
{
	switch(pn_)
	{
#define CASE_READ(n) case n : {static gpio<n> p##n; return p##n.read();}
	DEF53(CASE_READ)
	};
	assert(0);
	return level::low;
}

void gpio_pin::gentone(float gz)
{
	switch(pn_)
	{
#define CASE_GENTONE(n) case n : {static gpio<n> p##n; p##n.gentone(gz); return;}
	DEF53(CASE_GENTONE)
	};
	assert(0);
}

}
