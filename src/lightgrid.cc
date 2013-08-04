// TRON-Roguelike LightGrid.cc

#include <memory>

#include "engine/game.hh"
#include "engine/io.hh"
#include "engine/maptile.hh"
#include "engine/tiletype.hh"

#include "lightgrid.hh"

LightGrid::LightGrid()
{
	floor_[0] = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject('+', 197, dark_blue))));
	floor_[1] = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject('-', 196, dark_blue))));
	floor_[2] = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject('|', 179, dark_blue))));
	floor_[3] = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject(' ', 255, black))));

	wall_ = game().AddTileType(TileType(game().AddDisplayObject(DisplayObject('#', 219, dark_blue)), TileTypeFlags(1, 1)));
}

void LightGrid::Generate(AxisAligned_Rectangle2<int16_t> _rectangle)
{
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
					new MapTile(location, this, wall_))));
			else
			{
				if(y % 2)
				{
					row.push_back(std::move(std::unique_ptr<MapTile>(
						new MapTile(location, this, x % 2 ? floor_[0] : floor_[1]))));
				}
				else
				{
					row.push_back(std::move(std::unique_ptr<MapTile>(
						new MapTile(location, this, x % 2 ? floor_[2] : floor_[3]))));
				}
			}
		}

		tile_.push_back(std::move(row));
	}
	
	printf("LG %p: %li %li\n", this, tile_.size(), tile_[0].size());
}
