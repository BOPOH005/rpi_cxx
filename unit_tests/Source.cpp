#include <limits.h>
#include "../bcm2835.h"
#include "../pin.h"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>
#include <bitset>


using namespace rpi_cxx;
template<class T>
void* TestAdressGPIO(T m)
{
	GPIO::fields r = {};
	return (char*)0x7E200000+(size_t)(reinterpret_cast<char*>(&(r.*m)) - reinterpret_cast<char*>(&r));
}

template<class T>
void* TestAdressGPIOR(T m)
{
	GPIO::regs r = {};
	return (char*)0x7E200000+(size_t)(reinterpret_cast<char*>(&(r.*m)) - reinterpret_cast<char*>(&r));
}


TEST(GPIO, TestSizeofGPIO)
{
	ASSERT_EQ(size_t(0x7E2000B0 - 0x7E200000), sizeof(GPIO::fields));
	ASSERT_EQ(size_t(0x7E2000B0 - 0x7E200000), sizeof(GPIO::regs));
	ASSERT_EQ(size_t(0x7E2000B0 - 0x7E200000), sizeof(GPIO));
}

TEST(GPIO,TestGPFSEL)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPFSEL),(void*)0x7E200000);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPFSEL1),(void*)0x7E200000);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPFSEL2),(void*)0x7E200008);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPFSEL3),(void*)0x7E200010);
}
TEST(GPIO,TestGPSET)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPSET),(void*)0x7E20001C);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPSET),(void*)0x7E20001C);
}
TEST(GPIO,TestGPCLR)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPCLR),(void*)0x7E200028);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPCLR),(void*)0x7E200028);
}
TEST(GPIO,TestGPLEV)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPLEV),(void*)0x7E200034);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPLEV),(void*)0x7E200034);
}
TEST(GPIO,TestGPEDS)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPEDS),(void*)0x7E200040);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPEDS),(void*)0x7E200040);
}
TEST(GPIO,TestGPREN)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPREN),(void*)0x7E20004C);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPREN),(void*)0x7E20004C);
}
TEST(GPIO,TestGPFEN)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPFEN),(void*)0x7E200058);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPFEN),(void*)0x7E200058);
}
TEST(GPIO,TestGPHEN)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPHEN),(void*)0x7E200064);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPHEN),(void*)0x7E200064);
}
TEST(GPIO,TestGPLEN)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPLEN),(void*)0x7E200070);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPLEN),(void*)0x7E200070);
}
TEST(GPIO,TestGPAREN)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPAREN),(void*)0x7E20007C);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPAREN),(void*)0x7E20007C);
}
TEST(GPIO,TestGPAFEN)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPAFEN),(void*)0x7E200088);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPAFEN),(void*)0x7E200088);
}
TEST(GPIO,TestGPPUD)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPPUD),(void*)0x7E200094);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPPUD),(void*)0x7E200094);	
}
TEST(GPIO,TestGPPUDCLK)
{
	ASSERT_EQ(TestAdressGPIO(&GPIO::fields::GPPUDCLK),(void*)0x7E200098);
	ASSERT_EQ(TestAdressGPIOR(&GPIO::regs::GPPUDCLK),(void*)0x7E200098);
}

// TEST(PIN,InitPIN)
// {
// 	ASSERT_THROW(gpio_regs<pinN::p0>::instance(), std::runtime_error);
// }

// TEST(PIN, DynamicPIN)
// {
// 	ASSERT_THROW(gpio_pin p(pinN::p0), std::runtime_error);
// }



