#include "hwbp_core.h"
#include "hwbp_core_regs.h"
#include "hwbp_core_types.h"

#include "app.h"
#include "app_funcs.h"
#include "app_ios_and_regs.h"

#include "data_stream.h"
#define F_CPU 32000000
#include <util/delay.h>

/************************************************************************/
/* Declare application registers                                        */
/************************************************************************/
extern AppRegs app_regs;
extern uint8_t app_regs_type[];
extern uint16_t app_regs_n_elements[];
extern uint8_t *app_regs_pointer[];
extern void (*app_func_rd_pointer[])(void);
extern bool (*app_func_wr_pointer[])(void*);

/************************************************************************/
/* Initialize app                                                       */
/************************************************************************/
static const uint8_t default_device_name[] = "MyHarpDevice";

void hwbp_app_initialize(void)
{
    /* Define versions */
    uint8_t hwH = 1;
    uint8_t hwL = 0;
    uint8_t fwH = 1;
    uint8_t fwL = 0;
    uint8_t ass = 0;
    
   	/* Start core */
    core_func_start_core(
        2080,
        hwH, hwL,
        fwH, fwL,
        ass,
        (uint8_t*)(&app_regs),
        APP_NBYTES_OF_REG_BANK,
        APP_REGS_ADD_MAX - APP_REGS_ADD_MIN + 1,
        default_device_name
    );
}

/************************************************************************/
/* Handle if a catastrophic error occur                                 */
/************************************************************************/
void core_callback_catastrophic_error_detected(void)
{
	
}

/************************************************************************/
/* User functions                                                       */
/************************************************************************/
/* Add your functions here or load external functions if needed */
void update_LED_array(void)
{
	if (core_bool_is_visual_enabled())
	{
		if (read_CLOCK_OUT_EN)  {clr_LED_SLAVE; set_LED_MASTER;}
		if (read_CLOCK_IN_EN)   {set_LED_SLAVE; clr_LED_MASTER;}
		if (read_IO0) set_LED_IO0; else clr_LED_IO0;
		if (read_IO0) set_LED_IO1; else clr_LED_IO1;
		if (read_IO0) set_LED_IO2; else clr_LED_IO2;
	}
}

/************************************************************************/
/* Initialization Callbacks                                             */
/************************************************************************/
#define T_STARTUP_ON  100
#define T_STARTUP_OFF 0
void core_callback_1st_config_hw_after_boot(void)
{
	/* Initialize IOs */
	/* Don't delete this function!!! */
	init_ios();
	
	/* Initialize hardware */
	//set_LED_POWER;
	//_delay_ms(1000);
	//clr_LED_POWER;
	
	for (uint8_t i = 0; i < 2; i++)
	{
		set_LED_CLKIN;  _delay_ms(T_STARTUP_ON); clr_LED_CLKIN;  _delay_ms(T_STARTUP_OFF);
		set_LED_IO0;    _delay_ms(T_STARTUP_ON); clr_LED_IO0;    _delay_ms(T_STARTUP_OFF);
		set_LED_IO1;    _delay_ms(T_STARTUP_ON); clr_LED_IO1;    _delay_ms(T_STARTUP_OFF);
		set_LED_IO2;    _delay_ms(T_STARTUP_ON); clr_LED_IO2;    _delay_ms(T_STARTUP_OFF);
		set_LED_SLAVE;  _delay_ms(T_STARTUP_ON); clr_LED_SLAVE;  _delay_ms(T_STARTUP_OFF);
		set_LED_MASTER; _delay_ms(T_STARTUP_ON); clr_LED_MASTER; _delay_ms(T_STARTUP_OFF);
		set_LED_STATE;  _delay_ms(T_STARTUP_ON); clr_LED_STATE;  _delay_ms(T_STARTUP_OFF);
		set_LED_POWER;  _delay_ms(T_STARTUP_ON); clr_LED_POWER;  _delay_ms(T_STARTUP_OFF);
	}
	_delay_ms(200);
	
	for (uint8_t i = 0; i < 2; i++)
	{
		set_LED_CLKIN; set_LED_IO0;    set_LED_IO1;   set_LED_IO2;
		set_LED_SLAVE; set_LED_MASTER; set_LED_STATE; set_LED_POWER;
		_delay_ms(200);
	
		clr_LED_CLKIN; clr_LED_IO0;    clr_LED_IO1;   clr_LED_IO2;
		clr_LED_SLAVE; clr_LED_MASTER; clr_LED_STATE; clr_LED_POWER;
		_delay_ms(200);
	}
	
	_delay_ms(500);
	set_LED_POWER;
}

