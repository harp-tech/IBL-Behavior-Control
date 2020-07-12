#include <avr/io.h>
#include "hwbp_core_types.h"
#include "app_ios_and_regs.h"

/************************************************************************/
/* Configure and initialize IOs                                         */
/************************************************************************/
void init_ios(void)
{	/* Configure input pins */
	io_pin2in(&PORTJ, 3, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // ADC_SDO
	io_pin2in(&PORTC, 2, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // USER
	io_pin2in(&PORTF, 1, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // IO0
	io_pin2in(&PORTK, 1, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // IO1
	io_pin2in(&PORTK, 2, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // IO2

	/* Configure input interrupts */
	io_set_int(&PORTC, INT_LEVEL_LOW, 0, (1<<2), false);                 // USER
	io_set_int(&PORTF, INT_LEVEL_LOW, 0, (1<<1), false);                 // IO0
	io_set_int(&PORTK, INT_LEVEL_LOW, 0, (1<<1), false);                 // IO1
	io_set_int(&PORTK, INT_LEVEL_LOW, 1, (1<<2), false);                 // IO2

	/* Configure output pins */
	io_pin2out(&PORTF, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // CLOCK_IN_EN
	io_pin2out(&PORTF, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // CLOCK_OUT_EN
	io_pin2out(&PORTK, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // RELAY
	io_pin2out(&PORTJ, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // ADC_SCLK
	io_pin2out(&PORTJ, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // ADC_CNVST
	io_pin2out(&PORTD, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // EN_MASTER
	io_pin2out(&PORTH, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_CLKIN
	io_pin2out(&PORTH, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_IO0
	io_pin2out(&PORTH, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_IO1
	io_pin2out(&PORTH, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_IO2
	io_pin2out(&PORTH, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_SLAVE
	io_pin2out(&PORTH, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_MASTER
	io_pin2out(&PORTA, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_STATE
	io_pin2out(&PORTJ, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_POWER
	io_pin2out(&PORTF, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // IO0
	io_pin2out(&PORTK, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // IO1
	io_pin2out(&PORTK, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // IO2
	io_pin2out(&PORTK, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // IO0_DIR
	io_pin2out(&PORTK, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // IO1_DIR
	io_pin2out(&PORTK, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // IO2_DIR

	/* Initialize output pins */
	clr_CLOCK_IN_EN;
	clr_CLOCK_OUT_EN;
	clr_RELAY;
	clr_ADC_SCLK;
	clr_ADC_CNVST;
	clr_EN_MASTER;
	clr_LED_CLKIN;
	clr_LED_IO0;
	clr_LED_IO1;
	clr_LED_IO2;
	clr_LED_SLAVE;
	clr_LED_MASTER;
	clr_LED_STATE;
	clr_LED_POWER;
	clr_IO0;
	clr_IO1;
	clr_IO2;
	clr_IO0_DIR;
	clr_IO1_DIR;
	clr_IO2_DIR;
}

/************************************************************************/
/* Registers' stuff                                                     */
/************************************************************************/
AppRegs app_regs;

uint8_t app_regs_type[] = {
	TYPE_U16,
	TYPE_I16,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U8,
	TYPE_U16,
	TYPE_U16,
	TYPE_U16,
	TYPE_U16,
	TYPE_U8,
	TYPE_U16,
	TYPE_U16,
	TYPE_U16,
	TYPE_U16,
	TYPE_U8,
	TYPE_U16,
	TYPE_U16,
	TYPE_U16,
	TYPE_U16,
	TYPE_U8,
	TYPE_U16,
	TYPE_U16,
	TYPE_U16,
	TYPE_U16,
	TYPE_U8,
	TYPE_I16,
	TYPE_U16,
	TYPE_I16,
	TYPE_U16,
	TYPE_U8,
	TYPE_I16,
	TYPE_U16,
	TYPE_I16,
	TYPE_U16,
	TYPE_U8,
	TYPE_U8,
	TYPE_U16,
	TYPE_I16
};

uint16_t app_regs_n_elements[] = {
	1,
	4,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1
};

uint8_t *app_regs_pointer[] = {
	(uint8_t*)(&app_regs.REG_CONFIG),
	(uint8_t*)(app_regs.REG_DATA_STREAM),
	(uint8_t*)(&app_regs.REG_INPUTS),
	(uint8_t*)(&app_regs.REG_INPUT_IO0_CONFIG),
	(uint8_t*)(&app_regs.REG_INPUT_IO1_CONFIG),
	(uint8_t*)(&app_regs.REG_INPUT_IO2_CONFIG),
	(uint8_t*)(&app_regs.REG_OUTPUT_SET),
	(uint8_t*)(&app_regs.REG_OUTPUT_CLEAR),
	(uint8_t*)(&app_regs.REG_OUTPUT_TOGGLE),
	(uint8_t*)(&app_regs.REG_OUTPUT_WRITE),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH0_HIGH),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH0_HIGH_MS),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH0_LOW),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH0_LOW_MS),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH0_EVT_CONF),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH1_HIGH),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH1_HIGH_MS),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH1_LOW),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH1_LOW_MS),
	(uint8_t*)(&app_regs.REG_ANA_SENSOR_TH1_EVT_CONF),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH0_HIGH),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH0_HIGH_MS),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH0_LOW),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH0_LOW_MS),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH0_EVT_CONF),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH1_HIGH),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH1_HIGH_MS),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH1_LOW),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH1_LOW_MS),
	(uint8_t*)(&app_regs.REG_ANA_INPUT_TH1_EVT_CONF),
	(uint8_t*)(&app_regs.REG_ENCODER_TH0_HIGH),
	(uint8_t*)(&app_regs.REG_ENCODER_TH0_HIGH_MS),
	(uint8_t*)(&app_regs.REG_ENCODER_TH0_LOW),
	(uint8_t*)(&app_regs.REG_ENCODER_TH0_LOW_MS),
	(uint8_t*)(&app_regs.REG_ENCODER_TH0_EVT_CONF),
	(uint8_t*)(&app_regs.REG_ENCODER_TH1_HIGH),
	(uint8_t*)(&app_regs.REG_ENCODER_TH1_HIGH_MS),
	(uint8_t*)(&app_regs.REG_ENCODER_TH1_LOW),
	(uint8_t*)(&app_regs.REG_ENCODER_TH1_LOW_MS),
	(uint8_t*)(&app_regs.REG_ENCODER_TH1_EVT_CONF),
	(uint8_t*)(&app_regs.REG_TH_ENABLE_EVENTS),
	(uint8_t*)(&app_regs.REG_WRITE_AO),
	(uint8_t*)(&app_regs.REG_ENCODER)
};