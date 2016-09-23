#include "pin.h"

namespace rpi_cxx {


template<pinN p>
pinregs<p> &pinregs<p>::instance()
{
	static pinregs<p> r;
	return r;
}

#define PIN_GET_FSEL(n) template<>GPIO_REGS::pin_fun pinregs<pinN::p##n>::getFSEL()const \
						{return regs.GPFSEL.FSEL##n;}
#define PIN_GET_SET(n) template<>GPIO_REGS::output_set pinregs<pinN::p##n>::getSET()const\
						{return regs.GPSET.SET##n;}
#define PIN_GET_CLR(n) template<>GPIO_REGS::output_clr pinregs<pinN::p##n>::getCLR()const\
						{return regs.GPCLR.CLR##n;}
#define PIN_GET_LEV(n) template<>GPIO_REGS::pin_level pinregs<pinN::p##n>::getLEV()const\
						{return regs.GPLEV.LEV##n;}
#define PIN_GET_EDS(n) template<>GPIO_REGS::pin_event pinregs<pinN::p##n>::getEDS()const\
						{return regs.GPEDS.EDS##n;}
#define PIN_GET_REN(n) template<>GPIO_REGS::red_status pinregs<pinN::p##n>::getREN()const\
						{return regs.GPREN.REN##n;}
#define PIN_GET_FEN(n) template<>GPIO_REGS::fed_status pinregs<pinN::p##n>::getFEN()const\
						{return regs.GPFEN.FEN##n;}
#define PIN_GET_HEN(n) template<>GPIO_REGS::hd_status pinregs<pinN::p##n>::getHEN()const\
						{return regs.GPHEN.HEN##n;}
#define PIN_GET_LEN(n) template<>GPIO_REGS::ld_status pinregs<pinN::p##n>::getLEN()const\
						{return regs.GPLEN.LEN##n;}
#define PIN_GET_AREN(n) template<>GPIO_REGS::ared_status pinregs<pinN::p##n>::getAREN()const\
						{return regs.GPAREN.AREN##n;}
#define PIN_GET_AFEN(n) template<>GPIO_REGS::afed_status pinregs<pinN::p##n>::getAFEN()const\
						{return regs.GPAFEN.AFEN##n;}
#define PIN_GET_PUDCLK(n) template<>GPIO_REGS::pud_clock pinregs<pinN::p##n>::getPUDCLK()const\
						{return regs.GPPUDCLK.PUDCLK##n;}

#define PIN_GET_ALL(n) PIN_GET_FSEL(n) PIN_GET_SET(n) PIN_GET_CLR(n) PIN_GET_LEV(n) PIN_GET_EDS(n) PIN_GET_REN(n) \
		PIN_GET_FEN(n) PIN_GET_HEN(n) PIN_GET_LEN(n) PIN_GET_AREN(n) PIN_GET_AFEN(n) PIN_GET_PUDCLK(n)

#define PIN_SET_FSEL(n) template<> void pinregs<pinN::p##n>::setFSEL(GPIO_REGS::pin_fun p) \
						{regs.GPFSEL.FSEL##n=p;}
#define PIN_SET_SET(n) template<> void pinregs<pinN::p##n>::setSET(GPIO_REGS::output_set p)\
						{regs.GPSET.SET##n=p;}
#define PIN_SET_CLR(n) template<> void pinregs<pinN::p##n>::setCLR(GPIO_REGS::output_clr p)\
						{regs.GPCLR.CLR##n=p;}
#define PIN_SET_LEV(n) template<> void pinregs<pinN::p##n>::setLEV(GPIO_REGS::pin_level p)\
						{regs.GPLEV.LEV##n=p;}
#define PIN_SET_EDS(n) template<> void pinregs<pinN::p##n>::setEDS(GPIO_REGS::pin_event p)\
						{regs.GPEDS.EDS##n=p;}
#define PIN_SET_REN(n) template<> void pinregs<pinN::p##n>::setREN(GPIO_REGS::red_status p)\
						{regs.GPREN.REN##n=p;}
#define PIN_SET_FEN(n) template<> void pinregs<pinN::p##n>::setFEN(GPIO_REGS::fed_status p)\
						{regs.GPFEN.FEN##n=p;}
#define PIN_SET_HEN(n) template<> void pinregs<pinN::p##n>::setHEN(GPIO_REGS::hd_status p)\
						{regs.GPHEN.HEN##n=p;}
#define PIN_SET_LEN(n) template<> void pinregs<pinN::p##n>::setLEN(GPIO_REGS::ld_status p)\
						{regs.GPLEN.LEN##n=p;}
#define PIN_SET_AREN(n) template<> void pinregs<pinN::p##n>::setAREN(GPIO_REGS::ared_status p)\
						{regs.GPAREN.AREN##n=p;}
#define PIN_SET_AFEN(n) template<> void pinregs<pinN::p##n>::setAFEN(GPIO_REGS::afed_status p)\
						{regs.GPAFEN.AFEN##n=p;}
#define PIN_SET_PUDCLK(n) template<> void pinregs<pinN::p##n>::setPUDCLK(GPIO_REGS::pud_clock p)\
						{regs.GPPUDCLK.PUDCLK##n=p;}


#define PIN_SET_FSEL(n) template<> void pinregs<pinN::p##n>::setFSEL(GPIO_REGS::pin_fun p) \
						{regs.GPFSEL.FSEL##n=p;}
#define PIN_SET_SET(n) template<> void pinregs<pinN::p##n>::setSET(GPIO_REGS::output_set p)\
						{regs.GPSET.SET##n=p;}
#define PIN_SET_CLR(n) template<> void pinregs<pinN::p##n>::setCLR(GPIO_REGS::output_clr p)\
						{regs.GPCLR.CLR##n=p;}
#define PIN_SET_LEV(n) template<> void pinregs<pinN::p##n>::setLEV(GPIO_REGS::pin_level p)\
						{regs.GPLEV.LEV##n=p;}
#define PIN_SET_EDS(n) template<> void pinregs<pinN::p##n>::setEDS(GPIO_REGS::pin_event p)\
						{regs.GPEDS.EDS##n=p;}
#define PIN_SET_REN(n) template<> void pinregs<pinN::p##n>::setREN(GPIO_REGS::red_status p)\
						{regs.GPREN.REN##n=p;}
#define PIN_SET_FEN(n) template<> void pinregs<pinN::p##n>::setFEN(GPIO_REGS::fed_status p)\
						{regs.GPFEN.FEN##n=p;}
#define PIN_SET_HEN(n) template<> void pinregs<pinN::p##n>::setHEN(GPIO_REGS::hd_status p)\
						{regs.GPHEN.HEN##n=p;}
#define PIN_SET_LEN(n) template<> void pinregs<pinN::p##n>::setLEN(GPIO_REGS::ld_status p)\
						{regs.GPLEN.LEN##n=p;}
#define PIN_SET_AREN(n) template<> void pinregs<pinN::p##n>::setAREN(GPIO_REGS::ared_status p)\
						{regs.GPAREN.AREN##n=p;}
#define PIN_SET_AFEN(n) template<> void pinregs<pinN::p##n>::setAFEN(GPIO_REGS::afed_status p)\
						{regs.GPAFEN.AFEN##n=p;}
#define PIN_SET_PUDCLK(n) template<> void pinregs<pinN::p##n>::setPUDCLK(GPIO_REGS::pud_clock p)\
						{regs.GPPUDCLK.PUDCLK##n=p;}

#define PIN_SET_ALL(n) PIN_SET_FSEL(n) PIN_SET_SET(n) PIN_SET_CLR(n) PIN_SET_LEV(n) PIN_SET_EDS(n) PIN_SET_REN(n) \
		PIN_SET_FEN(n) PIN_SET_HEN(n) PIN_SET_LEN(n) PIN_SET_AREN(n) PIN_SET_AFEN(n) PIN_SET_PUDCLK(n)


DEF53(PIN_GET_ALL)
DEF53(PIN_SET_ALL)


pin::pin(pinN p) :pn(p),
	foo{
#define INST_SET_FSEL(n) [](GPIO_REGS::pin_fun f) {static auto pn=pinregs<pinN::p##n>::instance(); pn.setFSEL(f); return;},
	DEF53(INST_SET_FSEL)
	[](GPIO_REGS::pin_fun f){}}
{}

void pin::setFSEL_1(GPIO_REGS::pin_fun f)
{
	switch(pn)
	{
#define CASE_SET_FSEL(n) case pinN::p##n : {static auto pn=pinregs<pinN::p##n>::instance(); pn.setFSEL(f); return;}
	DEF53(CASE_SET_FSEL)
	};
}
void pin::setFSEL_2(GPIO_REGS::pin_fun f)
{
	foo[static_cast<size_t>(pn)](f);
}
void pin::setFSEL_3(GPIO_REGS::pin_fun f)
{
	static int* const GPFSEL=(int*)static_cast<void*>(&bcm2835::instance().registers());

	int pin=static_cast<int>(pn);
	int function=static_cast<int>(f);
	int reg      =  pin/10;
	int offset   = (pin%10)*3;
	GPFSEL[reg] &= ~((0b111 & ~function) << offset);
	GPFSEL[reg] |=  ((0b111 &  function) << offset);
}

}
