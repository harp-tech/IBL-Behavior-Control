#ifndef _APP_IOS_AND_REGS_H_
#define _APP_IOS_AND_REGS_H_
#include "cpu.h"

void init_ios(void);
/************************************************************************/
/* Definition of input pins                                             */
/************************************************************************/
// ADC_SDO                Description: Data from the analog sensor's ADC
// USER                   Description: USER's input button
// IO0                    Description: IO0 as input
// IO1                    Description: IO1 as input 
// IO2                    Description: IO2 as input 

#define read_ADC_SDO read_io(PORTJ, 3)          // ADC_SDO
#define read_USER read_io(PORTC, 2)             // USER
#define read_IO0 read_io(PORTF, 1)              // IO0
#define read_IO1 read_io(PORTK, 1)              // IO1
#define read_IO2 read_io(PORTK, 2)              // IO2

/************************************************************************/
/* Definition of output pins                                            */
/************************************************************************/
// CLOCK_IN_EN            Description: Device is sync from the external CLKIN
// CLOCK_OUT_EN           Description: Device syncs devices trough CLKOUT
// RELAY                  Description: Sends analog sensor to port A0
// ADC_SCLK               Description: Clock of the analog sensor's ADC
// ADC_CNVST              Description: Conversion of the analog sensor's ADC
// EN_MASTER              Description: Selects the comunication flow
// LED_CLKIN              Description: Drives the CLKIN LED
// LED_IO0                Description: Drives the IO0 LED
// LED_IO1                Description: Drives the IO1 LED
// LED_IO2                Description: Drives the IO2 LED
// LED_SLAVE              Description: Drives the SLAVE LED
// LED_MASTER             Description: Drives the MASTER LED
// LED_STATE              Description: Drives the STATE LED
// LED_POWER              Description: Drives the POWER LED
// IO0                    Description: IO0 as output
// IO1                    Description: IO1 as output
// IO2                    Description: IO2 as output
// IO0_DIR                Description: Configures IO0 direction
// IO1_DIR                Description: Configures IO1 direction
// IO2_DIR                Description: Configures I20 direction

/* CLOCK_IN_EN */
#define set_CLOCK_IN_EN set_io(PORTF, 4)
#define clr_CLOCK_IN_EN clear_io(PORTF, 4)
#define tgl_CLOCK_IN_EN toggle_io(PORTF, 4)
#define read_CLOCK_IN_EN read_io(PORTF, 4)

/* CLOCK_OUT_EN */
#define set_CLOCK_OUT_EN set_io(PORTF, 5)
#define clr_CLOCK_OUT_EN clear_io(PORTF, 5)
#define tgl_CLOCK_OUT_EN toggle_io(PORTF, 5)
#define read_CLOCK_OUT_EN read_io(PORTF, 5)

/* RELAY */
#define set_RELAY set_io(PORTK, 3)
#define clr_RELAY clear_io(PORTK, 3)
#define tgl_RELAY toggle_io(PORTK, 3)
#define read_RELAY read_io(PORTK, 3)

/* ADC_SCLK */
#define set_ADC_SCLK set_io(PORTJ, 4)
#define clr_ADC_SCLK clear_io(PORTJ, 4)
#define tgl_ADC_SCLK toggle_io(PORTJ, 4)
#define read_ADC_SCLK read_io(PORTJ, 4)

/* ADC_CNVST */
#define set_ADC_CNVST set_io(PORTJ, 5)
#define clr_ADC_CNVST clear_io(PORTJ, 5)
#define tgl_ADC_CNVST toggle_io(PORTJ, 5)
#define read_ADC_CNVST read_io(PORTJ, 5)

/* EN_MASTER */
#define set_EN_MASTER set_io(PORTD, 1)
#define clr_EN_MASTER clear_io(PORTD, 1)
#define tgl_EN_MASTER toggle_io(PORTD, 1)
#define read_EN_MASTER read_io(PORTD, 1)

