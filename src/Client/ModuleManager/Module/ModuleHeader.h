#pragma once
#include <string>
#include "../../../SDK/SDK.h"
#include "Utils/UtilsCollector.h"
#include "../../Value/ValueManager.h"
namespace Client::Module
{
    enum class ModuleCategory {
        Combat = 1,
        Visuals = 2,
        Player = 3,
        Misc = 4
    };
    class Module
    {
    public:
        V::ValueManager vManager = V::ValueManager();
        void Create(std::string name, bool state, int keyCode, ModuleCategory category)
        {
            this->name = name;
            this->state = state;
            this->key = keyCode;
            this->category = category;
        };
        std::string getName()
        {
            return name;
        };
        bool getEnabled()
        {
            return state;
        };
        void setEnabled(bool state)
        {
            this->state = state;
            if (state)
            {
                onEnabled();
            }
            else
            {
                onDisabled();
            }
        };
        int getKey()
        {
            return key;
        };
        void setKey(int key)
        {
            this->key = key;
        };
        ModuleCategory getCategory()
        {
            return category;
        };
        virtual void onPreCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal){};
        virtual void onPostCreateMove(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal){};
        virtual void onPrePrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal){};
        virtual void onPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal, int PredictedFlags){};
        virtual void onPostPrediction(CUserCmd *cmd, C_TerrorWeapon *pWeapon, C_TerrorPlayer *pLocal){};
        virtual void onRender2D(){};
        void toggle()
        {
            setEnabled(!state);
            client.fileManager.save();
        };
        virtual void onEnabled(){};
        virtual void onDisabled(){};
        int keytimeout = 0;
        bool ShouldToggle()
        {
            return keytimeout <= 0;
        }
        int animate = 20;
        void updateanimate()
        {
            if (state)
            {
                if (animate > 0)
                {
                    animate--;
                }
            }
            else
            {
                animate = 20;
            }
        }
    private:
        std::string name;
        bool state = false;
        int key = 0;
        ModuleCategory category;
    };
}