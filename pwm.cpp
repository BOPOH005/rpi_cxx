#include"pwm.h"

namespace rpi_cxx
{
template<>
void    pwn_regs<1>::setAlgorithm(PWM::algorithm a)
{
    regs_.CTL.MSEN1=a;
}

template<>
void    pwn_regs<2>::setAlgorithm(PWM::algorithm a)
{
    regs_.CTL.MSEN2=a;
}

template<>
void    pwn_regs<1>::setRange(u_int32_t r)
{
    regs_.RNG1=r;
}

template<>
void    pwn_regs<2>::setRange(u_int32_t r)
{
    regs_.RNG2=r;
}

template<>
void    pwn_regs<1>::enable()
{
    regs_.CTL.PWEN1=state::enable;
}

template<>
void    pwn_regs<2>::enable()
{
    regs_.CTL.PWEN2=state::enable;
}

template<>
void    pwn_regs<1>::disable()
{
    regs_.CTL.PWEN1=state::disable;
}

template<>
void    pwn_regs<2>::disable()
{
    regs_.CTL.PWEN2=state::disable;
}


}
