#pragma once
#include "EntityCache/EntityCache.h"
namespace Utils
{
	namespace RandomUtils {
		int generateRandomNumber(int min, int max);
		float generateRandomNumber(float min, float max);
		Vector genVector(float scope = 1.0f, bool x = true, bool y = true, bool z = true);
	};
}