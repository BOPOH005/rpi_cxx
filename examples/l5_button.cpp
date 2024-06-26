#include<iostream>
#include<chrono>
#include<thread>
#include<atomic>
#include"../rpi_cxx.h"

using namespace rpi_cxx;
using namespace std::this_thread;
using namespace std::chrono;

std::atomic<bool> quit;

template<pinN b, pinN l>
void button()
{
    gpio<b> p_b(mode::in);
    //p_b=hight;
    GPIO::gpset reg;
    auto& bcm=bcm2835::instance();
    bcm.pullupdown(pull::down, reg << p_b);
    
    std::cout << std::hex << reg.reg << std::endl;

    gpio<l> p_l(mode::out);
    level status=p_b;
    p_l=status;
    for(unsigned i=0; !quit; ) 
    { 
        const level lt=p_b;
        if(lt!=status)
        {
            p_l=status=lt;
            std::cout << i++ << (lt==level::hight?" on":" off") << std::endl;
        }
    }
    bcm.pullupdown(pull::off, reg);    
}

int main (void)
{
    std::cout << std::unitbuf;
    std::cout   << "Урок №5 Кнопка" << std::endl
                << "GPIO 17 -Out->  Диод" << std::endl
                << "GPIO 18 <-In-   Кнопка" << std::endl
                << "quit - для завершения" << std::endl;
	try
	{
        std::thread th([]()
        {  
            std::string cmd;
            while(cmd!="quit")std::cin >> cmd;
            quit=true;
        });
        th.detach();
        
        std::cout << "Управление на основе шаблонов" << std::endl;
        button<18,17>();
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