#ifndef   __RPI_CXX_H__
#define   __RPI_CXX_H__

#include<wiringPi.h>
#include<algorithm>
#include<iostream>
#include<stdexcept>
#include<string>
#include<utility>
#include<unistd.h>

namespace rpi_cxx
{
class gpio;
class sys_gpio;

template<typename cont_inout, typename cont_pud>
void init_gpio(const cont_inout& inout, const cont_pud& pud)
{
	if(geteuid () != 0)//не рут
		sys_gpio(inout, pud);
	else
		gpio(inout,pud);
}

enum class GPIOPinMode
{
	modIN=INPUT,
	modOUT=OUTPUT
};

enum class PUD
{
	Off=PUD_OFF,
	Down=PUD_DOWN,
	Up=PUD_UP
};

class gpio
{
public:
	enum class GPIOPin
	{
		GPIO0,
		GPIO1,
		GPIO2,
		GPIO3,
		GPIO4,
		GPIO5,
		GPIO6,
		GPIO7,
		GPIO21=21,
		GPIO22,
		GPIO23,
		GPIO24,
		GPIO25,
		GPIO26,
		GPIO27,
		GPIO28,
		GPIO29,
		GPIOMAX
	};

	template<typename cont_inout, typename cont_pud>
	gpio(const cont_inout& inout, const cont_pud& pud);

	static void set_mode(GPIOPin pin, GPIOPinMode mode);
	static void set_PUD(GPIOPin pin,PUD pud);
};

std::ostream &&operator<< (std::ostream &str, gpio::GPIOPin pin);
std::ostream &&operator<< (std::ostream &str, GPIOPinMode mode);
std::ostream &&operator<< (std::ostream &str, PUD pud);

class sys_gpio
{
public:
	enum class GPIOSysPin
		{
			GPIO0=17,
			GPIO1=18,
			GPIO2=27,
			GPIO3=22,
			GPIO4=23,
			GPIO5=24,
			GPIO6=25,
			GPIO7=4,
			GPIO21=5,
			GPIO22=6,
			GPIO23=13,
			GPIO24=19,
			GPIO25=26,
			GPIO26=12,
			GPIO27=16,
			GPIO28=20,
			GPIO29=21
		};
	static GPIOSysPin toGPIOSysPin(gpio::GPIOPin pin);

	template<typename cont_inout, typename cont_pud>
	sys_gpio(const cont_inout& inout, const cont_pud& pud);
	static void set_mode(GPIOSysPin pin, GPIOPinMode mode);
	static void set_PUD(gpio::GPIOPin pin, PUD mode);

};

template<typename T>
gpio::GPIOPin unpackPin(T& pack)
{
	return pack.first;
}

template<typename T>
GPIOPinMode unpackMode(T& pack)
{
	return pack.second;
}

template<typename T>
PUD unpackPUD(T& pack)
{
	return pack.second;
}


std::ostream &&operator<< (std::ostream &str, sys_gpio::GPIOSysPin pin);

template<typename cont_inout, typename cont_pud>
gpio::gpio(const cont_inout& inout, const cont_pud& pud)
{
	if(wiringPiSetup() == -1)
	{
		throw std::runtime_error("Ошибка инициализации wiringPiSetup");
	}
	using namespace std::placeholders;
	std::for_each(inout.begin(), inout.end(),
			[](const typename cont_inout::value_type& i)
			{
				gpio::set_mode(unpackPin(i),unpackMode(i));
			});
	std::for_each(pud.begin(), pud.end(),
			[](const typename cont_pud::value_type& pud)
			{
				gpio::set_PUD(unpackPin(pud),unpackPUD(pud));
			});
	system("gpio readall");
}

template<typename cont_inout, typename cont_pud>
sys_gpio::sys_gpio(const cont_inout& inout, const cont_pud& pud)
{
	system("sudo gpio unexportall");
	std::cout << "Порты сброшены" << std::endl;
	using namespace std::placeholders;
	std::for_each(inout.begin(), inout.end(),
			[](const typename cont_inout::value_type& i)
			{
				sys_gpio::set_mode(toGPIOSysPin(unpackPin(i)),unpackMode(i));
			});

	delay (500) ;
	wiringPiSetupSys();
	std::for_each(pud.begin(), pud.end(),
			[](const typename cont_pud::value_type& pud)
			{
				sys_gpio::set_PUD(unpackPin(pud),unpackPUD(pud));
			});
	system("gpio readall");
}

namespace
{
static std::vector<std::function<void()>> irsHandlers(static_cast<size_t>(gpio::GPIOPin::GPIOMAX));

template<size_t i>
void packHandler()
{
	if(irsHandlers.size()<i)
	{
		std::cout << "Ошибка вызова обработчика IRS #" << i << std::endl;
		return;
	}
	irsHandlers[i]();
}


}



template<size_t pin, typename function>
void setHadlerISR(function f)
{
	irsHandlers.at(pin)=std::move(f);
	if(wiringPiISR(pin, INT_EDGE_BOTH, static_cast<void(*)()>(packHandler<pin>)) < 0)
				throw std::runtime_error("ISR setup error");
}

enum class GPIOLevel
{
	low=LOW,
	hi=HIGH
};

void pinWrite(gpio::GPIOPin pin, GPIOLevel level);

};

#endif
