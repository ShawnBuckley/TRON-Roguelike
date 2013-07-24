// TRON-Roguelike TileType.hh

#ifndef TRON_RLENGINEX_TILETYPE_HH
#define TRON_RLENGINEX_TILETYPE_HH

#include "displayobject.hh"

struct TileTypeFlags
{
	TileTypeFlags() : render_(1), solid_(0) {};
	TileTypeFlags(bool _render, bool _solid) : render_(_render), solid_(_solid) {};

	bool render_;
	bool solid_;
};

class TileType
{
  public:
  	TileType() {};
	TileType(const DisplayObject _displayobject)
		: displayobject_(_displayobject) {};
	TileType(TileTypeFlags _tiletype_flags)
		: tiletype_flags_(_tiletype_flags) {};
	TileType(const DisplayObject _displayobject, TileTypeFlags _tiletype_flags)
		: displayobject_(_displayobject), tiletype_flags_(_tiletype_flags) {}

	~TileType() {};

	TileTypeFlags tiletype_flags_;
	// DisplayObject* displayobject_;
	DisplayObject displayobject_;
};

#endif // TRON_RLENGINEX_TILETYPE_HH
