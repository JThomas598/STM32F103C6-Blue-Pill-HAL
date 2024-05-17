#include "rcc.h"
#include "gpio.h"

extern void _estack(void);
void _reset(void);

const void* vectors[] __attribute__ ((section (".vectors"))) = {_estack, _reset};

int main(void);


void _reset(void){
    //enable GPIO clock

    /*
    *gpioc_crh = (*gpioc_crh & ~(0xf << ((13-8)*4))) | 
		    (6 << ((13-8)* 4));

    while(1) {
        for(int i = 0; i < 500000; i++);
        *gpioc_odr ^= 1 << 13;
    }
    */
    extern long _sbss, _ebss, _sdata, _edata, _sidata;

    for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
    for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;
    main();
}

int main(){
    rcc_clock_power(APB2, APB2_IOPA_EN | APB2_IOPB_EN | APB2_IOPC_EN, ON);

    GpioConfig config;

    config.pin_mode = OUTPUT;
    config.pin_mask = GPIO_PIN_15;
    config.pin_config.output.driver = PUSH_PULL;
    config.pin_config.output.mode = DEFAULT;
    config.pin_config.output.speed = MAX_2MHZ;
    gpio_config_port(GPIO_PORT_C, &config);

    config.pin_mode = INPUT;
    config.pin_mask = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_10 | GPIO_PIN_11;
    config.pin_config.input = PULL_DOWN;
    gpio_config_port(GPIO_PORT_B, &config);

    while(1) {
        
    }
}
