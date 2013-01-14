// TRON-Roguelike LightGrid.hh

#ifndef TRON_RLENGINEX_LIGHTGRID_HH
#define TRON_RLENGINEX_LIGHTGRID_HH

#include <memory>

#include "tiletype.hh"
#include "sector.hh"

class LightGrid : public Sector
{
  public:
	LightGrid();
	~LightGrid() {};

  	void Save(std::stringstream &_save);
  	void Load() {};

	void Generate(std::shared_ptr<Sector> _this, AxisAligned_Rectangle2<int16_t> _rectangle);
//	bool Fill(uint8_t Size);

	std::shared_ptr<TileType> kFloor[4];
	std::shared_ptr<TileType> kWall;
};

#endif // TRON_RLENGINEX_LIGHTGRID_HH