/* LED_CLKIN */
#define set_LED_CLKIN set_io(PORTH, 2)
#define clr_LED_CLKIN clear_io(PORTH, 2)
#define tgl_LED_CLKIN toggle_io(PORTH, 2)
#define read_LED_CLKIN read_io(PORTH, 2)

/* LED_IO0 */
#define set_LED_IO0 set_io(PORTH, 4)
#define clr_LED_IO0 clear_io(PORTH, 4)
#define tgl_LED_IO0 toggle_io(PORTH, 4)
#define read_LED_IO0 read_io(PORTH, 4)

/* LED_IO1 */
#define set_LED_IO1 set_io(PORTH, 6)
#define clr_LED_IO1 clear_io(PORTH, 6)
#define tgl_LED_IO1 toggle_io(PORTH, 6)
#define read_LED_IO1 read_io(PORTH, 6)

/* LED_IO2 */
#define set_LED_IO2 set_io(PORTH, 7)
#define clr_LED_IO2 clear_io(PORTH, 7)
#define tgl_LED_IO2 toggle_io(PORTH, 7)
#define read_LED_IO2 read_io(PORTH, 7)

/* LED_SLAVE */
#define set_LED_SLAVE set_io(PORTH, 3)
#define clr_LED_SLAVE clear_io(PORTH, 3)
#define tgl_LED_SLAVE toggle_io(PORTH, 3)
#define read_LED_SLAVE read_io(PORTH, 3)

/* LED_MASTER */
#define set_LED_MASTER set_io(PORTH, 5)
#define clr_LED_MASTER clear_io(PORTH, 5)
#define tgl_LED_MASTER toggle_io(PORTH, 5)
#define read_LED_MASTER read_io(PORTH, 5)

/* LED_STATE */
#define set_LED_STATE set_io(PORTA, 6)
#define clr_LED_STATE clear_io(PORTA, 6)
#define tgl_LED_STATE toggle_io(PORTA, 6)
#define read_LED_STATE read_io(PORTA, 6)

/* LED_POWER */
#define set_LED_POWER set_io(PORTJ, 0)
#define clr_LED_POWER clear_io(PORTJ, 0)
#define tgl_LED_POWER toggle_io(PORTJ, 0)
#define read_LED_POWER read_io(PORTJ, 0)

/* IO0 */
#define set_IO0 set_io(PORTF, 1)
#define clr_IO0 clear_io(PORTF, 1)
#define tgl_IO0 toggle_io(PORTF, 1)
#define read_IO0 read_io(PORTF, 1)

/* IO1 */
#define set_IO1 set_io(PORTK, 1)
#define clr_IO1 clear_io(PORTK, 1)
#define tgl_IO1 toggle_io(PORTK, 1)
#define read_IO1 read_io(PORTK, 1)

/* IO2 */
#define set_IO2 set_io(PORTK, 2)
#define clr_IO2 clear_io(PORTK, 2)
#define tgl_IO2 toggle_io(PORTK, 2)
#define read_IO2 read_io(PORTK, 2)

/* IO0_DIR */
#define set_IO0_DIR set_io(PORTK, 5)
#define clr_IO0_DIR clear_io(PORTK, 5)
#define tgl_IO0_DIR toggle_io(PORTK, 5)
#define read_IO0_DIR read_io(PORTK, 5)

/* IO1_DIR */
#define set_IO1_DIR set_io(PORTK, 6)
#define clr_IO1_DIR clear_io(PORTK, 6)
#define tgl_IO1_DIR toggle_io(PORTK, 6)
#define read_IO1_DIR read_io(PORTK, 6)

/* IO2_DIR */
#define set_IO2_DIR set_io(PORTK, 7)
#define clr_IO2_DIR clear_io(PORTK, 7)
#define tgl_IO2_DIR toggle_io(PORTK, 7)
#define read_IO2_DIR read_io(PORTK, 7)


