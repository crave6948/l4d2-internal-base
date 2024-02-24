#pragma once
#include "../../SDK/SDK.h"
#include "../ESP/ESP.h"
#include "../EnginePrediction/EnginePrediction.h"
#include "vector"
#include "Module/Modules/Player/BunnyHop.h"
#include "Module/Modules/Render/Arraylist.h"
#include "Module/Modules/Render/ESPHelper.h"
// #include "Module/Modules/Combat/Aimbot.h"
// #include "Module/Modules/Combat/NoSpread.h"
#include "Module/Modules/Combat/AutoShoot/AutoShoot.h"
namespace F {
	class Manager {

	public:
		std::vector<Module*> featurelist;
		//real class
		BunnyHopModule::BunnyHop bhop = BunnyHopModule::BunnyHop();
		
		ArraylistModule::Arraylist arraylist = ArraylistModule::Arraylist();
		
		AimbotModule::Aimbot aimbot = AimbotModule::Aimbot();
		NoSpreadModule::NoSpread noSpread = NoSpreadModule::NoSpread();
		AutoShootModule::AutoShoot autoShoot = AutoShootModule::AutoShoot();

		ESPHelperModule::ESPHelper espHelper = ESPHelperModule::ESPHelper();
		
		//pointer
		BunnyHopModule::BunnyHop* bhop_ptr = &bhop;
		ArraylistModule::Arraylist* arraylist_ptr = &arraylist;
		AimbotModule::Aimbot* aimbot_ptr = &aimbot;
		NoSpreadModule::NoSpread* noSpread_ptr = &noSpread;
		ESPHelperModule::ESPHelper* espHelper_ptr = &espHelper;
		AutoShootModule::AutoShoot* autoShoot_ptr = &autoShoot;
		void Init();
		void onRender2D();
		void onCreateMove(CUserCmd* cmd, C_TerrorPlayer* pLocal);
		void onKey();
	};
	inline Manager FeatureManager; 
}