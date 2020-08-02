#include "data_stream.h"
#include "app_ios_and_regs.h"
#include "app_funcs.h"
#include "hwbp_core.h"

/************************************************************************/
/* Declare application registers                                        */
/************************************************************************/
extern AppRegs app_regs;

/************************************************************************/
/* Global variables                                                     */
/************************************************************************/
uint8_t adc_accumulator_counter = 1;

/************************************************************************/
/* Data stream interrupt                                                */
/************************************************************************/
bool stream_is_enabled;

uint16_t ana_sensor_th0_up_counter = 0;
uint16_t ana_sensor_th1_up_counter = 0;
uint16_t ana_input_th0_up_counter = 0;
uint16_t ana_input_th1_up_counter = 0;
uint16_t encoder_th0_up_counter = 0;
uint16_t encoder_th1_up_counter = 0;

uint16_t ana_sensor_th0_down_counter = 0;
uint16_t ana_sensor_th1_down_counter = 0;
uint16_t ana_input_th0_down_counter = 0;
uint16_t ana_input_th1_down_counter = 0;
uint16_t encoder_th0_down_counter = 0;
uint16_t encoder_th1_down_counter = 0;

ISR(ADCA_CH0_vect, ISR_NAKED)
{
	app_regs.REG_DATA_STREAM[1] = (int16_t)(ADCA_CH0_RES & 0x0FFF);
	reti();
}


