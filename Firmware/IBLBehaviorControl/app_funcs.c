#include "app_funcs.h"
#include "app_ios_and_regs.h"
#include "hwbp_core.h"


/************************************************************************/
/* Create pointers to functions                                         */
/************************************************************************/
extern AppRegs app_regs;

void (*app_func_rd_pointer[])(void) = {
	&app_read_REG_CONFIG,
	&app_read_REG_DATA_STREAM,
	&app_read_REG_INPUTS,
	&app_read_REG_INPUT_IO0_CONFIG,
	&app_read_REG_INPUT_IO1_CONFIG,
	&app_read_REG_INPUT_IO2_CONFIG,
	&app_read_REG_OUTPUT_SET,
	&app_read_REG_OUTPUT_CLEAR,
	&app_read_REG_OUTPUT_TOGGLE,
	&app_read_REG_OUTPUT_WRITE,
	&app_read_REG_ANA_SENSOR_TH0_HIGH,
	&app_read_REG_ANA_SENSOR_TH0_HIGH_MS,
	&app_read_REG_ANA_SENSOR_TH0_LOW,
	&app_read_REG_ANA_SENSOR_TH0_LOW_MS,
	&app_read_REG_ANA_SENSOR_TH0_EVT_CONF,
	&app_read_REG_ANA_SENSOR_TH1_HIGH,
	&app_read_REG_ANA_SENSOR_TH1_HIGH_MS,
	&app_read_REG_ANA_SENSOR_TH1_LOW,
	&app_read_REG_ANA_SENSOR_TH1_LOW_MS,
	&app_read_REG_ANA_SENSOR_TH1_EVT_CONF,
	&app_read_REG_ANA_INPUT_TH0_HIGH,
	&app_read_REG_ANA_INPUT_TH0_HIGH_MS,
	&app_read_REG_ANA_INPUT_TH0_LOW,
	&app_read_REG_ANA_INPUT_TH0_LOW_MS,
	&app_read_REG_ANA_INPUT_TH0_EVT_CONF,
	&app_read_REG_ANA_INPUT_TH1_HIGH,
	&app_read_REG_ANA_INPUT_TH1_HIGH_MS,
	&app_read_REG_ANA_INPUT_TH1_LOW,
	&app_read_REG_ANA_INPUT_TH1_LOW_MS,
	&app_read_REG_ANA_INPUT_TH1_EVT_CONF,
	&app_read_REG_ENCODER_TH0_HIGH,
	&app_read_REG_ENCODER_TH0_HIGH_MS,
	&app_read_REG_ENCODER_TH0_LOW,
	&app_read_REG_ENCODER_TH0_LOW_MS,
	&app_read_REG_ENCODER_TH0_EVT_CONF,
	&app_read_REG_ENCODER_TH1_HIGH,
	&app_read_REG_ENCODER_TH1_HIGH_MS,
	&app_read_REG_ENCODER_TH1_LOW,
	&app_read_REG_ENCODER_TH1_LOW_MS,
	&app_read_REG_ENCODER_TH1_EVT_CONF,
	&app_read_REG_TH_ENABLE_EVENTS,
	&app_read_REG_WRITE_AO,
	&app_read_REG_ENCODER
};

