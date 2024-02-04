
#include "../../LIB/STD_TYPES.h"


u16 HFLEX_SENSOR_CALCULATE_RES(u16 Voutput,u16 Vinput,u32 fixed_resistance){
	//voltage divider equationg is
	//Vout=Vin*(R2/(R1+R2) where R1 is the flex
	//hence
	//flex resestince = (fixed resistance * (Vin - Vout)) / Vout
	u16 flex=(fixed_resistance*(Vinput-Voutput))/Voutput;
	return flex;
}

