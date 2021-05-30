#include "Engine.h"

Engine::Engine()
{}

Engine::~Engine()
{}

void Engine::Init(const char* title, glm::u32vec2 screenPos, glm::u32vec2 size, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 1) return;
#ifdef _DEBUG
	std::cout << "SDL Initialized" << std::endl;
#endif

	if (TTF_Init() == 1) return;
#ifdef _DEBUG
	std::cout << "TTF Initialized" << std::endl;
#endif

	m_Window = SDL_CreateWindow(title, screenPos.x, screenPos.y, size.x, size.y, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
	if (!m_Window) return;
#ifdef _DEBUG
	std::cout << "Main window created" << std::endl;
#endif

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_Renderer) return;
#ifdef _DEBUG
	std::cout << "Render created" << std::endl;
#endif

	m_Font = TTF_OpenFont((std::string(SDL_GetBasePath()) + "arial.ttf").c_str(), 25);
	if (!m_Font) return;
#ifdef _DEBUG
	std::cout << "Loaded font" << std::endl;
#endif

	// Get display info
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	m_MaxFPS = DM.refresh_rate;

	// Set up world
	Player* player = new Player(glm::i16vec2(size.x / 2, size.y / 2), m_Renderer);
	// Seed randomness with current time
	srand(time(0));
	std::vector<SquareObject*> apples = std::vector<SquareObject*>();
	for (size_t i = 0; i < 200; i++)
	{
		glm::i16vec2 position = glm::i16vec2(rand() % size.x, rand() % size.y);
		apples.push_back(new SquareObject(position, 10, m_Renderer));
	}
	m_World = new World(player, apples, m_Renderer);

	m_Running = true;
}

void Engine::MainLoop()
{
	const int frameDelay = 1000 / m_MaxFPS;

	Uint32 frameStart;
	int frameTime;

	while (m_Running)
	{
		frameStart = SDL_GetTicks();

		HandleEvents();
		Update();
		Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}
	Clean();
}

void Engine::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_Running = false;
		break;
	case SDL_KEYUP:
		if (m_World->GetPlayer()->GetVelocity().y != 1 && (event.key.keysym.sym == SDL_KeyCode::SDLK_UP || event.key.keysym.sym == SDL_KeyCode::SDLK_w))
		{
			m_World->GetPlayer()->SetVelocity(glm::i16vec2(0, -1));
		}
		else if (m_World->GetPlayer()->GetVelocity().y != -1 && (event.key.keysym.sym == SDL_KeyCode::SDLK_DOWN || event.key.keysym.sym == SDL_KeyCode::SDLK_s))
		{
			m_World->GetPlayer()->SetVelocity(glm::i16vec2(0, 1));
		}
		else if (m_World->GetPlayer()->GetVelocity().x != 1 && (event.key.keysym.sym == SDL_KeyCode::SDLK_LEFT || event.key.keysym.sym == SDL_KeyCode::SDLK_a))
		{
			m_World->GetPlayer()->SetVelocity(glm::i16vec2(-1, 0));
		}
		else if (m_World->GetPlayer()->GetVelocity().x != -1 && (event.key.keysym.sym == SDL_KeyCode::SDLK_RIGHT || event.key.keysym.sym == SDL_KeyCode::SDLK_d))
		{
			m_World->GetPlayer()->SetVelocity(glm::i16vec2(1, 0));
		}
		// quit
		else if (event.key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE) m_Running = false;
		break;
	}
}
void Engine::Update()
{
	m_World->Update();
}
void Engine::Render()
{
	// Set background color to black
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

	SDL_RenderClear(m_Renderer);

	m_World->Render();
	// Score
	std::string scoreString = "Score : " + std::to_string(m_World->GetPlayer()->GetEatenApples());
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(m_Font,
		scoreString.c_str(), color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);

	int texW = 0;
	int texH;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect destRect = { 0, 0, texW, texH};
	
	SDL_RenderCopy(m_Renderer, texture, NULL, &destRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(m_Renderer);
}
void Engine::Clean()
{
	TTF_CloseFont(m_Font);
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	TTF_Quit();
	SDL_Quit();
}