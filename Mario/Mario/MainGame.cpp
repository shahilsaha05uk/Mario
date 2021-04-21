#include "MainGame.h"
#include "HighScore.h"
MainGame::MainGame()
{
	if (InitSDL())
	{

		_sounds = new Sounds();
		_sounds->LoadMusic("Sounds/Mario.mp3");
		PlayBackgroundMusic();

		_menu = new MainMenu(g_renderer);
		_menu->Render();
		_gamescreen = new GameScreen(g_renderer);

		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
		g_old_time = SDL_GetTicks();
		quit = false;
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	CloseSDL();
}
MainGame::~MainGame()
{
	_sounds = nullptr;
	delete[] _sounds;

	_menu = nullptr;
	delete[] _menu;

	game_screen_manager = nullptr;
	delete[] game_screen_manager;
}
void MainGame::CloseSDL()
{
	delete game_screen_manager;
	game_screen_manager = NULL;

	SDL_DestroyRenderer(g_renderer);
	g_renderer = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	
}

bool MainGame::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not initialise. Error: " << Mix_GetError() << endl;
		}

		g_window = SDL_CreateWindow("Game Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if (g_renderer != nullptr)
		{
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise, Error: " << IMG_GetError();
			}
		}

		if (TTF_Init() == -1)
		{
			cout << "Font header didnt load" << TTF_GetError() << endl;
		}

		if (g_window == nullptr)
		{
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}
	return true;
}
void MainGame::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(g_renderer);
	game_screen_manager->Render();

	SDL_RenderPresent(g_renderer);
}
bool MainGame::Update()
{
	Uint32 new_time = SDL_GetTicks();
	SDL_PollEvent(&e);
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	GameControl(e);



	if (game_screen_manager->MariofetchHealth() == 0 || game_screen_manager->LuigifetchHealth() == 0)
	{
		game_screen_manager->ScoreUpdate();
		game_screen_manager->ChangeScreen(SCREEN_GAMEOVER);

		_sounds->LoadMusic("Sounds/GameOver.wav");
		_sounds->Play(0);

	}
	else if(game_screen_manager->FetchPlayerPosition() == true)
	{
		game_screen_manager->ChangeScreen(SCREEN_LEVEL2);
	}

	switch (e.type)
	{
		//click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;

	}
	g_old_time = new_time;
	return false;

}
void MainGame::GameControl(SDL_Event e)
{
	int x = 0;
	int y = 0;
	SDL_Color color = { 230,0,24 };

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			if (game_screen_manager->GetCurrentScreen() == SCREEN_GAMEOVER)
			{
				game_screen_manager->ChangeScreen(SCREEN_MENU);
				break;
			}
			break;

		case SDLK_r:
			game_screen_manager->ChangeScreen(SCREEN_MENU);
			break;
		case SDLK_m:
			_sounds->Pause();
			break;
		case SDLK_p:
			_sounds->Resume();
			break;
		}

	case SDL_MOUSEBUTTONDOWN:
		x = e.button.x;
		y = e.button.y;

		switch (e.button.button)
		{
		case SDL_BUTTON_LEFT:
			for (int i = 0; i < 4; i++)
			{
				switch (i)
				{
				case 0:
					if ((x > _menu->MainMenuRect[i]->x) && (x < _menu->MainMenuRect[i]->x + _menu->MainMenuRect[i]->w) && (y > _menu->MainMenuRect[i]->y) && (y < _menu->MainMenuRect[i]->y + _menu->MainMenuRect[i]->h))
					{
						g_old_time = SDL_GetTicks();

						cout << "Level 1 load" << endl;
						game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
					}
					break;
				case 1:
					if ((x > _menu->MainMenuRect[i]->x) && (x < _menu->MainMenuRect[i]->x + _menu->MainMenuRect[i]->w) && (y > _menu->MainMenuRect[i]->y) && (y < _menu->MainMenuRect[i]->y + _menu->MainMenuRect[i]->h))
					{
						g_old_time = SDL_GetTicks();

						cout << "Level 2 load" << endl;
						game_screen_manager->ChangeScreen(SCREEN_LEVEL2);
					}
					break;

				case 2:
					if ((x > _menu->MainMenuRect[i]->x) && (x < _menu->MainMenuRect[i]->x + _menu->MainMenuRect[i]->w) && (y > _menu->MainMenuRect[i]->y) && (y < _menu->MainMenuRect[i]->y + _menu->MainMenuRect[i]->h))
					{
						g_old_time = SDL_GetTicks();

						cout << "High Score load" << endl;
						game_screen_manager->ChangeScreen(SCREEN_HIGHSCORES);
					}
					break;
					//quit
				case 3:

					if ((x > _menu->MainMenuRect[i]->x) && (x < _menu->MainMenuRect[i]->x + _menu->MainMenuRect[i]->w) && (y > _menu->MainMenuRect[i]->y) && (y < _menu->MainMenuRect[i]->y + _menu->MainMenuRect[i]->h))
					{
						SDL_DestroyWindow(g_window);
						SDL_Quit();
					}
					break;
				}
			}
			break;
		}
		break;

	}
}
void MainGame::PlayBackgroundMusic()
{
	if (SDL_GetAudioStatus() == SDL_AUDIO_STOPPED)
	{
		_sounds->Play(-1);
	}

}