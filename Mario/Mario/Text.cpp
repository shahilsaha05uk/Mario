#include "Text.h"
Text::Text(SDL_Renderer* renderer, TTF_Font* font, string text, SDL_Color color)
{
	_renderer = renderer;;
	_color = color;

	_fonts = font;
	text_texture = Load(renderer, _fonts, text, color);
	SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
}
Text::~Text()
{
	text_texture = nullptr;
	delete[] text_texture;
}

void Text::Render(SDL_Rect rect, SDL_Renderer* renderer)
{
	text_rect.w = rect.w; text_rect.h = rect.h;
	text_rect.x = rect.x; text_rect.y = rect.y;

	SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
}
SDL_Texture* Text::Load(SDL_Renderer* renderer, TTF_Font* font, string text, SDL_Color color)
{
	if (font == nullptr)
	{
		return nullptr;
	}

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	SDL_FreeSurface(text_surface);
	return text_texture;

}

void Text::Update(string updated_text)
{
	text_texture = Load(_renderer, _fonts, updated_text, _color);
}
void Text::Update(string updated_text, SDL_Color updated_color)
{
	text_texture = Load(_renderer, _fonts, updated_text, updated_color);

}
void Text::Draw()
{

}
