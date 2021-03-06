#include "ScriptPump.h"
#include "Configuration.h"

extern Configuration Config;



ScriptPump::ScriptPump(Pump* p, bool enable, String label, unsigned int alarmDelay) : Script(enable, label, alarmDelay)
{
	pump = p;
}


ScriptPump::~ScriptPump()
{
}


bool ScriptPump::IsAlarm() {
	bool res = true;

	switch (pump->GetType()) {
	case UnitType::UT_Pump_Geo: {
		res = !((Config.DevMgr.tGeoI->GetActionStatus() == ActionStatus::ACTION_NORMAL)
			& (Config.DevMgr.tGeoO->GetActionStatus() == ActionStatus::ACTION_NORMAL));

		break;
	}
	default:
		res = false;
	}
	return res;
}

bool ScriptPump::Start(bool isSync) {
	bool res = false;

	if (pump->status == DeviceStatus::STATUS_ON) {
		res = true;
	}
	else {
		if (!IsAlarm()) {
			pump->StartPump();
			pump->status = DeviceStatus::STATUS_ON;
			res = true;
		}
	}
	return res;
}

bool ScriptPump::Stop(bool isSync) {
	bool res = false;
	if (pump->status == DeviceStatus::STATUS_OFF) {
		res = true;
		Loger::Debug("Pump Stopped(OFF)!");
	}
	else {
		pump->StopPump();
		pump->status = DeviceStatus::STATUS_OFF;
		res = true;
	}
	return res;
}

bool ScriptPump::ForceStop() {
	bool res = false;
	if (pump->status == DeviceStatus::STATUS_OFF) {
		res = true;
	}
	else {
		pump->StopPump();
		res = true;
	}
	return res;
}