TEST(PIN, TestSpeed)
{
// 	gpio_pin p[]={
// #define DEF_PIN_N(n) pinN::p##n,
// 			DEF53(DEF_PIN_N)
// 			pinN::p0
// 			};

// #define DEF_PINREGS(n) auto sp##n=gpio_regs<pinN::p##n>::instance();
// 	DEF53(DEF_PINREGS)

	const size_t count=1000000000;

// 	auto t1=std::chrono::high_resolution_clock::now();
//  	for(size_t i=0; i<count; ++i){
//  #define SET_FSEL_1(n) p[n].setmode(mode::out);
//  		DEF53(SET_FSEL_1)
//  		}
	auto regs=bcm2835::instance().registers().FIELDS;
	unsigned *GPFSEL = reinterpret_cast<unsigned*> (&regs);
	auto t2=std::chrono::high_resolution_clock::now();

	for(size_t i=0; i<count; ++i)
	{
#define SET_FSEL_3(n) {	 int reg      =  n/10;\
		int offset = (n % 10) * 3;\
		GPFSEL[reg] &= ~((0b111 & ~0b001) << offset);\
		GPFSEL[reg] |= ((0b111 & 0b000) << offset); }
		DEF53(SET_FSEL_3)
	}
	auto t4=std::chrono::high_resolution_clock::now();

	for(size_t i=0; i<count; ++i){
#define SET_FSEL_4(n) regs.GPFSEL.FSEL##n=mode::out;
//sp##n.setFSEL(mode::out);
		DEF53(SET_FSEL_4)
		}
	auto t5=std::chrono::high_resolution_clock::now();

//	auto d1 =(t2-t1).count();
	auto d2 = (t4-t2).count();
	//auto d3 = (t4-t3).count();
	auto d4 = (t5-t4).count();
	std::cout << "gpio_regs<n>	=" << d4 << std::endl
		<< "bit manual	=" << d2 << " more " << ((float)(d2 - d4) / (float)d4) * 100 << "%" << std::endl;
	//	<< "switch	=" << d1 << " more " << ((float)(d1 - d4) / (float)d4) * 100 << "%" << std::endl;
//				<< "function[] =" << d2 << " more " << ((float)(d2-d4)/(float)d4)*100 << "%" << std::endl;


	ASSERT_TRUE( /*d4<=d1 &&*/  d4<=d2 );
}

std::ostream &operator<<(std::ostream &os, const mode &s)
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

std::ostream &operator<<(std::ostream &os, const level &s)
{
	switch(s)
	{
		case level::low: return os << "lo";
		case level::hight: return os << "hi";
	}
	return os << "err";
}

std::ostream &operator<<(std::ostream &os, const GPIO::fields::fsels &s)
{
	std::bitset<64> bit1(*reinterpret_cast<const unsigned long long*>(&s));
	std::bitset<64> bit2(*(reinterpret_cast<const unsigned long long*>(&s)+1));
	std::bitset<64> bit3(*(reinterpret_cast<const unsigned long long*>(&s)+2));	
	return os 	<< "FSELS("<< &s << "):" << std::endl 
				<< bit3.to_string() << std::endl 
				<< bit2.to_string() << std::endl
				<< bit1.to_string() << std::endl
			<<"	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|" << std::endl
		<<"0	|"<< s.FSEL0 << "	|"<< s.FSEL1 << "	|"<< s.FSEL2 << "	|"<< s.FSEL3 << "	|"<< s.FSEL4 << "	|"<< s.FSEL5 << "	|"<< s.FSEL6 << "	|"<< s.FSEL7 << "	|"<< s.FSEL8 << "	|"<< s.FSEL9 << "	|"<< std::endl
		<<"1	|"<< s.FSEL10 << "	|"<< s.FSEL11 << "	|"<< s.FSEL12 << "	|"<< s.FSEL13 << "	|"<< s.FSEL14 << "	|"<< s.FSEL15 << "	|"<< s.FSEL16 << "	|"<< s.FSEL17 << "	|"<< s.FSEL18 << "	|"<< s.FSEL19 << "	|"<< std::endl
		<<"2	|"<< s.FSEL20 << "	|"<< s.FSEL21 << "	|"<< s.FSEL22 << "	|"<< s.FSEL23 << "	|"<< s.FSEL24 << "	|"<< s.FSEL25 << "	|"<< s.FSEL26 << "	|"<< s.FSEL27 << "	|"<< s.FSEL28 << "	|"<< s.FSEL29 << "	|"<< std::endl 
		<<"3	|"<< s.FSEL30 << "	|"<< s.FSEL31 << "	|"<< s.FSEL32 << "	|"<< s.FSEL33 << "	|"<< s.FSEL34 << "	|"<< s.FSEL35 << "	|"<< s.FSEL36 << "	|"<< s.FSEL37 << "	|"<< s.FSEL38 << "	|"<< s.FSEL39 << "	|"<< std::endl
		<<"4	|"<< s.FSEL40 << "	|"<< s.FSEL41 << "	|"<< s.FSEL42 << "	|"<< s.FSEL43 << "	|"<< s.FSEL44 << "	|"<< s.FSEL45 << "	|"<< s.FSEL46 << "	|"<< s.FSEL47 << "	|"<< s.FSEL48 << "	|"<< s.FSEL49 << "	|"<< std::endl
		<<"5	|"<< s.FSEL50 << "	|"<< s.FSEL51 << "	|"<< s.FSEL52 << "	|"<< s.FSEL53 << "	|"<< std::endl;
}

