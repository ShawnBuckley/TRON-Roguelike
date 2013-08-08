// TRON-Roguelike MapTile.hh

#include <yaml-cpp/yaml.h>

#include "maptile.hh"
#include "tiletype.hh"
#include "mapobject.hh"
#include "game.hh"
#include "serializer.hh"

MapTile::MapTile(const YAML::Node& in)
{
	location_ = Vector2<int16_t>(in["vector"][0].as<int>(), in["vector"][1].as<int>());
	tiletype_ = game().GetTileType(in["tiletype"].as<int>());

	mapobject_list_.clear();
	for(std::size_t i=0; i<in["mapobjects"].size(); i++)
	{
		mapobject_list_.push_back(game().GetMapObject(in["mapobjects"][i].as<int>()));
	}
}

std::vector<MapObject*> MapTile::SolidMapObject()
{
	std::vector<MapObject*> result;

	if(mapobject_list_.empty())
		return result;

	for(auto mapobject = mapobject_list_.begin(); mapobject != mapobject_list_.end(); ++mapobject)
	{
		if(*mapobject == NULL) continue;

		if((*mapobject)->flags_.clipping_)
		{
			result.push_back(*mapobject);
		}
	}

	return result;
}

bool MapTile::AnySolidMapObject()
{
	if(mapobject_list_.empty())
		return 0;

	for(auto mapobject = mapobject_list_.begin(); mapobject != mapobject_list_.end(); ++mapobject)
	{
		if(*mapobject == NULL) continue;

		if((*mapobject)->flags_.clipping_)
		{
			return 1;
		}
	}

	return 0;
}

DisplayObject* MapTile::VisibleMapObject()
{
	if(mapobject_list_.empty()) return NULL;

	for(auto mapobject = mapobject_list_.begin(); mapobject != mapobject_list_.end(); ++mapobject)
	{
		if((*mapobject) == NULL) continue;

		if((*mapobject)->flags_.visible_)
		{
			return (*mapobject)->displayobject_;
		}
	}

	return NULL;
}
