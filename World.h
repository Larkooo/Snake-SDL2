#pragma once
#include "Includes.h"
#include "Player.h"

class World
{
	Player* m_Player;
	std::vector<SquareObject*> m_Apples;
	SDL_Renderer* m_Renderer;

public:
	World(Player* player, std::vector<SquareObject*> apples, SDL_Renderer* renderer);
	World() {};
	~World() {};

	// Update and render player & apples
	void Update();
	void Render();

	Player* GetPlayer() { return m_Player; }
	std::vector<SquareObject*> GetApples() { return m_Apples; }
	void SpawnApple();
};