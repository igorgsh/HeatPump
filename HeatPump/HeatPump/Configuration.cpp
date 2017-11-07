#include "Configuration.h"
#include "Definitions.h"
#include "EEPROM.h"

#define WEB_ENABLED 1


Configuration::Configuration()
{
}


Configuration::~Configuration()
{
}

void Configuration::loop1() {
	DevMgr.loop1();
	ScenMgr.loop1();
}

void Configuration::loop5() {
#ifdef WEB_ENABLED
	web.loop();

#endif // WEB_ENABLED

	DevMgr.loop5();
	ScenMgr.loop5();
}

void Configuration::loop10() {
	DevMgr.loop10();
	ScenMgr.loop10();
}

void Configuration::begin() {
	DevMgr.begin();

#ifdef WEB_ENABLED
	Debug("Server Is Starting...");
	web.begin();
#endif
}

float Configuration::OutTemperature() {
	float outTemp = 0;
	if (desiredTemp<= 20)
		outTemp = 25;
	else if (desiredTemp >=45)
		outTemp = 45;
	else 
		outTemp = desiredTemp+5;
	return outTemp;
}

void Configuration::EepromWrite(unsigned int addr, byte value) {

	EEPROM.write(addr, value);
}

void Configuration::EepromWrite(unsigned int addr, unsigned int value) {

	EEPROM.write(addr, value%256);
	EEPROM.write(addr + 1, (value >> 8) & 0xFF);
}

byte Configuration::EepromRead(unsigned int addr) {
	return EEPROM.read(addr);
}

unsigned int Configuration::EepromRead2(unsigned int addr) {
	byte x;
	byte b;

	x = EEPROM.read(addr);
	b = EEPROM.read(addr + 1);
	return (unsigned)b << 8 & x;
}


void Configuration::setDesiredTemp(byte value) {
	
	if (desiredTemp != value) { //optimization: reduce number of write to EEPROM
		desiredTemp = value;
		EepromWrite(EEPROM_Desired_Temp, desiredTemp);
	}
}