ISR(TCD1_OVF_vect, ISR_NAKED)
{
	if (adc_accumulator_counter < ADC_ACCUMULATOR_TARGET)
	{
		set_ADC_CNVST;
		set_ADC_CNVST;
		clr_ADC_CNVST;
				
		adc_accumulator_counter++;
	}
	else /*if(adc_accumulator_counter == ADC_ACCUMULATOR_TARGET)*/
	{		
		adc_accumulator_counter = 1;
		
		timer_type1_stop(&TCD1);
		
		app_regs.REG_DATA_STREAM[0] = 0;
	
		set_ADC_SCLK; clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<13); clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<12); clr_ADC_SCLK;
	
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<11); clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<10); clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<9);  clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<8);  clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<7);  clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<6);  clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<5);  clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<4);  clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<3);  clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<2);  clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<1);  clr_ADC_SCLK;
		set_ADC_SCLK; if (read_ADC_SDO) app_regs.REG_DATA_STREAM[0] |= (1<<0);  clr_ADC_SCLK;
		
		
		int16_t prev_data_stream = app_regs.REG_DATA_STREAM[3];
		
		
		/* Analog sensor TH0 */
		if (app_regs.REG_DATA_STREAM[0] >= app_regs.REG_ANA_SENSOR_TH0_HIGH)
		{
			if (++ana_sensor_th0_up_counter >= app_regs.REG_ANA_SENSOR_TH0_HIGH_MS + 1)
				app_regs.REG_DATA_STREAM[3] |= B_ASTH0;
			if (ana_sensor_th0_up_counter > app_regs.REG_ANA_SENSOR_TH0_HIGH_MS)
				ana_sensor_th0_up_counter--;
				
			ana_sensor_th0_down_counter = 0;
		}
		else if (app_regs.REG_DATA_STREAM[0] <= app_regs.REG_ANA_SENSOR_TH0_LOW)
		{
			if (++ana_sensor_th0_down_counter >= app_regs.REG_ANA_SENSOR_TH0_LOW_MS + 1)
				app_regs.REG_DATA_STREAM[3] &= ~(B_ASTH0);
			if (ana_sensor_th0_down_counter > app_regs.REG_ANA_SENSOR_TH0_LOW_MS)
				ana_sensor_th0_down_counter--;
				
			ana_sensor_th0_up_counter = 0;
		}
		switch (app_regs.REG_ANA_SENSOR_TH0_EVT_CONF) {
			case GM_TH_ON_IO0: if (app_regs.REG_DATA_STREAM[3] & B_ASTH0) set_IO0; else clr_IO0; break;
			case GM_TH_ON_IO1: if (app_regs.REG_DATA_STREAM[3] & B_ASTH0) set_IO1; else clr_IO1; break;
			case GM_TH_ON_IO2: if (app_regs.REG_DATA_STREAM[3] & B_ASTH0) set_IO2; else clr_IO2; break;
		}
		
		/* Analog sensor TH1 */
		if (app_regs.REG_DATA_STREAM[0] >= app_regs.REG_ANA_SENSOR_TH1_HIGH)
		{
			if (++ana_sensor_th1_up_counter >= app_regs.REG_ANA_SENSOR_TH1_HIGH_MS + 1)
				app_regs.REG_DATA_STREAM[3] |= B_ASTH1;
			if (ana_sensor_th1_up_counter > app_regs.REG_ANA_SENSOR_TH1_HIGH_MS)
				ana_sensor_th1_up_counter--;
			
			ana_sensor_th1_down_counter = 0;
		}
		else if (app_regs.REG_DATA_STREAM[0] <= app_regs.REG_ANA_SENSOR_TH1_LOW)
		{
			if (++ana_sensor_th1_down_counter >= app_regs.REG_ANA_SENSOR_TH1_LOW_MS + 1)
				app_regs.REG_DATA_STREAM[3] &= ~(B_ASTH1);
			if (ana_sensor_th1_down_counter > app_regs.REG_ANA_SENSOR_TH1_LOW_MS)
				ana_sensor_th1_down_counter--;
			
			ana_sensor_th1_up_counter = 0;
		}
		switch (app_regs.REG_ANA_SENSOR_TH1_EVT_CONF) {
			case GM_TH_ON_IO0: if (app_regs.REG_DATA_STREAM[3] & B_ASTH1) set_IO0; else clr_IO0; break;
			case GM_TH_ON_IO1: if (app_regs.REG_DATA_STREAM[3] & B_ASTH1) set_IO1; else clr_IO1; break;
			case GM_TH_ON_IO2: if (app_regs.REG_DATA_STREAM[3] & B_ASTH1) set_IO2; else clr_IO2; break;
		}
		
		/* Analog input TH0 */
		if (app_regs.REG_DATA_STREAM[1] >= app_regs.REG_ANA_INPUT_TH0_HIGH)
		{
			if (++ana_input_th0_up_counter >= app_regs.REG_ANA_INPUT_TH0_HIGH_MS + 1)
				app_regs.REG_DATA_STREAM[3] |= B_AITH0;
			if (ana_input_th0_up_counter > app_regs.REG_ANA_INPUT_TH0_HIGH_MS)
				ana_input_th0_up_counter--;
			
			ana_input_th0_down_counter = 0;
		}
		else if (app_regs.REG_DATA_STREAM[1] <= app_regs.REG_ANA_INPUT_TH0_LOW)
		{
			if (++ana_input_th0_down_counter >= app_regs.REG_ANA_INPUT_TH0_LOW_MS + 1)
				app_regs.REG_DATA_STREAM[3] &= ~(B_AITH0);
			if (ana_input_th0_down_counter > app_regs.REG_ANA_INPUT_TH0_LOW_MS)
				ana_input_th0_down_counter--;
			
			ana_input_th0_up_counter = 0;
		}
		switch (app_regs.REG_ANA_INPUT_TH0_EVT_CONF) {
			case GM_TH_ON_IO0: if (app_regs.REG_DATA_STREAM[3] & B_AITH0) set_IO0; else clr_IO0; break;
			case GM_TH_ON_IO1: if (app_regs.REG_DATA_STREAM[3] & B_AITH0) set_IO1; else clr_IO1; break;
			case GM_TH_ON_IO2: if (app_regs.REG_DATA_STREAM[3] & B_AITH0) set_IO2; else clr_IO2; break;
		}
		
		/* Analog input TH1 */
		if (app_regs.REG_DATA_STREAM[1] >= app_regs.REG_ANA_INPUT_TH1_HIGH)
		{
			if (++ana_input_th1_up_counter >= app_regs.REG_ANA_INPUT_TH1_HIGH_MS + 1)
				app_regs.REG_DATA_STREAM[3] |= B_AITH1;
			if (ana_input_th1_up_counter > app_regs.REG_ANA_INPUT_TH1_HIGH_MS)
				ana_input_th1_up_counter--;
			
			ana_input_th1_down_counter = 0;
		}
		else if (app_regs.REG_DATA_STREAM[1] <= app_regs.REG_ANA_INPUT_TH1_LOW)
		{
			if (++ana_input_th1_down_counter >= app_regs.REG_ANA_INPUT_TH1_LOW_MS + 1)
				app_regs.REG_DATA_STREAM[3] &= ~(B_AITH1);
			if (ana_input_th1_down_counter > app_regs.REG_ANA_INPUT_TH1_LOW_MS)
				ana_input_th1_down_counter--;
			
			ana_input_th1_up_counter = 0;
		}
		switch (app_regs.REG_ANA_INPUT_TH1_EVT_CONF) {
			case GM_TH_ON_IO0: if (app_regs.REG_DATA_STREAM[3] & B_AITH1) set_IO0; else clr_IO0; break;
			case GM_TH_ON_IO1: if (app_regs.REG_DATA_STREAM[3] & B_AITH1) set_IO1; else clr_IO1; break;
			case GM_TH_ON_IO2: if (app_regs.REG_DATA_STREAM[3] & B_AITH1) set_IO2; else clr_IO2; break;
		}
		
		/* Encoder input TH0 */
		if (app_regs.REG_DATA_STREAM[2] >= app_regs.REG_ENCODER_TH0_HIGH)
		{
			if (++encoder_th0_up_counter >= app_regs.REG_ENCODER_TH0_HIGH_MS + 1)
				app_regs.REG_DATA_STREAM[3] |= B_ENTH0;
			if (encoder_th0_up_counter > app_regs.REG_ENCODER_TH0_HIGH_MS)
				encoder_th0_up_counter--;
			
			encoder_th0_down_counter = 0;
		}
		else if (app_regs.REG_DATA_STREAM[2] <= app_regs.REG_ENCODER_TH0_LOW)
		{
			if (++encoder_th0_down_counter >= app_regs.REG_ENCODER_TH0_LOW_MS + 1)
				app_regs.REG_DATA_STREAM[3] &= ~(B_ENTH0);
			if (encoder_th0_down_counter > app_regs.REG_ENCODER_TH0_LOW_MS)
				encoder_th0_down_counter--;
			
			encoder_th0_up_counter = 0;
		}
		switch (app_regs.REG_ENCODER_TH0_EVT_CONF) {
			case GM_TH_ON_IO0: if (app_regs.REG_DATA_STREAM[3] & B_ENTH0) set_IO0; else clr_IO0; break;
			case GM_TH_ON_IO1: if (app_regs.REG_DATA_STREAM[3] & B_ENTH0) set_IO1; else clr_IO1; break;
			case GM_TH_ON_IO2: if (app_regs.REG_DATA_STREAM[3] & B_ENTH0) set_IO2; else clr_IO2; break;
		}
		
		/* Encoder TH1 */
		if (app_regs.REG_DATA_STREAM[2] >= app_regs.REG_ENCODER_TH1_HIGH)
		{
			if (++encoder_th1_up_counter >= app_regs.REG_ENCODER_TH1_HIGH_MS + 1)
				app_regs.REG_DATA_STREAM[3] |= B_ENTH1;
			if (encoder_th1_up_counter > app_regs.REG_ENCODER_TH1_HIGH_MS)
				encoder_th1_up_counter--;
			
			encoder_th1_down_counter = 0;
		}
		else if (app_regs.REG_DATA_STREAM[2] <= app_regs.REG_ENCODER_TH1_LOW)
		{
			if (++encoder_th1_down_counter >= app_regs.REG_ENCODER_TH1_LOW_MS + 1)
				app_regs.REG_DATA_STREAM[3] &= ~(B_ENTH1);
			if (encoder_th1_down_counter > app_regs.REG_ENCODER_TH1_LOW_MS)
				encoder_th1_down_counter--;
			
			encoder_th1_up_counter = 0;
		}
		switch (app_regs.REG_ENCODER_TH1_EVT_CONF) {
			case GM_TH_ON_IO0: if (app_regs.REG_DATA_STREAM[3] & B_ENTH1) set_IO0; else clr_IO0; break;
			case GM_TH_ON_IO1: if (app_regs.REG_DATA_STREAM[3] & B_ENTH1) set_IO1; else clr_IO1; break;
			case GM_TH_ON_IO2: if (app_regs.REG_DATA_STREAM[3] & B_ENTH1) set_IO2; else clr_IO2; break;
		}
		
		if (!stream_is_enabled)
		{	
			if (app_regs.REG_TH_ENABLE_EVENTS & B_ASTH0) if ((prev_data_stream & B_ASTH0) != (app_regs.REG_DATA_STREAM[3] & B_ASTH0)) {core_func_send_event(ADD_REG_DATA_STREAM, true); reti();}
			if (app_regs.REG_TH_ENABLE_EVENTS & B_ASTH1) if ((prev_data_stream & B_ASTH1) != (app_regs.REG_DATA_STREAM[3] & B_ASTH1)) {core_func_send_event(ADD_REG_DATA_STREAM, true); reti();}
			if (app_regs.REG_TH_ENABLE_EVENTS & B_AITH0) if ((prev_data_stream & B_AITH0) != (app_regs.REG_DATA_STREAM[3] & B_AITH0)) {core_func_send_event(ADD_REG_DATA_STREAM, true); reti();}
			if (app_regs.REG_TH_ENABLE_EVENTS & B_AITH1) if ((prev_data_stream & B_AITH1) != (app_regs.REG_DATA_STREAM[3] & B_AITH1)) {core_func_send_event(ADD_REG_DATA_STREAM, true); reti();}
			if (app_regs.REG_TH_ENABLE_EVENTS & B_ENTH0) if ((prev_data_stream & B_ENTH0) != (app_regs.REG_DATA_STREAM[3] & B_ENTH0)) {core_func_send_event(ADD_REG_DATA_STREAM, true); reti();}
			if (app_regs.REG_TH_ENABLE_EVENTS & B_ENTH1) if ((prev_data_stream & B_ENTH1) != (app_regs.REG_DATA_STREAM[3] & B_ENTH1)) {core_func_send_event(ADD_REG_DATA_STREAM, true); reti();}
		}
		else
		{
			core_func_send_event(ADD_REG_DATA_STREAM, true);
		}
	}
	
	reti();
}