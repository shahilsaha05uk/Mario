#include "MarioCharacter.h"

MarioCharacter::MarioCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps) : Character(renderer, imagePath, start_position, maps)
{
	
	_jumpSound = new Sounds();
	//_jumpSound = new Sounds("Sounds/Jump.ogg");
	_jumpSound->LoadMusic("Sounds/Jump.ogg");

}
MarioCharacter::~MarioCharacter()
{
	delete[] _jumpSound;

}
void MarioCharacter::Render()
{
	Character::Render();
}
void MarioCharacter::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

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