bool (*app_func_wr_pointer[])(void*) = {
	&app_write_REG_CONFIG,
	&app_write_REG_DATA_STREAM,
	&app_write_REG_INPUTS,
	&app_write_REG_INPUT_IO0_CONFIG,
	&app_write_REG_INPUT_IO1_CONFIG,
	&app_write_REG_INPUT_IO2_CONFIG,
	&app_write_REG_OUTPUT_SET,
	&app_write_REG_OUTPUT_CLEAR,
	&app_write_REG_OUTPUT_TOGGLE,
	&app_write_REG_OUTPUT_WRITE,
	&app_write_REG_ANA_SENSOR_TH0_HIGH,
	&app_write_REG_ANA_SENSOR_TH0_HIGH_MS,
	&app_write_REG_ANA_SENSOR_TH0_LOW,
	&app_write_REG_ANA_SENSOR_TH0_LOW_MS,
	&app_write_REG_ANA_SENSOR_TH0_EVT_CONF,
	&app_write_REG_ANA_SENSOR_TH1_HIGH,
	&app_write_REG_ANA_SENSOR_TH1_HIGH_MS,
	&app_write_REG_ANA_SENSOR_TH1_LOW,
	&app_write_REG_ANA_SENSOR_TH1_LOW_MS,
	&app_write_REG_ANA_SENSOR_TH1_EVT_CONF,
	&app_write_REG_ANA_INPUT_TH0_HIGH,
	&app_write_REG_ANA_INPUT_TH0_HIGH_MS,
	&app_write_REG_ANA_INPUT_TH0_LOW,
	&app_write_REG_ANA_INPUT_TH0_LOW_MS,
	&app_write_REG_ANA_INPUT_TH0_EVT_CONF,
	&app_write_REG_ANA_INPUT_TH1_HIGH,
	&app_write_REG_ANA_INPUT_TH1_HIGH_MS,
	&app_write_REG_ANA_INPUT_TH1_LOW,
	&app_write_REG_ANA_INPUT_TH1_LOW_MS,
	&app_write_REG_ANA_INPUT_TH1_EVT_CONF,
	&app_write_REG_ENCODER_TH0_HIGH,
	&app_write_REG_ENCODER_TH0_HIGH_MS,
	&app_write_REG_ENCODER_TH0_LOW,
	&app_write_REG_ENCODER_TH0_LOW_MS,
	&app_write_REG_ENCODER_TH0_EVT_CONF,
	&app_write_REG_ENCODER_TH1_HIGH,
	&app_write_REG_ENCODER_TH1_HIGH_MS,
	&app_write_REG_ENCODER_TH1_LOW,
	&app_write_REG_ENCODER_TH1_LOW_MS,
	&app_write_REG_ENCODER_TH1_EVT_CONF,
	&app_write_REG_TH_ENABLE_EVENTS,
	&app_write_REG_WRITE_AO,
	&app_write_REG_ENCODER
};


/************************************************************************/
/* REG_CONFIG                                                           */
/************************************************************************/
#define DAC_GAINCAL 0x83
#define DAC_OFFSETCAL 0x85

extern bool stream_is_enabled;

uint8_t IO0_input_sense;
uint8_t IO1_input_sense;
uint8_t IO2_input_sense;

void app_read_REG_CONFIG(void)
{	
	if (stream_is_enabled)
	{
		app_regs.REG_CONFIG = B_DATA_1Khz;
	}
	else
	{
		app_regs.REG_CONFIG = B_DATA_QUIET;
	}

	
	if (read_CLOCK_OUT_EN)  app_regs.REG_CONFIG |= B_SYNC_TO_MASTER;
	if (read_CLOCK_IN_EN)   app_regs.REG_CONFIG |= B_SYNC_TO_SLAVE;
	
	if (!read_RELAY)        app_regs.REG_CONFIG |= B_ANA_SENSOR_TO_AO;
	if (read_RELAY)         app_regs.REG_CONFIG |= B_ANA_INTERNAL_TO_AO;
	
	if (ADCA_CTRLA != 0)
	{
		app_regs.REG_CONFIG |= B_EN_AI;
	}
	else
	{
		if (!read_IO0_DIR)      app_regs.REG_CONFIG |= B_IO0_TO_INPUT;
		if (read_IO0_DIR)       app_regs.REG_CONFIG |= B_IO0_TO_OUTPUT;
	}
	
	if (!read_IO1_DIR)      app_regs.REG_CONFIG |= B_IO1_TO_INPUT;
	if (read_IO1_DIR)       app_regs.REG_CONFIG |= B_IO1_TO_OUTPUT;
	
	if (!read_IO2_DIR)      app_regs.REG_CONFIG |= B_IO2_TO_INPUT;
	if (read_IO2_DIR)       app_regs.REG_CONFIG |= B_IO2_TO_OUTPUT;
}

