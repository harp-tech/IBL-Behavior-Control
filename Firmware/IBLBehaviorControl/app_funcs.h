#ifndef _APP_FUNCTIONS_H_
#define _APP_FUNCTIONS_H_
#include <avr/io.h>


/************************************************************************/
/* Define if not defined                                                */
/************************************************************************/
#ifndef bool
	#define bool uint8_t
#endif
#ifndef true
	#define true 1
#endif
#ifndef false
	#define false 0
#endif


/************************************************************************/
/* Prototypes                                                           */
/************************************************************************/
void app_read_REG_CONFIG(void);
void app_read_REG_DATA_STREAM(void);
void app_read_REG_INPUTS(void);
void app_read_REG_INPUT_IO0_CONFIG(void);
void app_read_REG_INPUT_IO1_CONFIG(void);
void app_read_REG_INPUT_IO2_CONFIG(void);
void app_read_REG_OUTPUT_SET(void);
void app_read_REG_OUTPUT_CLEAR(void);
void app_read_REG_OUTPUT_TOGGLE(void);
void app_read_REG_OUTPUT_WRITE(void);
void app_read_REG_ANA_SENSOR_TH0_HIGH(void);
void app_read_REG_ANA_SENSOR_TH0_HIGH_MS(void);
void app_read_REG_ANA_SENSOR_TH0_LOW(void);
void app_read_REG_ANA_SENSOR_TH0_LOW_MS(void);
void app_read_REG_ANA_SENSOR_TH0_EVT_CONF(void);
void app_read_REG_ANA_SENSOR_TH1_HIGH(void);
void app_read_REG_ANA_SENSOR_TH1_HIGH_MS(void);
void app_read_REG_ANA_SENSOR_TH1_LOW(void);
void app_read_REG_ANA_SENSOR_TH1_LOW_MS(void);
void app_read_REG_ANA_SENSOR_TH1_EVT_CONF(void);
void app_read_REG_ANA_INPUT_TH0_HIGH(void);
void app_read_REG_ANA_INPUT_TH0_HIGH_MS(void);
void app_read_REG_ANA_INPUT_TH0_LOW(void);
void app_read_REG_ANA_INPUT_TH0_LOW_MS(void);
void app_read_REG_ANA_INPUT_TH0_EVT_CONF(void);
void app_read_REG_ANA_INPUT_TH1_HIGH(void);
void app_read_REG_ANA_INPUT_TH1_HIGH_MS(void);
void app_read_REG_ANA_INPUT_TH1_LOW(void);
void app_read_REG_ANA_INPUT_TH1_LOW_MS(void);
void app_read_REG_ANA_INPUT_TH1_EVT_CONF(void);
void app_read_REG_ENCODER_TH0_HIGH(void);
void app_read_REG_ENCODER_TH0_HIGH_MS(void);
void app_read_REG_ENCODER_TH0_LOW(void);
void app_read_REG_ENCODER_TH0_LOW_MS(void);
void app_read_REG_ENCODER_TH0_EVT_CONF(void);
void app_read_REG_ENCODER_TH1_HIGH(void);
void app_read_REG_ENCODER_TH1_HIGH_MS(void);
void app_read_REG_ENCODER_TH1_LOW(void);
void app_read_REG_ENCODER_TH1_LOW_MS(void);
void app_read_REG_ENCODER_TH1_EVT_CONF(void);
void app_read_REG_TH_ENABLE_EVENTS(void);
void app_read_REG_WRITE_AO(void);
void app_read_REG_ENCODER(void);

bool app_write_REG_CONFIG(void *a);
bool app_write_REG_DATA_STREAM(void *a);
bool app_write_REG_INPUTS(void *a);
bool app_write_REG_INPUT_IO0_CONFIG(void *a);
bool app_write_REG_INPUT_IO1_CONFIG(void *a);
bool app_write_REG_INPUT_IO2_CONFIG(void *a);
bool app_write_REG_OUTPUT_SET(void *a);
bool app_write_REG_OUTPUT_CLEAR(void *a);
bool app_write_REG_OUTPUT_TOGGLE(void *a);
bool app_write_REG_OUTPUT_WRITE(void *a);
bool app_write_REG_ANA_SENSOR_TH0_HIGH(void *a);
bool app_write_REG_ANA_SENSOR_TH0_HIGH_MS(void *a);
bool app_write_REG_ANA_SENSOR_TH0_LOW(void *a);
bool app_write_REG_ANA_SENSOR_TH0_LOW_MS(void *a);
bool app_write_REG_ANA_SENSOR_TH0_EVT_CONF(void *a);
bool app_write_REG_ANA_SENSOR_TH1_HIGH(void *a);
bool app_write_REG_ANA_SENSOR_TH1_HIGH_MS(void *a);
bool app_write_REG_ANA_SENSOR_TH1_LOW(void *a);
bool app_write_REG_ANA_SENSOR_TH1_LOW_MS(void *a);
bool app_write_REG_ANA_SENSOR_TH1_EVT_CONF(void *a);
bool app_write_REG_ANA_INPUT_TH0_HIGH(void *a);
bool app_write_REG_ANA_INPUT_TH0_HIGH_MS(void *a);
bool app_write_REG_ANA_INPUT_TH0_LOW(void *a);
bool app_write_REG_ANA_INPUT_TH0_LOW_MS(void *a);
bool app_write_REG_ANA_INPUT_TH0_EVT_CONF(void *a);
bool app_write_REG_ANA_INPUT_TH1_HIGH(void *a);
bool app_write_REG_ANA_INPUT_TH1_HIGH_MS(void *a);
bool app_write_REG_ANA_INPUT_TH1_LOW(void *a);
bool app_write_REG_ANA_INPUT_TH1_LOW_MS(void *a);
bool app_write_REG_ANA_INPUT_TH1_EVT_CONF(void *a);
bool app_write_REG_ENCODER_TH0_HIGH(void *a);
bool app_write_REG_ENCODER_TH0_HIGH_MS(void *a);
bool app_write_REG_ENCODER_TH0_LOW(void *a);
bool app_write_REG_ENCODER_TH0_LOW_MS(void *a);
bool app_write_REG_ENCODER_TH0_EVT_CONF(void *a);
bool app_write_REG_ENCODER_TH1_HIGH(void *a);
bool app_write_REG_ENCODER_TH1_HIGH_MS(void *a);
bool app_write_REG_ENCODER_TH1_LOW(void *a);
bool app_write_REG_ENCODER_TH1_LOW_MS(void *a);
bool app_write_REG_ENCODER_TH1_EVT_CONF(void *a);
bool app_write_REG_TH_ENABLE_EVENTS(void *a);
bool app_write_REG_WRITE_AO(void *a);
bool app_write_REG_ENCODER(void *a);


#endif /* _APP_FUNCTIONS_H_ */