#include "Text.h"
Text::Text(SDL_Renderer* renderer, string path, string text, int fontsize, SDL_Color color)
{
	_renderer = renderer;;
	_path = path;
	_fontsize = fontsize;
	_color = color;


	text_texture = Load(renderer, path, text, color, fontsize);
	SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
}
Text::~Text()
{

}

void Text::Render(SDL_Rect rect, SDL_Renderer* renderer)
{
	text_rect.w = rect.w; text_rect.h = rect.h;
	text_rect.x = rect.x; text_rect.y = rect.y;

	SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
}

SDL_Texture* Text::Load(SDL_Renderer* renderer, string path, string text, SDL_Color color, int fontsize)
{
	TTF_Font* font = TTF_OpenFont(path.c_str(), fontsize);
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	text_texture = SDL_CreateTextureFromSurface(renderer,text_surface);

	SDL_FreeSurface(text_surface);
	return text_texture;

}
void Text::Update(string updated_text)
{
	text_texture = Load(_renderer, _path, updated_text, _color, _fontsize);

}
void Text::Update(string updated_text, SDL_Color updated_color)
{
	text_texture = Load(_renderer, _path, updated_text, updated_color, _fontsize);

}
void Text::Draw()
{

}
