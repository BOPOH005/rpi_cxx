#include "../bcm2835.h"
#include "../pin.h"
#include <gtest/gtest.h>


using namespace rpi_cxx;

TEST(GPIO, TestSizeofGPIO)
{
    ASSERT_EQ(size_t(0x7E2000B0 - 0x7E200000), sizeof(GPIO));
}

TEST(GPIO, TestGPFSEL)
{
    ASSERT_EQ(offsetof(GPIO, GPFSEL), size_t(0x7E200000 - 0x7E200000));
}

TEST(GPIO, TestGPSET)
{
    ASSERT_EQ(offsetof(GPIO, GPSET), size_t(0x7E20001C - 0x7E200000));
}

TEST(GPIO, TestGPCLR)
{
    ASSERT_EQ(offsetof(GPIO, GPCLR), size_t(0x7E200028 - 0x7E200000));
}
TEST(GPIO, TestGPLEV)
{
    ASSERT_EQ(offsetof(GPIO, GPLEV), size_t(0x7E200034 - 0x7E200000));
}
TEST(GPIO, TestGPEDS)
{
    ASSERT_EQ(offsetof(GPIO, GPEDS), size_t(0x7E200040 - 0x7E200000));
}
TEST(GPIO, TestGPREN)
{
    ASSERT_EQ(offsetof(GPIO, GPREN), size_t(0x7E20004C - 0x7E200000));
}
TEST(GPIO, TestGPFEN)
{
    ASSERT_EQ(offsetof(GPIO, GPFEN), size_t(0x7E200058 - 0x7E200000));
}
TEST(GPIO, TestGPHEN)
{
    ASSERT_EQ(offsetof(GPIO, GPHEN), size_t(0x7E200064 - 0x7E200000));
}
TEST(GPIO, TestGPLEN)
{
    ASSERT_EQ(offsetof(GPIO, GPLEN), size_t(0x7E200070 - 0x7E200000));
}
TEST(GPIO, TestGPAREN)
{
    ASSERT_EQ(offsetof(GPIO, GPAREN), size_t(0x7E20007C - 0x7E200000));
}
TEST(GPIO, TestGPAFEN)
{
    ASSERT_EQ(offsetof(GPIO, GPAFEN), size_t(0x7E200088 - 0x7E200000));
}
TEST(GPIO, TestGPPUD)
{
    ASSERT_EQ(offsetof(GPIO, GPPUD), size_t(0x7E200094 - 0x7E200000));
}
TEST(GPIO, TestGPPUDCLK)
{
    ASSERT_EQ(offsetof(GPIO, GPPUDCLK), size_t(0x7E200098 - 0x7E200000));
}

TEST(GPIO__gppudclk, Test_null)
{
    GPIO::gppudclk reg;
    ASSERT_TRUE(reg.reg == 0);
}

TEST(GPIO__gppudclk, Test_add2)
{
    GPIO::gppudclk reg;
    const u_int64_t i = -1;

#define EXPECT_GPPUDCLK(n) EXPECT_TRUE((reg << gpio_p<p##n>()).reg == (i >> (63 - n)));

    DEF53(EXPECT_GPPUDCLK)
}

TEST(GPIO__gpsetclr, Test_null)
{
    GPIO::gpsetclr reg;
    ASSERT_TRUE(reg.reg == 0);
}


TEST(GPIO__gpsetclr, Test_add2)
{
    GPIO::gpsetclr reg;
    const u_int64_t i = -1;

#define EXPECT_GPPUDCLK(n) EXPECT_TRUE((reg << gpio_p<p##n>()).reg == (i >> (63 - n)));

    DEF53(EXPECT_GPPUDCLK)
}

TEST(GPIO__gpsetclr, Test_multiblink)
{
    gpio_p<p17> p1(out);
    gpio_p<p18> p2(out);
    GPIO::gpsetclr reg;
    auto& bcm=bcm2835::instance();

    bcm.setlevel(hight, reg << p1 << p2 );
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(p1==hight && p2==hight);
    bcm.setlevel(low, reg );    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(p1==low && p2==low);
}
