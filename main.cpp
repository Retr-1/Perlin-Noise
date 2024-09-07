
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
		perlin.set_octaves(8);
		perlin.set_basedrop(2);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Q).bPressed) {
			perlin.set_octaves(perlin.get_octaves()+1);
			std::cout << perlin.get_octaves() << " Octaves\n";
		}
		if (GetKey(olc::A).bPressed) {
			perlin.set_octaves(perlin.get_octaves() - 1);
			std::cout << perlin.get_octaves() << " Octaves\n";
		}
		if (GetKey(olc::W).bPressed) {
			perlin.set_basedrop(perlin.get_basedrop() + 0.2);
			std::cout << perlin.get_basedrop() << " Basedrop\n";
		}
		if (GetKey(olc::S).bPressed) {
			perlin.set_basedrop(perlin.get_basedrop() - 0.2);
			std::cout << perlin.get_basedrop() << " Basedrop\n";
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