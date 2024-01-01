#pragma once
#include "FindTarget.h"

namespace Utils
{
	namespace RandomUtils {
		inline int generateRandomNumber(int min, int max)
		{
			// Use a random_device to seed the random number generator
			std::random_device rd;

			// Use the random_device to seed the Mersenne Twister PRNG
			std::mt19937 gen(rd());

			// Define a range for the random numbers
			std::uniform_int_distribution<int> distribution(min, max);

			// Generate a random number within the specified range
			int random_number = distribution(gen);

			return random_number;
		}
		inline float generateRandomNumber(float min, float max)
		{
			// Use a random_device to seed the random number generator
			std::random_device rd;

			// Use the random_device to seed the Mersenne Twister PRNG
			std::mt19937 gen(rd());

			// Define a range for the random numbers
			std::uniform_int_distribution<float> distribution(min, max);

			// Generate a random number within the specified range
			float random_number = distribution(gen);

			return random_number;
		}
		inline double generateRandomNumber(double min, double max)
		{
			// Use a random_device to seed the random number generator
			std::random_device rd;

			// Use the random_device to seed the Mersenne Twister PRNG
			std::mt19937 gen(rd());

			// Define a range for the random numbers
			std::uniform_int_distribution<double> distribution(min, max);

			// Generate a random number within the specified range
			double random_number = distribution(gen);

			return random_number;
		}
		inline Vector genVector(float scope = 1.0f, bool x = true, bool y = true, bool z = true) {
  			// Generate random values based on boolean flags
			float randX = x ? generateRandomNumber(-scope, scope) : 0;
			float randY = y ? generateRandomNumber(-scope, scope) : 0;
			float randZ = z ? generateRandomNumber(-scope, scope) : 0;
			// Create and return a Vector object
			return Vector(randX, randY, randZ);
		}
	};
	inline FindTarget target = FindTarget();
}