#include "LuigiCharacter.h"


LuigiCharacter::LuigiCharacter(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMaps* maps) : Character(renderer, imagePath, start_position,maps)
{

}
LuigiCharacter::~LuigiCharacter()
{


}
void LuigiCharacter::Render()
{

	Character::Render();

}
void LuigiCharacter::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_w:
			if (m_can_jump)
			{
				cout << "Down" << endl;
				Jump();
			}
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		case SDLK_w:
			cout << "JumpUp" << endl;

		default:
			break;
		}
	default:
		break;
	}

}

