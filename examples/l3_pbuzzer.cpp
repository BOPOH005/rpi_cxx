#include<iostream>
#include<chrono>
#include<thread>
#include"../rpi_cxx.h"

using namespace rpi_cxx;
using namespace std::this_thread;
using namespace std::chrono;

template<pinN n>
void pbuzzer_pin()
{
    gpio<n> p(out);

    p.gentone(261.63);
    sleep_for(milliseconds(200));
    p.gentone(293.66); 
    sleep_for(milliseconds(200));
    p.gentone(329.63);
    sleep_for(milliseconds(200));
    p.gentone(349.23);
    sleep_for(milliseconds(200));
    p.gentone(392);
    sleep_for(milliseconds(200));
    p.gentone(440);
    sleep_for(milliseconds(200));
    p.gentone(493.88);
    sleep_for(milliseconds(400));
    p.gentone(440);
    sleep_for(milliseconds(200));
    p.gentone(392);
    sleep_for(milliseconds(200));
    p.gentone(349.23);
    sleep_for(milliseconds(200));
    p.gentone(329.63);
    sleep_for(milliseconds(200));
    p.gentone(293.66);
    sleep_for(milliseconds(200));
    p.gentone(261.63);
    sleep_for(milliseconds(200));
    p.gentone(0);
}

int main (void)
{
    std::cout   << "Урок №3 Пассивный динамик" << std::endl
                << "GPIO 18 -Out->" << std::endl;

	try
	{
        std::cout << "Управление на основе шаблонов" << std::endl;
        pbuzzer_pin<18>();
	}
	catch (const std::runtime_error &err)
	{
		std::cerr << "Ошибка! Проверте запуск с sudo";
	}
	catch(...)
	{
		std::cerr << "Нeизвестное исключение";
	}
}
