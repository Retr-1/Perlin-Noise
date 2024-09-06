
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "perlin.h"

// Override base class with your custom functionality
class Window : public olc::PixelGameEngine
{
	Perlin1D perlin;
public:
	Window()
	{
		// Name your application
		sAppName = "Window";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		perlin.set_size(ScreenWidth());
		perlin.octaves = 8;
		perlin.basedrop = 2;
		perlin.calculate();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Q).bPressed) {
			perlin.octaves++;
			perlin.calculate();
			std::cout << perlin.octaves << " Octaves\n";
		}
		if (GetKey(olc::A).bPressed) {
			perlin.octaves--;
			perlin.calculate();
			std::cout << perlin.octaves << " Octaves\n";
		}
		if (GetKey(olc::W).bPressed) {
			perlin.basedrop += 0.2;
			perlin.calculate();
			std::cout << perlin.basedrop << " Basedrop\n";
		}
		if (GetKey(olc::S).bPressed) {
			perlin.basedrop -= 0.2;
			perlin.calculate();
			std::cout << perlin.basedrop << " Basedrop\n";
		}

		Clear(olc::BLACK);
		for (int i = 0; i < ScreenWidth(); i++) {
			float val = perlin.get(i);
			int h = (ScreenHeight() / 2) - (val * ScreenHeight() / 2);
			
			for (int j = 0; j < ScreenHeight() / 2; j++) {
				if (j >= h) {
					Draw(i, j, olc::GREEN);
				}
			}
		}
		return true;
	}
};

int main()
{
	srand(0);

	Window win;
	if (win.Construct(800, 800, 1, 1))
		win.Start();
	return 0;
}