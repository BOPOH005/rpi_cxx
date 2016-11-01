#include <limits.h>
#include "../bcm2835.h"
#include "../pin.h"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>
#include <bitset>


using namespace rpi_cxx;
// template<class T>
// void* TestAdressGPIO(T m)
// {
// 	GPIO::fields r = {};
// 	return (char*)0x7E200000+(size_t)(reinterpret_cast<char*>(&(r.*m)) - reinterpret_cast<char*>(&r));
// }


TEST(GPIO, TestSizeofGPIO)
{
	ASSERT_EQ(size_t(0x7E2000B0 - 0x7E200000), sizeof(GPIO));
}

TEST(GPIO,TestGPFSEL)
{
	ASSERT_EQ(offsetof(GPIO, GPFSEL), 0x7E200000-0x7E200000);
	ASSERT_EQ(offsetof(GPIO::gpfsel, fld), 0x7E200000-0x7E200000);
	// ASSERT_EQ((std::size_t) &(((GPIO::gpfsel*)0)->reg.r0)), 0x7E200000-0x7E200000);
	// ASSERT_EQ((std::size_t) &(((GPIO::gpfsel*)0)->reg.r1)), 0x7E200008-0x7E200000);
	// ASSERT_EQ((std::size_t) &(((GPIO::gpfsel*)0)->reg.r1)), 0x7E200010-0x7E200000);

	// ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPFSEL),(void*)0x7E200000);
	// ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPFSEL1),(void*)0x7E200000);
	// ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPFSEL2),(void*)0x7E200008);
	// ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPFSEL3),(void*)0x7E200010);
}
TEST(GPIO,TestGPSET)
{
	ASSERT_EQ(offsetof(GPIO, GPSET), 0x7E20001C-0x7E200000);
	
	// ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPSET),(void*)0x7E20001C);
	// ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPSET),(void*)0x7E20001C);
}
TEST(GPIO,TestGPCLR)
{
	ASSERT_EQ(offsetof(GPIO,GPCLR),0x7E200028-0x7E200000);
}
TEST(GPIO,TestGPLEV)
{
	ASSERT_EQ(offsetof(GPIO,GPLEV),0x7E200034-0x7E200000);
}
TEST(GPIO,TestGPEDS)
{
	ASSERT_EQ(offsetof(GPIO,GPEDS),0x7E200040-0x7E200000);
}
TEST(GPIO,TestGPREN)
{
	ASSERT_EQ(offsetof(GPIO,GPREN),0x7E20004C-0x7E200000);
}
TEST(GPIO,TestGPFEN)
{
	ASSERT_EQ(offsetof(GPIO,GPFEN),0x7E200058-0x7E200000);
}
TEST(GPIO,TestGPHEN)
{
	ASSERT_EQ(offsetof(GPIO,GPHEN),0x7E200064-0x7E200000);
}
TEST(GPIO,TestGPLEN)
{
	ASSERT_EQ(offsetof(GPIO,GPLEN),0x7E200070-0x7E200000);
}
TEST(GPIO,TestGPAREN)
{
	ASSERT_EQ(offsetof(GPIO,GPAREN),0x7E20007C-0x7E200000);
}
TEST(GPIO,TestGPAFEN)
{
	ASSERT_EQ(offsetof(GPIO,GPAFEN),0x7E200088-0x7E200000);
}
TEST(GPIO,TestGPPUD)
{
	ASSERT_EQ(offsetof(GPIO,GPPUD),0x7E200094-0x7E200000);
}
TEST(GPIO,TestGPPUDCLK)
{
	ASSERT_EQ(offsetof(GPIO,GPPUDCLK),0x7E200098-0x7E200000);
}

// // TEST(PIN,InitPIN)
// // {
// // 	ASSERT_THROW(gpio_regs<pinN::p0>::instance(), std::runtime_error);
// // }

// // TEST(PIN, DynamicPIN)
// // {
// // 	ASSERT_THROW(gpio_pin p(pinN::p0), std::runtime_error);
// // }



