#include "Coins.h"


Coins::Coins(SDL_Renderer* renderer, LevelMaps* maps)
{
	string filepath = "Images/Coin.png";

	_texture = new Texture2D(renderer);
	m_level_maps = maps;
	if (!_texture->LoadFromFile(filepath.c_str()))
	{
		cout << "Coin could not be loaded" << endl;
	}
	else
	{
		cout << "Coins Loaded" << endl;
	}
	m_level_maps = maps;
	m_single_sprite_width = _texture->GetWidth() / 3;
	m_single_sprite_height = _texture->GetHeight();
	m_total_coin_frames = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_width * 0.5f, 325);
}
Coins::~Coins()
{
	m_renderer = nullptr;
	delete[] _texture;
	m_level_maps = nullptr;
}
void Coins::Render()
{
	int frame_count = m_single_sprite_width*(m_total_coin_frames-1);
	if (frame_count <= m_total_coin_frames)
	{
		SDL_Rect first_frame = { frame_count,0,m_single_sprite_width,m_single_sprite_height };
		SDL_Rect frame_position = {(int)(m_position.x),(int)(m_position.y),m_single_sprite_width, m_single_sprite_height };
		_texture->Render(first_frame, frame_position, SDL_FLIP_NONE);
		frame_count - 1;
	}
}
void Coins::Update(float deltaTime, SDL_Event e)
{

}