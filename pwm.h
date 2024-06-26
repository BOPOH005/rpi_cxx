#pragma once
#include"pin.h"

namespace rpi_cxx
{

enum state
{
	disable		=0x0,
	enable  	=0x1
};

struct PWM
{
    enum useFIFO
    {
            done       =0x0, // Data register is transmitted 
            used       =0x1  //Fifo is used for transmission    
    };
    enum algorithm
    {
        MN     =0x0, // PWM algorithm is used (native "balanced" mode)
        MS     =0x1  // M/S transmission is used (standard mark:space mode)   
    };
    union __attribute__((packed, aligned(4))) 
    {
        struct 
        {
            
            state   PWEN1 :1; //Channel 1 Enable
            enum mode
            {
                PWM         =0x0,
                serialiser  =0x1
            }       MODE1 :1; //Channel 1 Mode
            enum repeatLastData 
            {
                FIFOisEmpty   =0x0,
                FIFOisNotEmpty=0x1
            }       RPTL1 :1; //Channel 1 Repeat Last Data
            level   SBIT1 :1; //Channel 1 Silence Bit
            enum polarity 
            {
                low_high   =0x0, //0=low 1=high
                high_low   =0x1  //1=low 0=high 
            }       POLA1 :1; //Channel 1 Polarity
            useFIFO USEF1 :1; //Channel 1 Use Fifo
            enum clearFIFO
            {
                //0x0 Has no effect
                clears      =0x1 // Clears FIFO 
            }       CLRF1 :1; //Clear Fifo
            algorithm       MSEN1 :1; //Channel 1 M/S Enable
            state           PWEN2 :1; //Channel 2 Enable
            mode            MODE2 :1; //Channel 2 Mode
            repeatLastData  RPTL2 :1; //Channel 2 Repeat Last Data
            level           SBIT2 :1; //Channel 2 Silence Bit
            polarity        POLA2 :1; //Channel 2 Polarity
            useFIFO         USEF2 :1; //Channel 2 Use Fifo
            u_char                 :1; //Reserved 
            algorithm       MSEN2 :1; //Channel 2 M/S Enable
            u_int32_t       :16;       //Reserved
        }           CTL;
        u_int32_t   CTL_32;
    }       ; //PWM Control 
    union __attribute__((packed, aligned(4))) 
    {
        struct 
        {
            bool FULL1 :1; //Fifo Full Flag 
            bool EMPT1 :1; //Fifo Empty Flag
            bool WERR1 :1; //Fifo Write Error Flag
            bool RERR1 :1; //Fifo Read Error Flag
            bool GAPO1 :1; //Channel 1 Gap Occurred Flag
            bool GAPO2 :1; //Channel 2 Gap Occurred Flag 
            bool GAPO3 :1; //Channel 3 Gap Occurred Flag 
            bool GAPO4 :1; //Channel 4 Gap Occurred Flag
            bool BERR :1; //Bus Error Flag
            useFIFO STA1 :1; //Channel 1 State 
            useFIFO STA2 :1; //Channel 2 State 
            useFIFO STA3 :1; //Channel 3 State 
            useFIFO STA4 :1; //Channel 4 State 
            u_int32_t   :19; //Reserved 
        }           STA;
        u_int32_t   STA_32;
    }       ;
    union __attribute__((packed, aligned(4))) 
    {
        struct 
        {
            u_int8_t  DREQ; //DMA Threshold for DREQ signal
            u_int8_t  PANIC; //DMA Threshold for PANIC signal
            u_int16_t :15; //Reserved
            state   ENAB :1;//DMA Enable
        }           DMAC;
        u_int32_t   DMAC_32;
    }       ;
    u_int32_t   :32;
    u_int32_t   RNG1; // Channel 1 Range
    u_int32_t   DAT1; // Channel 1 Data 
    u_int32_t   FIF1; // Channel FIFO Input
    u_int32_t   :32;
    u_int32_t   RNG2; // Channel 2 Range
    u_int32_t   DAT2; // Channel 2 Data
};


struct CM_PWM
{
    u_int32_t dword[40];
    union __attribute__((packed, aligned(4))) 
    {
        struct
        {
            unsigned SRC        :4;
            unsigned ENAB       :1;
            unsigned KILL       :1;
            unsigned            :1;
            const unsigned BUSY :1;
            unsigned FLIP       :1;
            unsigned MASH       :2;
            unsigned            :13;
            unsigned PASSWD     :8;
        }   CTL;
        u_int32_t CTL_32;
    };
    union __attribute__((packed, aligned(4))) 
    {
        struct
        {
            unsigned DIVF       :12;
            unsigned DIVI       :12;
            unsigned PASSWD     :8;
        } DIV;
        u_int32_t DIV_32;
    };
};

typedef u_int8_t pwnN;    

const u_int32_t PWM_CLK_PASSWORD=0x5a000000;
const u_int32_t PLL_FREQUENCY=500000000; // default PLLD value is 500 [MHz]
const u_int32_t CM_FREQUENCY=25000000;   // max pwm clk is 25 [MHz]
const u_int32_t PLL_CLOCK_DIVISOR(PLL_FREQUENCY / CM_FREQUENCY);

template<pwnN p>  
class pwn_regs
{
public:
    pwn_regs(PWM::algorithm alg=PWM::algorithm::MS):
        regs_(bcm2835::instance().registers<PWM>()),
        cm_(bcm2835::instance().registers<CM_PWM>()) 
        {
            cm_.CTL_32=0;
            cm_.CTL_32=PWM_CLK_PASSWORD|0x20; // Turn off clock generator
            while(cm_.CTL.BUSY);
            cm_.CTL_32=PWM_CLK_PASSWORD|0x206; // Src = unfiltered 500 MHz CLKD

            cm_.DIV_32=PWM_CLK_PASSWORD|(PLL_CLOCK_DIVISOR << 12); // PWM Freq = 25 MHz
            cm_.CTL_32= cm_.CTL_32|PWM_CLK_PASSWORD|0x10;    // Enable PWM clock
            while (!cm_.CTL.BUSY);    // Wait for generator to start    
   
            regs_.CTL_32=0; 

            setAlgorithm(alg);
            enable();
        }
    ~pwn_regs(){disable();}

