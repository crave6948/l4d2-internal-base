#pragma once
#include "Module/Modules/Player/BunnyHop.h"

#include "Module/Modules/Render/Arraylist.h"
#include "Module/Modules/Render/ClickGui/ClickGuiModule.h"
#include "Module/Modules/Render/ESPHelper.h"
#include "Module/Modules/Render/ThirdPerson/ThirdPerson.h"
#include "Module/Modules/Render/Rotation/Rotations.h"

#include "Module/Modules/Combat/Aimbot/Aimbot.h"
#include "Module/Modules/Combat/NoSpread.h"
#include "Module/Modules/Combat/AutoShoot/AutoShoot.h"
#include "Module/Modules/Combat/FastMelee/FastMelee.h"

#include "Module/Modules/Misc/FontManager/FontManager.h"

#include "../Engine/Prediction/EnginePrediction.h"
namespace Client::Module
{
	class ModuleManager
	{
	public:
		ModuleManager();
		~ModuleManager();
		std::vector<Module *> featurelist;
		// Pointer declarations
		BunnyHopModule::BunnyHop *bhop = new BunnyHopModule::BunnyHop();

		AimbotModule::Aimbot *aimbot = new AimbotModule::Aimbot();
		NoSpreadModule::NoSpread *noSpread = new NoSpreadModule::NoSpread();
		AutoShootModule::AutoShoot *autoShoot = new AutoShootModule::AutoShoot();
		FastMeleeModule::FastMelee *fastMelee = new FastMeleeModule::FastMelee();

		ArraylistModule::Arraylist *arraylist = new ArraylistModule::Arraylist();
		ESPHelperModule::ESPHelper *espHelper = new ESPHelperModule::ESPHelper();
		ClickGuiModule::ClickGui *clickGui = new ClickGuiModule::ClickGui();
		ThirdPersonModule::ThirdPerson *thirdPerson = new ThirdPersonModule::ThirdPerson();
		RotationsModule::Rotations *rotations = new RotationsModule::Rotations();

		FontManagerModule::FontManager *fontManager = new FontManagerModule::FontManager();

		void Init();
		void onRender2D();
		void onCreateMove(CUserCmd *cmd, C_TerrorPlayer *pLocal);
		void onFrameStageNotify(ClientFrameStage_t curStage);
		void onKey();
		Module *getFeature(std::string name);
		std::vector<Module *> getFeatureListByCategory(ModuleCategory category);

	private:
		int keyTimeout = 0;
	};
}
