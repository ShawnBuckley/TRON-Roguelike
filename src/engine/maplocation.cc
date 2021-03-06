// TRON-Roguelike MapLocation.cc

#include "maplocation.hh"
#include "maptile.hh"
#include "game.hh"
#include "serializer.hh"

MapLocation::MapLocation(AxisAligned_Rectangle2<int16_t> _rectangle) : rectangle_(_rectangle)
{
	maptile_.reserve(rectangle_.Width());

	for(int16_t x=0; x<=rectangle_.Width(); ++x)
	{
		std::vector<MapTile*> row;
		row.reserve(rectangle_.Height());
		maptile_.push_back(row);
	}
};

void MapLocation::Connect()
{
	for(int16_t x=0; x<rectangle_.Width(); ++x)
	{	
		std::vector<MapTile*> row;
	
		for(int16_t y=0; y<rectangle_.Height(); ++y)
		{
			MapTile* maptile = game().map_->Tile(rectangle_.Vertex(0) + Vector2<int16_t>(x, y));
			Vector2<int16_t> pos = rectangle_.Vertex(0) + Vector2<int16_t>(x, y);

			row.push_back(maptile);
		}

		maptile_.push_back(row);
	}
}