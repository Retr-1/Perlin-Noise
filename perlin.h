#pragma once
#include <random>

class Perlin1D {
	int size;
	int octaves;
	float basedrop;
	float* values;
	float* seed;

public:
	Perlin1D(int size=256, int octaves=8, float basedrop=2) : size(size), octaves(octaves), basedrop(basedrop) {
		values = new float[size];
		std::fill(values, values + size, 0);
	}

	void reset_seed() {
		delete[] seed;

		seed = new float[size];
		for (int i = 0; i < size; i++) {
			seed[i] = rand() / (float)RAND_MAX;
		}
	}

	void calculate() {
		for (int x = 0; x < size; x++) {
			for (int octave = 0; octave < octaves; octave++) {
				int pitch = size >> octave;
				int sample1 = x - x%pitch;
				int sample2 = (sample1 + pitch) % size;
			}
		}
	}

	float get(float x) {
		return 0;
	}

};