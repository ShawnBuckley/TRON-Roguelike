// TRON RLengineX Sector.cc

#include "game.hh"
#include "sector.hh"
#include "maptile.hh"

Sector::Sector()
{
	ground_ = game()->AddTileType(TileType(game()->AddDisplayObject(DisplayObject('.', 176, dark_blue))));
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
	rectangle_ = _rectangle;

	tile_.reserve(rectangle_.Width());

	for(int16_t x=0; x<=rectangle_.Width(); ++x)
	{
		std::vector<std::unique_ptr<MapTile>> row;
		row.reserve(rectangle_.Height());

		for(int16_t y=0; y<=rectangle_.Height(); ++y)
		{
			row.push_back(std::move(std::unique_ptr<MapTile>(
				new MapTile(Vector2<int16_t>(x+rectangle_.Vertex(0).x, y+rectangle_.Vertex(0).y), this, ground_))));
		}

		tile_.push_back(std::move(row));
	}
}

bool SectorGenerator::Tick()
{
	
}
