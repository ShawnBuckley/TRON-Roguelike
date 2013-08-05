// TRON-Roguelike Map.cc

#include <inttypes.h>

#include <yaml-cpp/yaml.h>

#include "map.hh"
#include "maptile.hh"
#include "sector.hh"

Map::Map(const YAML::Node& in)
{
	const YAML::Node& rectangle = in["rectangle"];
	rectangle_ = AxisAligned_Rectangle2<int16_t>(
		Vector2<int16_t>(rectangle[0].as<int>(), rectangle[1].as<int>()),
		rectangle[2].as<int>(), rectangle[3].as<int>());
}

void Map::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << "type" << "Map";
	out << "rectangle" << YAML::Flow << YAML::BeginSeq;
	out << (int)rectangle_.Vertex(0).x << (int)rectangle_.Vertex(0).y;
	out << (int)rectangle_.Width() << (int)rectangle_.Height();
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

void Map::GenerateSector(Sector* _sector, AxisAligned_Rectangle2<int16_t> _rectangle)
{
	_sector->Generate(_rectangle);
	sector_.push_back(std::move(std::unique_ptr<Sector>(_sector)));

	if(_rectangle.Vertex(0).x < rectangle_.Vertex(0).x)
		rectangle_.Origin(Vector2<int16_t>((_rectangle.Vertex(0).x), rectangle_.Vertex(0).y));

	if(_rectangle.Vertex(0).y < rectangle_.Vertex(0).y)
		rectangle_.Origin(Vector2<int16_t>((rectangle_.Vertex(0).x), _rectangle.Vertex(0).y));

	if(_rectangle.Width()+_rectangle.Vertex(0).x > rectangle_.Width())
		rectangle_.Width(_rectangle.Width()+_rectangle.Vertex(0).x);

	if(_rectangle.Height()+_rectangle.Vertex(0).y > rectangle_.Height())
		rectangle_.Height(_rectangle.Height()+_rectangle.Vertex(0).y);
}

MapTile* Map::Tile(Vector2<int16_t> _coord)
{
	if(!CoordValid(_coord))
		return NULL;

	for(auto sector = sector_.begin();
		sector != sector_.end(); ++sector)
	{
		if((*sector) != NULL)
		{
			if((*sector)->rectangle_.Intersect(_coord))
			{
				return (*sector)->tile_[_coord.x - (*sector)->rectangle_.Vertex(0).x][_coord.y-(*sector)->rectangle_.Vertex(0).y].get();
			}
		}
	}

	return NULL;
}

void Map::AddTileType(TileType *_tiletype)
{
	
}