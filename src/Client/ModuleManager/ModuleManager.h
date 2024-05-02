#pragma once
#include "Module/Modules/Player/BunnyHop.h"

#include "Module/Modules/Render/Arraylist.h"
#include "Module/Modules/Render/ClickGui/ClickGuiModule.h"
#include "Module/Modules/Render/ESPHelper.h"
#include "Module/Modules/Render/ThirdPerson/ThirdPerson.h"

#include "Module/Modules/Combat/Aimbot.h"
#include "Module/Modules/Combat/NoSpread.h"
#include "Module/Modules/Combat/AutoShoot/AutoShoot.h"
#include "Module/Modules/Combat/FastMelee/FastMelee.h"

#include "../Engine/Prediction/EnginePrediction.h"
namespace Client::Module
{
    class ModuleManager
    {
    public:
        ModuleManager();
		std::vector<Module*> featurelist;
		//real class
		BunnyHopModule::BunnyHop bhop = BunnyHopModule::BunnyHop();
		
		AimbotModule::Aimbot aimbot = AimbotModule::Aimbot();
		NoSpreadModule::NoSpread noSpread = NoSpreadModule::NoSpread();
		AutoShootModule::AutoShoot autoShoot = AutoShootModule::AutoShoot();
		FastMeleeModule::FastMelee fastMelee = FastMeleeModule::FastMelee();

		ArraylistModule::Arraylist arraylist = ArraylistModule::Arraylist();
		ESPHelperModule::ESPHelper espHelper = ESPHelperModule::ESPHelper();
		ClickGuiModule::ClickGui clickGui = ClickGuiModule::ClickGui();
		ThirdPersonModule::ThirdPerson thirdPerson = ThirdPersonModule::ThirdPerson();
		
		//pointer
		BunnyHopModule::BunnyHop* bhop_ptr = &bhop;
		
		AimbotModule::Aimbot* aimbot_ptr = &aimbot;
		NoSpreadModule::NoSpread* noSpread_ptr = &noSpread;
		AutoShootModule::AutoShoot* autoShoot_ptr = &autoShoot;
		FastMeleeModule::FastMelee* fastMelee_ptr = &fastMelee;

		ArraylistModule::Arraylist* arraylist_ptr = &arraylist;
		ESPHelperModule::ESPHelper* espHelper_ptr = &espHelper;
		ClickGuiModule::ClickGui* clickGui_ptr = &clickGui;
		ThirdPersonModule::ThirdPerson* thirdPerson_ptr = &thirdPerson;
		
		void Init();
		void onRender2D();
		void onOverrideView(CViewSetup* view);
		void onPostOverrideView(CViewSetup* view);
		void onCreateMove(CUserCmd* cmd, C_TerrorPlayer* pLocal);
		void onFrameStageNotify(ClientFrameStage_t curStage);
		void onKey();
		Module* getFeature(std::string name);
		std::vector<Module*> getFeatureListByCategory(ModuleCategory category);
		private:
		int keyTimeout = 0;
    };
}
