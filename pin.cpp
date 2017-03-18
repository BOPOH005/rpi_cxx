#include "pin.h"
#include <cassert>

namespace rpi_cxx {


template<pinN p>
gpio_regs<p> &gpio_regs<p>::instance()
{
	static gpio_regs<p> r;
	return r;
}

#define PIN_GET_FSEL(n) template<>mode gpio_regs<pinN::p##n>::getFSEL()const \
						{return regs_.GPFSEL.fld.p##n;}
#define PIN_GET_LEV(n) template<>level gpio_regs<pinN::p##n>::getLEV()const\
						{return regs_.GPLEV.fld.p##n;}
#define PIN_GET_EDS(n) template<>event gpio_regs<pinN::p##n>::getEDS()const\
						{return regs_.GPEDS.fld.p##n;}
#define PIN_GET_REN(n) template<>status gpio_regs<pinN::p##n>::getREN()const\
						{return regs_.GPREN.fld.p##n;}
#define PIN_GET_FEN(n) template<>status gpio_regs<pinN::p##n>::getFEN()const\
						{return regs_.GPFEN.fld.p##n;}
#define PIN_GET_HEN(n) template<>status gpio_regs<pinN::p##n>::getHEN()const\
						{return regs_.GPHEN.fld.p##n;}
#define PIN_GET_LEN(n) template<>status gpio_regs<pinN::p##n>::getLEN()const\
						{return regs_.GPLEN.fld.p##n;}
#define PIN_GET_AREN(n) template<>status gpio_regs<pinN::p##n>::getAREN()const\
						{return regs_.GPAREN.fld.p##n;}
#define PIN_GET_AFEN(n) template<>status gpio_regs<pinN::p##n>::getAFEN()const\
						{return regs_.GPAFEN.fld.p##n;}
#define PIN_GET_PUDCLK(n) template<>clock gpio_regs<pinN::p##n>::getPUDCLK()const\
						{return regs_.GPPUDCLK.fld.p##n;}

#define PIN_GET_ALL(n) PIN_GET_FSEL(n) PIN_GET_LEV(n) PIN_GET_EDS(n) PIN_GET_REN(n) \
		PIN_GET_FEN(n) PIN_GET_HEN(n) PIN_GET_LEN(n) PIN_GET_AREN(n) PIN_GET_AFEN(n) PIN_GET_PUDCLK(n)

#define PIN_SET_FSEL(n) template<> void gpio_regs<pinN::p##n>::setFSEL(mode p) \
						{regs_.GPFSEL.fld.p##n=p;}
#define PIN_SET_SET(n) template<> void gpio_regs<pinN::p##n>::setSET()\
						{regs_.GPSET.fld.p##n=true;}
#define PIN_SET_CLR(n) template<> void gpio_regs<pinN::p##n>::setCLR()\
						{regs_.GPCLR.fld.p##n=true;}
#define PIN_SET_EDS(n) template<> void gpio_regs<pinN::p##n>::setEDS(event p)\
						{regs_.GPEDS.fld.p##n=p;}
#define PIN_SET_REN(n) template<> void gpio_regs<pinN::p##n>::setREN(status p)\
						{regs_.GPREN.fld.p##n=p;}
#define PIN_SET_FEN(n) template<> void gpio_regs<pinN::p##n>::setFEN(status p)\
						{regs_.GPFEN.fld.p##n=p;}
#define PIN_SET_HEN(n) template<> void gpio_regs<pinN::p##n>::setHEN(status p)\
						{regs_.GPHEN.fld.p##n=p;}
#define PIN_SET_LEN(n) template<> void gpio_regs<pinN::p##n>::setLEN(status p)\
						{regs_.GPLEN.fld.p##n=p;}
#define PIN_SET_AREN(n) template<> void gpio_regs<pinN::p##n>::setAREN(status p)\
						{regs_.GPAREN.fld.p##n=p;}
#define PIN_SET_AFEN(n) template<> void gpio_regs<pinN::p##n>::setAFEN(status p)\
						{regs_.GPAFEN.fld.p##n=p;}
#define PIN_SET_PUDCLK(n) template<> void gpio_regs<pinN::p##n>::setPUDCLK(clock p)\
						{regs_.GPPUDCLK.fld.p##n=p;}


#define PIN_SET_ALL(n) PIN_SET_FSEL(n) PIN_SET_SET(n) PIN_SET_CLR(n) PIN_SET_EDS(n) PIN_SET_REN(n) \
		PIN_SET_FEN(n) PIN_SET_HEN(n) PIN_SET_LEN(n) PIN_SET_AREN(n) PIN_SET_AFEN(n) PIN_SET_PUDCLK(n)


DEF53(PIN_GET_ALL)
DEF53(PIN_SET_ALL)

#define __ALL_5__

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
#define CASE_SETMODE(n) case pinN::p##n : {static gpio_p<pinN::p##n> p##n; p##n.setmode(f); return;}
	DEF53(CASE_SETMODE)
	};
}

void gpio_pin::write(level l)
{
	switch(pn_)
	{
#define CASE_WRITE(n) case pinN::p##n : {static gpio_p<pinN::p##n> p##n; p##n.write(l); return;}
	DEF53(CASE_WRITE)
	};
}

level gpio_pin::read()const
{
	switch(pn_)
	{
#define CASE_READ(n) case pinN::p##n : {static gpio_p<pinN::p##n> p##n; return p##n.read();}
	DEF53(CASE_READ)
	};
	assert(0);
	return level::low;
}

}
