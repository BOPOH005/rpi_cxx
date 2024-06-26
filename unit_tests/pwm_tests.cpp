#include "../pwm.h"
#include "gtest/gtest.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace rpi_cxx;
using namespace std::chrono;

TEST(PWM, testSizeOfPWM)
{
    ASSERT_EQ(size_t(0x28), sizeof(PWM));
}

TEST(PWM, testSizeOfCTLRegister)
{
    PWM pwm;
    ASSERT_EQ(size_t(0x4), sizeof(pwm.CTL));
    ASSERT_EQ(size_t(0x4), sizeof(pwm.CTL_32));
}

TEST(PWM, testSizeOfSTARegister)
{
    PWM pwm;
    ASSERT_EQ(size_t(0x4), sizeof(pwm.STA));
    ASSERT_EQ(size_t(0x4), sizeof(pwm.STA_32));
}

TEST(PWM, testSizeOfDMACRegister)
{
    PWM pwm;
    ASSERT_EQ(size_t(0x4), sizeof(pwm.DMAC));
    ASSERT_EQ(size_t(0x4), sizeof(pwm.DMAC_32));
}

TEST(PWM, testAdressOfChanelsRange)
{
    PWM pwm;
    ASSERT_EQ(size_t(0x10), size_t(&pwm.RNG1)-size_t(&pwm.CTL));
    ASSERT_EQ(size_t(0x20), size_t(&pwm.RNG2)-size_t(&pwm.CTL));
}

TEST(PWM, test_pwn_gpio)
{
    try
    {
        pwn_gpio<pwn_18> led;

        led.setRange(320);
                
        for(u_int32_t i=0;i<320;i++){
            led = i;
            sleep_for(milliseconds(10));
        }
        for(u_int32_t i=320;i>0;--i){
            led = i;
            sleep_for(milliseconds(10));
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

