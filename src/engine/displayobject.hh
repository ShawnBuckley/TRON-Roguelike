// TRON-Roguelike DisplayObject.hh

#ifndef TRON_RLENGINEX_DISPLAYOBJECT_HH
#define TRON_RLENGINEX_DISPLAYOBJECT_HH

#include <cstdio>
#include <cstdint>
#include <memory>

#include "io.hh"

namespace YAML
{
	class Emitter;
}

class DisplayObject
{
  public:
	DisplayObject() : print_(0), sprite_(0) {};
	DisplayObject(char _print, uint8_t _sprite, uint8_t _color) : print_(_print), sprite_(_sprite), color_(_color) {};
	~DisplayObject() {};

	void Serialize(YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "type";
		out << YAML::Value << "DisplayObject";
		out << YAML::Key << "id";
		out << YAML::Value << id_;
		out << YAML::Key << "print";
		out << YAML::Value << (char)print_;
		out << YAML::Key << "sprite";
		out << YAML::Value << (int)sprite_;
		out << YAML::Key << "color";
		out << YAML::Value << (int)color_;
		out << YAML::EndMap;
	}

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
	
//	GLuint display_list_;
};

#endif // TRON_RLENGINEX_DISPLAYOBJECT_HH
