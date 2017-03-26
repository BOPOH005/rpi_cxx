#include<iostream>
#include<chrono>
#include<thread>
#include<rpi_cxx.h>

using namespace rpi_cxx;

template<pinN n>
void abuzzer_pin()
{
    gpio_p<n> p(out);

    for(int i=3; i>0; --i)
    {
        p=hight;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        p=low;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main (void)
{
    std::cout   << "Урок №2 Активный динамик" << std::endl
                << "GPIO 18 -Out->" << std::endl;

	try
	{
        std::cout << "Управление на основе шаблонов" << std::endl;
        abuzzer_pin<pinN::p18>();
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
