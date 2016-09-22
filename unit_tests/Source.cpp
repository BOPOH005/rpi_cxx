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
	ASSERT_THROW(spin<pinN::p0> p, std::runtime_error);
}

TEST(PIN, DynamicPIN)
{
	ASSERT_THROW(pin p(pinN::p0), std::runtime_error);
}



TEST(PIN, TestSpeed)
{
	pin p[]={pinN::p0, pinN::p1, pinN::p2, pinN::p3, pinN::p4, pinN::p5, pinN::p6, pinN::p7, pinN::p8, pinN::p9};
	spin<pinN::p0> sp0;
	spin<pinN::p1> sp1;
	spin<pinN::p2> sp2;
	spin<pinN::p3> sp3;
	spin<pinN::p4> sp4;
	spin<pinN::p5> sp5;
	spin<pinN::p6> sp6;
	spin<pinN::p7> sp7;
	spin<pinN::p8> sp8;
	spin<pinN::p9> sp9;

	auto t1=std::chrono::high_resolution_clock::now();
	for(int i=0; i<1000; ++i){
			p[0].setFSEL(GPIO_REGS::out);
		p[1].setFSEL(GPIO_REGS::out);
		p[2].setFSEL(GPIO_REGS::out);
		p[3].setFSEL(GPIO_REGS::out);
		p[4].setFSEL(GPIO_REGS::out);
		p[5].setFSEL(GPIO_REGS::out);
		p[6].setFSEL(GPIO_REGS::out);
		p[7].setFSEL(GPIO_REGS::out);
		p[8].setFSEL(GPIO_REGS::out);
		p[9].setFSEL(GPIO_REGS::out);
		}
	auto t2=std::chrono::high_resolution_clock::now();
	for(int i=0; i<1000; ++i)
	{
		p[0].setFSEL_fast(GPIO_REGS::out);
		p[1].setFSEL_fast(GPIO_REGS::out);
		p[2].setFSEL_fast(GPIO_REGS::out);
		p[3].setFSEL_fast(GPIO_REGS::out);
		p[4].setFSEL_fast(GPIO_REGS::out);
		p[5].setFSEL_fast(GPIO_REGS::out);
		p[6].setFSEL_fast(GPIO_REGS::out);
		p[7].setFSEL_fast(GPIO_REGS::out);
		p[8].setFSEL_fast(GPIO_REGS::out);
		p[9].setFSEL_fast(GPIO_REGS::out);
	}
	auto t3=std::chrono::high_resolution_clock::now();
	for(int i=0; i<1000; ++i){
		sp0.setFSEL(GPIO_REGS::out);
		sp1.setFSEL(GPIO_REGS::out);
		sp2.setFSEL(GPIO_REGS::out);
		sp3.setFSEL(GPIO_REGS::out);
		sp4.setFSEL(GPIO_REGS::out);
		sp5.setFSEL(GPIO_REGS::out);
		sp6.setFSEL(GPIO_REGS::out);
		sp7.setFSEL(GPIO_REGS::out);
		sp8.setFSEL(GPIO_REGS::out);
		sp9.setFSEL(GPIO_REGS::out);
	
		}
	auto t4=std::chrono::high_resolution_clock::now();

	auto d1 =(t2-t1).count();
	auto d2 = (t3-t2).count();
	auto d3 = (t4-t3).count();
	std::cout 	<< "spin        =" << std::setw(10) << d3 << std::endl
				<< "setFSEL_fast=" << std::setw(10) << d2 << " more " << ((float)(d2-d3)/(float)d3)*100 << "%" << std::endl
				<< "setFSEL=     "  << std::setw(10) << d1 << " more " << ((float)(d1-d3)/(float)d3)*100 << "%" << std::endl;


	ASSERT_TRUE( d3 < d2  );
}



int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
