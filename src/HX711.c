#include "HX711.h"

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"

#include <stdint.h>
#include <stdbool.h>


static uint_fast8_t counter;
static int32_t values[8];

static void timerFunc(void *timer_arg) {
    HX711 * obj = (HX711*)timer_arg;
    HX711_tick(obj);
}

static inline void set_clock(bool high) {
    if(true == high)
        // gpio_output_set(BIT12, 0, BIT12, 0);  // 12 high
        gpio_output_set(BIT5, 0, BIT5, 0);  // 5 high
    else
        // gpio_output_set(0, BIT12, BIT12, 0);  // 12 low
        gpio_output_set(0, BIT5, BIT5, 0);  // 5 low
}

static inline uint_fast8_t get_dout(void) {
    // return GPIO_INPUT_GET(13);
    return GPIO_INPUT_GET(4);
}

void HX711_init(HX711 * obj) {
    // //gpio init
    // PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO12);
    // PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U,FUNC_GPIO13);

    // GPIO_DIS_OUTPUT(13);
    // PIN_PULLUP_EN(PERIPHS_IO_MUX_MTCK_U);
        //gpio init
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO5);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U,FUNC_GPIO4);

    GPIO_DIS_OUTPUT(4);
    PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO4_U);

    set_clock(false); //low

    //timer init
    static os_timer_t timer;

	os_timer_disarm(&timer);
	os_timer_setfn(&timer, (os_timer_func_t*)timerFunc, obj);
	os_timer_arm(&timer, 100, 1);

    // init variables  
    memset(values,0,sizeof(values));
    counter = 0;
}

static inline int getValue(void) {
    uint32_t value = 0;

    for(uint32_t i = 0; i <= 24; i++) {
        os_delay_us(1);
        set_clock(true);
        os_delay_us(1);
        value = value << 1;
        value |= get_dout();
        set_clock(false);
    }
    if( 0 != (value & 0x800000)) // value is 24 bit int extend highest 8 bits.
        value |= 0xff000000;
    
    // one extra clock for Gain 128
    for(uint32_t i = 0; i <= 3; i++) {
        os_delay_us(1);
        set_clock(true);
        os_delay_us(1);
        set_clock(false);
    }
    return (int)value;
}

void HX711_tick(HX711 * obj) {

    if(0 != get_dout())
        return;

    int32_t value = getValue();

    values[counter] = value;
    counter++;
    if(counter >= (sizeof(values) / sizeof(values[0] )) ) {
        value = 0;
        for(uint_fast8_t i = 0; i < (sizeof(values) / sizeof(values[0])) ; i++ ) {
            value += values[i];
        }
        value /= (sizeof(values) / sizeof(values[0]));
        obj->new_value_callback(value, obj->new_value_callback_obj);
        counter = 0;
    }
}
