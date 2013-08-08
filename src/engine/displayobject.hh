// TRON-Roguelike DisplayObject.hh

#ifndef TRON_RLENGINEX_DISPLAYOBJECT_HH
#define TRON_RLENGINEX_DISPLAYOBJECT_HH

#include <cstdio>
#include <cstdint>
#include <memory>

#include <yaml-cpp/yaml.h>

#include "io.hh"

namespace YAML
{
	class Emitter;
	class Node;
}

class Serializer;

class DisplayObject
{
  public:
	DisplayObject() : print_(0), sprite_(0) {};
	DisplayObject(char _print, uint8_t _sprite, uint8_t _color) : print_(_print), sprite_(_sprite), color_(_color) {};
	DisplayObject(const YAML::Node& in)
	{
		id_ = in["id"].as<int>();
		print_ = in["print"].as<int>();
		sprite_ = in["sprite"].as<int>();
		color_ = in["color"].as<int>();
	};

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
	
	friend class Serializer;
};

#endif // TRON_RLENGINEX_DISPLAYOBJECT_HH
