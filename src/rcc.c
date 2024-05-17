#include "utilities.h"
#include "rcc.h"

//RCC Register Space Start
#define RCC_REGS_START 0x40021000

//RCC Register Addresses
#define RCC_CR        RCC_REGS_START
#define RCC_CFGR     (RCC_REGS_START + 0x04)
#define RCC_CIR      (RCC_REGS_START + 0x08)
#define RCC_APB2RSTR (RCC_REGS_START + 0x0C)
#define RCC_APB1RSTR (RCC_REGS_START + 0x10)
#define RCC_AHBENR   (RCC_REGS_START + 0x14)
#define RCC_APB2ENR  (RCC_REGS_START + 0x18)
#define RCC_APB1ENR  (RCC_REGS_START + 0x1C)
#define RCC_BDCR     (RCC_REGS_START + 0x20)
#define RCC_CSR      (RCC_REGS_START + 0x24)


int rcc_clock_power(RCC_Bus bus, uint val, PowerState state){
    volatile uint* reg = 0x00;
    switch (bus){
        case AHB:
            reg = (uint*) RCC_AHBENR;
            break;
        case APB1:
            reg = (uint*) RCC_APB1ENR;
            break;
        case APB2:
            reg = (uint*) RCC_APB2ENR;
            break;
        default: 
            return 1;
    }

    if(state == ON)
        *reg |= val;
    else
        *reg &= ~(val);
    return 0;
}
