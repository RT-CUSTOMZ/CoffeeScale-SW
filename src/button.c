#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"


#define BUTTON_SHORT_TICK_TIME	(50000)
#define BUTTON_LONG_TICK_TIME	(500000)

#define CMD_NEXT_EFFECT 0x0001
#define CMD_PREV_EFFECT 0x0002
#define CMD_NEXT_MODULE 0x0003
#define CMD_PREV_MODULE 0x0004
#define CMD_RECORD_ON   0x0101
#define CMD_RECORD_OFF  0x0102
void cube_cmd_next_effect(uint16_t cmd_number);

static os_timer_t timer;

static bool button_state;
static uint32_t last_falling_edge_tick = 0;

static ICACHE_FLASH_ATTR void button_timer_function(void *timer_arg) {
    uint32_t state =  GPIO_INPUT_GET(2);
    if(0 == state) {
        if( 0 != button_state) {
            // falling edge
            last_falling_edge_tick = system_get_time();
        }
    }
    else {
        if(0 == button_state) {
            //rising edge
            if( (last_falling_edge_tick + BUTTON_LONG_TICK_TIME) <  system_get_time() ) {
                //long
                //cube_cmd_next_effect(CMD_RECORD_OFF);
	            os_printf("Button long\n");
            } else if ( (last_falling_edge_tick + BUTTON_SHORT_TICK_TIME) <  system_get_time() ) {
                //short tick
                //cube_cmd_next_effect(CMD_RECORD_ON);
	            os_printf("Button short\n");
            }
        }
    }
    button_state = state;
}

void ICACHE_FLASH_ATTR button_init(void) {
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2);
    GPIO_DIS_OUTPUT(2);
    PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO2_U);

    os_timer_setfn(
        &timer,
        button_timer_function,
        NULL);
    last_falling_edge_tick = system_get_time();
    os_timer_arm (
        &timer,
        10,
        true);
}

