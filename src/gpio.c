#include "gpio.h"

//gpio regs address
#define PINS_PER_PORT 16

//configuration bits
#define MODE_BIT0 0x1
#define MODE_BIT1 0x2
#define CNF_BIT0  0x4
#define CNF_BIT1  0x8

//port register offsets (32 bits per increment)
#define CRL_OFFSET  0
#define CRH_OFFSET  1
#define IDR_OFFSET  2
#define ODR_OFFSET  3
#define BSRR_OFFSET 4
#define BRR_OFFSET  5
#define LCKR_OFFSET 6

uint GPIO_PORT_ADDRS[] = 
{
    0x40010800, //PORT A
    0x40010C00,
    0x40011000,
    0x40011400, //...
    0x40011800,
    0x40011C00,
    0x40012000  //PORT G
};

//helper functions
int _check_pin_num(uint pin_num){
    if(pin_num < 0 || pin_num > PINS_PER_PORT - 1){
        return 0;
    }
    return 1;
}

//public functions
int gpio_config_port(GpioPort port, GpioConfig* config){
    uint* port_addr = (uint*)GPIO_PORT_ADDRS[port];
    uint* crl_addr = port_addr + CRL_OFFSET;
    uint* crh_addr = port_addr + CRH_OFFSET;

    volatile uint* odr_reg_addr = port_addr + ODR_OFFSET;
    uint conf_val = 0x0;

    switch(config->pin_mode){
        case INPUT:
            switch(config->pin_config.input){
                case ANALOG: break;
                case FLOATING:
                    conf_val |= CNF_BIT0;
                    break;
                case PULL_DOWN:
                    conf_val |= CNF_BIT1;
                    *odr_reg_addr &= ~(config->pin_mask);
                    break;
                case PULL_UP:
                    conf_val |= CNF_BIT1;
                    *odr_reg_addr |= config->pin_mask;
                    break;
            }
        case OUTPUT:
            if(config->pin_config.output.driver == OPEN_DRAIN){
                conf_val |= CNF_BIT0;
            }
            if(config->pin_config.output.mode == ALT_FUNC){
                conf_val |= CNF_BIT1;
            }
            switch(config->pin_config.output.speed){
                case MAX_10MHZ:
                    conf_val |= MODE_BIT0;
                    break;
                case MAX_2MHZ:
                    conf_val |= MODE_BIT1;
                    break;
                case MAX_50MHZ:
                    conf_val |= MODE_BIT0;
                    conf_val |= MODE_BIT1;
                    break;
            }
            break;
        default:
            break; 
    }

    int pin_num = 0;
    unsigned short curr_mask = config->pin_mask;

    //apply requested configuration to all specified pins in config->pin_mask
    while(curr_mask != 0){
        if(curr_mask & 1){
            uint clear_mask = ~((uint)0xF << (4 * (pin_num % 8)));
            if(pin_num > (PINS_PER_PORT / 2) - 1){
                *crh_addr &= clear_mask; 
                *crh_addr |= (conf_val << (4 * (pin_num - 8)));
            }
            else{
                *crl_addr &= clear_mask; 
                *crl_addr |= (conf_val << (4 * pin_num));
            }
        }
        curr_mask >>= 1;
        pin_num++;
    }
    return 0;
}

int gpio_set_pin(GpioPort port, int pin_num, PinState state){
    if(!_check_pin_num(pin_num)){
        return 1; 
    }

    volatile uint* bsrr_addr = (uint*)(GPIO_PORT_ADDRS[port]) + BSRR_OFFSET;

    if(state == HIGH){
        *bsrr_addr = 1 << pin_num;
    }
    else{
        *bsrr_addr = 1 << (pin_num + PINS_PER_PORT);
    }
    return 0;
}

PinState gpio_read_pin(GpioPort port, int pin_num){
    if(!_check_pin_num(pin_num)){
        return -1;
    }

    volatile uint* idr_addr = (uint*)(GPIO_PORT_ADDRS[port]) + IDR_OFFSET;
    if(*idr_addr & (1 << pin_num)){
        return HIGH;
    }
    else{
        return LOW;
    }
}