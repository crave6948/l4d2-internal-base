#pragma once
#include "../../ModuleHeader.h"

#include <functional>
namespace Client::Module
{
	namespace ESPHelperModule
	{
		class ESPHelper : public Module
		{
		public:
			ESPHelper()
			{
				this->Create("ESPHelper", true, VK_RIGHT, ModuleCategory::Visuals);
				vManager.AddValue(aimbotColor);
				vManager.AddValue(aimbotInRangeColor);
				vManager.AddValue(infected);
				vManager.AddValue(boomer);
				vManager.AddValue(spitter);
				vManager.AddValue(charger);
				vManager.AddValue(smoker);
				vManager.AddValue(jockey);
				vManager.AddValue(hunter);
				vManager.AddValue(witch);
				vManager.AddValue(tank);
			};
			void onRender2D() override;
			// color of aimbotesp
			V::ColorValue* aimbotColor = new V::ColorValue("Aimbot ESP Color", 44, 100, 41, 1);
			V::ColorValue* aimbotInRangeColor = new V::ColorValue("Aimbot In Range Color", 41, 85, 100, 1);
			// infected, special infected, witch, tank
			V::BooleanValue* infected = new V::BooleanValue("Infected", true);
			// specialInfected has boomer, spitter, charger, smoker, jockey, hunter
			V::BooleanValue* boomer = new V::BooleanValue("Boomer", true);
			V::BooleanValue* spitter = new V::BooleanValue("Spitter", true);
			V::BooleanValue* charger = new V::BooleanValue("Charger", true);
			V::BooleanValue* smoker = new V::BooleanValue("Smoker", true);
			V::BooleanValue* jockey = new V::BooleanValue("Jockey", true);
			V::BooleanValue* hunter = new V::BooleanValue("Hunter", true); 
			// witch and tank are separate from specialInfected value
			V::BooleanValue* witch = new V::BooleanValue("Witch", true);
			V::BooleanValue* tank = new V::BooleanValue("Tank", true);
		private:
			void drawESP(C_BaseEntity *pBaseEntity, int hit);
			std::vector<std::pair<std::function<bool()>, EClientClass>> entityTypes = {
				{std::bind(&V::BooleanValue::GetValue, infected), EClientClass::Infected},
				{std::bind(&V::BooleanValue::GetValue, boomer), EClientClass::Boomer},
				{std::bind(&V::BooleanValue::GetValue, spitter), EClientClass::Spitter},
				{std::bind(&V::BooleanValue::GetValue, charger), EClientClass::Charger},
				{std::bind(&V::BooleanValue::GetValue, smoker), EClientClass::Smoker},
				{std::bind(&V::BooleanValue::GetValue, jockey), EClientClass::Jockey},
				{std::bind(&V::BooleanValue::GetValue, hunter), EClientClass::Hunter},
				{std::bind(&V::BooleanValue::GetValue, witch), EClientClass::Witch},
				{std::bind(&V::BooleanValue::GetValue, tank), EClientClass::Tank}};
		};
	};
};