    void    setAlgorithm(PWM::algorithm a);
    void    setRange(u_int32_t r);
    void    enable();
    void    disable();
    pwn_regs<p>&    operator=(u_int32_t data){regs_.DAT1=data;return *this;}


private:

    volatile PWM	&regs_;
    volatile CM_PWM	&cm_;
};

template<pinN p, pwnN pw, mode alt>
struct pwn_pin_cfg
{
    const static pinN gpio=p;
    const static pwnN pwn=pw;  
    const static mode fun=alt;
};

typedef pwn_pin_cfg<12, 1, mode::fun0> pwn_12;
typedef pwn_pin_cfg<13, 2, mode::fun0> pwn_13;
typedef pwn_pin_cfg<18, 1, mode::fun5> pwn_18;
typedef pwn_pin_cfg<19, 2, mode::fun5> pwn_19;
typedef pwn_pin_cfg<40, 1, mode::fun0> pwn_40;
typedef pwn_pin_cfg<41, 2, mode::fun0> pwn_41;
typedef pwn_pin_cfg<45, 2, mode::fun0> pwn_45;


template<typename T>  
class pwn_gpio
{
public:
    pwn_gpio(PWM::algorithm alg=PWM::algorithm::MS):pin(T::fun),pwn(alg){}
    
    void            setRange(u_int32_t r){pwn.setRange(r);}
    pwn_gpio<T>&    operator=(u_int32_t data){pwn=data;return *this;}

private:
    gpio<T::gpio>       pin;
    pwn_regs<T::pwn>    pwn;
};

}