std::ostream &operator<<(std::ostream &os, const GPIO::fields::levs &s)
{
	std::bitset<64> bit1(*reinterpret_cast<const unsigned long long*>(&s));	
	return os 	<< "LEVS" << std::endl
		<< std::oct << std::setfill('0')
		<< std::setw(22) << *reinterpret_cast<const unsigned long long*>(&s) << std::endl
		<< bit1.to_string() << std::endl
		<<"	|0	|1	|2	|3	|4	|5	|6	|7	|8	|9	|" << std::endl
		<<"0	|"<< s.LEV0 << "	|"<< s.LEV1 << "	|"<< s.LEV2 << "	|"<< s.LEV3 << "	|"<< s.LEV4 << "	|"<< s.LEV5 << "	|"<< s.LEV6 << "	|"<< s.LEV7 << "	|"<< s.LEV8 << "	|"<< s.LEV9 << "	|"<< std::endl
		<<"1	|"<< s.LEV10 << "	|"<< s.LEV11 << "	|"<< s.LEV12 << "	|"<< s.LEV13 << "	|"<< s.LEV14 << "	|"<< s.LEV15 << "	|"<< s.LEV16 << "	|"<< s.LEV17 << "	|"<< s.LEV18 << "	|"<< s.LEV19 << "	|"<< std::endl
		<<"2	|"<< s.LEV20 << "	|"<< s.LEV21 << "	|"<< s.LEV22 << "	|"<< s.LEV23 << "	|"<< s.LEV24 << "	|"<< s.LEV25 << "	|"<< s.LEV26 << "	|"<< s.LEV27 << "	|"<< s.LEV28 << "	|"<< s.LEV29 << "	|"<< std::endl 
		<<"3	|"<< s.LEV30 << "	|"<< s.LEV31 << "	|"<< s.LEV32 << "	|"<< s.LEV33 << "	|"<< s.LEV34 << "	|"<< s.LEV35 << "	|"<< s.LEV36 << "	|"<< s.LEV37 << "	|"<< s.LEV38 << "	|"<< s.LEV39 << "	|"<< std::endl
		<<"4	|"<< s.LEV40 << "	|"<< s.LEV41 << "	|"<< s.LEV42 << "	|"<< s.LEV43 << "	|"<< s.LEV44 << "	|"<< s.LEV45 << "	|"<< s.LEV46 << "	|"<< s.LEV47 << "	|"<< s.LEV48 << "	|"<< s.LEV49 << "	|"<< std::endl
		<<"5	|"<< s.LEV50 << "	|"<< s.LEV51 << "	|"<< s.LEV52 << "	|"<< s.LEV53 << "	|"<< std::endl;
}


