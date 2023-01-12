#include "AT24C32EEPROM.h"

void EEPROMinit(defAT24C32EEPROM *at, uint8_t addresDevice, I2C_HandleTypeDef * i2c){
	at->hi2c = i2c;
	at->adrDevice = addresDevice<<1;
}
void EEPROMwrite(defAT24C32EEPROM *at, uint32_t adr, uint32_t val, EnumEEPROMType type){
	if(adr >= AT24C32_BEGINADDRESS && adr <= AT24C32_ENDADDRESS - 0x04) {
		uint8_t TXbuffer[7] = {0,};

		TXbuffer[0] = (uint8_t)(adr>>8); 	//ADDRES_DATA_LSB;
		TXbuffer[1] = (uint8_t)adr; 		//ADDRES_DATA_MSB;

		switch(type){
		case BYTE:
			TXbuffer[2] = (uint8_t)(val);
			break;
		case HALFWORD:
			TXbuffer[2] = (uint8_t)(val>>8);
			TXbuffer[3] = (uint8_t)(val);
			break;
		case WORD:
			TXbuffer[2] = (uint8_t)(val>>24);
			TXbuffer[3] = (uint8_t)(val>>16);
			TXbuffer[4] = (uint8_t)(val>>8);
			TXbuffer[5] = (uint8_t)(val);
			break;
		}

		HAL_I2C_Master_Transmit(at->hi2c, at->adrDevice, (uint8_t*)TXbuffer, (uint16_t)(2 + type), 1000);
	}
}
uint32_t EEPROMread(defAT24C32EEPROM *at, uint32_t adr, EnumEEPROMType type){
	if(adr >= AT24C32_BEGINADDRESS && adr <= AT24C32_ENDADDRESS - 0x04) {
		uint8_t TXbuffer[2] = {0,};
		uint8_t RXbuffer[4] = {0,};

		TXbuffer[0] = (uint8_t)(adr>>8); 	//ADDRES_DATA_LSB;
		TXbuffer[1] = (uint8_t)adr; 		//ADDRES_DATA_MSB;

		HAL_I2C_Master_Transmit(at->hi2c, at->adrDevice, (uint8_t*)TXbuffer, (uint16_t)(2), 1000);
		HAL_I2C_Master_Receive (at->hi2c, at->adrDevice, (uint8_t*)RXbuffer, type, 1000);

		uint32_t returnVal = 0x00;
		switch(type){
		case BYTE:
			returnVal |= RXbuffer[0];
			break;
		case HALFWORD:
			returnVal |= RXbuffer[0]<<8;
			returnVal |= RXbuffer[1];
			break;
		case WORD:
			returnVal |= RXbuffer[0]<<24;
			returnVal |= RXbuffer[1]<<16;
			returnVal |= RXbuffer[2]<<8;
			returnVal |= RXbuffer[3];
			break;
		}
		return returnVal;
	}
	return 0;
}
