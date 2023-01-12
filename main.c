#include "AT24C32EEPROM.h"

defAT24C32EEPROM			eeprom;

void main(){

	/*
	 * Address device:
	 * A0-A2 GNG or VCC
	 *    | 0x50 | 0x51 | 0x52 | 0x53 | 0x54 | 0x55 | 0x56 | 0x57 |
	 * ------------------------------------------------------------
	 * A0 |   0  |   0  |   0  |   0  |   1  |   1  |   1  |   1  |
	 * A1 |   0  |   0  |   1  |   1  |   0  |   0  |   1  |   1  |
	 * A2 |   0  |   1  |   0  |   1  |   0  |   1  |   0  |   1  |
	 */
	EEPROMinit(&eeprom, 0x57, &hi2c1);
	uint16_t valWrite = 0xA11A;
	uint16_t valRead = 0;
	#define ADDRESS_VAL 0x1000

	/*
	*	0x00 to 0x8000 (32Kbyte = 32768byte)
	*	uint8_t   => 1byte => address+=0x01
	*	uint16_t  => 2byte => address+=0x02
	*	uint32_t  => 4byte => address+=0x04
	*/

	while(1){
		EEPROMwrite(&eeprom, ADDRESS_VAL, valWrite, HALFWORD);
		valRead = EEPROMread(&eeprom, ADDRESS_VAL, HALFWORD);
	}
}
