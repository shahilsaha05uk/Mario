#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{	
	Load();
	quit = false;
	m_renderer = renderer;
}
MainMenu::~MainMenu()
{
	delete[] MainMenuRect;
}
void MainMenu::Load()
{
	menuTexture = new Texture2D(m_renderer);
	if (!menuTexture->LoadFromFile("Images/MainMenu.png"))
	{
		cout << "Title Screen failed to load!" << endl;
	}
	MenuTextLoad();
}
void MainMenu::Render()
{
	menuTexture->Render(Vector2D(),SDL_FLIP_NONE);
	MenuTextRender();
}
void MainMenu::Update(float deltaTime, SDL_Event e)
{
	MenuTextUpdate(deltaTime, e);
}



void MainMenu::MenuTextLoad()
{
	game_manager = new GameScreenManager(m_renderer);
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			_menuText[i] = new Text(m_renderer, game_manager->fontLoad[1],  "Level 1", { 255,255,255,255 });
		}
		if (i == 1)
		{
			_menuText[i] = new Text(m_renderer, game_manager->fontLoad[1],  "Level 2", { 255,255,255,255 });
		}
		if (i == 2)
		{
			_menuText[i] = new Text(m_renderer, game_manager->fontLoad[1],  "High Score", { 255,255,255,255 });
		}
		if (i == 3)
		{
			_menuText[i] = new Text(m_renderer, game_manager->fontLoad[1], "Quit",  { 255,255,255,255 });
		}
	}
}
void MainMenu::MenuTextRender()
{
	for (int i = 0; i < 4; i++)
	{
		//new Game
		if (i == 0)
		{
			MainMenuRect[i] = new SDL_Rect;
			MainMenuRect[i]->x = 225; MainMenuRect[i]->y = 18;
			MainMenuRect[i]->w = 80; MainMenuRect[i]->h = 80;
			_menuText[i]->Render(*MainMenuRect[i], m_renderer);
		}
		if(i==1)
		{
			//Level 2
			MainMenuRect[i] = new SDL_Rect;
			MainMenuRect[i]->x = 225; MainMenuRect[i]->y = 80;
			MainMenuRect[i]->w = 80; MainMenuRect[i]->h = 80;
			_menuText[i]->Render(*MainMenuRect[i], m_renderer);
		}
		if (i == 2)
		{
			//HighScore
			MainMenuRect[i] = new SDL_Rect;
			MainMenuRect[i]->x = 225; MainMenuRect[i]->y = 160;
			MainMenuRect[i]->w = 80; MainMenuRect[i]->h = 80;
			_menuText[i]->Render(*MainMenuRect[i], m_renderer);
		}
		if (i == 3)
		{
			//Quit
			MainMenuRect[i] = new SDL_Rect;
			MainMenuRect[i]->x = 225; MainMenuRect[i]->y = 240;
			MainMenuRect[i]->w = 80; MainMenuRect[i]->h = 80;
			_menuText[i]->Render(*MainMenuRect[i], m_renderer);
		}
	}
}
void MainMenu::MenuTextUpdate(float deltaTime, SDL_Event e)
{
	int x = 0;
	int y = 0;
	SDL_Color color = { 230,0,24 };

	switch (e.type)
	{
	case SDL_MOUSEMOTION:
		x = e.motion.x;
		y = e.motion.y;
		for (int i = 0; i < 4; i++)
		{
			//new Game
			if (i == 0)
			{
				if ((x > MainMenuRect[i]->x) && (x < MainMenuRect[i]->x + MainMenuRect[i]->w) && (y > MainMenuRect[i]->y) && (y < MainMenuRect[i]->y + MainMenuRect[i]->h))
				{
					_menuText[i]->Load(m_renderer, game_manager->fontLoad[1], "Level 1", color);
				}
				else
				{
					_menuText[i]->Load(m_renderer, game_manager->fontLoad[1], "Level 1", _menuText[i]->default_color);
				}
			}
			//new Game
			if (i == 1)
			{
				if ((x > MainMenuRect[i]->x) && (x < MainMenuRect[i]->x + MainMenuRect[i]->w) && (y > MainMenuRect[i]->y) && (y < MainMenuRect[i]->y + MainMenuRect[i]->h))
				{
					_menuText[i]->Load(m_renderer, game_manager->fontLoad[1], "Level 2", color);
				}
				else
				{
					_menuText[i]->Load(m_renderer, game_manager->fontLoad[1], "Level 2", _menuText[i]->default_color);
				}
			}
			//highScore
			if (i == 2)
			{
				if ((x > MainMenuRect[i]->x) && (x < MainMenuRect[i]->x + MainMenuRect[i]->w) && (y > MainMenuRect[i]->y) && (y < MainMenuRect[i]->y + MainMenuRect[i]->h))
				{
					_menuText[i]->Load(m_renderer, game_manager->fontLoad[1], "High Score", color);
				}
				else
				{
					_menuText[i]->Load(m_renderer, game_manager->fontLoad[1], "High Score", _menuText[i]->default_color);
				}

			}
			//quit
			if (i == 3)
			{
				if ((x > MainMenuRect[i]->x) && (x < MainMenuRect[i]->x + MainMenuRect[i]->w) && (y > MainMenuRect[i]->y) && (y < MainMenuRect[i]->y + MainMenuRect[i]->h))
				{
					_menuText[i]->Load(m_renderer, game_manager->fontLoad[1], "Quit", color);
				}
				else
				{
					_menuText[i]->Load(m_renderer, game_manager->fontLoad[1], "Quit", _menuText[i]->default_color);
				}

			}
		}
		break;
	}
}