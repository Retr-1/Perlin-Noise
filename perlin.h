#pragma once
#include <random>

//void perlin_nd(int pos, int dimension, int* size, int octaves, float basedrop, float* seed, float* output) {
//	if (dimension <= 0) {
//		return;
//	}
//
//	int s = size[dimension - 1];
//	for (int i = 0; i < s; i++) {
//		for (int octave = 0; octave < octaves; octave++) {
//			int pitch = s >> octave;
//
//			if (pitch <= 0) {
//				break;
//			}
//
//			int sample1 = i - i % pitch;
//			int sample2 = sample1 + pitch;
//
//			float blend = (i - sample1) / (float)pitch;
//			float value = (1-blend)*perlin_nd()
//		}
//	}
//}
//void perlinND(int dimensions, int* size, int octaves, float basedrop, float* seed, float* output) {
//	for (int dimension = 0; dimension < dimensions; dimension++) {
//		int pos = 0;
//		for (int i = 0; i < size[dimension]; i++) {
//			float scale_factor = 1;
//			float scale_sum = 0;
//			for (int octave = 0; octave < octaves; octave++) {
//				int pitch = size[dimension] >> octave;
//
//				if (pitch <= 0) {
//					break;
//				}
//
//				int sample1 = i - i % pitch;
//				int sample2 = sample1 + pitch;
//
//				float blend = (i - sample1) / (float)pitch;
//				float value = ((1 - blend) * seed[pos + sample1] + blend * seed[pos + sample2]) * scale_factor;
//				output[pos + i] += value;
//				output[pos + i] /= scale_factor;
//				scale_sum += scale_factor;
//				scale_factor /= basedrop;
//			}
//			output[pos + i] /= scale_sum;
//		}
//
//	}
//}

//void perlinND(int dimension, int depth, int* pos, )

void perlinND(int dimensions, int* size, int octaves, float basedrop, float* seed, float* output) {
	int* pos = new int[dimensions];

	std::function<void(int, int)> recursive;
	recursive = [&](int dimension, int depth) -> void {
		if (depth == dimensions-1) {
			float scale_factor = 1;
			float scale_sum = 0;
			for (int octave = 0; octave < octaves; octave++) {
				int pitch = size[dimension] >> octave;

				int sample1 = (pos[dimension] / pitch) * pitch;
				int sample2 = sample1 + pitch;

				float blend = (pos[dimension] - sample1) / (float)pitch;
			}
		}
		else {
			for (int i = 0; i < size[depth]; i++) {
				pos[depth] = i;
				recursive(dimension, depth + 1);
			}
		}
	};

	for (int dimension = 0; dimension < dimensions; dimension++) {

	}

	delete[] pos;
}

class Perlin {
protected:
	int size;
	float* values;
	float* seed;
	bool init_seed = false;
	bool tainted = true;
	int octaves;
	float basedrop;

public:
	Perlin(int size = 256, int octaves = 8, float basedrop = 2) : size(size), octaves(octaves), basedrop(basedrop) {
		values = new float[size];
		seed = new float[size];
	}

	~Perlin() {
		delete[] values;
		delete[] seed;
	}

	void randomize_seed() {
		for (int i = 0; i < size; i++) {
			seed[i] = rand() / (float)RAND_MAX;
			//std::cout << seed[i] << " RA\n";
		}
		init_seed = true;
		tainted = true;
	}

	void set_size(int size) {
		this->size = size;

		delete[] values;
		delete[] seed;

		values = new float[size];
		seed = new float[size];
		init_seed = false;
		tainted = true;
	}

	void set_octaves(int octaves) {
		this->octaves = octaves;
		tainted = true;
	}

	void set_basedrop(float basedrop) {
		this->basedrop = basedrop;
		tainted = true;
	}

	int get_size() { return size; }
	int get_octaves() { return octaves; }
	float get_basedrop() { return basedrop; }

	virtual void calculate() {}

	float get(int x) {
		if (!init_seed) {
			randomize_seed();
		}
		if (tainted) {
			calculate();
		}
		return values[x];
	}
};

class Perlin1D : public Perlin {
	using Perlin::Perlin;

	void calculate() override {
		for (int x = 0; x < size; x++) {
			float scale_factor = 1;
			float scale_sum = 0;
			values[x] = 0;
			for (int octave = 0; octave < octaves; octave++) {
				int pitch = size >> octave;

				if (pitch <= 0) {
					break;
				}

				int sample1 = x - x % pitch;
				int sample2 = (sample1 + pitch) % size;
				float blend = (x - sample1) / (float)pitch;
				float value = ((1 - blend) * seed[sample1] + blend * seed[sample2]) * scale_factor;
				values[x] += value;
				scale_sum += scale_factor;
				scale_factor /= basedrop;
			}
			values[x] /= scale_sum;
		}
		tainted = false;
	}
};

class Perlin2D {
protected:
	int width;
	int height;
	int octaves;
	float basedrop;

	float* values;
	float* seed;

public:
	Perlin2D(int width = 256, int height = 256, int octaves = 8, float basedrop = 2) : width(width), height(height), octaves(octaves), basedrop(basedrop) {

	}

	~Perlin2D() {
		delete[] values;
		delete[] seed;
	}


};