void core_callback_reset_registers(void)
{
	/* Initialize registers */
	app_regs.REG_CONFIG  = B_SYNC_TO_MASTER | B_ANA_SENSOR_TO_AO | B_EN_AI;
	app_regs.REG_CONFIG |= B_COM_TO_MAIN    | B_IO1_TO_OUTPUT    | B_IO2_TO_OUTPUT;
	app_regs.REG_CONFIG |= B_DATA_1Khz;
	
	app_regs.REG_INPUT_IO0_CONFIG = GM_INPUT_SENSE_BOTH;
	app_regs.REG_INPUT_IO1_CONFIG = GM_INPUT_SENSE_BOTH;
	app_regs.REG_INPUT_IO2_CONFIG = GM_INPUT_SENSE_BOTH;
	
	app_regs.REG_OUTPUT_WRITE = 0;	
	
	app_regs.REG_ANA_SENSOR_TH0_HIGH = 2500;
	app_regs.REG_ANA_SENSOR_TH0_HIGH_MS = 1;
	app_regs.REG_ANA_SENSOR_TH0_LOW = 1500;
	app_regs.REG_ANA_SENSOR_TH0_LOW_MS = 1;
	app_regs.REG_ANA_SENSOR_TH0_EVT_CONF = GM_TH_NOT_USED;
	app_regs.REG_ANA_SENSOR_TH1_HIGH = 2;
	app_regs.REG_ANA_SENSOR_TH1_HIGH_MS = 1;
	app_regs.REG_ANA_SENSOR_TH1_LOW = 0;
	app_regs.REG_ANA_SENSOR_TH1_LOW_MS = 1;
	app_regs.REG_ANA_SENSOR_TH1_EVT_CONF = GM_TH_NOT_USED;
	app_regs.REG_ANA_INPUT_TH0_HIGH = 2500;
	app_regs.REG_ANA_INPUT_TH0_HIGH_MS = 1;
	app_regs.REG_ANA_INPUT_TH0_LOW = 1500;
	app_regs.REG_ANA_INPUT_TH0_LOW_MS = 1;
	app_regs.REG_ANA_INPUT_TH0_EVT_CONF = GM_TH_NOT_USED;
	app_regs.REG_ANA_INPUT_TH1_HIGH = 2;
	app_regs.REG_ANA_INPUT_TH1_HIGH_MS = 1;
	app_regs.REG_ANA_INPUT_TH1_LOW = 0;
	app_regs.REG_ANA_INPUT_TH1_LOW_MS = 1;
	app_regs.REG_ANA_INPUT_TH1_EVT_CONF = GM_TH_NOT_USED;
	app_regs.REG_ENCODER_TH0_HIGH = 2;
	app_regs.REG_ENCODER_TH0_HIGH_MS = 1;
	app_regs.REG_ENCODER_TH0_LOW = 0;
	app_regs.REG_ENCODER_TH0_LOW_MS = 1;
	app_regs.REG_ENCODER_TH0_EVT_CONF = GM_TH_NOT_USED;
	app_regs.REG_ENCODER_TH1_HIGH = 2;
	app_regs.REG_ENCODER_TH1_HIGH_MS = 1;
	app_regs.REG_ENCODER_TH1_LOW = 0;
	app_regs.REG_ENCODER_TH1_LOW_MS = 1;
	app_regs.REG_ENCODER_TH1_EVT_CONF = GM_TH_NOT_USED;
	
	app_regs.REG_WRITE_AO = 0;
	app_regs.REG_ENCODER = 0;
	 
	app_regs.REG_TH_ENABLE_EVENTS = 0;
}

void core_callback_registers_were_reinitialized(void)
{
	/* Update registers*/
	app_write_REG_CONFIG(&app_regs.REG_CONFIG);
	
	app_regs.REG_DATA_STREAM[0] = 0;
	app_regs.REG_DATA_STREAM[1] = 0;
	app_regs.REG_DATA_STREAM[2] = 0;
	app_regs.REG_DATA_STREAM[3] = 0;	
	
	app_write_REG_OUTPUT_WRITE(&app_regs.REG_OUTPUT_WRITE);	
	
	app_write_REG_WRITE_AO(&app_regs.REG_WRITE_AO);	
}

/************************************************************************/
/* Callbacks: Visualization                                             */
/************************************************************************/
void core_callback_visualen_to_on(void)
{
	/* Update visual indicators */
	if (read_CLOCK_OUT_EN)	{set_LED_MASTER; clr_LED_SLAVE;}
	if (read_CLOCK_IN_EN)	{clr_LED_MASTER; set_LED_SLAVE;}
	if(read_IO0) set_LED_IO0; else clr_LED_IO0;
	if(read_IO1) set_LED_IO1; else clr_LED_IO1;
	if(read_IO2) set_LED_IO2; else clr_LED_IO2;
	set_LED_POWER;
}