// TEST(PIN, TestSpeed)
// {
// // 	gpio_pin p[]={
// // #define DEF_PIN_N(n) pinN::p##n,
// // 			DEF53(DEF_PIN_N)
// // 			pinN::p0
// // 			};

// // #define DEF_PINREGS(n) auto sp##n=gpio_regs<pinN::p##n>::instance();
// // 	DEF53(DEF_PINREGS)

// 	const size_t count=1000000000;

// // 	auto t1=std::chrono::high_resolution_clock::now();
// //  	for(size_t i=0; i<count; ++i){
// //  #define SET_FSEL_1(n) p[n].setmode(mode::out);
// //  		DEF53(SET_FSEL_1)
// //  		}
// 	auto regs=bcm2835::instance().registers().FIELDS;
// 	unsigned *GPFSEL = reinterpret_cast<unsigned*> (&regs);
// 	auto t2=std::chrono::high_resolution_clock::now();

// 	for(size_t i=0; i<count; ++i)
// 	{
#define SET_FSEL_3(n) {	 int reg      =  n/10;\
		int offset = (n % 10) * 3;\
		GPFSEL[reg] &= ~((0b111 & ~0b001) << offset);\
		GPFSEL[reg] |= ((0b111 & 0b000) << offset); }
// 		DEF53(SET_FSEL_3)
// 	}
// 	auto t4=std::chrono::high_resolution_clock::now();

// 	for(size_t i=0; i<count; ++i){
// #define SET_FSEL_4(n) regs.GPFSEL.fld.f##n=mode::out;
// //sp##n.setFSEL(mode::out);
// 		DEF53(SET_FSEL_4)
// 		}
// 	auto t5=std::chrono::high_resolution_clock::now();

// //	auto d1 =(t2-t1).count();
// 	auto d2 = (t4-t2).count();
// 	//auto d3 = (t4-t3).count();
// 	auto d4 = (t5-t4).count();
// 	std::cout << "gpio_regs<n>	=" << d4 << std::endl
// 		<< "bit manual	=" << d2 << " more " << ((float)(d2 - d4) / (float)d4) * 100 << "%" << std::endl;
// 	//	<< "switch	=" << d1 << " more " << ((float)(d1 - d4) / (float)d4) * 100 << "%" << std::endl;
// //				<< "function[] =" << d2 << " more " << ((float)(d2-d4)/(float)d4)*100 << "%" << std::endl;


// 	ASSERT_TRUE( /*d4<=d1 &&*/  d4<=d2 );
// }

std::ostream &operator<<(std::ostream &os, const mode s)
{
	os << std::hex << (int)s << ":";
	switch(s)
	{
		case mode::in: return os << "in";
		case mode::out: return os << "out";
		case mode::fun0: return os << "alt0";
		case mode::fun1: return os << "alt1";
		case mode::fun2: return os << "alt2";
		case mode::fun3: return os << "alt3";
		case mode::fun4: return os << "alt4";
		case mode::fun5: return os << "alt5";
	}
	return os << "err";
}

std::ostream &operator<<(std::ostream &os, const level s)
{
	switch(s)
	{
		case level::low: return os << "lo";
		case level::hight: return os << "hi";
	}
	return os << "err";
}

