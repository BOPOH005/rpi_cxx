#include<iostream>
#include<chrono>
#include<thread>
#include<rpi_cxx.h>

using namespace rpi_cxx;
using namespace std::this_thread;
using namespace std::chrono;

template<pinN tilt, pinN leg> 
void tiltswitch()
{
    gpio_p<tilt> p_t(in);
    gpio_p<leg> p_l(out);
    level status=low;
    p_l=status;

    while(1)
    {
        const level l=p_t;
        if(l!=status)
        {
            p_l=status=l;
            std::cout << (l==hight?"on":"off") << std::endl;
        }
    }
}

int main (void)
{
    std::cout   << "Урок №4 Датчик наклона" << std::endl
                << "GPIO 18 -Out->" << std::endl
                << "GPIO 17 <-In-" << std::endl;
	try
	{
        std::cout << "Управление на основе шаблонов" << std::endl;
        tiltswitch<pinN::p17,pinN::p18>();
	}
	catch (std::runtime_error err)
	{
		std::cerr << "Ошибка! Проверте запуск с sudo";
	}
	catch(...)
	{
		std::cerr << "Нeизвестное исключение";
	}
}