#pragma once

#include "Includes.h"
#include "World.h"

class Engine
{
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	TTF_Font* m_Font;
	World* m_World;
	bool m_Running = false;
	Uint16 m_MaxFPS;

public:
	Engine();
	~Engine();

	void Init(const char* title, glm::u32vec2 screenPos, glm::u16vec2 size, bool fullscreen);

	inline bool IsRunning() { return m_Running; }
	
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	void MainLoop();

};