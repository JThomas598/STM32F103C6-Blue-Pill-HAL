#include "timer.h"

uint TIMER_ADDRS[] = {

    0x40000000, //TIM2
    0x40000400,
    0x40000800,
    0x40000C00,
    0x40001000,
    0x40001400, 
    0x40013400, //...
    0x40014C00,
    0x40015000,
    0x40015400,
    0x40001800,
    0x40001C00,
    0x40002000, //TIM14
}

//register offsets
#define CR1_OFFSET     0
#define CR2_OFFSET     1
#define SMCR_OFFSET    2
#define DIER_OFFSET    3
#define SR_OFFSET      4
#define EGR_OFFSET     5
#define CCMR1_OFFSET   6
#define CCMR2_OFFSET   7
#define CCER_OFFSET    8
#define CNT_OFFSET     9
#define PSC_OFFSET     10
#define ARR_OFFSET     11
#define CCR1_OFFSET    12
#define CCR2_OFFSET    13
#define CCR3_OFFSET    14
#define CCR4_OFFSET    15
#define DCR_OFFSET     16
#define DMAR_OFFSET    17

