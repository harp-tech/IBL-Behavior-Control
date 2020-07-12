#ifndef _ADC_H_
#define _ADC_H_
#include <avr/io.h>
#include "cpu.h"

#define ADC_ACCUMULATOR_TARGET 64			// This number needs to be a 2^n

											// Measured with the photodiode plugged in
											// 128 2 bits ~0.403 mVp-p
											// 64  3 bits ~0.604 mVp-p
											// 32  4 bits ~0.806 mVp-p
											// 16  7 bits ~1.410 mVp-p
											// 8   14 bits ~2.820 mVp-p
											
#define ACCUMULATOR_INTERVAL_uS_FLOAT 4

#define START_ACCUMULATOR_TIMER	do { \
	set_ADC_CNVST; \
	set_ADC_CNVST; \
	clr_ADC_CNVST; \
	timer_type1_enable(&TCD1, TIMER_PRESCALER_DIV1,  ACCUMULATOR_INTERVAL_uS_FLOAT * 32,   INT_LEVEL_LOW); \
} while (0)

#endif /* _ADC_H_ */