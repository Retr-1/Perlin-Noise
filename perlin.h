#pragma once
#include <random>

class Perlin1D {
protected:
	int size;
	float* values;
	float* seed;

public:
	int octaves;
	float basedrop;

	Perlin1D(int size=256, int octaves=8, float basedrop=2) : size(size), octaves(octaves), basedrop(basedrop) {
		values = new float[size];
		seed = new float[size];
		randomize_seed();
	}

	~Perlin1D() {
		delete[] values;
		delete[] seed;
	}

	void randomize_seed() {
		for (int i = 0; i < size; i++) {
			seed[i] = rand() / (float)RAND_MAX;
			//std::cout << seed[i] << " RA\n";
		}
	}

	void set_size(int size) {
		this->size = size;

		delete[] values;
		delete[] seed;

		values = new float[size];
		seed = new float[size];
		randomize_seed();
	}

	void calculate() {
		std::fill(values, values + size, 0);

		for (int x = 0; x < size; x++) {
			float scale_factor = 1;
			float scale_sum = 0;
			for (int octave = 0; octave < octaves; octave++) {
				int pitch = size >> octave;
				
				if (pitch <= 0) {
					break;
				}

				int sample1 = x - x%pitch;
				int sample2 = (sample1 + pitch) % size;
				float blend = (x - sample1) / (float)pitch;
				float value = ((1 - blend) * seed[sample1] + blend * seed[sample2]) * scale_factor;
				values[x] += value;
				scale_sum += scale_factor;
				scale_factor /= basedrop;
			}
			values[x] /= scale_sum;
		}
	}

	float get(int x) {
		return values[x];
	}

};