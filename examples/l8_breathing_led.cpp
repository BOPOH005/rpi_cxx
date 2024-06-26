#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <bitset>
#include <iomanip>
#include "../rpi_cxx.h"
#include "../pwm.h"

using namespace rpi_cxx;
using namespace std::this_thread;
using namespace std::chrono;

std::atomic<bool> quit;

int main(void)
{
    std::cout << std::unitbuf;
    std::cout << "Урок №8 Дыхание LED" << std::endl
              << "GPIO 18 (PWM1) -Out->  Диод" << std::endl
              << "quit - для завершения" << std::endl;
    try
    {
        std::thread th([]() {
            std::string cmd;
            while (cmd != "quit"){
                std::cin >> cmd;
            }
            quit = true;
        });
        th.detach();

        // gpio<18> p(mode::fun5);
        // sleep_for(microseconds(110));
        // pwn_regs<1> ledPin;
        // ledPin.setAlgorithm(PWM::algorithm::MS);

        pwn_gpio<pwn_18> ledPin;
        ledPin.setRange(320);
        sleep_for(microseconds(10));
        
        std::cout << "Поехали!" << std::endl;
        while(!quit){
            std::cout << "/";
            for(u_int32_t i=0;i<320;i++){
                ledPin = i;
                sleep_for(milliseconds(2));
            }
            std::cout << "\\";
            for(u_int32_t i=320;i>0;--i){
                ledPin = i;
                sleep_for(milliseconds(2));
            }
 	    }
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << "Ошибка! Проверте запуск с sudo";
    }
    catch (...)
    {
        std::cerr << "Нeизвестное исключение";
    }
}