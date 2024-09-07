
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "perlin.h"

// Override base class with your custom functionality
class Window : public olc::PixelGameEngine
{
	Perlin1D perlin;
	Perlin2D perlin2;
	Perlin2D perlin3;
	int mode = 0;
	float timer = 0;

	template <typename P>
	void perlin_controls(P& perlin) {
		if (GetKey(olc::Q).bPressed) {
			perlin.set_octaves(perlin.get_octaves() + 1);
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
		if (GetKey(olc::SPACE).bPressed) {
			perlin.randomize_seed();
		}
	}

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

		perlin2.set_size(ScreenWidth(), ScreenHeight());
		perlin2.set_octaves(8);
		perlin2.set_basedrop(2);

		perlin3.set_size(ScreenWidth(), 5000);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Key::K1).bPressed) {
			mode = 0;
		}
		if (GetKey(olc::Key::K2).bPressed) {
			mode = 1;
		}
		if (GetKey(olc::Key::K3).bPressed) {
			mode = 2;
		}

		switch (mode) {
			case 0: {
				perlin_controls(perlin);

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
				break;
			} 

			case 1: {
				perlin_controls(perlin2);

				for (int x = 0; x < ScreenWidth(); x++) {
					for (int y = 0; y < ScreenHeight(); y++) {
						int color = perlin2.get(x, y)*255;
						//std::cout << perlin2.get(x, y) << '\n';
						Draw(x, y, olc::Pixel(color, color, color));
					}
				}
				break;
			}

			case 2: {
				timer += fElapsedTime*100;
				timer = fmodf(timer, 5000);

				perlin_controls(perlin3);

				Clear(olc::BLACK);
				for (int i = 0; i < ScreenWidth(); i++) {
					float val = perlin3.get(i,(int)timer);
					int h = (ScreenHeight() / 2) - (val * ScreenHeight() / 2);

					for (int j = 0; j < ScreenHeight() / 2; j++) {
						if (j >= h) {
							Draw(i, j, olc::GREEN);
						}
					}
				}
				break;
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