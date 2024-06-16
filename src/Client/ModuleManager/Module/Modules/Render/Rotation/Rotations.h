#pragma once
#include "../../../ModuleHeader.h"

namespace Client::Module
{
    namespace RotationsModule
    {
        class Rotations : public Module
        {
        public:
            Rotations()
            {
                this->Create("Rotations", false, 0, ModuleCategory::Visuals);
                vManager.AddValue(ForceFocusTicks);
                vManager.AddValue(rotationModes);
                // linear
                vManager.AddValue(linear_horizontalTurnSpeed);
                vManager.AddValue(linear_verticalTurnSpeed);
                // sigmoid
                vManager.AddValue(sigmoid_horizontalTurnSpeed);
                vManager.AddValue(sigmoid_verticalTurnSpeed);
                vManager.AddValue(steepness);
                vManager.AddValue(midpoint);
                // conditional
                vManager.AddValue(coefDistance);      // aim accuracy
                vManager.AddValue(coefDiffH);         // horizontal starting aim speed
                vManager.AddValue(coefDiffV);         // vertical starting aim speed
                vManager.AddValue(coefCrosshairH);    // horizontal aim jitter while tracking enemy
                vManager.AddValue(coefCrosshairV);    // vertical aim jitter while tracking enemy
                vManager.AddValue(interceptH);        // horizontal rotation speed while attacking
                vManager.AddValue(interceptV);        // vertical rotation speed while attacking
                vManager.AddValue(minimumTurnSpeedH); // minimum horizontal rotation speed
                vManager.AddValue(minimumTurnSpeedV); // minimum vertical rotation speed
            };
            V::NumberValue *ForceFocusTicks = new V::NumberValue("ForceFocusTicks", 5, 1, 20, "Ticks");
            V::ListValue *rotationModes = new V::ListValue("Rotation Modes", std::vector<std::string>{"Linear", "Sigmoid", "Conditional"}, std::string("Sigmoid"));
            // Linear Values
            V::FloatRangeValue *linear_horizontalTurnSpeed = new V::FloatRangeValue("Linear-HorizontalTurnSpeed", V::Range(180.f, 180.f),
                                                                                    V::Range(0.0f, 180.f));
            V::FloatRangeValue *linear_verticalTurnSpeed = new V::FloatRangeValue("Linear-VerticalTurnSpeed", V::Range(180.f, 180.f),
                                                                                  V::Range(0.0f, 180.f));
            // Sigmoid Values
            V::FloatRangeValue *sigmoid_horizontalTurnSpeed = new V::FloatRangeValue("Sigmoid_HorizontalTurnSpeed", V::Range(180.f, 180.f),
                                                                                     V::Range(0.0f, 180.f));
            V::FloatRangeValue *sigmoid_verticalTurnSpeed = new V::FloatRangeValue("Sigmoid_VerticalTurnSpeed", V::Range(180.f, 180.f),
                                                                                   V::Range(0.0f, 180.f));

            V::FloatValue *steepness = new V::FloatValue("Steepness", 10.f, 0.0f, 20.f);
            V::FloatValue *midpoint = new V::FloatValue("Midpoint", 0.3f, 0.0f, 1.0f);
            // Conditional Values
            V::FloatValue *coefDistance = new V::FloatValue("CoefDistance", -1.393f, -2.f, 2.f);
            V::FloatValue *coefDiffH = new V::FloatValue("CoefDiffH", 0.21f, -1.f, 1.f);
            V::FloatValue *coefDiffV = new V::FloatValue("CoefDiffV", 0.14f, -1.f, 1.f);
            V::FloatValue *coefCrosshairH = new V::FloatValue("CoefCrosshairH", -5.99f, -30.f, 30.f);
            V::FloatValue *coefCrosshairV = new V::FloatValue("CoefCrosshairV", -14.32f, -30.f, 30.f);
            V::FloatValue *interceptH = new V::FloatValue("InterceptH", 11.988f, 0.f, 20.f);
            V::FloatValue *interceptV = new V::FloatValue("InterceptV", 4.715f, 0.f, 10.f);
            V::FloatValue *minimumTurnSpeedH = new V::FloatValue("MinimumTurnSpeedH", 3.05f, 0.f, 10.f);
            V::FloatValue *minimumTurnSpeedV = new V::FloatValue("MinimumTurnSpeedV", 5.96f, 0.f, 10.f);
        };
    };
};