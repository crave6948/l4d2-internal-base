#pragma once
#include "../../../ModuleHeader.h"

namespace Client::Module
{
	namespace ThirdPersonModule
	{
		class ThirdPerson : public Module
		{
		public:
			ThirdPerson()
			{
				this->Create("ThirdPerson", false, VK_NUMPAD6, ModuleCategory::Visuals);
				vManager.AddValue(debug);
				vManager.AddValue(distance);
			};
			void onRender2D() override;
			void onPostPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
			void onFrameStageNotify(ClientFrameStage_t curStage) override;
			V::BooleanValue *debug = new V::BooleanValue("Debug", false);
			V::NumberValue *distance = new V::NumberValue("Distance", 50, 0, 180);
			V::StringValue *keyValue = new V::StringValue("Key", "v");
		private:
			bool isThirdPerson = false;
			Vector rotation = Vector(0, 0, 0);
		};
	};
};