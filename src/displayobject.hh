// RLengineX DisplayObject.hh

#ifndef RLENGINEX_DISPLAYOBJECT_HH
#define RLENGINEX_DISPLAYOBJECT_HH

#include <cstdio>
#include <cstdint>
#include <memory>

#include "object.hh"
#include "color.hh"

class DisplayObject : public Object
{
  public:
	DisplayObject() : print_(0), sprite_(0) {};
	DisplayObject(char _print, uint8_t _sprite, std::shared_ptr<Color> _color) : print_(_print), sprite_(_sprite), color_(_color) {};
//	DisplayObject(DisplayObject *_displayobject) : print_(_displayobject->print_), sprite_(_displayobject->sprite_), color_(_displayobject->color_) {};
//	DisplayObject(const DisplayObject &_displayobject) : print_(_displayobject.print_), sprite_(_displayobject.sprite_), color_(_displayobject.color_) {};
	~DisplayObject() {};

 	virtual void Save(std::stringstream &_save);
  	virtual void Load();
 
	char print_;
	uint8_t sprite_;
	std::shared_ptr<Color> color_;
	
//	GLuint display_list_;
};

#endif // RLENGINEX_DISPLAYOBJECT_HH
