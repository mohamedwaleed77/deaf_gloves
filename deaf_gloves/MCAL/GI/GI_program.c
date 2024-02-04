/****************************************************/
/*   AUTHOR      : Abdelrahman Hossam               */
/*   Description : GI DRIVER                        */
/*   DATE        : 23 SEP 2022                      */
/*   VERSION     : V01                              */
/****************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "GI_interface.h"
#include "GI_private.h"
#include "GI_configuration.h"


void MGI_voidEnable (void)
{
	SET_BIT(SREG,GLOBAL_INTERRUPT_ENABLE_BIT);
}
void MGI_voidDisable (void)
{
	CLR_BIT(SREG,GLOBAL_INTERRUPT_ENABLE_BIT);
}
