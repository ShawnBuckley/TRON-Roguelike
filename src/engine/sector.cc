// TRON RLengineX Sector.cc

#include <yaml-cpp/yaml.h>

#include "game.hh"
#include "sector.hh"
#include "maptile.hh"

Sector::Sector(const YAML::Node& in)
{
	const YAML::Node& rectangle = in["rectangle"];
	rectangle_ = AxisAligned_Rectangle2<int16_t>(
		Vector2<int16_t>(rectangle[0].as<int>(), rectangle[1].as<int>()),
		rectangle[2].as<int>(), rectangle[3].as<int>());

	std::size_t x_limit = in["tiles"].size();
	for(std::size_t x=0; x<x_limit; x++)
	{
		std::vector<std::unique_ptr<MapTile>> row;
		std::size_t y_limit = in["tiles"][x].size();
		for(std::size_t y=0; y<y_limit; y++)
		{
			row.push_back(std::unique_ptr<MapTile>(new MapTile(in["tiles"][x][y])));
		}

		tile_.push_back(std::move(row));
	}
}

void Sector::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << "type" << "Sector";
	out << "rectangle" << YAML::Flow << YAML::BeginSeq;
	out << (int)rectangle_.Vertex(0).x << (int)rectangle_.Vertex(0).y;
	out << (int)rectangle_.Width() << (int)rectangle_.Height();
	out << YAML::EndSeq;
	out << "tiles" << YAML::BeginSeq;
	std::size_t x_limit = tile_.size();
	for(std::size_t x=0; x<x_limit; x++)
	{
		out << YAML::BeginSeq;
		std::size_t y_limit = tile_[x].size();
		for(std::size_t y=0; y<y_limit; y++)
		{
			tile_[x][y]->Serialize(out);
		}
		out << YAML::EndSeq;
	}
	out << YAML::EndSeq;
	out << YAML::EndMap;
}

MapTile* Sector::Tile(Vector2<int16_t> _coord)
{
	if(0 <= _coord.x && _coord.x <=rectangle_.Width() && 0 <= _coord.y && _coord.y <= rectangle_.Height())
	{
		return tile_[_coord.x][_coord.y].get();
	}

	return NULL;
};

void Sector::Generate(AxisAligned_Rectangle2<int16_t> _rectangle)
{
	printf("generate\n");

	TileType* ground = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject('.', 176, dark_blue))));

	printf("generate\n");

	rectangle_ = _rectangle;

	tile_.reserve(rectangle_.Width());

	for(int16_t x=0; x<=rectangle_.Width(); ++x)
	{
		std::vector<std::unique_ptr<MapTile>> row;
		row.reserve(rectangle_.Height());

		for(int16_t y=0; y<=rectangle_.Height(); ++y)
		{
			row.push_back(std::move(std::unique_ptr<MapTile>(
				new MapTile(Vector2<int16_t>(x+rectangle_.Vertex(0).x, y+rectangle_.Vertex(0).y), this, ground))));
		}

		tile_.push_back(std::move(row));
	}
}

bool SectorGenerator::Tick()
{
	
}
