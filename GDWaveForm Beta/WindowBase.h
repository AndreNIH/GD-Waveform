#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdexcept>
#include "Drawable.h"
#include <memory>
#include <vector>


class WindowBase {
protected:
	std::string _innerWinTitle;
	int _width;  //determine width of the window
	int _height; //determines height of the window
	bool _closed = false; //this variable dictates when to exit the update loop
	SDL_Window* _sdlWinHandle  = nullptr; //internal handle for SDL library
	SDL_Renderer* _sdlRendererHandle = nullptr;  //inter handle for SDL library
	std::vector<Drawable*>_drawableObjects; //
	virtual void eventHandler(SDL_Event& Event);
public:
	WindowBase(const std::string& winTitle, int width, int height);
	~WindowBase();
	void poll_event();
	virtual void draw() = 0;
	bool is_closed() const { return _closed; }
	SDL_Renderer* get_renderer() const;
	
	void append(Drawable* drawable_obj);

};
