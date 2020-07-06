#pragma once
#include <SDL_ttf.h>
#include "Drawable.h"
#include <string>
#include <stdexcept>
class LabelTTF : public Drawable{
private:
	SDL_Texture* _texture = nullptr;
	TTF_Font* _font = nullptr;
	SDL_Surface* _surface = nullptr;
	SDL_Rect _labelRect;
public:
	LabelTTF(const std::string& text, const std::string& fontname, int fontSize);
	~LabelTTF();
	void set_position(int x, int y);
	void set_label(const std::string& text);
	static LabelTTF create_string(const std::string& text, const std::string& fontname, int fontSize);
	static LabelTTF create_string(const std::string& fontname, int fontSize);
	void draw_node(SDL_Renderer* sharedRender) override;

};