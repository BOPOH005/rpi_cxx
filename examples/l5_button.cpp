#include<iostream>
#include<chrono>
#include<thread>
#include<rpi_cxx.h>

using namespace rpi_cxx;
using namespace std::this_thread;
using namespace std::chrono;

template<pinN b, pinN l>
void button()
{
    gpio_p<b> p_b(in);
    GPIO::gppudclk reg;
    pullupdown(up, reg << p_b);
    
    gpio_p<l> p_l(out);
    level status=p_b;
    p_l=status;
    std::cout << std::unitbuf;
    for(unsigned i=0; 1; ) 
    { 
        const level lt=p_b;
        if(lt!=status)
        {
            p_l=status=lt;
            std::cout << i++ << (lt==hight?" on":" off") << std::endl;
        }
    }
}

int main (void)
{
    std::cout   << "Урок №4 Кнопка" << std::endl
                << "GPIO 18 -Out->" << std::endl
                << "GPIO 17 <-In-" << std::endl;
	try
	{
        std::cout << "Управление на основе шаблонов" << std::endl;
        button<pinN::p17,pinN::p18>();
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