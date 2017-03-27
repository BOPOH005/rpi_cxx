#include <limits.h>
#include "../bcm2835.h"
#include "../pin.h"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>
#include <bitset>

using namespace rpi_cxx;

TEST(PIN, TestSpeed)
{
#define DEF23(macro) macro(0) macro(1) macro(2) macro(3) macro(4) macro(5) macro(6) macro(7) \
    macro(8) macro(9) macro(10) macro(11) macro(12) macro(13) macro(14) macro(15)            \
	macro(16) macro(17) macro(18) macro(19) macro(20) macro(21) macro(22) macro(23)

    gpio_pin p[] = {
#define DEF_PIN_N(n) pinN::p##n,
	DEF23(DEF_PIN_N)
	    pinN::p0};

    // #define DEF_PINREGS(n) auto sp##n=gpio_regs<pinN::p##n>::instance();
    // 	DEF53(DEF_PINREGS)

    const size_t count = 100000;

    auto t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < count; ++i)
    {
#define SET_FSEL_1(n) p[n].setmode(mode::out);
	DEF23(SET_FSEL_1)
    }
    auto &regs = bcm2835::instance().registers();
    volatile unsigned *GPFSEL = reinterpret_cast<volatile unsigned *>(&regs.GPFSEL);
    auto t2 = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < count; ++i)
    {
#define SET_FSEL_3(n)                                 \
    {                                                 \
	int reg = n / 10;                             \
	int offset = (n % 10) * 3;                    \
	GPFSEL[reg] &= ~((0b111 & ~0b001) << offset); \
	GPFSEL[reg] |= ((0b111 & 0b000) << offset);   \
    }
	DEF23(SET_FSEL_3)
    }
    auto t4 = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < count; ++i)
    {
#define SET_FSEL_4(n) regs.GPFSEL.fld.p##n = mode::out;
	//sp##n.setFSEL(mode::out);
	DEF23(SET_FSEL_4)
    }
    auto t5 = std::chrono::high_resolution_clock::now();

    auto d1 = (t2 - t1).count();
    auto d2 = (t4 - t2).count();
    //auto d3 = (t4-t3).count();
    auto d4 = (t5 - t4).count();
    std::cout << "GPFSEL.fld.p	=" << d4 << std::endl
	      << "bit manual	=" << d2 << " more " << ((float)(d2 - d4) / (float)d4) * 100 << "%" << std::endl
	      << "switch   	=" << d1 << " more " << ((float)(d1 - d4) / (float)d4) * 100 << "%" << std::endl;
    //		<< "function[] =" << d2 << " more " << ((float)(d2-d4)/(float)d4)*100 << "%" << std::endl;

    ASSERT_TRUE(d4 <= d1 && d4 <= d2);
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

std::ostream &operator<<(std::ostream &os, const level s)
{
    switch (s)
    {
    case level::low:
	return os << "lo";
    case level::hight:
	return os << "hi";
    }
    return os << "err";
}

std::ostream &operator<<(std::ostream &os, const volatile GPIO::gpfsel &s)
{
    return os << "GPFSEL" << std::endl
	      << std::oct << std::setfill('0')
	      << std::setw(64) << std::bitset<64>(s.reg.r2) << std::endl
	      << std::setw(64) << std::bitset<64>(s.reg.r1) << std::endl
	      << std::setw(64) << std::bitset<64>(s.reg.r0) << std::endl

	      << "	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|" << std::endl
	      << "0	|" << s.fld.p0 << "	|" << s.fld.p1 << "	|" << s.fld.p2 << "	|" << s.fld.p3 << "	|" << s.fld.p4 << "	|" << s.fld.p5 << "	|" << s.fld.p6 << "	|" << s.fld.p7 << "	|" << s.fld.p8 << "	|" << s.fld.p9 << "	|" << std::endl
	      << "1	|" << s.fld.p10 << "	|" << s.fld.p11 << "	|" << s.fld.p12 << "	|" << s.fld.p13 << "	|" << s.fld.p14 << "	|" << s.fld.p15 << "	|" << s.fld.p16 << "	|" << s.fld.p17 << "	|" << s.fld.p18 << "	|" << s.fld.p19 << "	|" << std::endl
	      << "2	|" << s.fld.p20 << "	|" << s.fld.p21 << "	|" << s.fld.p22 << "	|" << s.fld.p23 << "	|" << s.fld.p24 << "	|" << s.fld.p25 << "	|" << s.fld.p26 << "	|" << s.fld.p27 << "	|" << s.fld.p28 << "	|" << s.fld.p29 << "	|" << std::endl
	      << "3	|" << s.fld.p30 << "	|" << s.fld.p31 << "	|" << s.fld.p32 << "	|" << s.fld.p33 << "	|" << s.fld.p34 << "	|" << s.fld.p35 << "	|" << s.fld.p36 << "	|" << s.fld.p37 << "	|" << s.fld.p38 << "	|" << s.fld.p39 << "	|" << std::endl
	      << "4	|" << s.fld.p40 << "	|" << s.fld.p41 << "	|" << s.fld.p42 << "	|" << s.fld.p43 << "	|" << s.fld.p44 << "	|" << s.fld.p45 << "	|" << s.fld.p46 << "	|" << s.fld.p47 << "	|" << s.fld.p48 << "	|" << s.fld.p49 << "	|" << std::endl
	      << "5	|" << s.fld.p50 << "	|" << s.fld.p51 << "	|" << s.fld.p52 << "	|" << s.fld.p53 << "	|" << std::endl;
}

