#include<iostream>
#include<chrono>
#include<thread>
#include<utility>
#include<rpi_cxx.h>

using namespace rpi_cxx;

template<pinN n>
void leg_pin()
{
    gpio_p<n> p(out);

    for(int i=5; i>0; --i)
    {
        p   << std::make_pair(hight,std::chrono::milliseconds(100))
            << std::make_pair(low,std::chrono::milliseconds(100));
    }
}

void leg_pin(pinN n)
{
	gpio_pin p(n, out);
		
		for(int i=5; i>0; --i)
		{
			p.write(hight);
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			p.write(low);
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
}

void leg_bcm()
{
    auto &gpio=bcm2835::instance().registers();
    gpio.GPFSEL.fld.p17=mode::out;

    for(int i=5; i>0; --i)
    {
        gpio.GPSET.fld.p17=true;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        gpio.GPCLR.fld.p17=true;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main (void)
{
    std::cout   << "Урок №1 Мигающий диод" << std::endl
                << "GPIO 17 -Out->" << std::endl;

	try
	{
        std::cout << "Управление на основе шаблонов" << std::endl;
        leg_pin<pinN::p17>();
        std::cout << "Управление на основе параметра" << std::endl;
        leg_pin(pinN::p17);
        std::cout << "Управление регистрами" << std::endl;
        leg_bcm();    
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
