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
	if(read_USER)
	{
		app_regs.REG_INPUTS &= ~B_USER;
	}
	else
	{
		app_regs.REG_INPUTS |= B_USER;
	}
		
	core_func_send_event(ADD_REG_INPUTS, true);
		
	reti();
}

/************************************************************************/
/* IO0                                                                  */
/************************************************************************/
ISR(PORTF_INT0_vect, ISR_NAKED)
{
	if(read_IO0)
	{
		app_regs.REG_INPUTS |= B_IO0;
	}
	else
	{
		app_regs.REG_INPUTS &= ~B_IO0;
	}
	
	core_func_send_event(ADD_REG_INPUTS, true);
	
	reti();
}

/************************************************************************/
/* IO1                                                                  */
/************************************************************************/
ISR(PORTK_INT0_vect, ISR_NAKED)
{
	if(read_IO1)
	{
		app_regs.REG_INPUTS |= B_IO1;
	}
	else
	{
		app_regs.REG_INPUTS &= ~B_IO1;
	}
	
	core_func_send_event(ADD_REG_INPUTS, true);
	
	reti();
}

/************************************************************************/
/* IO2                                                                  */
/************************************************************************/
ISR(PORTK_INT1_vect, ISR_NAKED)
{
	if(read_IO2)
	{
		app_regs.REG_INPUTS |= B_IO2;
	}
	else
	{
		app_regs.REG_INPUTS &= ~B_IO2;
	}
	
	core_func_send_event(ADD_REG_INPUTS, true);
	
	reti();
}

