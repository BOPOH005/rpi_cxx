/*
 * bcm2835.cpp
 *
 *  Created on: 18.09.2016
 *      Author: bopoh
 */

#include "bcm2835.h"
#include <iostream>
#include <stdexcept>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <chrono>
#include <thread>
#include <iomanip>
#include <bitset>


using namespace std::this_thread;
using namespace std::chrono;

namespace rpi_cxx {
static const size_t RASPBERRY_PI_PERI_BASE(0x3F000000);
static const size_t GPIO_BASE(RASPBERRY_PI_PERI_BASE+0x200000);
static const size_t BLOCK_SIZE(4*1024);

bcm2835::bcm2835()
{
	auto file=open("/dev/gpiomem", O_RDWR | O_SYNC);
	mem_fd_.reset(file);
	if ( mem_fd_.get() < 0 ) {
		static const std::string err(std::strerror(errno)+std::string(" /Failed to open /dev/mem"));
		std::cerr << err << std::endl;
		throw std::runtime_error(err);
	}
	auto map=mmap(
				nullptr,
				BLOCK_SIZE,
				PROT_READ|PROT_WRITE,
				MAP_SHARED,
				mem_fd_.get(),      // File descriptor to physical memory virtual file '/dev/mem'
				GPIO_BASE);
	p_map_.reset(map);
	if (p_map_.get() == MAP_FAILED) {
		static const std::string err(std::strerror(errno)+std::string(" /Failed call mmap(/dev/mem)"));
		std::cerr << err << std::endl;
		throw std::runtime_error(err);
	}
}

void fcloser::operator()(int p)
{
	close(p);
}

void mcloser::operator()(void* p)
{
	munmap(p, BLOCK_SIZE);
}

bcm2835& bcm2835::instance()
{
	static bcm2835 bcm;
	return bcm;
}

volatile GPIO& bcm2835::registers()
{
	return *static_cast<volatile GPIO*>(p_map_.get());
}

void bcm2835::pullupdown(pull f, const GPIO::gpset& reg)
{
	auto& gpio=registers();
	gpio.GPPUD.fld.f=f;
	sleep_for(microseconds(10));
	gpio.GPPUDCLK.reg=reg.reg;
	sleep_for(microseconds(10));
	gpio.GPPUD.fld.f=off;
	gpio.GPPUDCLK.reg=0;
}

void bcm2835::setlevel(level l, const GPIO::gpset& reg)
{
	auto& gpio=registers();
	if(l==level::hight)
		gpio.GPSET.reg=reg.reg;
	else	
		gpio.GPCLR.reg=reg.reg;
}

void bcm2835::detect(detectmode mode, const GPIO::gpset& reg)
{
	auto& gpio=registers();
	if(mode & detectmode::RISING)
		gpio.GPREN.reg=reg.reg;
	if(mode & detectmode::FALLING)
		gpio.GPFEN.reg=reg.reg;
    if(mode & detectmode::HIGHT)
		gpio.GPHEN.reg=reg.reg;
    if(mode & detectmode::LOW)
		gpio.GPLEN.reg=reg.reg;
    if(mode & detectmode::ARISING)
		gpio.GPAREN.reg=reg.reg;
    if(mode & detectmode::AFILLING)
		gpio.GPAFEN.reg=reg.reg;
}

void bcm2835::undetect_all(detectmode mode)
{
	GPIO::gpset reg;
	auto& gpio=registers();
	if(mode & detectmode::RISING)
	{
		reg.reg|=gpio.GPREN.reg;
		gpio.GPREN.reg=0;
	}
	if(mode & detectmode::FALLING)
	{
		reg.reg|=gpio.GPFEN.reg;
		gpio.GPFEN.reg=0;
	}
    if(mode & detectmode::HIGHT)
	{
		reg.reg|=gpio.GPHEN.reg;
		gpio.GPHEN.reg=0;
	}
    if(mode & detectmode::LOW)
	{
		reg.reg|=gpio.GPLEN.reg;
		gpio.GPLEN.reg=0;
	}
    if(mode & detectmode::ARISING)
	{
		reg.reg|=gpio.GPAREN.reg;
		gpio.GPAREN.reg=0;
	}
    if(mode & detectmode::AFILLING)
	{
		reg.reg|=gpio.GPAFEN.reg;
		gpio.GPAREN.reg=0;
	}
	gpio.GPEDS.reg=reg.reg;
}

std::ostream &operator<<(std::ostream &os, const volatile GPIO::gpset &s)
{
    return os
	   << std::oct << std::setfill('0') << std::setw(64) << std::bitset<64>(s.reg) << std::endl
	   << " |0|1|2|3|4|5|6|7|8|9|" << std::endl
	   << "0|" << s.fld.p0 << "|" << s.fld.p1 << "|" << s.fld.p2 << "|" << s.fld.p3 << "|" << s.fld.p4 << "|" << s.fld.p5 << "|" << s.fld.p6 << "|" << s.fld.p7 << "|" << s.fld.p8 << "|" << s.fld.p9 << "|" << std::endl
	   << "1|" << s.fld.p10 << "|" << s.fld.p11 << "|" << s.fld.p12 << "|" << s.fld.p13 << "|" << s.fld.p14 << "|" << s.fld.p15 << "|" << s.fld.p16 << "|" << s.fld.p17 << "|" << s.fld.p18 << "|" << s.fld.p19 << "|" << std::endl
	   << "2|" << s.fld.p20 << "|" << s.fld.p21 << "|" << s.fld.p22 << "|" << s.fld.p23 << "|" << s.fld.p24 << "|" << s.fld.p25 << "|" << s.fld.p26 << "|" << s.fld.p27 << "|" << s.fld.p28 << "|" << s.fld.p29 << "|" << std::endl
	   << "3|" << s.fld.p30 << "|" << s.fld.p31 << "|" << s.fld.p32 << "|" << s.fld.p33 << "|" << s.fld.p34 << "|" << s.fld.p35 << "|" << s.fld.p36 << "|" << s.fld.p37 << "|" << s.fld.p38 << "|" << s.fld.p39 << "|" << std::endl
	   << "4|" << s.fld.p40 << "|" << s.fld.p41 << "|" << s.fld.p42 << "|" << s.fld.p43 << "|" << s.fld.p44 << "|" << s.fld.p45 << "|" << s.fld.p46 << "|" << s.fld.p47 << "|" << s.fld.p48 << "|" << s.fld.p49 << "|" << std::endl
	   << "5|" << s.fld.p50 << "|" << s.fld.p51 << "|" << s.fld.p52 << "|" << s.fld.p53 << "|" << std::endl;
}

std::ostream &operator<<(std::ostream &os, const level s)
{
    switch (s)
    {
    case level::low:
	return os << "-";
    case level::hight:
	return os << "+";
    }
    return os << std::hex << static_cast<int>(s);
}

std::ostream &operator<<(std::ostream &os, const set s)
{
    switch (s)
    {
    case set::on:
	return os << "*";
    default:
	return os << " ";
    }
}

std::ostream &operator<<(std::ostream &os, const volatile GPIO::gplev &s)
{
    return os
	   << std::oct << std::setfill('0') << std::setw(64) << std::bitset<64>(s.reg) << std::endl
	   << " |0|1|2|3|4|5|6|7|8|9|" << std::endl
	   << "0|" << s.fld.p0 << "|" << s.fld.p1 << "|" << s.fld.p2 << "|" << s.fld.p3 << "|" << s.fld.p4 << "|" << s.fld.p5 << "|" << s.fld.p6 << "|" << s.fld.p7 << "|" << s.fld.p8 << "|" << s.fld.p9 << "|" << std::endl
	   << "1|" << s.fld.p10 << "|" << s.fld.p11 << "|" << s.fld.p12 << "|" << s.fld.p13 << "|" << s.fld.p14 << "|" << s.fld.p15 << "|" << s.fld.p16 << "|" << s.fld.p17 << "|" << s.fld.p18 << "|" << s.fld.p19 << "|" << std::endl
	   << "2|" << s.fld.p20 << "|" << s.fld.p21 << "|" << s.fld.p22 << "|" << s.fld.p23 << "|" << s.fld.p24 << "|" << s.fld.p25 << "|" << s.fld.p26 << "|" << s.fld.p27 << "|" << s.fld.p28 << "|" << s.fld.p29 << "|" << std::endl
	   << "3|" << s.fld.p30 << "|" << s.fld.p31 << "|" << s.fld.p32 << "|" << s.fld.p33 << "|" << s.fld.p34 << "|" << s.fld.p35 << "|" << s.fld.p36 << "|" << s.fld.p37 << "|" << s.fld.p38 << "|" << s.fld.p39 << "|" << std::endl
	   << "4|" << s.fld.p40 << "|" << s.fld.p41 << "|" << s.fld.p42 << "|" << s.fld.p43 << "|" << s.fld.p44 << "|" << s.fld.p45 << "|" << s.fld.p46 << "|" << s.fld.p47 << "|" << s.fld.p48 << "|" << s.fld.p49 << "|" << std::endl
	   << "5|" << s.fld.p50 << "|" << s.fld.p51 << "|" << s.fld.p52 << "|" << s.fld.p53 << "|" << std::endl;
}
// void bcm2835::setmode(mode m, const GPIO::gpfsel& reg)
// {
	
// }

} /* namespace rpi_cxx */
