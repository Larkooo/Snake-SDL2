#include "Engine.h"

int main(int argc, char** argv)
{
	Engine engine;

	engine.Init("Snake", glm::u32vec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), glm::u32vec2(720, 400), false);

	engine.MainLoop();

	return 0;
}