std::ostream &operator<<(std::ostream &os, const volatile GPIO::gpfsel &s)
{
	return os << "GPFSEL" << std::endl << std::oct << std::setfill('0') 
		<< std::setw(64) << std::bitset<64>(s.reg.r2) << std::endl
		<< std::setw(64) << std::bitset<64>(s.reg.r1) << std::endl
		<< std::setw(64) << std::bitset<64>(s.reg.r0) << std::endl
		
		<<"	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|" << std::endl
		<<"0	|"<< s.fld.p0 << "	|"<< s.fld.p1 << "	|"<< s.fld.p2 << "	|"<< s.fld.p3 << "	|"<< s.fld.p4 << "	|"<< s.fld.p5 << "	|"<< s.fld.p6 << "	|"<< s.fld.p7 << "	|"<< s.fld.p8 << "	|"<< s.fld.p9 << "	|"<< std::endl
		<<"1	|"<< s.fld.p10 << "	|"<< s.fld.p11 << "	|"<< s.fld.p12 << "	|"<< s.fld.p13 << "	|"<< s.fld.p14 << "	|"<< s.fld.p15 << "	|"<< s.fld.p16 << "	|"<< s.fld.p17 << "	|"<< s.fld.p18 << "	|"<< s.fld.p19 << "	|"<< std::endl
		<<"2	|"<< s.fld.p20 << "	|"<< s.fld.p21 << "	|"<< s.fld.p22 << "	|"<< s.fld.p23 << "	|"<< s.fld.p24 << "	|"<< s.fld.p25 << "	|"<< s.fld.p26 << "	|"<< s.fld.p27 << "	|"<< s.fld.p28 << "	|"<< s.fld.p29 << "	|"<< std::endl 
		<<"3	|"<< s.fld.p30 << "	|"<< s.fld.p31 << "	|"<< s.fld.p32 << "	|"<< s.fld.p33 << "	|"<< s.fld.p34 << "	|"<< s.fld.p35 << "	|"<< s.fld.p36 << "	|"<< s.fld.p37 << "	|"<< s.fld.p38 << "	|"<< s.fld.p39 << "	|"<< std::endl
		<<"4	|"<< s.fld.p40 << "	|"<< s.fld.p41 << "	|"<< s.fld.p42 << "	|"<< s.fld.p43 << "	|"<< s.fld.p44 << "	|"<< s.fld.p45 << "	|"<< s.fld.p46 << "	|"<< s.fld.p47 << "	|"<< s.fld.p48 << "	|"<< s.fld.p49 << "	|"<< std::endl
		<<"5	|"<< s.fld.p50 << "	|"<< s.fld.p51 << "	|"<< s.fld.p52 << "	|"<< s.fld.p53 << "	|"<< std::endl;
}



std::ostream &operator<<(std::ostream &os, const volatile GPIO::gplev &s)
{
	return os 	<< "GPLEVS" << std::endl
		<< std::oct << std::setfill('0') << std::setw(22) << s.reg << std::endl
		<<"	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|" << std::endl
		<<"0	|"<< s.fld.p0 << "	|"<< s.fld.p1 << "	|"<< s.fld.p2 << "	|"<< s.fld.p3 << "	|"<< s.fld.p4 << "	|"<< s.fld.p5 << "	|"<< s.fld.p6 << "	|"<< s.fld.p7 << "	|"<< s.fld.p8 << "	|"<< s.fld.p9 << "	|"<< std::endl
		<<"1	|"<< s.fld.p10 << "	|"<< s.fld.p11 << "	|"<< s.fld.p12 << "	|"<< s.fld.p13 << "	|"<< s.fld.p14 << "	|"<< s.fld.p15 << "	|"<< s.fld.p16 << "	|"<< s.fld.p17 << "	|"<< s.fld.p18 << "	|"<< s.fld.p19 << "	|"<< std::endl
		<<"2	|"<< s.fld.p20 << "	|"<< s.fld.p21 << "	|"<< s.fld.p22 << "	|"<< s.fld.p23 << "	|"<< s.fld.p24 << "	|"<< s.fld.p25 << "	|"<< s.fld.p26 << "	|"<< s.fld.p27 << "	|"<< s.fld.p28 << "	|"<< s.fld.p29 << "	|"<< std::endl 
		<<"3	|"<< s.fld.p30 << "	|"<< s.fld.p31 << "	|"<< s.fld.p32 << "	|"<< s.fld.p33 << "	|"<< s.fld.p34 << "	|"<< s.fld.p35 << "	|"<< s.fld.p36 << "	|"<< s.fld.p37 << "	|"<< s.fld.p38 << "	|"<< s.fld.p39 << "	|"<< std::endl
		<<"4	|"<< s.fld.p40 << "	|"<< s.fld.p41 << "	|"<< s.fld.p42 << "	|"<< s.fld.p43 << "	|"<< s.fld.p44 << "	|"<< s.fld.p45 << "	|"<< s.fld.p46 << "	|"<< s.fld.p47 << "	|"<< s.fld.p48 << "	|"<< s.fld.p49 << "	|"<< std::endl
		<<"5	|"<< s.fld.p50 << "	|"<< s.fld.p51 << "	|"<< s.fld.p52 << "	|"<< s.fld.p53 << "	|"<< std::endl;
}

