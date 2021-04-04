#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>
#include <string>

#include "Commons.h"
#include "GameScreenManager.h"
#include "Sounds.h"
#include "constants.h"
#include "Coins.h"
#include "Texture2D.h"
#include "TitleScreen.h"
//Namespaces
using namespace std;

//Global Variables
SDL_Window* g_window = nullptr; // g_window is to create a window which is initialised to 0/ nullptr
SDL_Renderer* g_renderer = nullptr; //to render the images related to Mario
GameScreenManager* game_screen_manager;
//Mix_Music* g_music = nullptr;
Sounds* _sounds = nullptr;

Uint32 g_old_time;
float angle = 0.0f;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void KeyEvent();
void PlayBackgroundMusic();

// Main Function
int main(int argc, char* args[])
{
	if (InitSDL()) //if the video is greater than 0
	{
		_sounds = new Sounds();
		_sounds->LoadMusic("Sounds/Mario.mp3");
		PlayBackgroundMusic();

		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		g_old_time = SDL_GetTicks();
		bool quit = false; // the program quit will not be true

		while (!quit) // till the time quit is not true
		{
			Render();
			quit = Update(); //quit is equal to the Update method which says... if the user clicks on the X button the program will return true else it will return false
							 // And till the time quit is not equal to true the program keeps looping
		}
	}
	return 0;
}

//Function bodies
bool InitSDL()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not initialise. Error: " << Mix_GetError() << endl;
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0) // if there is no video
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError(); // give the error
		return false;
	}
	else
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not initialise. Error: " << Mix_GetError() << endl;
		}
		//else create a window which uses the parameters: title, position at x, position at y, width of the window, height of the window, window state(shown, hidden,maximized, minimized... etc)
		g_window = SDL_CreateWindow("Game Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED); /* Create a new renderer for the game takes 3 parameters in:
																										 1)the window to be rendered
																										 2)index at which the redering driver should be initialised to
																										 3)Combination of SDL_RenderFlags*/
		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			//g_texture = ("Images/Test.png");
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise, Error: " << IMG_GetError();
			}
		}

		// What if the window does not get created?
		if (g_window == nullptr) // if the window is not created
		{
			cout << "Window was not created. Error: " << SDL_GetError(); // Give an error
			return false;
		}
	}
	return true;
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	SDL_Event e; // there is a struct called SDL_Event which is under Update method the methods and objects are used by the variable 'e'
	SDL_PollEvent(&e);
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false; // by default it will return false
}

void Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(g_renderer);
	//KeyEvent();
	game_screen_manager->Render();
	SDL_RenderPresent(g_renderer);
}

void CloseSDL()
{
	//release the texture
	delete game_screen_manager;
	game_screen_manager = nullptr;
}

void KeyEvent()
{
	SDL_Event keypress;

	SDL_PollEvent(&keypress);

	switch (keypress.type)
	{
	case SDL_KEYUP:
		switch (keypress.key.keysym.sym)
		{
		case SDLK_t:
			game_screen_manager = new GameScreenManager(g_renderer, SCREEN_INTRO);
			game_screen_manager->ChangeScreen(SCREEN_INTRO);
			cout << "Intro Screen" << endl;
			break;

		case SDLK_1:
			game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
			game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
			cout << "Level 1 screen" << endl;
			break;
		}
	}
}

void PlayBackgroundMusic()
{
	if (SDL_GetAudioStatus() == SDL_AUDIO_STOPPED)
	{
		_sounds->Play(-1);
	}
}