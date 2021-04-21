#include "MarioCharacter.h"

MarioCharacter::MarioCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps) : Character(renderer, imagePath, start_position, maps)
{
	_jumpSound = new Sounds();
	_jumpSound->LoadMusic("Sounds/Jump.wav");


	m_single_sprite_h = m_texture->GetHeight();
	m_single_sprite_w = m_texture->GetWidth() / 6;
	TotalframesCount = 6;
}
MarioCharacter::~MarioCharacter()
{
	delete[] _jumpSound;

}
void MarioCharacter::Render()
{
	int firstSprite = currentFrameCount * m_single_sprite_w;
	
	SDL_Rect firstFrame = { firstSprite,0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect worldDrawPosition = { (int)m_position.x , (int)m_position.y , m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(firstFrame, worldDrawPosition, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		m_texture->Render(firstFrame, worldDrawPosition, SDL_FLIP_NONE);
	}
}
void MarioCharacter::Update(float deltaTime, SDL_Event e)
{
	MarioKeyboard(deltaTime, e);

	Character::Update(deltaTime, e);

	MarioAnimation(deltaTime, e);
}
void MarioCharacter::JumpSound(bool play)
{
	if (play == true)
	{
		if (SDL_GetAudioStatus() == SDL_AUDIO_STOPPED)
		{
			_jumpSound->Play(0);
		}
	}
}
void MarioCharacter::MarioKeyboard(float deltatime, SDL_Event e)
{

		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_moving_left = true;
				break;
			case SDLK_RIGHT:
				m_moving_right = true;
				break;
			case SDLK_SPACE:
				if (m_can_jump)
				{
					Jump();
					JumpSound(true);
				}
				else
				{
					JumpSound(false);
				}
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_moving_left = false;
				break;
			case SDLK_RIGHT:
				m_moving_right = false;
				break;
			case SDLK_SPACE:
				if (!m_can_jump)
				{
					JumpSound(false);
				}
				else
				{
					JumpSound(false);
				}
			}
		default:
			break;
		}
}


void MarioCharacter::MarioAnimation(float deltaTime, SDL_Event e)
{
	mtimer += deltaTime;
	if (m_moving_right || m_moving_left)
	{
		if (mtimer > ANIMATIONDELAY)
		{
			currentFrameCount++;
			mtimer = 0;

			if (currentFrameCount > 3)
			{
				currentFrameCount = 0;
			}
		}
		else if (m_jumping)
		{
			currentFrameCount = 4;
		}
	}
}
