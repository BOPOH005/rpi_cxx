#include<iostream>
#include<chrono>
#include<thread>
#include<atomic>
#include"../rpi_cxx.h"

using namespace rpi_cxx;
using namespace std::this_thread;
using namespace std::chrono;

int main (void)
{
    std::cout << std::unitbuf;
    std::cout   << "Урок №6 Реле" << std::endl
                << "GPIO 18 -Out->  Транзистор" << std::endl
                << "quit - для завершения" << std::endl;
	try
	{
   
        std::cout << "Управление на основе шаблонов" << std::endl;
        
        gpio<18> p(mode::out);
        for(int i=0; i<10; ++i)
        {
            p=level::low;
            sleep_for(milliseconds(1000));
            p=level::hight; 
            sleep_for(milliseconds(1000));           
        }
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