/************************************************************************/
/* Registers' structure                                                 */
/************************************************************************/
typedef struct
{
	uint16_t REG_CONFIG;
	int16_t REG_DATA_STREAM[4];
	uint8_t REG_INPUTS;
	uint8_t REG_INPUT_IO0_CONFIG;
	uint8_t REG_INPUT_IO1_CONFIG;
	uint8_t REG_INPUT_IO2_CONFIG;
	uint8_t REG_OUTPUT_SET;
	uint8_t REG_OUTPUT_CLEAR;
	uint8_t REG_OUTPUT_TOGGLE;
	uint8_t REG_OUTPUT_WRITE;
	uint16_t REG_ANA_SENSOR_TH0_HIGH;
	uint16_t REG_ANA_SENSOR_TH0_HIGH_MS;
	uint16_t REG_ANA_SENSOR_TH0_LOW;
	uint16_t REG_ANA_SENSOR_TH0_LOW_MS;
	uint8_t REG_ANA_SENSOR_TH0_EVT_CONF;
	uint16_t REG_ANA_SENSOR_TH1_HIGH;
	uint16_t REG_ANA_SENSOR_TH1_HIGH_MS;
	uint16_t REG_ANA_SENSOR_TH1_LOW;
	uint16_t REG_ANA_SENSOR_TH1_LOW_MS;
	uint8_t REG_ANA_SENSOR_TH1_EVT_CONF;
	uint16_t REG_ANA_INPUT_TH0_HIGH;
	uint16_t REG_ANA_INPUT_TH0_HIGH_MS;
	uint16_t REG_ANA_INPUT_TH0_LOW;
	uint16_t REG_ANA_INPUT_TH0_LOW_MS;
	uint8_t REG_ANA_INPUT_TH0_EVT_CONF;
	uint16_t REG_ANA_INPUT_TH1_HIGH;
	uint16_t REG_ANA_INPUT_TH1_HIGH_MS;
	uint16_t REG_ANA_INPUT_TH1_LOW;
	uint16_t REG_ANA_INPUT_TH1_LOW_MS;
	uint8_t REG_ANA_INPUT_TH1_EVT_CONF;
	int16_t REG_ENCODER_TH0_HIGH;
	uint16_t REG_ENCODER_TH0_HIGH_MS;
	int16_t REG_ENCODER_TH0_LOW;
	uint16_t REG_ENCODER_TH0_LOW_MS;
	uint8_t REG_ENCODER_TH0_EVT_CONF;
	int16_t REG_ENCODER_TH1_HIGH;
	uint16_t REG_ENCODER_TH1_HIGH_MS;
	int16_t REG_ENCODER_TH1_LOW;
	uint16_t REG_ENCODER_TH1_LOW_MS;
	uint8_t REG_ENCODER_TH1_EVT_CONF;
	uint8_t REG_TH_ENABLE_EVENTS;
	uint16_t REG_WRITE_AO;
	int16_t REG_ENCODER;
} AppRegs;

