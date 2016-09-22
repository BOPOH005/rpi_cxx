#include <limits.h>
#include "bcm2835.h"
#include "pin.h"
#include "gtest/gtest.h"



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
	ASSERT_THROW(pin<pinN::p0> p, std::runtime_error);
}



int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
