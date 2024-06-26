#include <iostream>
#include <atomic>
#include"../adc0832.h"


using namespace rpi_cxx;
using namespace std::this_thread;
using namespace std::chrono;

std::atomic<bool> quit(false);

int main(void)
{
    std::cout << std::unitbuf;
// см. схему работы АЦП "../examples/png/17_ADC0832 timing.png"
    std::cout << "Урок №18 Термистор" << std::endl
              << "GPIO 18 -Out|In->  DIO (out:шина 3-битных комманд; in:шина 8-битных данных)" << std::endl
              << "GPIO 17 -Out->  CS (chip select - должна быть low в ходе передачи)" << std::endl
              << "GPIO 27 -Out->  CLK (такты для бит-сигналов DIO)" << std::endl
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

        ADC0832<18, 17, 27> adc;
          
        std::cout << "Поехали!" << std::endl;
        std::bitset<8> res0, res1;
        while(!quit){
            try{
                auto data0=adc.read(CH0);
                auto data1=adc.read(CH1);

                if(res0!=data0 || res1!=data1) {
                    res0=data0;
                    res1=data1;
                    std::cout << "(CH0): " << data0 << " : "<< std::hex << data0.to_ulong() << " : " << std::fixed << std::setprecision(1) << float(data0.to_ulong())/0xff*100 << "%"
                        << " ------ (CH1): " << data1 << " : "<< std::hex << data1.to_ulong() << " : " << std::fixed << std::setprecision(1) << float(data1.to_ulong())/0xff*100 << "%" 
                        << std::endl;
                }}
            catch (const std::runtime_error &err){
                std::cout <<  err.what() << std::endl;
            }
            sleep_for(milliseconds(500));
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
