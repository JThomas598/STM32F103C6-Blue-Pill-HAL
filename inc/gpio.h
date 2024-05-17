#include "types.h"

//pin masks
#define GPIO_PIN_0  1
#define GPIO_PIN_1  1 << 1
#define GPIO_PIN_2  1 << 2
#define GPIO_PIN_3  1 << 3
#define GPIO_PIN_4  1 << 4
#define GPIO_PIN_5  1 << 5
#define GPIO_PIN_6  1 << 6
#define GPIO_PIN_7  1 << 7
#define GPIO_PIN_8  1 << 8
#define GPIO_PIN_9  1 << 9
#define GPIO_PIN_10 1 << 10
#define GPIO_PIN_11 1 << 11
#define GPIO_PIN_12 1 << 12
#define GPIO_PIN_13 1 << 13
#define GPIO_PIN_14 1 << 14
#define GPIO_PIN_15 1 << 15

//output driver enum
typedef enum GpioOutputDriver{
    PUSH_PULL,
    OPEN_DRAIN
}GpioOutputDriver;

//output mode enum
typedef enum GpioOutputFunc{
    DEFAULT,
    ALT_FUNC
}GpioOutputFunc;

//output mode enum
typedef enum GpioOutputSpeed{
    MAX_2MHZ,
    MAX_10MHZ,
    MAX_50MHZ
}GpioOutputSpeed;

//output config struct
typedef struct GpioOutputConfig{
    GpioOutputDriver driver;
    GpioOutputFunc   mode;
    GpioOutputSpeed  speed;
}GpioOutputConfig;

//input mode enum
typedef enum GpioInputConfig{
    ANALOG,
    FLOATING,
    PULL_DOWN,
    PULL_UP 
}GpioInputConfig;

//pin config union
typedef union GpioPinConfig{
    GpioOutputConfig output;
    GpioInputConfig  input;
}GpioPinConfig;

//gpio pin mode
typedef enum GpioPinMode{
    INPUT,
    OUTPUT
}GpioPinMode;

//gpio port enum
typedef enum GpioPort{
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G
}GpioPort;

//gpio configuration struct
typedef struct GpioConfig{
    unsigned short pin_mask; 
    GpioPinMode    pin_mode;
    GpioPinConfig  pin_config;
}GpioConfig;

//pin output state enum
typedef enum PinState{
   HIGH,
   LOW 
}PinState;

//declarations
int gpio_config_port(GpioPort port, GpioConfig* config);

int gpio_set_pin(GpioPort port, int pin_num, PinState state);

PinState gpio_read_pin(GpioPort port, int pin_num);