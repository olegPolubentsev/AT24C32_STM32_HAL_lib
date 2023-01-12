
#ifndef EXTERNDRIVERS_AT24C32_EEPROM_AT24C32EEPROM_H_
#define EXTERNDRIVERS_AT24C32_EEPROM_AT24C32EEPROM_H_

#include "main.h"

#define AT24C32_BEGINADDRESS 	0x00
#define AT24C32_ENDADDRESS 		0x8000  //AT24C64 => 0x10000

typedef enum EnumEEPROMType{
	BYTE = 1,
	HALFWORD = 2,
	WORD = 4
}EnumEEPROMType;

typedef struct{
	I2C_HandleTypeDef *hi2c;
	uint8_t adrDevice;
} defAT24C32EEPROM;

void EEPROMinit(defAT24C32EEPROM *at, uint8_t addresDevice, I2C_HandleTypeDef * i2c);
void EEPROMwrite(defAT24C32EEPROM *at, uint32_t adr, uint32_t val, EnumEEPROMType type);
uint32_t EEPROMread(defAT24C32EEPROM *at, uint32_t adr, EnumEEPROMType type);


#endif /* EXTERNDRIVERS_AT24C32_EEPROM_AT24C32EEPROM_H_ */
