#include "World.h"

World::World(Player* player, std::vector<SquareObject*> apples, SDL_Renderer* renderer)
{
	m_Player = player;
	m_Apples = apples;
	m_Renderer = renderer;
}

void World::SpawnApple()
{
	int screenWidth;
	int screenHeight;
	SDL_GetRendererOutputSize(m_Renderer, &screenWidth, &screenHeight);

	SquareObject* apple = new SquareObject(glm::i16vec2(rand() % screenWidth, rand() % screenHeight), 10, m_Renderer);
	m_Apples.push_back(apple);
}

void World::Update()
{
	m_Player->Update();

	// Check if player head collides with apple
	std::vector<SquareObject*> playerNodes = m_Player->GetNodes();
	SquareObject* playerHead = playerNodes.at(0);
	for (size_t i = 0; i < m_Apples.size(); i++)
	{
		if (playerHead->Collides(*m_Apples.at(i)))
		{
			// Increment score
			m_Player->IncrementEatenApples();
			// Remove eaten apple
			m_Apples.erase(m_Apples.begin() + i);
			// Add new snake node to player
			m_Player->AddNode(new SquareObject(playerHead->GetPosition() - glm::i16vec2(15, 0), 10, m_Renderer));
			// Spawn a new apple
			SpawnApple();
		}
	}

	// check if player head out of bound
	glm::i16vec2 playerHeadPos = playerHead->GetPosition();
	int screenWidth, screenHeight;
	SDL_GetRendererOutputSize(m_Renderer, &screenWidth, &screenHeight);

	if (playerHeadPos.x > screenWidth)
	{
		playerHeadPos.x = 0;
	}
	else if (playerHeadPos.x < 0)
	{
		playerHeadPos.x = screenWidth;
	}

	if (playerHeadPos.y > screenHeight)
	{
		playerHeadPos.y = 0;
	}
	else if (playerHeadPos.y < 0)
	{
		playerHeadPos.y = screenHeight;
	}
	playerHead->SetPosition(playerHeadPos);
}

void World::Render()
{
	// Order is important here
	// Render apples before player for z-order
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 255, 255);
	for (SquareObject* apple : m_Apples)
	{
		apple->Render();
	}

	// Player
	SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
	m_Player->Render();
}

