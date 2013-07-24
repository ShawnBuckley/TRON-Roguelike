// TRON-Roguelike LightGrid.cc

#include <memory>

#include "engine/io.hh"
#include "engine/maptile.hh"
#include "engine/tiletype.hh"

#include "lightgrid.hh"

LightGrid::LightGrid()
{
	kFloor[0] = TileType(DisplayObject('+', 197, dark_blue));
	kFloor[1] = TileType(DisplayObject('-', 196, dark_blue));
	kFloor[2] = TileType(DisplayObject('|', 179, dark_blue));
	kFloor[3] = TileType(DisplayObject(' ', 255, black));

	kWall = TileType(DisplayObject('#', 219, dark_blue), TileTypeFlags(1, 1));
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
					new MapTile(location, this, &kWall))));
			else
			{
				if(y % 2)
				{
					row.push_back(std::move(std::unique_ptr<MapTile>(
						new MapTile(location, this, x % 2 ? &kFloor[0] : &kFloor[1]))));
				}
				else
				{
					row.push_back(std::move(std::unique_ptr<MapTile>(
						new MapTile(location, this, x % 2 ? &kFloor[2] : &kFloor[3]))));
				}
			}
		}

		tile_.push_back(std::move(row));
	}
	
	printf("LG %p: %li %li\n", this, tile_.size(), tile_[0].size());
}