void core_callback_visualen_to_off(void)
{
	/* Clear all the enabled indicators */
	clr_LED_CLKIN; clr_LED_IO0;    clr_LED_IO1;   clr_LED_IO2;
	clr_LED_SLAVE; clr_LED_MASTER; clr_LED_POWER;
}

/************************************************************************/
/* Callbacks: Change on the operation mode                              */
/************************************************************************/
void core_callback_device_to_standby(void) {}
void core_callback_device_to_active(void) {}
void core_callback_device_to_enchanced_active(void) {}
void core_callback_device_to_speed(void) {}

/************************************************************************/
/* Callbacks: 1 ms timer                                                */
/************************************************************************/
uint8_t countdown_init_ana_sensor = 3;

void core_callback_t_before_exec(void) {}
void core_callback_t_after_exec(void) {}

void core_callback_t_new_second(void)
{
	if(countdown_init_ana_sensor == 0)
	{		
		/* Launch the photodiode acquisition in 256 us */
		//timer_type1_enable(&TCE1, TIMER_PRESCALER_DIV1024, 8, INT_LEVEL_LOW);		
	}
	else
	{
		countdown_init_ana_sensor--;
	}

}

uint8_t update_leds_counter;

void core_callback_t_500us(void)
{
	if (update_leds_counter++ & 0x10)	// Update LEDs each 16 ms
	{	
		if (core_bool_is_visual_enabled())
		{
			if (read_CLOCK_OUT_EN)  {clr_LED_SLAVE; set_LED_MASTER;}
			if (read_CLOCK_IN_EN)   {set_LED_SLAVE; clr_LED_MASTER;}
			if (read_IO0) set_LED_IO0; else clr_LED_IO0;
			if (read_IO1) set_LED_IO1; else clr_LED_IO1;
			if (read_IO2) set_LED_IO2; else clr_LED_IO2;
		}
	}   
}

void core_callback_t_1ms(void)
{
	START_ACCUMULATOR_TIMER;
	
	/* Trigger ADC read */
	if (ADCA_CTRLA != 0)
	{
		ADCA_CH0_MUXCTRL = 0;				// Select pin
		ADCA_CH0_CTRL |= ADC_CH_START_bm;	// Start conversion
	}
	
	/*
	set_ADC_CNVST;
	set_ADC_CNVST;
	clr_ADC_CNVST;
	timer_type1_enable(&TCD1, TIMER_PRESCALER_DIV1,  ACCUMULATOR_INTERVAL_uS_FLOAT * 32,   INT_LEVEL_LOW);
	*/
}

/************************************************************************/
/* Callbacks: uart control                                              */
/************************************************************************/
void core_callback_uart_rx_before_exec(void) {}
void core_callback_uart_rx_after_exec(void) {}
void core_callback_uart_tx_before_exec(void) {}
void core_callback_uart_tx_after_exec(void) {}
void core_callback_uart_cts_before_exec(void) {}
void core_callback_uart_cts_after_exec(void) {}

/************************************************************************/
/* Callbacks: Read app register                                         */
/************************************************************************/
bool core_read_app_register(uint8_t add, uint8_t type)
{
	/* Check if it will not access forbidden memory */
	if (add < APP_REGS_ADD_MIN || add > APP_REGS_ADD_MAX)
		return false;
	
	/* Check if type matches */
	if (app_regs_type[add-APP_REGS_ADD_MIN] != type)
		return false;
	
	/* Receive data */
	(*app_func_rd_pointer[add-APP_REGS_ADD_MIN])();	

	/* Return success */
	return true;
}

/************************************************************************/
/* Callbacks: Write app register                                        */
/************************************************************************/
bool core_write_app_register(uint8_t add, uint8_t type, uint8_t * content, uint16_t n_elements)
{
	/* Check if it will not access forbidden memory */
	if (add < APP_REGS_ADD_MIN || add > APP_REGS_ADD_MAX)
		return false;
	
	/* Check if type matches */
	if (app_regs_type[add-APP_REGS_ADD_MIN] != type)
		return false;

	/* Check if the number of elements matches */
	if (app_regs_n_elements[add-APP_REGS_ADD_MIN] != n_elements)
		return false;

	/* Process data and return false if write is not allowed or contains errors */
	return (*app_func_wr_pointer[add-APP_REGS_ADD_MIN])(content);
}