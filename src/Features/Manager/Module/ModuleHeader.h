#pragma once
#include "string"
#include "Utils/UtilsCollector.h"
#include "../../Value/ValueManager.h"
class Module
{
public:
	void Create(std::string name, bool state, int keyCode);
	std::string getName() {
		return name;
	};
	bool getEnabled() {
		return state;
	};
	int getKey() {
		return key;
	};
	virtual void onPreCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) {};
	virtual void onPostCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) {};
	virtual void onPrePrediction(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) {};
	virtual void onPrediction(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal,int PredictedFlags) {};
	virtual void onPostPrediction(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) {};
	virtual void onRender2D() {};
	void toggle() { 
		state = !state;
		if (state) {
			onEnabled();
		}
		else {
			onDisabled();
		}
	};
	virtual void onEnabled() {};
	virtual void onDisabled() {};
	 int keytimeout = 0;
	 bool ShouldToggle()
	 {
		 return keytimeout <= 0;
	 }
	 int animate = 20;
	 void updateanimate() {
		 if (state) {
			 if (animate > 0)
			 {
				animate--;
			 }
		 }
		 else {
			 animate = 20;
		 }
	 }
private:
	 std::string name;
	 bool state = false;
	 int key = 0;
};

inline void Module::Create(std::string name, bool state, int keyCode) {
	this->name = name;
	this->state = state;
	this->key = keyCode;
}