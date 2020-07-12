#include "cpu.h"
#include "hwbp_core_types.h"
#include "app_ios_and_regs.h"
#include "app_funcs.h"
#include "hwbp_core.h"

/************************************************************************/
/* Declare application registers                                        */
/************************************************************************/
extern AppRegs app_regs;

/************************************************************************/
/* Interrupts from Timers                                               */
/************************************************************************/
// ISR(TCC0_OVF_vect, ISR_NAKED)
// ISR(TCD0_OVF_vect, ISR_NAKED)
// ISR(TCE0_OVF_vect, ISR_NAKED)
// ISR(TCF0_OVF_vect, ISR_NAKED)
// 
// ISR(TCC0_CCA_vect, ISR_NAKED)
// ISR(TCD0_CCA_vect, ISR_NAKED)
// ISR(TCE0_CCA_vect, ISR_NAKED)
// ISR(TCF0_CCA_vect, ISR_NAKED)
// 
// ISR(TCD1_OVF_vect, ISR_NAKED)
// 
// ISR(TCD1_CCA_vect, ISR_NAKED)

/************************************************************************/ 
/* USER                                                                 */
/************************************************************************/
ISR(PORTC_INT0_vect, ISR_NAKED)
{
	reti();
}

/************************************************************************/
/* IO0                                                                  */
/************************************************************************/
ISR(PORTF_INT0_vect, ISR_NAKED)
{
	if(read_IO0) {if(core_bool_is_visual_enabled()) set_LED_IO0;} else clr_LED_IO0;
	reti();
}

/************************************************************************/
/* IO1                                                                  */
/************************************************************************/
ISR(PORTK_INT0_vect, ISR_NAKED)
{
	if(read_IO1) {if(core_bool_is_visual_enabled()) set_LED_IO1;} else clr_LED_IO1;
	reti();
}

/************************************************************************/
/* IO2                                                                  */
/************************************************************************/
ISR(PORTK_INT1_vect, ISR_NAKED)
{
	if(read_IO2) {if(core_bool_is_visual_enabled()) set_LED_IO2;} else clr_LED_IO2;
	reti();
}

