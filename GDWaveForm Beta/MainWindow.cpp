#include "MainWindow.h"
#include <iostream>
void MainWindow::eventHandler(SDL_Event& Event)
{
	switch (Event.type) {
	case SDL_MOUSEBUTTONDOWN:
		grid_x = Event.motion.x;
		enableCursorUpdate = true;
		break;
	case SDL_MOUSEBUTTONUP:
		enableCursorUpdate = false;
		break;
	case SDL_MOUSEMOTION:
		if(enableCursorUpdate)  grid_x = Event.motion.x;
		break;
	case SDL_KEYDOWN:
		if (Event.key.keysym.sym == SDLK_RIGHT) {
			std::cout << "Yeet\n";
			grid_x += 14;
		}
		break;
	case SDL_QUIT:
		_closed = true;
		break;
	}
}

MainWindow::MainWindow(const std::string& title, int width, int height) : WindowBase(title,width,height)
{
	if (!IMG_Init(IMG_INIT_PNG)) throw std::runtime_error{ "IMG_INIT Failed to initialize" };
}

MainWindow::~MainWindow()
{
	if (_texture != nullptr) SDL_DestroyTexture(_texture);
}

void MainWindow::load_image(const std::string& filename)
{
	if (_texture != nullptr) SDL_DestroyTexture(_texture);
	_texture = nullptr;
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr) throw std::runtime_error{ "Unable to locate file" };
	_texture = SDL_CreateTextureFromSurface(_sdlRendererHandle,surface);
	if (_texture == nullptr) throw std::runtime_error{ "CreateTextureFromSurface Error" };
}

void MainWindow::draw()
{
	SDL_RenderClear(_sdlRendererHandle);
	SDL_RenderCopy(_sdlRendererHandle, _texture, 0, 0);
	
	cursorHighlight.x = grid_x;

	SDL_SetRenderDrawColor(_sdlRendererHandle, 0, 255, 0, 0);
	SDL_RenderFillRect(_sdlRendererHandle, &cursorHighlight);

	for (auto& noderef : _drawableObjects) { (*noderef.get())->draw_node(_sdlRendererHandle); }
	SDL_RenderPresent(_sdlRendererHandle);
}
int MainWindow::get_x() const
{
	return grid_x;
}

