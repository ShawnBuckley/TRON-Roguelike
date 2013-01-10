// TRON-Rouglike GL.hh

#ifndef ENGINE_XGL_HH
#define ENGINE_XGL_HH

#include <cstdint>
#include <vector>
#include <string>
#include "sdl.hh"

typedef uint8_t GLubyte;
typedef unsigned int GLuint;

struct SDL_Surface;

class Color;
class DisplayObject;

struct ClipRect
{
	uint16_t y;
	uint16_t x;
};

struct FontRect
{
	float a;
	float b;
	float c;
	float d;
};

class GL : public SDL
{
  private:
	
  public:
	GL() : texture_(NULL) {};
	~GL();

	void Init();

	bool LoadTexture(std::string _file);
	void LoadFont(int _x, int _y, int _xwdith, int _yhieght);

	void SetState();
	void EndState();
	void Clear();
	void Refresh();
	void SetColor(std::shared_ptr<Color> _color);
	void Print(uint8_t _print, std::shared_ptr<Color> _color);


	GLuint *texture_;

	std::vector<FontRect> font_;
};

#endif