std::ostream &operator<<(std::ostream &os, const volatile GPIO::gplev &s)
{
    return os << "GPLEVS" << std::endl
	      << std::oct << std::setfill('0') << std::setw(64) << std::bitset<64>(s.reg) << std::endl
	      << "	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|" << std::endl
	      << "0	|" << s.fld.p0 << "	|" << s.fld.p1 << "	|" << s.fld.p2 << "	|" << s.fld.p3 << "	|" << s.fld.p4 << "	|" << s.fld.p5 << "	|" << s.fld.p6 << "	|" << s.fld.p7 << "	|" << s.fld.p8 << "	|" << s.fld.p9 << "	|" << std::endl
	      << "1	|" << s.fld.p10 << "	|" << s.fld.p11 << "	|" << s.fld.p12 << "	|" << s.fld.p13 << "	|" << s.fld.p14 << "	|" << s.fld.p15 << "	|" << s.fld.p16 << "	|" << s.fld.p17 << "	|" << s.fld.p18 << "	|" << s.fld.p19 << "	|" << std::endl
	      << "2	|" << s.fld.p20 << "	|" << s.fld.p21 << "	|" << s.fld.p22 << "	|" << s.fld.p23 << "	|" << s.fld.p24 << "	|" << s.fld.p25 << "	|" << s.fld.p26 << "	|" << s.fld.p27 << "	|" << s.fld.p28 << "	|" << s.fld.p29 << "	|" << std::endl
	      << "3	|" << s.fld.p30 << "	|" << s.fld.p31 << "	|" << s.fld.p32 << "	|" << s.fld.p33 << "	|" << s.fld.p34 << "	|" << s.fld.p35 << "	|" << s.fld.p36 << "	|" << s.fld.p37 << "	|" << s.fld.p38 << "	|" << s.fld.p39 << "	|" << std::endl
	      << "4	|" << s.fld.p40 << "	|" << s.fld.p41 << "	|" << s.fld.p42 << "	|" << s.fld.p43 << "	|" << s.fld.p44 << "	|" << s.fld.p45 << "	|" << s.fld.p46 << "	|" << s.fld.p47 << "	|" << s.fld.p48 << "	|" << s.fld.p49 << "	|" << std::endl
	      << "5	|" << s.fld.p50 << "	|" << s.fld.p51 << "	|" << s.fld.p52 << "	|" << s.fld.p53 << "	|" << std::endl;
}

TEST(PIN, bcmBlink)
{
    try
    {
	bcm2835 &bcm = bcm2835::instance();
	volatile GPIO &gpio = bcm.registers();
	gpio.GPFSEL.fld.p18 = mode::out;

	for (int i = 3; i > 0; --i)
	{
	    gpio.GPSET.fld.p18 = true;
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_TRUE(gpio.GPLEV.fld.p18 == level::hight);

	    gpio.GPCLR.fld.p18 = true;
	    std::this_thread::sleep_for(std::chrono::milliseconds(100));
	    EXPECT_TRUE(gpio.GPLEV.fld.p18 == level::low);
	}
    }
    catch (std::runtime_error err)
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
	gpio_p<pinN::p18> p(mode::out);

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
    catch (std::runtime_error err)
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
	gpio_pin p(pinN::p18, mode::out);

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
    catch (std::runtime_error err)
    {
	FAIL() << "Ошибка! Проверте запуск с sudo";
    }
    catch (...)
    {
	FAIL() << "Нeизвестное исключение";
    }
}
