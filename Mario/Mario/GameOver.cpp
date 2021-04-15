#include "GameOver.h"



GameOver::GameOver(SDL_Renderer* renderer): GameScreen(renderer)
{
	Load();
}
GameOver::~GameOver()
{


}

bool GameOver::Load()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/GameOver.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}
}
		
void GameOver::Update(SDL_Event e, float deltatime)
{

}
void GameOver::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

}
