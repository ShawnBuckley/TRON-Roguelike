// TRON-Roguelike TileType.cc

#include <yaml-cpp/yaml.h>

#include "displayobject.hh"
#include "game.hh"
#include "tiletype.hh"
#include "serializer.hh"

// TileTypeFlags

TileTypeFlags::TileTypeFlags(const YAML::Node& in)
{
	render_ = in["render"].as<bool>();
	solid_ = in["solid"].as<bool>();
};

inline bool TileTypeFlags::operator==(const TileTypeFlags& _other) const
{
	return (render_ == _other.render_ &&
		solid_ == _other.solid_);
}

// TileType

TileType::TileType(const YAML::Node& in)
{
	id_ = in["id"].as<int>();
	flags_ = TileTypeFlags(in["flags"]);
	displayobject_ = game().GetDisplayObject(in["displayobject"].as<int>());
};

bool TileType::operator==(const TileType &_other) const
{
	return (flags_ == _other.flags_ &&
		displayobject_ == _other.displayobject_);
}