bool app_write_REG_CONFIG(void *a)
{
	uint16_t reg = *((uint16_t*)a);
	
	if (reg & B_SYNC_TO_MASTER)	{clr_CLOCK_IN_EN;  set_CLOCK_OUT_EN; set_LED_MASTER; clr_LED_SLAVE;}
	if (reg & B_SYNC_TO_SLAVE)	{clr_CLOCK_OUT_EN; set_CLOCK_IN_EN;  clr_LED_MASTER; set_LED_SLAVE;}
	
	if (reg & B_ANA_SENSOR_TO_AO)
	{
		clr_RELAY;
		
		/* Disable DACB */
		DACB.CTRLA = 0;
	}
	if (reg & B_ANA_INTERNAL_TO_AO)
	{
		/* Configure DAC calibration using default values */
		DACB.CH0GAINCAL = DAC_GAINCAL;
		DACB.CH0OFFSETCAL = DAC_OFFSETCAL;
		
		/* Initialize DACB single channel using AVCC as reference */
		DACB.CTRLB = DAC_CHSEL_SINGLE_gc;
		//DACB.CTRLC = DAC_REFSEL_AREFB_gc;
		DACB.CTRLC = DAC_REFSEL_AVCC_gc;
		DACB.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;
		
		set_RELAY;
	}
	
	if (reg & B_EN_AI)
	{
		io_set_int(&PORTF, INT_LEVEL_OFF, 0, (1<<1), false);	// Disable IO0 interrupt
		io_pin2in(&PORTF, 1, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);
		clr_IO0_DIR;
		
		adc_A_initialize_single_ended(ADC_REFSEL_AREFB_gc);
		ADCA_CH0_INTCTRL |= ADC_CH_INTLVL_LO_gc;				// Enable ADC interrupt
	}
	
	if (reg & B_IO0_TO_INPUT)
	{
		ADCA_CTRLA = 0;											// Disable ADCA
		PR_PRPA |= PR_ADC_bm;									// Enable power reduction
		
		clr_IO0_DIR;
		app_write_REG_INPUT_IO0_CONFIG(&app_regs.REG_INPUT_IO0_CONFIG);
	}
	if (reg & B_IO0_TO_OUTPUT)
	{
		ADCA_CTRLA = 0;											// Disable ADCA
		PR_PRPA |= PR_ADC_bm;									// Enable power reduction		
		
		io_set_int(&PORTF, INT_LEVEL_OFF, 0, (1<<1), false);
		io_pin2out(&PORTF, 1, OUT_IO_DIGITAL, true);
		set_IO0_DIR;
	}
	
	if (reg & B_IO1_TO_INPUT)
	{
		clr_IO1_DIR;
		app_write_REG_INPUT_IO1_CONFIG(&app_regs.REG_INPUT_IO1_CONFIG);
	}
	if (reg & B_IO1_TO_OUTPUT)
	{
		io_set_int(&PORTK, INT_LEVEL_OFF, 0, (1<<1), false);
		io_pin2out(&PORTK, 1, OUT_IO_DIGITAL, true);
		set_IO1_DIR;
	}
	
	if (reg & B_IO2_TO_INPUT)
	{
		clr_IO2_DIR;
		app_write_REG_INPUT_IO2_CONFIG(&app_regs.REG_INPUT_IO2_CONFIG);
	}
	if (reg & B_IO2_TO_OUTPUT)
	{
		io_set_int(&PORTK, INT_LEVEL_OFF, 1, (1<<2), false);
		io_pin2out(&PORTK, 2, OUT_IO_DIGITAL, true);
		set_IO2_DIR;
	}
	
	if (reg & B_DATA_1Khz)  stream_is_enabled = true;
	if (reg & B_DATA_QUIET) stream_is_enabled = false;

	app_regs.REG_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_DATA_STREAM                                                      */
/************************************************************************/
// This register is an array with 4 positions
void app_read_REG_DATA_STREAM(void) {}
	
bool app_write_REG_DATA_STREAM(void *a) {return false;}


/************************************************************************/
/* REG_INPUTS                                                           */
/************************************************************************/
void app_read_REG_INPUTS(void)
{
	app_regs.REG_INPUTS  = (read_IO0) ? B_IO0 : 0;
	app_regs.REG_INPUTS |= (read_IO1) ? B_IO1 : 0;
	app_regs.REG_INPUTS |= (read_IO2) ? B_IO2 : 0;
}

bool app_write_REG_INPUTS(void *a) {return false;}


/************************************************************************/
/* REG_INPUT_IO0_CONFIG                                                 */
/************************************************************************/
void app_read_REG_INPUT_IO0_CONFIG(void) {}
bool app_write_REG_INPUT_IO0_CONFIG(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (ADCA_CTRLA == 0 && !read_IO0_DIR)
	{
		switch (reg)
		{
			case GM_INPUT_NOT_USED:
				io_pin2in(&PORTF, 1, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);
				io_set_int(&PORTF, INT_LEVEL_OFF, 0, (1<<1), false);
				break;
			
			case GM_INPUT_SENSE_BOTH:
				io_pin2in(&PORTF, 1, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);
				io_set_int(&PORTF, INT_LEVEL_LOW, 0, (1<<1), false);
				tgl_LED_IO2;
				break;
		}
	}

	app_regs.REG_INPUT_IO0_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_INPUT_IO1_CONFIG                                                 */
/************************************************************************/
void app_read_REG_INPUT_IO1_CONFIG(void) {}
bool app_write_REG_INPUT_IO1_CONFIG(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (!read_IO1_DIR)
	{
		switch (reg)
		{
			case GM_INPUT_NOT_USED:
				io_pin2in(&PORTK, 1, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);
				io_set_int(&PORTK, INT_LEVEL_OFF, 0, (1<<1), false);
				break;
			
			case GM_INPUT_SENSE_BOTH:
				io_pin2in(&PORTK, 1, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);
				io_set_int(&PORTK, INT_LEVEL_LOW, 0, (1<<1), false);
				break;
		}
	}

	app_regs.REG_INPUT_IO1_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_INPUT_IO2_CONFIG                                                 */
/************************************************************************/
void app_read_REG_INPUT_IO2_CONFIG(void) {}
bool app_write_REG_INPUT_IO2_CONFIG(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	
	if (!read_IO2_DIR)
	{
		switch (reg)
		{
			case GM_INPUT_NOT_USED:
				io_pin2in(&PORTK, 2, PULL_IO_TRISTATE, SENSE_IO_NO_INT_USED);
				io_set_int(&PORTK, INT_LEVEL_OFF, 1, (1<<2), false);
				break;
			
			case GM_INPUT_SENSE_BOTH:
				io_pin2in(&PORTK, 2, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);
				io_set_int(&PORTK, INT_LEVEL_LOW, 1, (1<<2), false);
				break;
		}
	}
	
	app_regs.REG_INPUT_IO2_CONFIG = reg;
	return true;
}


/************************************************************************/
/* REG_OUTPUT_SET                                                       */
/************************************************************************/
void app_read_REG_OUTPUT_SET(void)
{
	app_read_REG_OUTPUT_WRITE();
	app_regs.REG_OUTPUT_SET = app_regs.REG_OUTPUT_WRITE;
}

bool app_write_REG_OUTPUT_SET(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	if (reg & B_IO0) set_IO0;
	if (reg & B_IO1) set_IO1;
	if (reg & B_IO2) set_IO2;
	app_regs.REG_OUTPUT_SET = reg;
	return true;
}


/************************************************************************/
/* REG_OUTPUT_CLEAR                                                     */
/************************************************************************/
void app_read_REG_OUTPUT_CLEAR(void)
{
	app_read_REG_OUTPUT_WRITE();
	app_regs.REG_OUTPUT_CLEAR = (~app_regs.REG_OUTPUT_WRITE) & 0x07;
}

bool app_write_REG_OUTPUT_CLEAR(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	if (reg & B_IO0) clr_IO0;
	if (reg & B_IO1) clr_IO1;
	if (reg & B_IO2) clr_IO2;
	app_regs.REG_OUTPUT_CLEAR = reg;
	return true;
}


/************************************************************************/
/* REG_OUTPUT_TOGGLE                                                    */
/************************************************************************/
void app_read_REG_OUTPUT_TOGGLE(void) {
	app_regs.REG_OUTPUT_TOGGLE = 0;
}

bool app_write_REG_OUTPUT_TOGGLE(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	if (reg & B_IO0) tgl_IO0;
	if (reg & B_IO1) tgl_IO1;
	if (reg & B_IO2) tgl_IO2;
	app_regs.REG_OUTPUT_TOGGLE = reg;
	return true;
}


/************************************************************************/
/* REG_OUTPUT_WRITE                                                     */
/************************************************************************/
void app_read_REG_OUTPUT_WRITE(void)
{
	app_regs.REG_OUTPUT_WRITE = 0;
	
	if (ADCA_CTRLA == 0)
	{		
		if (read_IO0_DIR)
		{
			app_regs.REG_OUTPUT_WRITE  |= (read_IO0) ? B_IO0 : 0;
		}
	}
	
	if (read_IO1_DIR)
	{
		app_regs.REG_OUTPUT_WRITE  |= (read_IO1) ? B_IO1 : 0;
	}
	
	if (read_IO1_DIR)
	{
		app_regs.REG_OUTPUT_WRITE  |= (read_IO2) ? B_IO2 : 0;
	}
}

bool app_write_REG_OUTPUT_WRITE(void *a)
{
	uint8_t reg = *((uint8_t*)a);
	if (reg & B_IO0) set_IO0; else clr_IO0;
	if (reg & B_IO1) set_IO1; else clr_IO1;
	if (reg & B_IO2) set_IO2; else clr_IO2;
	app_regs.REG_OUTPUT_WRITE = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH0_HIGH                                              */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH0_HIGH(void)
{
	//app_regs.REG_ANA_SENSOR_TH0_HIGH = 0;

}

bool app_write_REG_ANA_SENSOR_TH0_HIGH(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH0_HIGH = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH0_HIGH_MS                                           */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH0_HIGH_MS(void)
{
	//app_regs.REG_ANA_SENSOR_TH0_HIGH_MS = 0;

}

bool app_write_REG_ANA_SENSOR_TH0_HIGH_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH0_HIGH_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH0_LOW                                               */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH0_LOW(void)
{
	//app_regs.REG_ANA_SENSOR_TH0_LOW = 0;

}

bool app_write_REG_ANA_SENSOR_TH0_LOW(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH0_LOW = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH0_LOW_MS                                            */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH0_LOW_MS(void)
{
	//app_regs.REG_ANA_SENSOR_TH0_LOW_MS = 0;

}

bool app_write_REG_ANA_SENSOR_TH0_LOW_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH0_LOW_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH0_EVT_CONF                                          */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH0_EVT_CONF(void)
{
	//app_regs.REG_ANA_SENSOR_TH0_EVT_CONF = 0;

}

bool app_write_REG_ANA_SENSOR_TH0_EVT_CONF(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH0_EVT_CONF = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH1_HIGH                                              */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH1_HIGH(void)
{
	//app_regs.REG_ANA_SENSOR_TH1_HIGH = 0;

}

bool app_write_REG_ANA_SENSOR_TH1_HIGH(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH1_HIGH = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH1_HIGH_MS                                           */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH1_HIGH_MS(void)
{
	//app_regs.REG_ANA_SENSOR_TH1_HIGH_MS = 0;

}

bool app_write_REG_ANA_SENSOR_TH1_HIGH_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH1_HIGH_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH1_LOW                                               */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH1_LOW(void)
{
	//app_regs.REG_ANA_SENSOR_TH1_LOW = 0;

}

bool app_write_REG_ANA_SENSOR_TH1_LOW(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH1_LOW = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH1_LOW_MS                                            */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH1_LOW_MS(void)
{
	//app_regs.REG_ANA_SENSOR_TH1_LOW_MS = 0;

}

bool app_write_REG_ANA_SENSOR_TH1_LOW_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH1_LOW_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_SENSOR_TH1_EVT_CONF                                          */
/************************************************************************/
void app_read_REG_ANA_SENSOR_TH1_EVT_CONF(void)
{
	//app_regs.REG_ANA_SENSOR_TH1_EVT_CONF = 0;

}

bool app_write_REG_ANA_SENSOR_TH1_EVT_CONF(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_SENSOR_TH1_EVT_CONF = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH0_HIGH                                               */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH0_HIGH(void)
{
	//app_regs.REG_ANA_INPUT_TH0_HIGH = 0;

}

bool app_write_REG_ANA_INPUT_TH0_HIGH(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH0_HIGH = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH0_HIGH_MS                                            */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH0_HIGH_MS(void)
{
	//app_regs.REG_ANA_INPUT_TH0_HIGH_MS = 0;

}

bool app_write_REG_ANA_INPUT_TH0_HIGH_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH0_HIGH_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH0_LOW                                                */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH0_LOW(void)
{
	//app_regs.REG_ANA_INPUT_TH0_LOW = 0;

}

bool app_write_REG_ANA_INPUT_TH0_LOW(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH0_LOW = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH0_LOW_MS                                             */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH0_LOW_MS(void)
{
	//app_regs.REG_ANA_INPUT_TH0_LOW_MS = 0;

}

bool app_write_REG_ANA_INPUT_TH0_LOW_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH0_LOW_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH0_EVT_CONF                                           */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH0_EVT_CONF(void)
{
	//app_regs.REG_ANA_INPUT_TH0_EVT_CONF = 0;

}

bool app_write_REG_ANA_INPUT_TH0_EVT_CONF(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH0_EVT_CONF = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH1_HIGH                                               */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH1_HIGH(void)
{
	//app_regs.REG_ANA_INPUT_TH1_HIGH = 0;

}

bool app_write_REG_ANA_INPUT_TH1_HIGH(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH1_HIGH = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH1_HIGH_MS                                            */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH1_HIGH_MS(void)
{
	//app_regs.REG_ANA_INPUT_TH1_HIGH_MS = 0;

}

bool app_write_REG_ANA_INPUT_TH1_HIGH_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH1_HIGH_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH1_LOW                                                */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH1_LOW(void)
{
	//app_regs.REG_ANA_INPUT_TH1_LOW = 0;

}

bool app_write_REG_ANA_INPUT_TH1_LOW(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH1_LOW = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH1_LOW_MS                                             */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH1_LOW_MS(void)
{
	//app_regs.REG_ANA_INPUT_TH1_LOW_MS = 0;

}

bool app_write_REG_ANA_INPUT_TH1_LOW_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH1_LOW_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ANA_INPUT_TH1_EVT_CONF                                           */
/************************************************************************/
void app_read_REG_ANA_INPUT_TH1_EVT_CONF(void)
{
	//app_regs.REG_ANA_INPUT_TH1_EVT_CONF = 0;

}

bool app_write_REG_ANA_INPUT_TH1_EVT_CONF(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ANA_INPUT_TH1_EVT_CONF = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH0_HIGH                                                 */
/************************************************************************/
void app_read_REG_ENCODER_TH0_HIGH(void)
{
	//app_regs.REG_ENCODER_TH0_HIGH = 0;

}

bool app_write_REG_ENCODER_TH0_HIGH(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH0_HIGH = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH0_HIGH_MS                                              */
/************************************************************************/
void app_read_REG_ENCODER_TH0_HIGH_MS(void)
{
	//app_regs.REG_ENCODER_TH0_HIGH_MS = 0;

}

bool app_write_REG_ENCODER_TH0_HIGH_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH0_HIGH_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH0_LOW                                                  */
/************************************************************************/
void app_read_REG_ENCODER_TH0_LOW(void)
{
	//app_regs.REG_ENCODER_TH0_LOW = 0;

}

bool app_write_REG_ENCODER_TH0_LOW(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH0_LOW = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH0_LOW_MS                                               */
/************************************************************************/
void app_read_REG_ENCODER_TH0_LOW_MS(void)
{
	//app_regs.REG_ENCODER_TH0_LOW_MS = 0;

}

bool app_write_REG_ENCODER_TH0_LOW_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH0_LOW_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH0_EVT_CONF                                             */
/************************************************************************/
void app_read_REG_ENCODER_TH0_EVT_CONF(void)
{
	//app_regs.REG_ENCODER_TH0_EVT_CONF = 0;

}

bool app_write_REG_ENCODER_TH0_EVT_CONF(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH0_EVT_CONF = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH1_HIGH                                                 */
/************************************************************************/
void app_read_REG_ENCODER_TH1_HIGH(void)
{
	//app_regs.REG_ENCODER_TH1_HIGH = 0;

}

bool app_write_REG_ENCODER_TH1_HIGH(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH1_HIGH = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH1_HIGH_MS                                              */
/************************************************************************/
void app_read_REG_ENCODER_TH1_HIGH_MS(void)
{
	//app_regs.REG_ENCODER_TH1_HIGH_MS = 0;

}

bool app_write_REG_ENCODER_TH1_HIGH_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH1_HIGH_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH1_LOW                                                  */
/************************************************************************/
void app_read_REG_ENCODER_TH1_LOW(void)
{
	//app_regs.REG_ENCODER_TH1_LOW = 0;

}

bool app_write_REG_ENCODER_TH1_LOW(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH1_LOW = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH1_LOW_MS                                               */
/************************************************************************/
void app_read_REG_ENCODER_TH1_LOW_MS(void)
{
	//app_regs.REG_ENCODER_TH1_LOW_MS = 0;

}

bool app_write_REG_ENCODER_TH1_LOW_MS(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH1_LOW_MS = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER_TH1_EVT_CONF                                             */
/************************************************************************/
void app_read_REG_ENCODER_TH1_EVT_CONF(void)
{
	//app_regs.REG_ENCODER_TH1_EVT_CONF = 0;

}

bool app_write_REG_ENCODER_TH1_EVT_CONF(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER_TH1_EVT_CONF = reg;
	return true;
}


/************************************************************************/
/* REG_TH_ENABLE_EVENTS                                                 */
/************************************************************************/
void app_read_REG_TH_ENABLE_EVENTS(void)
{
	//app_regs.REG_TH_ENABLE_EVENTS = 0;

}

bool app_write_REG_TH_ENABLE_EVENTS(void *a)
{
	uint8_t reg = *((uint8_t*)a);

	app_regs.REG_TH_ENABLE_EVENTS = reg;
	return true;
}


/************************************************************************/
/* REG_WRITE_AO                                                         */
/************************************************************************/
void app_read_REG_WRITE_AO(void)
{
	//app_regs.REG_WRITE_AO = 0;

}

bool app_write_REG_WRITE_AO(void *a)
{
	uint16_t reg = *((uint16_t*)a);
	
	DACB.CH0DATA = reg;

	app_regs.REG_WRITE_AO = reg;
	return true;
}


/************************************************************************/
/* REG_ENCODER                                                          */
/************************************************************************/
void app_read_REG_ENCODER(void)
{
	//app_regs.REG_ENCODER = 0;

}

bool app_write_REG_ENCODER(void *a)
{
	int16_t reg = *((int16_t*)a);

	app_regs.REG_ENCODER = reg;
	return true;
}