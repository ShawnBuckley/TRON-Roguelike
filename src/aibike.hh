// TRON-Roguelike AiBike.hh

#ifndef TRON_RLENGINEX_AIBIKE_HH
#define TRON_RLENGINEX_AIBIKE_HH

#include <inttypes.h>

#include "math/vector2.hh"

#include "bike.hh"
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

	void Think(uint16_t _remaining_time);
	ControlObjectMove Move();

  private:
	void Default();
	void Tunnel();
	
	bool CheckMapObjects(std::shared_ptr<MapTile> _tile);
	void CheckDirection();
	bool CheckTile(std::shared_ptr<MapTile> _tile);
	bool CheckTunnel();
	void ChangeDirection(Vector2<int16_t> _vector);

	void AttackEnemy(MapObject *_mapobject);
	MapObject* TargetClosestEntity();

	bool think_;
	AiState ai_state_;
	uint8_t ai_skill_;
	
	uint8_t tunnel_distance;

	// Vector2<int8_t> wall_hug_;

	Vector2<int16_t> next_move_;
};

#endif // TRON_RLENGINEX_AIBIKE_HH
