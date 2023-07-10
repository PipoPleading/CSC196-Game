#pragma once
#include <random>

namespace kiko
{
	void seed_random(unsigned int seed) { srand(seed); }
	int random() { return rand(); }
	int random(unsigned int max) { return rand() % max; } // 0 to (max - 1)
	int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1) ; } // min to max

	float randomf() { return random() / RAND_MAX; }
	float randomf(float max) { return randomf() * max; }
	float randomf(float min, float max) { return min + randomf() * (max - min); }
}