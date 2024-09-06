
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
		perlin = Perlin1D(ScreenWidth());
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		// Called once per frame, draws random coloured pixels
		for (int i = 0; i < ScreenWidth(); i++) {
			float val = perlin.get(i);
			for (int j = val * ScreenHeight() / 2; j < ScreenHeight() / 2; j++) {
				Draw(i, j, olc::GREEN);
			}
		}
		return true;
	}
};

int main()
{
	Window win;
	if (win.Construct(800, 800, 1, 1))
		win.Start();
	return 0;
}