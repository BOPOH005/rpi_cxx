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


namespace rpi_cxx {

static const size_t GPIO_BASE(0x20200000);
static const size_t BLOCK_SIZE(4*1024);

bcm2835::bcm2835():
		mem_fd_(open("/dev/mem", O_RDWR | O_SYNC)),
		p_map_(mmap(
				nullptr,
				BLOCK_SIZE,
				PROT_READ|PROT_WRITE,
				MAP_SHARED,
				mem_fd_.get(),      // File descriptor to physical memory virtual file '/dev/mem'
				GPIO_BASE))
{
	if ( mem_fd_.get() == nullptr) {
		static const std::string err(std::strerror(errno)+std::string(" /Failed to open /dev/mem"));
		std::cerr << err << std::endl;
		throw std::runtime_error(err);
	}

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

//void bcm2835::setPinModeIn(pin p)
//{
//
//}

GPIO_REGS& bcm2835::get_Regs()
{
	return *static_cast<GPIO_REGS*>(p_map_.get());
}

} /* namespace rpi_cxx */
