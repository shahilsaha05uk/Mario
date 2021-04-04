#include "Texture2D.h"
#include <iostream>
#include <SDL_image.h>
#include "SDL.h"

//namespaces
using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}
Texture2D::~Texture2D()
{
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path)
{
	Free();
	SDL_Surface* p_surface = nullptr;
	m_texture = nullptr;
	//Load the image
	p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0XFF, 0XFF));
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
	}
	if (p_surface == nullptr)
	{
		cout << "Unable to create texture from surface. Error: " << SDL_GetError();
	}


	//remove the loaded surface coz we already have the texture now
	SDL_FreeSurface(p_surface);

	if (m_texture != nullptr)
	{
		//cout << "Texture Error: " << IMG_GetError();
		m_width = p_surface->w;
		m_height = p_surface->h;
	}

	//return the texture
	return m_texture != nullptr;
}
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{

	if (angle > 360)
	{
		angle = 0;
	}
	//Clear the screen

	//set where to render the texture
	SDL_Rect renderLocation = { new_position.x,new_position.y, m_width, m_height };

	//Render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderLocation, angle, NULL, flip);

	/*Parameters:
	1. The renderer
	2. The texture
	3. The source of the rectangle
	4. The destination rectangle
	5. an angle
	6. a SDL_Point of center of the texture
	7. Flipping- Hori, Verti*/
}
void Texture2D::Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(m_renderer, m_texture, &src_rect, &src_dest, angle, NULL, flip);

}

void Texture2D::Free()
{
	if (m_texture == nullptr)
	{
		m_width = 0;
		m_height = 0;
	}
}

int Texture2D::GetWidth() { return m_width; }
int Texture2D::GetHeight() { return m_height; }
