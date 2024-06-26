#include <limits.h>
#include "../bcm2835.h"
#include "../pin.h"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>
#include <bitset>

using namespace rpi_cxx;

void setmode(int n, volatile unsigned *GPFSEL, bool out)
{
	const int reg = n / 10;                             
	const int offset = (n % 10) * 3;               
	GPFSEL[reg] &= ~(0b111<<offset);
	if(out)GPFSEL[reg] |= (0b001<<offset);                                          
}

TEST(PIN, TestSpeed)
{
#define DEF31(macro) macro(0) macro(1) macro(2) macro(3) macro(4) macro(5) macro(6) macro(7) \
    macro(8) macro(9) macro(10) macro(11) macro(12) macro(13) macro(14) macro(15)            \
	macro(16) macro(17) macro(18) macro(19) macro(20) macro(21) macro(22) macro(23)      \
	    macro(24) macro(25) macro(26) macro(27) macro(28) macro(29) macro(30) macro(31)

    gpio_pin p[] = {
#define DEF_PIN_N(n) n,
	DEF31(DEF_PIN_N) 0};

#define DEF_PINREGS(n) gpio<n> sp##n;
    DEF31(DEF_PINREGS)

    const size_t count = 100000;

    auto t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i)
    {
#define SET_FSEL_1(n) p[n].setmode(mode::out);
	DEF31(SET_FSEL_1)
    }
	auto t1_1 = std::chrono::high_resolution_clock::now();
	
    auto &regs = bcm2835::instance().registers<GPIO>();
    volatile unsigned *GPFSEL = reinterpret_cast<volatile unsigned *>(&regs.GPFSEL);

    auto t2 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i)
    {
#define SET_FSEL_3(n) setmode(n, GPFSEL, true);
    
	DEF31(SET_FSEL_3)
    }
	    
	auto t4 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i)
    {
#define SET_FSEL_4(n) sp##n.setmode(mode::out);

	DEF31(SET_FSEL_4)
    }
    auto t5 = std::chrono::high_resolution_clock::now();

    auto d1 = (t1_1 - t1).count();
    auto d2 = (t4 - t2).count();
    auto d4 = (t5 - t4).count();
    std::cout 	<< "gpio<>		=" << d4 << std::endl
	    		<< "bit manual	=" << d2 << " more " << ((float)(d2 - d4) / (float)d4) * 100 << "%" << std::endl
	      		<< "switch   	=" << d1 << " more " << ((float)(d1 - d4) / (float)d4) * 100 << "%" << std::endl;

    ASSERT_GT( (float)(d1-d4)/(float)d4 * 100 , -0.1);
}

std::ostream &operator<<(std::ostream &os, const mode s)
{
    os << std::hex << (int)s << ":";
    switch (s)
    {
    case mode::in:
	return os << "in";
    case mode::out:
	return os << "out";
    case mode::fun0:
	return os << "alt0";
    case mode::fun1:
	return os << "alt1";
    case mode::fun2:
	return os << "alt2";
    case mode::fun3:
	return os << "alt3";
    case mode::fun4:
	return os << "alt4";
    case mode::fun5:
	return os << "alt5";
    }
    return os << "err";
}

// std::ostream &operator<<(std::ostream &os, const volatile GPIO::gpfset &s)
// {
//     return os
// 	   << std::oct << std::setfill('0') << std::setw(64) << std::bitset<64>(s.reg) << std::endl
// 	   << " |0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|" << std::endl
// 	   << "0|" << s.fld.p0 << "	|" << s.fld.p1 << "	|" << s.fld.p2 << "	|" << s.fld.p3 << "	|" << s.fld.p4 << "	|" << s.fld.p5 << "	|" << s.fld.p6 << "	|" << s.fld.p7 << "	|" << s.fld.p8 << "	|" << s.fld.p9 << "	|" << std::endl
// 	   << "1|" << s.fld.p10 << "	|" << s.fld.p11 << "	|" << s.fld.p12 << "	|" << s.fld.p13 << "	|" << s.fld.p14 << "	|" << s.fld.p15 << "	|" << s.fld.p16 << "	|" << s.fld.p17 << "	|" << s.fld.p18 << "	|" << s.fld.p19 << "	|" << std::endl
// 	   << "2|" << s.fld.p20 << "	|" << s.fld.p21 << "	|" << s.fld.p22 << "	|" << s.fld.p23 << "	|" << s.fld.p24 << "	|" << s.fld.p25 << "	|" << s.fld.p26 << "	|" << s.fld.p27 << "	|" << s.fld.p28 << "	|" << s.fld.p29 << "	|" << std::endl
// 	   << "3|" << s.fld.p30 << "	|" << s.fld.p31 << "	|" << s.fld.p32 << "	|" << s.fld.p33 << "	|" << s.fld.p34 << "	|" << s.fld.p35 << "	|" << s.fld.p36 << "	|" << s.fld.p37 << "	|" << s.fld.p38 << "	|" << s.fld.p39 << "	|" << std::endl
// 	   << "4|" << s.fld.p40 << "	|" << s.fld.p41 << "	|" << s.fld.p42 << "	|" << s.fld.p43 << "	|" << s.fld.p44 << "	|" << s.fld.p45 << "	|" << s.fld.p46 << "	|" << s.fld.p47 << "	|" << s.fld.p48 << "	|" << s.fld.p49 << "	|" << std::endl
// 	   << "5|" << s.fld.p50 << "	|" << s.fld.p51 << "	|" << s.fld.p52 << "	|" << s.fld.p53 << "	|" << std::endl;
// }