TEST(PIN, bcmBlink)
{
	try
	{
		bcm2835& bcm=bcm2835::instance();
		volatile GPIO &gpio=bcm.registers();
		gpio.GPFSEL.fld.p18=mode::out;

		std::cout 	<< gpio.GPFSEL << std::endl;

		gpio.GPSET.fld.p18=output::set;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
		std::cout << gpio.GPLEV << std::endl;	
		ASSERT_TRUE(gpio.GPLEV.fld.p18 == level::hight);
		
		gpio.GPCLR.fld.p18=output::set;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		std::cout << gpio.GPLEV << std::endl;
		ASSERT_TRUE(gpio.GPLEV.fld.p18 == level::low);


	}
	catch (std::runtime_error err)
	{
		FAIL() << "Ошибка! Проверте запуск с sudo";
	}
	catch(...)
	{
		FAIL() << "Нeизвестное исключение";
	}
}


// TEST(PIN, Blink)
// {
// 	try
// 	{
// 		gpio_p<pinN::p18> p(mode::out);

// 		p.write(level::hight);
// 		std::this_thread::sleep_for(std::chrono::milliseconds(100));
// 		ASSERT_TRUE(p.read() == level::hight);
// 		p.write(level::low);
// 		std::this_thread::sleep_for(std::chrono::milliseconds(100));
// 		ASSERT_TRUE(p.read() == level::low);


// 	}
// 	catch (std::runtime_error err)
// 	{
// 		FAIL() << "Ошибка! Проверте запуск с sudo";
// 	}
// 	catch(...)
// 	{
// 		FAIL() << "Нeизвестное исключение";
// 	}
// }

// TEST(CPP, bitMap)
// {
// 	foo f ={0b00101011};

// 	std::cout 	<< "foo(" << std::bitset<8>(f.a) << "):" << std::endl
// 				<<"0	|1	|2	|3	|4	|5	|6	|7	|" << std::endl
// 				<< f.b.l0 << "	|" << f.b.l1 << "	|"<< f.b.l2<< "	|" << f.b.l3 << "	|"<< f.b.l4 << "	|"<< f.b.l5 << "	|"<< f.b.l6 << "	|"<< f.b.l7<< "	|" << std::endl; 
// 	ASSERT_TRUE(f.a==0b00101011);
// 	ASSERT_TRUE(f.b.l0==level::hight);
// 	ASSERT_TRUE(f.b.l1==level::hight);
// 	ASSERT_TRUE(f.b.l2==level::low);
// 	ASSERT_TRUE(f.b.l3==level::hight);
// }

TEST(CPP, bitGPIO_REGS)
{
	u_int64_t m[3]={0b1010101010111110101100011010001000,0b110110110110110111110101100011010001000,0b100100100100100111110101100011010001000};
	const GPIO &s=*(GPIO*)m;
	GPIO s2=s;

	std::cout 	<< s.GPFSEL << std::endl 
				<< s2.GPFSEL << std::endl;
				
	ASSERT_TRUE(s.GPFSEL.fld.p0==mode::in);
	ASSERT_TRUE(s.GPFSEL.fld.p1==mode::out);
	ASSERT_TRUE(s.GPFSEL.fld.p2==mode::fun5);
	ASSERT_TRUE(s.GPFSEL.fld.p3==mode::fun4);
	ASSERT_TRUE(s.GPFSEL.fld.p4==mode::fun0);
	ASSERT_TRUE(s.GPFSEL.fld.p5==mode::fun1);
	ASSERT_TRUE(s.GPFSEL.fld.p6==mode::fun2);
	ASSERT_TRUE(s.GPFSEL.fld.p7==mode::fun3);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
