#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{	
	Load();
	quit = false;
	m_renderer = renderer;
	//score = new HighScore(renderer, true);
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
	//ScreenLoader(e, deltaTime);
}
//void MainMenu::ScreenLoader(SDL_Event e, float deltatime)
//{
//	int x = 0;
//	int y = 0;
//
//	switch (e.type)
//	{
//	case SDL_KEYDOWN:
//		switch (e.key.keysym.sym)
//		{
//		case SDLK_ESCAPE:
//			//score = new HighScore(g_renderer,true);
//			score->StoreScore(false);
//			//SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
//
//			//SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
//
//			break;
//		}
//	case SDL_KEYUP:
//		switch (e.key.keysym.sym)
//		{
//		case SDLK_ESCAPE:
//			score->StoreScore(true);
//			break;
//		}
//
//	case SDL_MOUSEBUTTONDOWN:
//		x = e.button.x;
//		y = e.button.y;
//
//		switch (e.button.button)
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				switch (i)
//				{
//				case 0:
//					if ((x > MainMenuRect[i]->x) && (x < MainMenuRect[i]->x + MainMenuRect[i]->w) && (y > MainMenuRect[i]->y) && (y < MainMenuRect[i]->y + MainMenuRect[i]->h))
//					{
//						cout << "Level 1 load" << endl;
//						game_manger->ChangeScreen(SCREEN_LEVEL1);
//
//						quit = false;
//						while (!quit)
//						{
//							Render();
//							SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
//						}
//					}
//				}
//			}
//		}
//	}
//}
void MainMenu::MenuTextLoad()
{
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			_menuText[i] = new Text(m_renderer, "Fonts/BASTION_.TTF",  "Level 1", MEDIUMTEXTSIZE, { 255,255,255,255 });
		}
		if (i == 1)
		{
			_menuText[i] = new Text(m_renderer, "Fonts/BASTION_.TTF",  "Level 2", MEDIUMTEXTSIZE, { 255,255,255,255 });
		}
		if (i == 2)
		{
			_menuText[i] = new Text(m_renderer, "Fonts/BASTION_.TTF",  "High Score", MEDIUMTEXTSIZE, { 255,255,255,255 });
		}
		if (i == 3)
		{
			_menuText[i] = new Text(m_renderer, "Fonts/BASTION_.TTF", "Quit",  MEDIUMTEXTSIZE, { 255,255,255,255 });
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
					_menuText[i]->Load(m_renderer, "Fonts/BASTION_.ttf", "Level 1", color, MEDIUMTEXTSIZE);
				}
				else
				{
					_menuText[i]->Load(m_renderer, "Fonts/BASTION_.ttf", "Level 1", _menuText[i]->default_color, MEDIUMTEXTSIZE);
				}
			}
			//new Game
			if (i == 1)
			{
				if ((x > MainMenuRect[i]->x) && (x < MainMenuRect[i]->x + MainMenuRect[i]->w) && (y > MainMenuRect[i]->y) && (y < MainMenuRect[i]->y + MainMenuRect[i]->h))
				{
					_menuText[i]->Load(m_renderer, "Fonts/BASTION_.ttf", "Level 2", color, MEDIUMTEXTSIZE);
				}
				else
				{
					_menuText[i]->Load(m_renderer, "Fonts/BASTION_.ttf", "Level 2", _menuText[i]->default_color, MEDIUMTEXTSIZE);
				}
			}

			//highScore
			if (i == 2)
			{
				if ((x > MainMenuRect[i]->x) && (x < MainMenuRect[i]->x + MainMenuRect[i]->w) && (y > MainMenuRect[i]->y) && (y < MainMenuRect[i]->y + MainMenuRect[i]->h))
				{
					_menuText[i]->Load(m_renderer, "Fonts/BASTION_.ttf", "High Score", color, MEDIUMTEXTSIZE);
				}
				else
				{
					_menuText[i]->Load(m_renderer, "Fonts/BASTION_.ttf", "High Score", _menuText[i]->default_color, MEDIUMTEXTSIZE);
				}

			}
			//quit
			if (i == 3)
			{
				if ((x > MainMenuRect[i]->x) && (x < MainMenuRect[i]->x + MainMenuRect[i]->w) && (y > MainMenuRect[i]->y) && (y < MainMenuRect[i]->y + MainMenuRect[i]->h))
				{
					_menuText[i]->Load(m_renderer, "Fonts/BASTION_.ttf", "Quit", color, MEDIUMTEXTSIZE);
				}
				else
				{
					_menuText[i]->Load(m_renderer, "Fonts/BASTION_.ttf", "Quit", _menuText[i]->default_color, MEDIUMTEXTSIZE);
				}

			}
		}
		break;
	}
}