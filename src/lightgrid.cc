// TRON-Roguelike LightGrid.cc

#include <memory>

#include "engine/game.hh"
#include "engine/io.hh"
#include "engine/maptile.hh"
#include "engine/tiletype.hh"

#include "lightgrid.hh"
#include "tronserializer.hh"

LightGrid::LightGrid(const YAML::Node& in)
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

void LightGrid::Serialize(Serializer& out)
{
	printf("sector out\n");
	TronSerializer& tron_out = (TronSerializer&)out;
	tron_out.Serialize(*this);
}
void LightGrid::Generate(AxisAligned_Rectangle2<int16_t> _rectangle)
{
	TileType *grid_floor[4];
	grid_floor[0] = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject('+', 197, dark_blue))));
	grid_floor[1] = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject('-', 196, dark_blue))));
	grid_floor[2] = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject('|', 179, dark_blue))));
	grid_floor[3] = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject(' ', 255, black))));

	TileType *grid_wall = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject('#', 219, dark_blue)), TileTypeFlags(1, 1)));

	rectangle_ = _rectangle;

	tile_.reserve(rectangle_.Width());

	for(int16_t x=0; x<=rectangle_.Width(); ++x)
	{
		std::vector<std::unique_ptr<MapTile>> row;
		row.reserve(rectangle_.Height());

		for(int16_t y=0; y<=rectangle_.Height(); ++y)
		{
			Vector2<int16_t> location(x+rectangle_.Vertex(0).x, y+rectangle_.Vertex(0).y);
		
			if(y == 0 || y >= rectangle_.Height()-1 || x == 0 || x >= rectangle_.Width()-1)
				row.push_back(std::move(std::unique_ptr<MapTile>(
					new MapTile(location, this, grid_wall))));
			else
			{
				if(y % 2)
				{
					row.push_back(std::move(std::unique_ptr<MapTile>(
						new MapTile(location, this, x % 2 ? grid_floor[0] : grid_floor[1]))));
				}
				else
				{
					row.push_back(std::move(std::unique_ptr<MapTile>(
						new MapTile(location, this, x % 2 ? grid_floor[2] : grid_floor[3]))));
				}
			}
		}

		tile_.push_back(std::move(row));
	}
	
	printf("LG %p: %li %li\n", this, tile_.size(), tile_[0].size());
}
