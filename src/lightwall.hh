// TRON-Roguelike LightWall.hh

#ifndef TRON_RLENGINEX_LIGHTWALL_HH
#define TRON_RLENGINEX_LIGHTWALL_HH

#include "engine/mapobject.hh"
#include "engine/displayobject.hh"

class LightWall : public MapObject
{
  public:
	LightWall() : bike_(NULL) {};
	LightWall(DisplayObject _displayobject, MapLocation<int16_t> _location, uint64_t _time_dropped, Bike *_bike);

	bool CheckBump(MapObject *_mapobject) { printf("%p mapobject double dispatch call - bumped\n", this); return _mapobject->DoubleDispatch_CheckBump(this); };
	bool DoubleDispatch_CheckBump(MapObject *_mapobject) { printf("%p DD LW bumped MO\n",this); return 1; };
	bool DoubleDispatch_CheckBump(Bike *_bike) { printf("%p DD LW bumped BK\n",this); return 1; };
	bool DoubleDispatch_CheckBump(LightWall *_lightwall) { printf("%p DD LW bumped LW\n",this); return 1; };

	bool CheckBumped(MapObject *_mapobject) { printf("bike double dispatch call\n"); return _mapobject->DoubleDispatch_CheckBumped(this); };
	bool DoubleDispatch_CheckBumped(MapObject *_mapobject) { printf("%p DD LW check MO\n",this); return 0; };
	bool DoubleDispatch_CheckBumped(Bike *_bike) { printf("%p DD LW check BK\n",this); return 1; };
	bool DoubleDispatch_CheckBumped(LightWall *_lightwall) { printf("%p DD LW check LW\n",this); return 1; };
	
	Bike *bike_;
	uint64_t time_dropped_;
};

#endif // TRON_RLENGINEX_LIGHTWALL_HH
