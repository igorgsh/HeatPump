#include "ScriptManager.h"
#include "Configuration.h"

extern Configuration Config;

ScriptManager::ScriptManager(DeviceManager* DevMgr)
{
	this->DevMgr = DevMgr;
	init();
}

void ScriptManager::init() {

	scriptPumpGeo = new ScriptPump(DevMgr->pumpGeo, true, "PG");
	scriptPumpContour1 = new ScriptPump(DevMgr->pumpContour1, true, "P1");
	scriptPumpContour2 = new ScriptPump(DevMgr->pumpContour2, true, "P2");
	scriptCompressor = new ScriptCompressor(&(DevMgr->compressor), true,"C1", scriptPumpGeo, scriptPumpContour1, scriptPumpContour2);

}



ScriptManager::~ScriptManager()
{
	/*
	for (int i = 0; i < NUMBER_OF_SCRIPTS; i++) {
		delete scripts[i];
	}
	*/
}


bool ScriptManager::setup() {
	bool res = false;
	scriptPumpContour1->Start(false);
	scriptPumpContour2->Start(false);
	SetCmd(ScenarioCmd::SCENARIO_START);
	return res;
}



void ScriptManager::loop() {
	// Main loop for scenario run
	scriptCompressor->Run(lastCmd);
}

void ScriptManager::SetCmd(ScenarioCmd cmd) {
	lastCmd = cmd;
}


