#include "ModuleManager.h"
#include "../Rotation/RotationManager.h"
#include "../None.h"
namespace Client::Module
{

    ModuleManager::ModuleManager()
    {
    }

    void ModuleManager::Init()
    {
        featurelist.push_back(bhop_ptr);

        featurelist.push_back(aimbot_ptr);
        featurelist.push_back(autoShoot_ptr);
        featurelist.push_back(noSpread_ptr);
        featurelist.push_back(fastMelee_ptr);

        featurelist.push_back(arraylist_ptr);
        featurelist.push_back(espHelper_ptr);
        featurelist.push_back(clickGui_ptr);
        featurelist.push_back(thirdPerson_ptr);
    }

    void ModuleManager::onRender2D()
    {
        Utils::g_EntityCache.update();
        for (Module *mod : featurelist)
        {
            if (!mod->getEnabled())
                continue;
            mod->onRender2D();
        }
        if (!I::EngineClient->IsInGame())
        {
            return;
        };
        if (I::EngineVGui->IsGameUIVisible())
        {
            return;
        }
        C_TerrorPlayer *pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TerrorPlayer *>();
        if (!Helper::rotationManager.getServerRotationVector().IsZero())
        {
            Vector vec = U::Math.AngleVectors(Helper::rotationManager.getServerRotationVector());
            CGameTrace trace;
            CTraceFilterHitAll filter{pLocal};
            G::Util.Trace(pLocal->Weapon_ShootPosition(), pLocal->Weapon_ShootPosition() + (vec * 1400.0f), (MASK_SHOT | CONTENTS_GRATE), &filter, &trace);
            Vector vViewAngleOnWorld = trace.endpos;
            Vector screen;
            G::Util.W2S(vViewAngleOnWorld, screen);

            int screenW = G::Draw.m_nScreenW, screenH = G::Draw.m_nScreenH;

            if (Helper::rotationManager.DisabledRotation)
            {
                screenW = screenW / 2;
                screenH = screenH / 2;
                G::Draw.Line(screenW, screenH, screenW - 4, screenH + 4, Color(255, 255, 255, 255));
                G::Draw.Line(screenW, screenH, screenW + 4, screenH + 4, Color(255, 255, 255, 255));
                screenW = screenW * 2;
                screenH = screenH * 2;
            }
            else
            {
                G::Draw.Line(screen.x, screen.y, screen.x - 4, screen.y + 4, Color(255, 255, 255, 255));
                G::Draw.Line(screen.x, screen.y, screen.x + 4, screen.y + 4, Color(255, 255, 255, 255));
            }
            // G::Draw.Circle(screen.x, screen.y, 2, 8, );
        }
    }

    void ModuleManager::onOverrideView(CViewSetup* view)
    {
        for (Module *mod : featurelist)
        {
            if (!mod->getEnabled())
                continue;
            mod->onOverrideView(view);
        }
    }

    void ModuleManager::onPostOverrideView(CViewSetup *view)
    {
        for (Module *mod : featurelist)
        {
            if (!mod->getEnabled())
                continue;
            mod->onPostOverrideView(view);
        }
    }

    void ModuleManager::onCreateMove(CUserCmd *cmd, C_TerrorPlayer *pLocal)
    {
        if (pLocal && !pLocal->deadflag())
        {
            C_TerrorWeapon *pWeapon = pLocal->GetActiveWeapon()->As<C_TerrorWeapon *>();
            Vector oldViewangles = cmd->viewangles;
            for (Module *mod : featurelist)
            {
                if (!mod->getEnabled())
                    continue;
                mod->onPreCreateMove(cmd, pWeapon, pLocal);
            }
            Helper::rotationManager.onUpdate();
            if (!Helper::rotationManager.getServerRotationVector().IsZero() && !Helper::rotationManager.DisabledRotation)
                cmd->viewangles = Helper::rotationManager.getServerRotationVector();
            for (Module *mod : featurelist)
            {
                if (!mod->getEnabled())
                    continue;
                mod->onPostCreateMove(cmd, pWeapon, pLocal);
            }
            if (pWeapon)
            {
                for (Module *mod : featurelist)
                {
                    if (!mod->getEnabled())
                        continue;
                    mod->onPrePrediction(cmd, pWeapon, pLocal);
                }
                F::EnginePrediction.Start(pLocal, cmd);
                {
                    for (Module *mod : featurelist)
                    {
                        if (!mod->getEnabled())
                            continue;
                        mod->onPrediction(cmd, pWeapon, pLocal, F::EnginePrediction.GetPredictedFlags());
                    }
                }
                F::EnginePrediction.Finish(pLocal, cmd);
            }
            for (Module *mod : featurelist)
            {
                if (!mod->getEnabled())
                    continue;
                mod->onPostPrediction(cmd, pWeapon, pLocal);
            }
            G::Util.FixMovement(oldViewangles, cmd);
        }
    }
    void ModuleManager::onFrameStageNotify(ClientFrameStage_t curStage)
    {
        for (Module *mod : featurelist)
        {
            if (!mod->getEnabled())
                continue;
            mod->onFrameStageNotify(curStage);
        }
    }
    void ModuleManager::onKey()
    {
        // bool isToggled = keyState & 1;
        // bool isDown = keyState & 0x8000;
        if (GetAsyncKeyState(VK_HOME) & 0x8000 && keyTimeout <= 0)
        {
            Client::client.fileManager.load();
            keyTimeout = 1;
        }
        else
        {
            if (keyTimeout > 0)
                keyTimeout--;
        }
        for (Module *mod : featurelist)
        {
            if (GetAsyncKeyState(mod->getKey()) & 0x8000)
            {
                if (!mod->ShouldToggle())
                    continue;
                mod->toggle();
                mod->keytimeout = 1;
            }
            else
            {
                if (mod->keytimeout > 0)
                    mod->keytimeout--;
            }
        }
    }
    Module *ModuleManager::getFeature(std::string name)
    {
        for (Module *mod : featurelist)
        {
            if (mod->getName().compare(name) == 0)
            {
                return mod;
            }
        }
        return nullptr;
    }
    std::vector<Module *> ModuleManager::getFeatureListByCategory(ModuleCategory category)
    {
        std::vector<Module *> result;
        for (Module *mod : featurelist)
        {
            if (mod->getCategory() == category)
            {
                result.push_back(mod);
            }
        }
        return result;
    }
}
