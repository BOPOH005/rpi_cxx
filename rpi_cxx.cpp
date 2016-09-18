/*
 * rpi_cxx.cpp
 *
 *  Created on: 04.09.2016
 *      Author: bopoh
 */

#include"rpi_cxx.h"
#include<sstream>
#include<functional>
#include<vector>

namespace rpi_cxx
{

std::ostream &&operator<< (std::ostream &str, gpio::GPIOPin pin)
{
	return std::move(str << "GPIO" << static_cast<int>(pin));
}

std::ostream &&operator<< (std::ostream &str, GPIOPinMode mode)
{
	switch(mode)
	{
	case GPIOPinMode::modOUT: return std::move(str << "OUT");
	case GPIOPinMode::modIN: return std::move(str << "IN");
	}
	return std::move(str << "Неопределено (" << static_cast<int>(mode) << ")");
}


std::ostream &&operator<< (std::ostream &str, sys_gpio::GPIOSysPin pin)
{
	return std::move(str << "SYS_GPIO" << static_cast<int>(pin));
}

std::ostream &&operator<< (std::ostream &str, PUD pud)
{
	switch(pud)
	{
	case PUD::Down: return std::move(str << "DOWN");
	case PUD::Off: return std::move(str << "OFF");
	case PUD::Up: return std::move(str << "UP");
	}
	return std::move(str << "Неопределено (" << static_cast<int>(pud) << ")");
}

std::ostream &&operator<< (std::ostream &str, GPIOLevel level)
{
	switch(level)
	{
	case GPIOLevel::low: return std::move(str << "low");
	case GPIOLevel::hi: return std::move(str << "hi");
	}
	return std::move(str << "Неопределено (" << static_cast<int>(level) << ")");
}



void gpio::set_mode(GPIOPin pin, GPIOPinMode mode)
{
	std::cout << "Настройка порта: " << pin << " " << mode << std::endl;
	pinMode(static_cast<int>(pin),static_cast<int>(mode));
}

void gpio::set_PUD(GPIOPin pin, PUD pud)
{
	std::cout << "Настройка Pull Up/Down режима резистора: " << pin << " " << pud << std::endl;

	pullUpDnControl(static_cast<int>(pin),static_cast<int>(pud));
}

sys_gpio::GPIOSysPin sys_gpio::toGPIOSysPin(gpio::GPIOPin pin)
{
	const static std::vector<GPIOSysPin> map{
		GPIOSysPin::GPIO0,
		GPIOSysPin::GPIO1,
		GPIOSysPin::GPIO2,
		GPIOSysPin::GPIO3,
		GPIOSysPin::GPIO4,
		GPIOSysPin::GPIO5,
		GPIOSysPin::GPIO6,
		GPIOSysPin::GPIO7
	};

	return map[static_cast<int>(pin)];
}

void sys_gpio::set_mode(GPIOSysPin pin, GPIOPinMode mode)
{
	std::stringstream str;
	str << "sudo gpio export "<< static_cast<int>(pin) << " " << (mode==GPIOPinMode::modIN?"in":"out");
	std::cout << "Настройка порта: " << str.str() << std::endl;
	system(str.str().c_str());
}

void sys_gpio::set_PUD(gpio::GPIOPin pin, PUD pud)
{
	std::stringstream str;
	str << "sudo gpio mode "<< static_cast<int>(pin) << " ";
	switch(pud)
	{
	case PUD::Up: str << "up"; break;
	case PUD::Down: str << "down"; break;
	case PUD::Off: str << "tri"; break;
	default: return;
	}
	std::cout << "Настройка Pull Up/Down режима резистора: " << str.str() << std::endl;
	system(str.str().c_str());
}

void pinWrite(gpio::GPIOPin pin, GPIOLevel level)
{
	//std::cout << "Меняем уровень " << pin << "=" << level << std::endl;
	digitalWrite(static_cast<int>(pin), static_cast<int>(level));
}

void pinPWMWrite(gpio::GPIOPin pin, int freq)
{
	pwmWrite(static_cast<int>(pin), freq);

}

}

