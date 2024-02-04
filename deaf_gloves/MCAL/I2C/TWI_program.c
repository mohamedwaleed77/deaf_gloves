
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_config.h"

void TWI_init(void)
{
    /* Bit Rate: 400.000 kbps using (pre-scaler=1 -->TWPS=00) and F_CPU=8Mhz */
    TWBR = 0x02;
	TWSR = 0x00;

    /* Two Wire Bus address my address if any master device want to call me:
     * bits(7:1) 0x1 (used in case this MC is a slave device)
     * bit 0: General Call Recognition: Off
     */
    TWAR = 0b00000010; // my address = 0x01 :)

    TWCR = (1<<TWCR_TWEN); /* enable TWI */
}

void TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1 (not cleared automatically)
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWSTA) | (1 << TWCR_TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWCR_TWINT));
}

void TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWSTO) | (1 << TWCR_TWEN);
}


/* write cmd
 * Function to Send Slave Address for Write operation */
void TWI_writeByte(u8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWCR_TWINT));
}

u8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN) | (1 << TWCR_TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWCR_TWINT));
    /* Read Data */
    return TWDR;
}

u8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWCR_TWINT) | (1 << TWCR_TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWCR_TWINT));
    /* Read Data */
    return TWDR;
}

u8 TWI_getStatus(void)
{
    u8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
