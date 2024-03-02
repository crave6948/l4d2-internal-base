#pragma once
#include "Module/Modules/Player/BunnyHop.h"
#include "Module/Modules/Render/Arraylist.h"
#include "Module/Modules/Render/ESPHelper.h"
#include "Module/Modules/Combat/Aimbot.h"
#include "Module/Modules/Combat/NoSpread.h"
#include "Module/Modules/Combat/AutoShoot/AutoShoot.h"
#include "Module/Modules/Combat/FastMelee/FastMelee.h"

#include "../Engine/Prediction/EnginePrediction.h"
namespace Client::Module
{
    class ModuleManager
    {
    private:
        /* data */
    public:
        ModuleManager();
		std::vector<Module*> featurelist;
		//real class
		BunnyHopModule::BunnyHop bhop = BunnyHopModule::BunnyHop();
		
		ArraylistModule::Arraylist arraylist = ArraylistModule::Arraylist();
		
		AimbotModule::Aimbot aimbot = AimbotModule::Aimbot();
		NoSpreadModule::NoSpread noSpread = NoSpreadModule::NoSpread();
		AutoShootModule::AutoShoot autoShoot = AutoShootModule::AutoShoot();
		FastMeleeModule::FastMelee fastMelee = FastMeleeModule::FastMelee();

		ESPHelperModule::ESPHelper espHelper = ESPHelperModule::ESPHelper();
		
		//pointer
		BunnyHopModule::BunnyHop* bhop_ptr = &bhop;
		ArraylistModule::Arraylist* arraylist_ptr = &arraylist;
		AimbotModule::Aimbot* aimbot_ptr = &aimbot;
		NoSpreadModule::NoSpread* noSpread_ptr = &noSpread;
		ESPHelperModule::ESPHelper* espHelper_ptr = &espHelper;
		AutoShootModule::AutoShoot* autoShoot_ptr = &autoShoot;
		FastMeleeModule::FastMelee* fastMelee_ptr = &fastMelee;
		void Init();
		void onRender2D();
		void onCreateMove(CUserCmd* cmd, C_TerrorPlayer* pLocal);
		void onKey();
    };
}
