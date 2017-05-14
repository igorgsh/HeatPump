#pragma once
#include "Arduino.h"

typedef enum {
	NOSENSOR = 0,
	THERMOMETER = 1,
	CONTACT = 2
} SensorType;
/*
typedef enum {
	NO_ERROR = 0,
	SENSOR_DISCONNECTED = 1,
	LOW_VALUE = 2,
	HIGH_VALUE = 3,
	CONTACT_ERROR = 4
} ErrorCode;
*/
typedef enum {
	ACTION_NODATA = 0,
	ACTION_LOW = 1,
	ACTION_NORMAL = 2,
	ACTION_HIGH = 3
} ActionStatus;


class Sensor
{
public:
	Sensor(String label, int pin, float actionLow, float actionHigh, int critThreshold = 5);
	//SType of Sensor
	SensorType type = NOSENSOR;
	SensorType getType() { return type; };

	//Current value of sensor
	virtual float getValue() { return currentValue; };

	// Last Eror
//	ErrorCode getError() { return error; };
//	void setError(ErrorCode e) { error = e; };
	// Number of errors occured
	int ErrorCounter = 0;
	// Is error critical
	virtual bool isCritical() { return (ErrorCounter >= criticalThreshold); };

	//Label of Sensor
	String getLabel() { return label; };
	void setLabel(String lbl) { label = lbl; };

	//Pin where sensor is connected
	int getPin() { return pin; };

	// Request values from sensor
	virtual bool loop(unsigned long counter) = 0;

	bool getData();

	ActionStatus getActionStatus() { return actionStatus; };

	void setActionLow(float value) { actionLow = value; };
	float getActionLow() { return actionLow; };
	void setActionHigh(float value) { actionHigh = value; };
	float getActionHigh() { return actionHigh; };
	void setCriticalThreshold(int value) { criticalThreshold = value; };
	int getCriticalThreshold() { return criticalThreshold; };

protected:
	// Is Data Ready for this Sensor
	virtual bool checkDataReady() = 0;
//	ErrorCode error = NO_ERROR;
	String label;
	int pin;
	// Alarm line: AlarmLow: -... alarmLow); No Alarm: alarmLow...alarmHigh;AlarmHigh:alarmHigh...
	// Action line: ActionLow:-...actionLow; ActionNormal:actionLow...actionHigh; ActionHigh: actionHigh...+ 
//	float alarmLow;
//	float alarmHigh;
	float actionLow;
	float actionHigh;



	// how many times alarm should be set before it became critical
	int criticalThreshold;

	ActionStatus actionStatus = ActionStatus::ACTION_NODATA;
//	AlarmStatus alarmStatus = AlarmStatus::ALARM_LOW;

	float currentValue;
private:
	void init(String label, int pin, float actionLow, float actionHigh, int critThreshold);

};

