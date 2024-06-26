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

TEST(GPIO__gpset, Test_null)
{
    GPIO::gpset reg;
    ASSERT_TRUE(reg.reg == 0);
}


TEST(GPIO__gpset, Test_add2)
{
    GPIO::gpset reg;
    const u_int64_t i = -1;

#define EXPECT_GPPUDCLK(n) EXPECT_TRUE((reg << gpio<n>()).reg == (i >> (63 - n)));

    DEF53(EXPECT_GPPUDCLK)
}

TEST(GPIO__gpset, Test_multiblink)
{
    gpio<17> p1(mode::out);
    gpio<18> p2(mode::out);
    GPIO::gpset reg;
    auto& bcm=bcm2835::instance();

    bcm.setlevel(level::hight, reg << p1 << p2 );
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(p1==level::hight && p2==level::hight);
    bcm.setlevel(level::low, reg );    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_TRUE(p1==level::low && p2==level::low);
}

TEST(GPIO_detect, RISING)
{
    try 
    {
    gpio<1> p1(mode::out);
    gpio<2> p2(mode::out);
    auto& bcm=bcm2835::instance(); 
    GPIO::gpset reg;

    p1=level::low;
    p2=level::hight; // может породить событие

    bcm.detect(detectmode::RISING, 
        reg << p1 << p2);

    p1.checkevent(); 
    p2.checkevent(); //сбрасываем ренее возникшее событие

    p1=level::hight;
    p2=level::low;

    EXPECT_TRUE(p1.checkevent()==set::on);
    EXPECT_TRUE(p2.checkevent()!=set::on);

    bcm.undetect_all(detectmode::RISING);
    }
    catch (const std::runtime_error& err)
    {
	FAIL() << "Ошибка! Проверте запуск с sudo";
    }
    catch (...)
    {
	FAIL() << "Нeизвестное исключение";
    }
}

TEST(GPIO_detect, FALLING)
{
    try 
    {
    gpio<3> p1(mode::out);
    gpio<4> p2(mode::out);
    auto& bcm=bcm2835::instance(); 
    GPIO::gpset reg; 

    p1=level::low; // может породить событие
    p2=level::hight; 
   
    bcm.detect(detectmode::FALLING, 
        reg << p1 << p2);

    p1.checkevent(); //сбрасываем ренее возникшее событие
    p2.checkevent();

    p1=level::hight;
    p2=level::low;

    EXPECT_TRUE(p1.checkevent()!=set::on);
    EXPECT_TRUE(p2.checkevent()==set::on);

    bcm.undetect_all(detectmode::FALLING);
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

TEST(GPIO_detect, RISING_FALLING)
{
    try 
    {
    gpio<5> p1(mode::out);
    gpio<6> p2(mode::out);
    auto& bcm=bcm2835::instance(); 
    GPIO::gpset reg; 

    p1=level::low; // может породить событие
    p2=level::hight; // может породить событие
   
    bcm.detect(detectmode::FALLING | detectmode::RISING, 
        reg << p1 << p2);

    p1.checkevent(); //сбрасываем ренее возникшее событие
    p2.checkevent(); //сбрасываем ренее возникшее событие

    p1=level::hight;
    p2=level::low;

    EXPECT_TRUE(p1.checkevent()==set::on);
    EXPECT_TRUE(p2.checkevent()==set::on);
    
    bcm.undetect_all(detectmode::FALLING | detectmode::RISING);
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

TEST(GPIO_detect, HIGHT)
{
    try 
    {
    gpio<7> p1(mode::out);
    gpio<8> p2(mode::out);
    auto& bcm=bcm2835::instance(); 
    GPIO::gpset reg; 

    p1=level::low; 
    p2=level::hight; 
   
    bcm.detect(detectmode::HIGHT, 
        reg << p1 << p2);

    EXPECT_TRUE(p1.checkevent()!=set::on); 
    EXPECT_TRUE(p2.checkevent()==set::on);
    EXPECT_TRUE(p2.checkevent()==set::on); //событие не сбрасывается

    p1=level::hight;
    p2=level::low;

    EXPECT_TRUE(p1.checkevent()==set::on);
    EXPECT_TRUE(p1.checkevent()==set::on); //событие не сбрасывается
    EXPECT_TRUE(p2.checkevent()==set::on);
    EXPECT_TRUE(p2.checkevent()!=set::on); //событие сбрасывается

    bcm.undetect_all(detectmode::HIGHT);
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

TEST(GPIO_detect, LOW)
{
    try 
    {
    gpio<9> p1(mode::out);
    gpio<10> p2(mode::out);
    auto& bcm=bcm2835::instance(); 
    GPIO::gpset reg; 

    p1=level::low; 
    p2=level::hight; 
   
    bcm.detect(detectmode::LOW, 
        reg << p1 << p2);

    EXPECT_TRUE(p1.checkevent()==set::on); 
    EXPECT_TRUE(p1.checkevent()==set::on); //событие не сбрасывается
    EXPECT_TRUE(p2.checkevent()!=set::on);

    p1=level::hight;
    p2=level::low;

    EXPECT_TRUE(p1.checkevent()==set::on);
    EXPECT_TRUE(p1.checkevent()!=set::on); //событие сбрасывается
    EXPECT_TRUE(p2.checkevent()==set::on);
    EXPECT_TRUE(p2.checkevent()==set::on); //событие не сбрасывается

    bcm.undetect_all(detectmode::LOW);
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
