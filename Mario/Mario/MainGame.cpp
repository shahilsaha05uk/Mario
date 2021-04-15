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
		score = new HighScore(g_renderer, true);

		//_score = new GameScreen(g_renderer);
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
	trial(e);
	health = game_screen_manager->trial();
	if (health == 0)
	{
		_scores = game_screen_manager->Scores();
		UpdateScoreFile(true);
		cout << "Scores from main game: " << game_screen_manager->Scores();
		game_screen_manager->ChangeScreen(SCREEN_GAMEOVER);

	}

	switch (e.type)
	{
		//click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;

	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;

}
void MainGame::trial(SDL_Event e)
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
			if (game_screen_manager->trialScreen() == SCREEN_GAMEOVER)
			{
				game_screen_manager->ChangeScreen(SCREEN_MENU);
			}
		
			break;

		}
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			game_screen_manager->ChangeScreen(SCREEN_MENU);
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
//void MainGame::StoreScore(bool b)
//{
//	int tempscore = 0;
//	if (b == true)
//	{
//		tempscore += _score->ScoreRecord();
//		cout << "Scores are: " << tempscore;
//	}
//
//	outfile.open("Score.txt", ios::app);
//	outfile << "Score is: " << tempscore << endl;
//	outfile.close();
//
//	if (!outfile.is_open())
//	{
//		cout << "File successfully updated" << endl;
//	}
//}
void MainGame::PlayBackgroundMusic()
{
	if (SDL_GetAudioStatus() == SDL_AUDIO_STOPPED)
	{
		//_sounds->Play(-1);
	}
}

void MainGame::UpdateScoreFile(bool b)
{
	ofstream writefile;
	if (b == true)
	{
		cout << "Scores are: " << _scores;
		b = false;

	}
	writefile.open("Score.txt", ios::app);
	if (_scores > 0)
	{
		writefile << "Score is: " << _scores << endl;
	}
	writefile.close();

	if (!writefile.is_open())
	{
		cout << "File successfully updated" << endl;
	}
	writefile.close();
}