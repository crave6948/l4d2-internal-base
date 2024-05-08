#pragma once
#include "../../../ModuleHeader.h"
#include "../../../../../Rotation/RotationManager.h"

#include <functional>
namespace Client::Module
{
    namespace AimbotModule
    {
        class TargetInfo
        {
        public:
            IClientEntity *target = nullptr;
            Vector targetPosition;
            Helper::Rotation aimRotation;
            int hitGroup;
            TargetInfo(){
                this->target = nullptr;
            };
            TargetInfo(IClientEntity *target, Vector targetPosition, Helper::Rotation aim, int hitGroup)
            {
                this->target = target;
                this->targetPosition = targetPosition;
                this->aimRotation = aim;
                this->hitGroup = hitGroup;
            };
        };
        class Aimbot : public Module
        {
        public:
            Aimbot()
            {
                this->Create("Aimbot", true, VK_NUMPAD7, ModuleCategory::Combat);
                vManager.AddValue(range);
                vManager.AddValue(fov);
                vManager.AddValue(silent);
                vManager.AddValue(switchDelay);

                vManager.AddValue(infected);
                vManager.AddValue(boomer);
                vManager.AddValue(spitter);
                vManager.AddValue(charger);
                vManager.AddValue(smoker);
                vManager.AddValue(jockey);
                vManager.AddValue(hunter);
                vManager.AddValue(witch);
                vManager.AddValue(tank);
                
                vManager.AddValue(debug);
            };
            V::FloatValue *range = new V::FloatValue("Range", 1400.f, 100.f, 2000.f);
            V::NumberValue *fov = new V::NumberValue("Fov", 180, 0, 180);
            V::BooleanValue *silent = new V::BooleanValue("Silent", true);
            V::NumberValue *switchDelay = new V::NumberValue("SwitchDelay", 400, 0, 1000, "ms");
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

            V::BooleanValue* debug = new V::BooleanValue("Debug Mode", false);

            void onPreCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
            void onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal) override;
            void onRender2D() override;
            void onEnabled() override;
            void onDisabled() override;

            TargetInfo targetInfo;
        private:
            bool ShouldRun(C_TerrorPlayer *pLocal, C_TerrorWeapon *pWeapon, CUserCmd *cmd);
            bool isInCrossHair(CUserCmd *cmd, C_TerrorPlayer *pLocal, IClientEntity *target);
            TargetInfo GetTarget(C_TerrorPlayer *pLocal, C_TerrorWeapon *pWeapon, CUserCmd *cmd);
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
            int lastSwitchTime = 0;
        };
    }
};