/************************************************************************/
/* Registers' address                                                   */
/************************************************************************/
/* Registers */
#define ADD_REG_CONFIG                      32 // U16    Configures the device
#define ADD_REG_DATA_STREAM                 33 // I16    [0] Analog sensor [1] Analog input [2] Encoder [3] … (ENTH1) (ENTH0) (AITH1) (AITH0)  (ASTH1) (ASTH0) 
#define ADD_REG_INPUTS                      34 // U8     Contains the state of the digital inputs (IO2) (IO1) (IO0)
#define ADD_REG_INPUT_IO0_CONFIG            35 // U8     Configuration of IO0 when used as digital input
#define ADD_REG_INPUT_IO1_CONFIG            36 // U8     Configuration of IO1 when used as digital input
#define ADD_REG_INPUT_IO2_CONFIG            37 // U8     Configuration of IO2 when used as digital input
#define ADD_REG_OUTPUT_SET                  38 // U8     Sets the IOx according to bit mask
#define ADD_REG_OUTPUT_CLEAR                39 // U8     Clears the IOx according to bit mask
#define ADD_REG_OUTPUT_TOGGLE               40 // U8     Toggle the IOx according to bit mask
#define ADD_REG_OUTPUT_WRITE                41 // U8     Write to all the IOx according to bit mask
#define ADD_REG_ANA_SENSOR_TH0_HIGH         42 // U16    Sets the higher threshold 0 for the analog sensor
#define ADD_REG_ANA_SENSOR_TH0_HIGH_MS      43 // U16    Sets the number of milliseconds to consider a valid high threshold 0
#define ADD_REG_ANA_SENSOR_TH0_LOW          44 // U16    Sets the lower threshold 0 for the analog sensor
#define ADD_REG_ANA_SENSOR_TH0_LOW_MS       45 // U16    Sets the number of milliseconds to consider a valid low threshold 0
#define ADD_REG_ANA_SENSOR_TH0_EVT_CONF     46 // U8     Configures what to do when the thresholds 0 are crossed
#define ADD_REG_ANA_SENSOR_TH1_HIGH         47 // U16    Sets the higher threshold 1 for the analog sensor
#define ADD_REG_ANA_SENSOR_TH1_HIGH_MS      48 // U16    Sets the number of milliseconds to consider a valid high threshold 1
#define ADD_REG_ANA_SENSOR_TH1_LOW          49 // U16    Sets the lower threshold 1 for the analog sensor
#define ADD_REG_ANA_SENSOR_TH1_LOW_MS       50 // U16    Sets the number of milliseconds to consider a valid low threshold 1
#define ADD_REG_ANA_SENSOR_TH1_EVT_CONF     51 // U8     Configures what to do when the thresholds 1 are crossed
#define ADD_REG_ANA_INPUT_TH0_HIGH          52 // U16    Sets the higher threshold 0 for the analog input
#define ADD_REG_ANA_INPUT_TH0_HIGH_MS       53 // U16    Sets the number of milliseconds to consider a valid high threshold 0
#define ADD_REG_ANA_INPUT_TH0_LOW           54 // U16    Sets the lower threshold 0 for the analog input
#define ADD_REG_ANA_INPUT_TH0_LOW_MS        55 // U16    Sets the number of milliseconds to consider a valid low threshold 0
#define ADD_REG_ANA_INPUT_TH0_EVT_CONF      56 // U8     Configures what to do when the thresholds 0 are crossed
#define ADD_REG_ANA_INPUT_TH1_HIGH          57 // U16    Sets the higher threshold 1 for the analog input
#define ADD_REG_ANA_INPUT_TH1_HIGH_MS       58 // U16    Sets the number of milliseconds to consider a valid high threshold 1
#define ADD_REG_ANA_INPUT_TH1_LOW           59 // U16    Sets the lower threshold 1 for the analog input
#define ADD_REG_ANA_INPUT_TH1_LOW_MS        60 // U16    Sets the number of milliseconds to consider a valid low threshold 1
#define ADD_REG_ANA_INPUT_TH1_EVT_CONF      61 // U8     Configures what to do when the thresholds 1 are crossed
#define ADD_REG_ENCODER_TH0_HIGH            62 // I16    Sets the higher threshold 0 for the encoder
#define ADD_REG_ENCODER_TH0_HIGH_MS         63 // U16    Sets the number of milliseconds to consider a valid high threshold 0
#define ADD_REG_ENCODER_TH0_LOW             64 // I16    Sets the lower threshold 0 for the encoder
#define ADD_REG_ENCODER_TH0_LOW_MS          65 // U16    Sets the number of milliseconds to consider a valid low threshold 0
#define ADD_REG_ENCODER_TH0_EVT_CONF        66 // U8     Configures what to do when the thresholds 0 are crossed
#define ADD_REG_ENCODER_TH1_HIGH            67 // I16    Sets the higher threshold 1 for the encoder
#define ADD_REG_ENCODER_TH1_HIGH_MS         68 // U16    Sets the number of milliseconds to consider a valid high threshold 1
#define ADD_REG_ENCODER_TH1_LOW             69 // I16    Sets the lower threshold 1 for the encoder
#define ADD_REG_ENCODER_TH1_LOW_MS          70 // U16    Sets the number of milliseconds to consider a valid low threshold 1
#define ADD_REG_ENCODER_TH1_EVT_CONF        71 // U8     Configures what to do when the thresholds 1 are crossed
#define ADD_REG_TH_ENABLE_EVENTS            72 // U8     Enables the events from the threshold detection (uses DATA_STREAM bit masks)
#define ADD_REG_WRITE_AO                    73 // U16    Writes to the analog output available on port AO
#define ADD_REG_ENCODER                     74 // I16    Value of the digital encoder

