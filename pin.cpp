#include "pin.h"

using namespace rpi_cxx;

pin_regs & rpi_cxx::pin::registers()
{
	pin_regs reg();
	reg.SET = bcm.registers().GPSET0.SET0;
	// TODO: вставьте здесь оператор return
}
