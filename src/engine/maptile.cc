// TRON-Roguelike MapTile.hh

#include <yaml-cpp/yaml.h>

#include "maptile.hh"
#include "tiletype.hh"
#include "mapobject.hh"

void MapTile::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << "type" << "MapTile";
	out << YAML::Key << "vector";
	out << YAML::Flow << YAML::BeginSeq;
	out << (int)location_.x << (int)location_.y << YAML::EndSeq;
	// out << "sector" << sector_->id_; // TODO
	out << "tiletype" << (int)tiletype_->id_;
	out << "mapobjects" << YAML::Flow << YAML::BeginSeq;
	for(MapObject* mapobject : mapobject_list_)
		out << (int)mapobject->id_;
	out << YAML::EndSeq;
	out << YAML::EndMap;
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
