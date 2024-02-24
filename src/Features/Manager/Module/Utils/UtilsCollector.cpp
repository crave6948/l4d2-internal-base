#include "UtilsCollector.h"
#include <random>

namespace Utils
{
    namespace RandomUtils {
        int generateRandomNumber(int min, int max)
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
        float generateRandomNumber(float min, float max)
        {
            // Create a random number generator engine
            std::random_device rd;
            std::mt19937 gen(rd());

            // Create a uniform distribution for the specified range
            std::uniform_real_distribution<float> distribution(min, max);

            // Generate a random number within the specified range
            float random_number = distribution(gen);

            return random_number;
        }
        Vector genVector(float scope, bool x, bool y, bool z) {
  			// Generate random values based on boolean flags
            float randX = x ? generateRandomNumber(-scope, scope) : 0;
            float randY = y ? generateRandomNumber(-scope, scope) : 0;
            float randZ = z ? generateRandomNumber(-scope, scope) : 0;
            // Create and return a Vector object
            return Vector(randX, randY, randZ);
        }
    };
}