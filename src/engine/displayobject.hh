// TRON-Roguelike DisplayObject.hh

#ifndef TRON_RLENGINEX_DISPLAYOBJECT_HH
#define TRON_RLENGINEX_DISPLAYOBJECT_HH

#include <cstdio>
#include <cstdint>
#include <memory>

#include "io.hh"

class Serializer;

class DisplayObject
{
  public:
	DisplayObject() : print_(0), sprite_(0) {};
	DisplayObject(char _print, uint8_t _sprite, uint8_t _color) : print_(_print), sprite_(_sprite), color_(_color) {};
	~DisplayObject() {};

	inline bool operator==(const DisplayObject& _other) const
	{
		return(print_ == _other.print_ &&
			sprite_ == _other.print_ &&
			color_ == _other.color_);
	}

	uint16_t id_;
	char print_;
	uint8_t sprite_;
	uint8_t color_;
	
	DisplayObject(uint16_t _id, char _print, uint8_t _sprite, uint8_t _color) : id_(_id), print_(_print), sprite_(_sprite), color_(_color) {};
	friend class Serializer;
};

#endif // TRON_RLENGINEX_DISPLAYOBJECT_HH
