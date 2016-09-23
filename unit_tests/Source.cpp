#include <limits.h>
#include "../bcm2835.h"
#include "../pin.h"
#include "gtest/gtest.h"
#include <chrono>



using namespace rpi_cxx;
template<class T>
void TestAdressGPIO(T m, size_t a)
{
	GPIO_REGS r = {};
	ASSERT_EQ((void*)(a - 0x7E200000),
		(void*)(reinterpret_cast<char*>(&(r.*m)) - reinterpret_cast<char*>(&r)));
}

TEST(GPIO, TestGPIO_REGS)
{
	ASSERT_EQ(size_t(0x7E2000B0 - 0x7E200000), sizeof(GPIO_REGS));
}

TEST(GPIO,TestGPFSEL)
{
	TestAdressGPIO(&GPIO_REGS::GPFSEL,0x7E200000);
}
TEST(GPIO,TestGPSET)
{
	TestAdressGPIO(&GPIO_REGS::GPSET,0x7E20001C);
}
TEST(GPIO,TestGPCLR)
{
	TestAdressGPIO(&GPIO_REGS::GPCLR,0x7E200028);
}
TEST(GPIO,TestGPLEV)
{
	TestAdressGPIO(&GPIO_REGS::GPLEV,0x7E200034);
}
TEST(GPIO,TestGPEDS)
{
	TestAdressGPIO(&GPIO_REGS::GPEDS,0x7E200040);
}
TEST(GPIO,TestGPREN)
{
	TestAdressGPIO(&GPIO_REGS::GPREN,0x7E20004C);
}
TEST(GPIO,TestGPFEN)
{
	TestAdressGPIO(&GPIO_REGS::GPFEN,0x7E200058);
}
TEST(GPIO,TestGPHEN)
{
	TestAdressGPIO(&GPIO_REGS::GPHEN,0x7E200064);
}
TEST(GPIO,TestGPLEN)
{
	TestAdressGPIO(&GPIO_REGS::GPLEN,0x7E200070);
}
TEST(GPIO,TestGPAREN)
{
	TestAdressGPIO(&GPIO_REGS::GPAREN,0x7E20007C);
}
TEST(GPIO,TestGPAFEN)
{
	TestAdressGPIO(&GPIO_REGS::GPAFEN,0x7E200088);
}
TEST(GPIO,TestGPPUD)
{
	TestAdressGPIO(&GPIO_REGS::GPPUD,0x7E200094);
}
TEST(GPIO,TestGPPUDCLK)
{
	TestAdressGPIO(&GPIO_REGS::GPPUDCLK,0x7E200098);
}

TEST(PIN,InitPIN)
{
	ASSERT_THROW(pinregs<pinN::p0>::instance(), std::runtime_error);
}

TEST(PIN, DynamicPIN)
{
	ASSERT_THROW(pin p(pinN::p0), std::runtime_error);
}



TEST(PIN, TestSpeed)
{
	pin p[]={
#define DEF_PIN_N(n) pinN::p##n,
			DEF53(DEF_PIN_N)
			pinN::p0
			};

#define DEF_PINREGS(n) auto sp##n=pinregs<pinN::p##n>::instance();
	DEF53(DEF_PINREGS)

	const size_t count=100000000;

	auto t1=std::chrono::high_resolution_clock::now();
	for(size_t i=0; i<count; ++i){
#define SET_FSEL_1(n) p[n].setFSEL_1(GPIO_REGS::out);
		DEF53(SET_FSEL_1)
		}
	auto t2=std::chrono::high_resolution_clock::now();
	for(size_t i=0; i<count; ++i)
	{
#define SET_FSEL_2(n) p[n].setFSEL_2(GPIO_REGS::out);
		DEF53(SET_FSEL_2)
	}
	auto t3=std::chrono::high_resolution_clock::now();
	for(size_t i=0; i<count; ++i)
	{
#define SET_FSEL_3(n) p[n].setFSEL_3(GPIO_REGS::out);
		DEF53(SET_FSEL_3)
	}
	auto t4=std::chrono::high_resolution_clock::now();

	for(size_t i=0; i<count; ++i){
#define SET_FSEL_4(n) sp##n.setFSEL(GPIO_REGS::out);
		DEF53(SET_FSEL_4)
		}
	auto t5=std::chrono::high_resolution_clock::now();

	auto d1 =(t2-t1).count();
	auto d2 = (t3-t2).count();
	auto d3 = (t4-t3).count();
	auto d4 = (t5-t4).count();
	std::cout 	<< "pinregs<n> =" << d4 << std::endl
				<< "bit manual =" << d3 << " more " << ((float)(d3-d4)/(float)d4)*100 << "%" << std::endl
				<< "switch     =" << d1 << " more " << ((float)(d1-d4)/(float)d4)*100 << "%" << std::endl
				<< "function[] =" << d2 << " more " << ((float)(d2-d4)/(float)d4)*100 << "%" << std::endl;


	ASSERT_TRUE( d4<=d1 && d4<=d2 && d4<=d3 );
}



int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
