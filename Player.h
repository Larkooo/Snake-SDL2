#pragma once
#include "Includes.h"
#include "SquareObject.h"

class Player
{
	bool m_Alive;
	uint16_t m_EatenApples;
	glm::u16vec2 m_Velocity;
	std::vector<SquareObject*> m_Nodes;
	SDL_Renderer* m_Renderer;

public:
	Player(glm::u16vec2 position, SDL_Renderer* renderer);
	~Player() {};

	void Update();
	void Render();

	inline bool IsAlive() { return m_Alive; }
	inline void Kill() { m_Alive = false; }
	inline uint16_t GetEatenApples() { return m_EatenApples; }
	inline void IncrementEatenApples() { m_EatenApples++; }

	inline std::vector<SquareObject*> GetNodes() { return m_Nodes; }
	inline void AddNode(SquareObject* node) { m_Nodes.push_back(node); }

	inline glm::u16vec2 GetVelocity() { return m_Velocity; }
	inline void SetVelocity(glm::u16vec2 velocity) { m_Velocity = velocity; }
};