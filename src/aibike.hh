// TRONLIKE xAiBike.hh

#ifndef TRONLIKE_XAIBIKE_HH
#define TRONLIKE_XAIBIKE_HH

#include <inttypes.h>

#include "bike.hh"
#include "coord2.hh"
#include "controlobject.hh"

class MapObject;
class MapTile;

enum AiState
{
	AI_DEFAULT = 0,
	AI_WALLHUG,
	AI_TUNNEL,
	AI_DEFENSE,
	AI_OFFENSE,
	AI_DISPERSE,
};

class AiBike : public ControlObject
{
  public:
	AiBike();
	AiBike(std::shared_ptr<AiBike> _this, std::shared_ptr<Bike> _bike);

	void Save(std::stringstream &_save);
	void Load() {};

	void Think();

  private:
	void Default();
	void Tunnel();
	
	bool CheckMapObjects(std::shared_ptr<MapTile> _tile);
	void CheckDirection();
	bool CheckTile(std::shared_ptr<MapTile> _tile);
	bool CheckTunnel();
	void ChangeDirection(Coord2<int8_t> _vector);

	void AttackEnemy(MapObject *_mapobject);
	MapObject* TargetClosestEntity();


	AiState ai_state_;
	uint8_t ai_skill_;
	
	uint8_t tunnel_distance;

	Coord2<int8_t> wall_hug_;
};

#endif
