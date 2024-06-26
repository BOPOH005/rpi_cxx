#pragma once
#include <bitset>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>
#include "rpi_cxx.h"

namespace rpi_cxx
{

enum channel: bool{
    CH0 = 0x0,
    CH1 = 0x1
};

using namespace std::chrono;
using namespace std::this_thread;

template<pinN DIO, pinN CS, pinN CLK>
class ADC0832
{
public:
    ADC0832():pinADC_CS(mode::out), pinADC_CLK(mode::out){}
    std::bitset<8> read(channel ch) {
        pinADC_CS=level::low; //начало цикла аналого-цифрового преобразования 
            
                pinADC_DIO.setmode(mode::out); // начало передачи 3-битной команды
                pinADC_CLK=level::low; 
                    pinADC_DIO=level::hight;// стартовый команды бит всегда 1
                
                    sleep_for(microseconds(2)); //  
                    pinADC_CLK=level::hight;     //  формируем такт для передачи бита по DIO
                    sleep_for(microseconds(2)); //
                
                pinADC_CLK=level::low;          
                    pinADC_DIO=level::hight;// 2-бит, задающий режим работы входов CH0 и CH1. Если лог. 1, то входы одиночные (недифференциальные), если лог. 0, то входы дифференциальные.
                    
                    sleep_for(microseconds(2)); //  
                    pinADC_CLK=level::hight;     //  формируем такт для передачи бита по DIO
                    sleep_for(microseconds(2)); //
                
                pinADC_CLK=level::low;
                    pinADC_DIO=ch?level::hight:level::low;  //  3-бит, задающий номер выбранного входа CH0 или CH1 (когда вход недифференциальный), 
                                                            //  либо полярность дифференциальных входом (когда вход дифференциальный). 
                    sleep_for(microseconds(2)); //  
                    pinADC_CLK=level::hight;     //  формируем такт для передачи бита по DIO
                    sleep_for(microseconds(2)); //                        
                
                pinADC_CLK=level::low; // начало приема данных
                sleep_for(microseconds(2)); //  
                pinADC_DIO.setmode(mode::in);    
                    
                    //auto null=pinADC_DIO.read(); // первый бит-нулевой
                    std::bitset<8> first;
                    for(int i=7; i>=0; i--){ // цикл считывания основных 8-битовых данных
                        pinADC_CLK=level::hight;
                        sleep_for(microseconds(2)); // 
                        pinADC_CLK=level::low;
                        sleep_for(microseconds(2)); //
                        first[i]=pinADC_DIO;
                    }

                    std::bitset<8> second;
                    for(int i=0; i<8; i++){ // цикл считывания контрольных 8-битовых данных
                        second[i]=pinADC_DIO;
                        pinADC_CLK=level::hight;
                        sleep_for(microseconds(2)); // 
                        pinADC_CLK=level::low;
                        sleep_for(microseconds(2)); //
                    }
                       
            pinADC_CS=level::hight; //конец цикла аналого-цифрового преобразования

            if(first!=second){
                std::ostringstream s;
                s << "ADC0832 Ошибка контроля данных: (" << std::hex << first.to_ulong() << "!=" << second.to_ulong() << ")";
                throw std::runtime_error( s.str());
            }
            return first;
    }
private:
    gpio<DIO>   pinADC_DIO;
    gpio<CS>    pinADC_CS;
    gpio<CLK>   pinADC_CLK;
};

}