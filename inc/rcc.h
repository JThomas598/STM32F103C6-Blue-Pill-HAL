#include "types.h"

//APB2 Enable Masks
#define APB2_AFIO_EN   1
#define APB2_IOPA_EN   1 << 2
#define APB2_IOPB_EN   1 << 3
#define APB2_IOPC_EN   1 << 4
#define APB2_IOPD_EN   1 << 5
#define APB2_IOPE_EN   1 << 6 
#define APB2_IOPF_EN   1 << 7 
#define APB2_IOPG_EN   1 << 8
#define APB2_ADC1_EN   1 << 9
#define APB2_ADC2_EN   1 << 10
#define APB2_TIM1_EN   1 << 11
#define APB2_SPI1_EN   1 << 12 
#define APB2_TIM8_EN   1 << 13 
#define APB2_USART1_EN 1 << 14
#define APB2_ADC3_EN   1 << 15
#define APB2_TIM9_EN   1 << 19
#define APB2_TIM10_EN  1 << 20
#define APB2_TIM11_EN  1 << 21

//Power State Enumerations
typedef enum PowerState{
    ON,
    OFF
}PowerState;

//Bus Select Enumerations
typedef enum RCC_Bus{
    AHB,
    APB1,
    APB2
}RCC_Bus;

//public functions
int rcc_clock_power(RCC_Bus bus, uint val, PowerState state);