/************************************************************************/
/* PWM Generator registers' memory limits                               */
/*                                                                      */
/* DON'T change the APP_REGS_ADD_MIN value !!!                          */
/* DON'T change these names !!!                                         */
/************************************************************************/
/* Memory limits */
#define APP_REGS_ADD_MIN                    0x20
#define APP_REGS_ADD_MAX                    0x4A
#define APP_NBYTES_OF_REG_BANK              77

/************************************************************************/
/* Registers' bits                                                      */
/************************************************************************/
#define B_SYNC_TO_MASTER                   (1<<0)       // The device outputs the internal clock sync
#define B_SYNC_TO_SLAVE                    (1<<1)       // The device receives the clock sync trough CLKIN and daisy chain it into CLKOUT
#define B_ANA_SENSOR_TO_AO                 (1<<2)       // The analog sensor data is sent to port AO
#define B_ANA_INTERNAL_TO_AO               (1<<3)       // The internal analog generator is sent to port AO
#define B_EN_AI                            (1<<4)       // Enables the analog input on port AI
#define B_COM_TO_MAIN                      (1<<5)       // USB interface is connected to the main microcontroller
#define B_COM_TO_SCREEN                    (1<<6)       // USB interface is connected to the timestamp microcontroller
#define B_IO0_TO_INPUT                     (1<<7)       // Configures the port IO0 to be a digital 0-5V output
#define B_IO0_TO_OUTPUT                    (1<<8)       // Configures the port IO0 to be a digital input
#define B_IO1_TO_INPUT                     (1<<9)       // Configures the port IO1 to be a digital 0-5V output
#define B_IO1_TO_OUTPUT                    (1<<10)      // Configures the port IO1 to be a digital input
#define B_IO2_TO_INPUT                     (1<<11)      // Configures the port IO2 to be a digital 0-5V output
#define B_IO2_TO_OUTPUT                    (1<<12)      // Configures the port IO2 to be a digital input
#define B_DATA_QUIET                       (1<<13)      // Data is sent based on events according to  register TH_ENABLE_EVENTS
#define B_DATA_1Khz                        (1<<14)      // Data is streamed at 1 KHz
#define B_ASTH0                            (1<<0)       // 
#define B_ASTH1                            (1<<1)       // 
#define B_AITH0                            (1<<2)       // 
#define B_AITH1                            (1<<3)       // 
#define B_ENTH0                            (1<<4)       // 
#define B_ENTH1                            (1<<5)       // 
#define MSK_INPUT_OPTIONS                  0x03         // Options available for registers INPUT_IOx_CONFIG
#define GM_INPUT_NOT_USED                  (0<<0)       // Input is not used
#define GM_INPUT_SENSE_RISING              (1<<0)       // Input sensitive to rising only
#define GM_INPUT_SENSE_FALLING             (2<<0)       // Input sensitive to falling only
#define GM_INPUT_SENSE_BOTH                (3<<0)       // Input sensitive to any state change
#define B_IO0                              (1<<0)       // Mask of IO0
#define B_IO1                              (1<<1)       // Mask of IO1
#define B_IO2                              (1<<2)       // Mask of IO2
#define B_USER                             (1<<3)       // Mask of USER's button
#define MSK_TH_OPTIONS                     0x07         // Options for registers ANA_x_THx_EVT_CONF and ENCODER_THx_EVT_CONF
#define GM_TH_NOT_USED                     (0<<0)       // Not used
#define GM_TH_ON_IO0                       (1<<0)       // Externalize event on IO0
#define GM_TH_ON_IO1                       (2<<0)       // Externalize event on IO1
#define GM_TH_ON_IO2                       (3<<0)       // Externalize event on IO2

#endif /* _APP_REGS_H_ */