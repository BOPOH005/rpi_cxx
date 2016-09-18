/*
 * bcm2835.h
 *
 *  Created on: 18.09.2016
 *      Author: bopoh
 */

#ifndef BCM2835_H_
#define BCM2835_H_

#include<memory>

namespace rpi_cxx {

struct fcloser
{
	struct pointer {
		pointer() {}
		pointer(std::nullptr_t) {}
		pointer(int handle) : value_(handle) {}

		operator int() { return value_; }

		friend bool operator==(pointer lhs, pointer rhs) { return lhs.value_ == rhs.value_; }
		friend bool operator!=(pointer lhs, pointer rhs) { return !(lhs == rhs); }

		int value_ = -1;
	};

	void operator()(int p);
};

struct mcloser	{ void operator()(void* p);typedef void* pointer;};

class bcm2835 {
public:
	bcm2835();
private:
	std::unique_ptr<int, 	fcloser>  	mem_fd;
	std::unique_ptr<void*, 	mcloser> 	p_map;
};


} /* namespace rpi_cxx */

#endif /* BCM2835_H_ */