struct foo
{
	union{
		char a;
		struct  
		{
			level l0:1;
			level l1:1;
			level l2:1;
			level l3:1;
			level l4:1;
			level l5:1;
			level l6:1;
			level l7:1;
		}b;
	};
};

TEST(PIN, bcmBlink)
{
	try
	{
		bcm2835& bcm=bcm2835::instance();
		GPIO& gpio=bcm.registers();
		//auto& const regs=gpio.FIELDS;		
		gpio.FIELDS.GPFSEL.FSEL18=mode::out;

		ASSERT_EQ((void*)&gpio.REGS.GPFSEL1,(void*)&gpio.FIELDS.GPFSEL);
		
		std::cout 	<< "gpio.REGS->" << (void*)&gpio.REGS << " gpio.FIELDS->" << (void*)&gpio.FIELDS << std::endl
					<< std::oct << std::setfill('0') 
					<< std::setw(22) << gpio.REGS.GPFSEL3 << " " 
					<< std::setw(22) << gpio.REGS.GPFSEL2 << " " 
					<< std::setw(22) << gpio.REGS.GPFSEL1 << std::endl
					<< gpio.FIELDS.GPFSEL << std::endl;

		gpio.FIELDS.GPSET.SET18=output::set;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
		std::cout << gpio.FIELDS.GPLEV << std::endl;	
		ASSERT_TRUE(gpio.FIELDS.GPLEV.LEV18 == level::hight);
		
		gpio.FIELDS.GPCLR.CLR18=output::set;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		std::cout << gpio.FIELDS.GPLEV << std::endl;
		ASSERT_TRUE(gpio.FIELDS.GPLEV.LEV18 == level::low);


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


TEST(PIN, Blink)
{
	try
	{
		gpio_p<pinN::p18> p(mode::out);

		p.write(level::hight);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ASSERT_TRUE(p.read() == level::hight);
		p.write(level::low);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ASSERT_TRUE(p.read() == level::low);


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

TEST(CPP, bitMap)
{
	foo f ={0b00101011};

	std::cout 	<< "foo(" << std::bitset<8>(f.a) << "):" << std::endl
				<<"0	|1	|2	|3	|4	|5	|6	|7	|" << std::endl
				<< f.b.l0 << "	|" << f.b.l1 << "	|"<< f.b.l2<< "	|" << f.b.l3 << "	|"<< f.b.l4 << "	|"<< f.b.l5 << "	|"<< f.b.l6 << "	|"<< f.b.l7<< "	|" << std::endl; 
	ASSERT_TRUE(f.a==0b00101011);
	ASSERT_TRUE(f.b.l0==level::hight);
	ASSERT_TRUE(f.b.l1==level::hight);
	ASSERT_TRUE(f.b.l2==level::low);
	ASSERT_TRUE(f.b.l3==level::hight);
}

TEST(CPP, bitGPIO_REGS)
{
	GPIO s= {0b111110101100011010001000};

	std::cout 	<< s.FIELDS.GPFSEL << std::endl;
				
	ASSERT_TRUE(s.FIELDS.GPFSEL.FSEL0==mode::in);
	ASSERT_TRUE(s.FIELDS.GPFSEL.FSEL1==mode::out);
	ASSERT_TRUE(s.FIELDS.GPFSEL.FSEL2==mode::fun5);
	ASSERT_TRUE(s.FIELDS.GPFSEL.FSEL3==mode::fun4);
	ASSERT_TRUE(s.FIELDS.GPFSEL.FSEL4==mode::fun0);
	ASSERT_TRUE(s.FIELDS.GPFSEL.FSEL5==mode::fun1);
	ASSERT_TRUE(s.FIELDS.GPFSEL.FSEL6==mode::fun2);
	ASSERT_TRUE(s.FIELDS.GPFSEL.FSEL7==mode::fun3);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
