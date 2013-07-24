// TRON-Roguelike DisplayObject.hh

#ifndef TRON_RLENGINEX_DISPLAYOBJECT_HH
#define TRON_RLENGINEX_DISPLAYOBJECT_HH

#include <cstdio>
#include <cstdint>
#include <memory>

#include "io.hh"

class DisplayObject
{
  public:
	DisplayObject() : print_(0), sprite_(0) {};
	DisplayObject(char _print, uint8_t _sprite, uint8_t _color) : print_(_print), sprite_(_sprite), color_(_color) {};
	~DisplayObject() {};

	char print_;
	uint8_t sprite_;
	uint8_t color_;
	
//	GLuint display_list_;
};

#endif // TRON_RLENGINEX_DISPLAYOBJECT_HH
