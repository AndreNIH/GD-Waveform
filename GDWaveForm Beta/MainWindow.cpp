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

void MainWindow::copy(const MainWindow& rhs)
{
	// Nondynamic copying of Window Base members
	_innerWinTitle = rhs._innerWinTitle;
	_width = rhs._width;
	_height = rhs._height;
	_closed = rhs._closed;
	
	// TODO: give independent winhandles and rendererhandles
	_sdlWinHandle = rhs._sdlWinHandle; 
	_sdlRendererHandle = rhs._sdlRendererHandle;

	// Nondynamic copying of Main Window members
	grid_x = rhs.grid_x;
	enableCursorUpdate = rhs.enableCursorUpdate;
	cursorHighlight = rhs.cursorHighlight;

	_texture = rhs._texture;

	// deep copy all drawable objects in the _drawableObjects vector
	for (Drawable* drawableRHS : rhs._drawableObjects)
	{
		_drawableObjects.push_back(drawableRHS->send_copy());
	}
}

void MainWindow::dealloc()
{
	if (_texture != nullptr) SDL_DestroyTexture(_texture);
}

MainWindow::MainWindow(const std::string& title, int width, int height) : WindowBase(title,width,height) {}

MainWindow::MainWindow(const MainWindow& rhs)
{
	copy(rhs);
}

MainWindow& MainWindow::operator=(const MainWindow& rhs)
{
	dealloc();
	copy(rhs);

	return *this;
}

MainWindow::~MainWindow()
{
	dealloc();
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

	for (auto& noderef : _drawableObjects) { noderef->draw_node(_sdlRendererHandle); }
	SDL_RenderPresent(_sdlRendererHandle);
}

int MainWindow::get_x() const
{
	return grid_x;
}

