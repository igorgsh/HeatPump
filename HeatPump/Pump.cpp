#include "Pump.h"
#include "Configuration.h"

extern Configuration Config;

Pump::Pump(String label, PumpType pumpType, int pin, bool on, unsigned long minTimeOn, unsigned long minTimeOff) : 
	Relay(pin,on)
{
	status = DeviceStatus::STATUS_OFF;
	type = pumpType;
	this->minTimeOn = minTimeOn;
	this->minTimeOff = minTimeOff;
	this->label = label;
}

Pump::~Pump()
{
}

void Pump::StopPump() {
	disconnect();
	lastStatusTimestamp = Config.Counter1s;
}

void Pump::StartPump() {
	connect();
	lastStatusTimestamp = Config.Counter1s;
}

void Pump::begin() {
	Relay::begin();
}