TEST(PIN, testMode)
{
    try
    {
	gpio<18> pin(mode::in);
	std::cout << pin.getmode() << std::endl;
	EXPECT_TRUE(pin.getmode() == mode::in);
	pin.setmode(mode::out);
	std::cout << pin.getmode() << std::endl;
	EXPECT_TRUE(pin.getmode() == mode::out);
	pin.setmode(mode::in);
	std::cout << pin.getmode() << std::endl;
	EXPECT_TRUE(pin.getmode() == mode::in);
    }
    catch (const std::runtime_error &err)
    {
	FAIL() << "Ошибка! Проверте запуск с sudo";
    }
    catch (...)
    {
	FAIL() << "Нeизвестное исключение";
    }
}

TEST(PIN, bitBlink)
{
    try
    {
	bcm2835 &bcm = bcm2835::instance();
	volatile GPIO &gpio = bcm.registers<GPIO>();
	volatile u_int32_t *GPFSEL = reinterpret_cast<volatile u_int32_t *>(&gpio.GPFSEL.fld);
	volatile u_int32_t *GPSET = reinterpret_cast<volatile u_int32_t *>(&gpio.GPSET.fld);
	volatile u_int32_t *GPCLR = reinterpret_cast<volatile u_int32_t *>(&gpio.GPCLR.fld);
	volatile const u_int32_t *GPLEV = reinterpret_cast<volatile const u_int32_t *>(&gpio.GPLEV);
	const int pin = 18;
	const int reg3 = pin / 10;
	const int offset3 = (pin % 10) * 3;
	const int reg = pin / 31;
	const int offset = (pin % 31);
	GPFSEL[reg3] &= ~(0b111 << offset3);
	GPFSEL[reg3] |= (0b001 << offset3);

	for (size_t i = 0; i < 3; ++i)
	{
	    GPSET[reg] = (1 << offset);
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_TRUE(GPLEV[reg] & (1 << offset));
	    GPCLR[reg] = (1 << offset);
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_FALSE(GPLEV[reg] & (1 << offset));
	}
    }
    catch (const std::runtime_error &err)
    {
	FAIL() << "Ошибка! Проверте запуск с sudo";
    }
    catch (...)
    {
	FAIL() << "Нeизвестное исключение";
    }
}

TEST(PIN, bcmBlink)
{
    try
    {
	bcm2835 &bcm = bcm2835::instance();
	volatile GPIO &gpio = bcm.registers<GPIO>();

	gpio.GPFSEL.fld.p18 = mode::in;
	gpio.GPFSEL.fld.p18 = mode::out;
	for (int i = 3; i > 0; --i)
	{
	    GPIO::gpset regs;
	    regs.fld.p18 = set::on;
	    gpio.GPSET.reg = regs.reg;
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_TRUE(gpio.GPLEV.fld.p18 == level::hight);
	    gpio.GPCLR.reg = regs.reg;
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_TRUE(gpio.GPLEV.fld.p18 == level::low);
	}
    }
    catch (const std::runtime_error &err)
    {
	FAIL() << "Ошибка! Проверте запуск с sudo";
    }
    catch (...)
    {
	FAIL() << "Нeизвестное исключение";
    }
}

TEST(PIN, Blink)
{
    try
    {
	gpio<18> p(mode::out);

	for (int i = 3; i > 0; --i)
	{
	    p = level::hight;
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_TRUE(p == level::hight);
	    p = level::low;
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_TRUE(p == level::low);
	}
    }
    catch (const std::runtime_error &err)
    {
	FAIL() << "Ошибка! Проверте запуск с sudo";
    }
    catch (...)
    {
	FAIL() << "Нeизвестное исключение";
    }
}

TEST(PIN, pinBlink)
{
    try
    {
	gpio_pin p(18, mode::out);

	for (int i = 3; i > 0; --i)
	{
	    p.write(level::hight);
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_TRUE(p.read() == level::hight);
	    p.write(level::low);
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_TRUE(p.read() == level::low);
	}
    }
    catch (const std::runtime_error &err)
    {
	FAIL() << "Ошибка! Проверте запуск с sudo";
    }
    catch (...)
    {
	FAIL() << "Нeизвестное исключение";
    }
}

