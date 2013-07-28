// TRON-Roguelike LightGrid.hh

#ifndef TRON_RLENGINEX_LIGHTGRID_HH
#define TRON_RLENGINEX_LIGHTGRID_HH

#include <memory>

#include "engine/tiletype.hh"
#include "engine/sector.hh"

class LightGrid : public Sector
{
  public:
	LightGrid();
	~LightGrid() {};

	void Generate(AxisAligned_Rectangle2<int16_t> _rectangle);
//	bool Fill(uint8_t Size);

	TileType* floor_[4];
	TileType* wall_;
};

#endif // TRON_RLENGINEX_LIGHTGRID_HH
