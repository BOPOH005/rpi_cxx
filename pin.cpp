#include "pin.h"

namespace rpi_cxx {


template<pinN p>
gpio_regs<p> &gpio_regs<p>::instance()
{
	static gpio_regs<p> r;
	return r;
}

#define PIN_GET_FSEL(n) template<>mode gpio_regs<pinN::p##n>::getFSEL()const \
						{return regs.GPFSEL.FSEL##n;}
#define PIN_GET_SET(n) template<>output gpio_regs<pinN::p##n>::getSET()const\
						{return regs.GPSET.SET##n;}
#define PIN_GET_CLR(n) template<>output gpio_regs<pinN::p##n>::getCLR()const\
						{return regs.GPCLR.CLR##n;}
#define PIN_GET_LEV(n) template<>level gpio_regs<pinN::p##n>::getLEV()const\
						{return regs.GPLEV.LEV##n;}
#define PIN_GET_EDS(n) template<>event gpio_regs<pinN::p##n>::getEDS()const\
						{return regs.GPEDS.EDS##n;}
#define PIN_GET_REN(n) template<>status gpio_regs<pinN::p##n>::getREN()const\
						{return regs.GPREN.REN##n;}
#define PIN_GET_FEN(n) template<>status gpio_regs<pinN::p##n>::getFEN()const\
						{return regs.GPFEN.FEN##n;}
#define PIN_GET_HEN(n) template<>status gpio_regs<pinN::p##n>::getHEN()const\
						{return regs.GPHEN.HEN##n;}
#define PIN_GET_LEN(n) template<>status gpio_regs<pinN::p##n>::getLEN()const\
						{return regs.GPLEN.LEN##n;}
#define PIN_GET_AREN(n) template<>status gpio_regs<pinN::p##n>::getAREN()const\
						{return regs.GPAREN.AREN##n;}
#define PIN_GET_AFEN(n) template<>status gpio_regs<pinN::p##n>::getAFEN()const\
						{return regs.GPAFEN.AFEN##n;}
#define PIN_GET_PUDCLK(n) template<>clock gpio_regs<pinN::p##n>::getPUDCLK()const\
						{return regs.GPPUDCLK.PUDCLK##n;}

#define PIN_GET_ALL(n) PIN_GET_FSEL(n) PIN_GET_SET(n) PIN_GET_CLR(n) PIN_GET_LEV(n) PIN_GET_EDS(n) PIN_GET_REN(n) \
		PIN_GET_FEN(n) PIN_GET_HEN(n) PIN_GET_LEN(n) PIN_GET_AREN(n) PIN_GET_AFEN(n) PIN_GET_PUDCLK(n)

#define PIN_SET_FSEL(n) template<> void gpio_regs<pinN::p##n>::setFSEL(mode p) \
						{regs.GPFSEL.FSEL##n=p;}
#define PIN_SET_SET(n) template<> void gpio_regs<pinN::p##n>::setSET(output p)\
						{regs.GPSET.SET##n=p;}
#define PIN_SET_CLR(n) template<> void gpio_regs<pinN::p##n>::setCLR(output p)\
						{regs.GPCLR.CLR##n=p;}
#define PIN_SET_LEV(n) template<> void gpio_regs<pinN::p##n>::setLEV(level p)\
						{regs.GPLEV.LEV##n=p;}
#define PIN_SET_EDS(n) template<> void gpio_regs<pinN::p##n>::setEDS(event p)\
						{regs.GPEDS.EDS##n=p;}
#define PIN_SET_REN(n) template<> void gpio_regs<pinN::p##n>::setREN(status p)\
						{regs.GPREN.REN##n=p;}
#define PIN_SET_FEN(n) template<> void gpio_regs<pinN::p##n>::setFEN(status p)\
						{regs.GPFEN.FEN##n=p;}
#define PIN_SET_HEN(n) template<> void gpio_regs<pinN::p##n>::setHEN(status p)\
						{regs.GPHEN.HEN##n=p;}
#define PIN_SET_LEN(n) template<> void gpio_regs<pinN::p##n>::setLEN(status p)\
						{regs.GPLEN.LEN##n=p;}
#define PIN_SET_AREN(n) template<> void gpio_regs<pinN::p##n>::setAREN(status p)\
						{regs.GPAREN.AREN##n=p;}
#define PIN_SET_AFEN(n) template<> void gpio_regs<pinN::p##n>::setAFEN(status p)\
						{regs.GPAFEN.AFEN##n=p;}
#define PIN_SET_PUDCLK(n) template<> void gpio_regs<pinN::p##n>::setPUDCLK(clock p)\
						{regs.GPPUDCLK.PUDCLK##n=p;}


#define PIN_SET_FSEL(n) template<> void gpio_regs<pinN::p##n>::setFSEL(mode p) \
						{regs.GPFSEL.FSEL##n=p;}
#define PIN_SET_SET(n) template<> void gpio_regs<pinN::p##n>::setSET(output p)\
						{regs.GPSET.SET##n=p;}
#define PIN_SET_CLR(n) template<> void gpio_regs<pinN::p##n>::setCLR(output p)\
						{regs.GPCLR.CLR##n=p;}
#define PIN_SET_LEV(n) template<> void gpio_regs<pinN::p##n>::setLEV(level p)\
						{regs.GPLEV.LEV##n=p;}
#define PIN_SET_EDS(n) template<> void gpio_regs<pinN::p##n>::setEDS(event p)\
						{regs.GPEDS.EDS##n=p;}
#define PIN_SET_REN(n) template<> void gpio_regs<pinN::p##n>::setREN(status p)\
						{regs.GPREN.REN##n=p;}
#define PIN_SET_FEN(n) template<> void gpio_regs<pinN::p##n>::setFEN(status p)\
						{regs.GPFEN.FEN##n=p;}
#define PIN_SET_HEN(n) template<> void gpio_regs<pinN::p##n>::setHEN(status p)\
						{regs.GPHEN.HEN##n=p;}
#define PIN_SET_LEN(n) template<> void gpio_regs<pinN::p##n>::setLEN(status p)\
						{regs.GPLEN.LEN##n=p;}
#define PIN_SET_AREN(n) template<> void gpio_regs<pinN::p##n>::setAREN(status p)\
						{regs.GPAREN.AREN##n=p;}
#define PIN_SET_AFEN(n) template<> void gpio_regs<pinN::p##n>::setAFEN(status p)\
						{regs.GPAFEN.AFEN##n=p;}
#define PIN_SET_PUDCLK(n) template<> void gpio_regs<pinN::p##n>::setPUDCLK(clock p)\
						{regs.GPPUDCLK.PUDCLK##n=p;}

#define PIN_SET_ALL(n) PIN_SET_FSEL(n) PIN_SET_SET(n) PIN_SET_CLR(n) PIN_SET_LEV(n) PIN_SET_EDS(n) PIN_SET_REN(n) \
		PIN_SET_FEN(n) PIN_SET_HEN(n) PIN_SET_LEN(n) PIN_SET_AREN(n) PIN_SET_AFEN(n) PIN_SET_PUDCLK(n)


DEF53(PIN_GET_ALL)
DEF53(PIN_SET_ALL)

#define __ALL_5__

gpio_pin::gpio_pin(pinN p) :pn_(p)
{

}

gpio_pin::gpio_pin(pinN p, mode f) :pn_(p)
{
// #define INIT_GPIO_PIN(n) static auto r##n=gpio_regs<pinN::p##n>::instance();
// 	DEF53(INIT_GPIO_PIN)
	switch(pn_)
	{
#define CASE_SET_FSEL(n) case pinN::p##n : {static auto p##n=gpio_regs<pinN::p##n>::instance(); p##n.setFSEL(f); return;}
	DEF53(CASE_SET_FSEL)
	};
}

void gpio_pin::setmode(mode f)
{
	switch(pn_)
	{
#define CASE_SETMODE(n) case pinN::p##n : {static gpio_regs<pinN::p##n> p##n; p##n.semode(f); return;}
	DEF53(CASE_SET_FSEL)
	};
}

}
