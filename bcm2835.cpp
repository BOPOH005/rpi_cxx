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
static const size_t RASPBERRY_PI_PERI_BASE(0x3F000000);
static const size_t GPIO_BASE(RASPBERRY_PI_PERI_BASE+0x200000);
static const size_t BLOCK_SIZE(4*1024);

bcm2835::bcm2835()
{
	auto file=open("/dev/mem", O_RDWR | O_SYNC);
	mem_fd_.reset(file);
	if ( mem_fd_.get() < 0 ) {
		static const std::string err(std::strerror(errno)+std::string(" /Failed to open /dev/mem"));
		std::cerr << err << std::endl;
		throw std::runtime_error(err);
	}
	
	std::cout << "open(/dev/mem)=" << file << std::endl;
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
	std::cout << "mmap(/dev/mem)=" << map << std::endl;
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
	return *static_cast<GPIO*>(p_map_.get());
}

} /* namespace rpi_cxx */
