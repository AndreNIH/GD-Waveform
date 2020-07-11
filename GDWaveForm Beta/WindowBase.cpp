#include "WindowBase.h"

void WindowBase::eventHandler(SDL_Event& Event){
	switch (Event.type)
	{
	case SDL_QUIT:
		_closed = true;
		break;

	default:
		break;
	}
	
}

WindowBase::WindowBase(const std::string& winTitle, int width, int height) :
	_innerWinTitle(winTitle),
	_width(width), 
	_height(height) 
{
	_sdlWinHandle = SDL_CreateWindow(winTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0); 
	if (_sdlWinHandle == nullptr) throw std::runtime_error{ "SDL_CreateWindow fail" };
	_sdlRendererHandle = SDL_CreateRenderer(_sdlWinHandle, -1, SDL_RENDERER_ACCELERATED);
	if (_sdlRendererHandle == nullptr) throw std::runtime_error{ "SDL_CreateRender fail" };
	
	
}

WindowBase::~WindowBase() {
	if (_sdlWinHandle != nullptr) SDL_DestroyWindow(_sdlWinHandle);
	if (_sdlRendererHandle != nullptr) SDL_DestroyRenderer(_sdlRendererHandle);
}

void WindowBase::poll_event() {
	SDL_Event programEvent;
	if (SDL_PollEvent(&programEvent)) eventHandler(programEvent);
}

SDL_Renderer* WindowBase::get_renderer() const{return _sdlRendererHandle;}

void WindowBase::append(Drawable* drawable_obj){
	_drawableObjects.push_back(drawable_obj);
}

