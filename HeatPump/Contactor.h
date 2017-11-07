#pragma once
#include "Sensor.h"
class Contactor :
	public Sensor
{
public:
	~Contactor();

	Contactor(String label, int pin, bool lhOn, bool alarmOn, int critThreshold);
	void begin();
	bool checkDataReady();
	bool loop();

private:
	bool lhOn;
	void init();
	bool AlarmOn;

};
