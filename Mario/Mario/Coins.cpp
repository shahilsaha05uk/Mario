#include "Coins.h"

Coins::Coins(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps) : Character(renderer, imagePath, start_position, maps)
{
	_coinSound = new Sounds();
	_coinSound->LoadMusic("Sounds/coin.mp3");
	m_position = start_position;
	frame_delay = COINS_ROTATE_SPEED;
	m_total_coin_frames = 3;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}
Coins::~Coins()
{

}
void Coins::Render()
{
	int left = currentFrame * m_single_sprite_w;
	SDL_Rect first_frame = { left,0,m_single_sprite_w,m_single_sprite_h };
	SDL_Rect draw_pos = { (int)(m_position.x),(int)(m_position.y),m_single_sprite_w, m_single_sprite_h };
	m_texture->Render(first_frame, draw_pos, SDL_FLIP_NONE);

}
void Coins::Update(float deltaTime, SDL_Event e)
{
	frame_delay -= deltaTime;
	if (frame_delay <= 0)
	{
		frame_delay = COINS_ROTATE_SPEED;
		currentFrame++;

		if (currentFrame > 2)
		{
			currentFrame = 0;
		}
	}
	//Character::Update(deltaTime, e);

}

void Coins::CoinSound(bool play)
{
	if (play == true)
	{
		if (SDL_GetAudioStatus() == SDL_AUDIO_STOPPED)
		{
			_coinSound->Play(0);
		}
	}
}

