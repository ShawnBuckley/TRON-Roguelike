// TRON-Roguelike AiBike.hh

#ifndef TRON_RLENGINEX_AIBIKE_HH
#define TRON_RLENGINEX_AIBIKE_HH

#include <inttypes.h>

#include "engine/math/vector2.hh"
#include "engine/controlobject.hh"

#include "bike.hh"

namespace YAML
{
	class Emitter;
}

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
	AiBike(Bike* _bike) : ai_state_(AI_DEFAULT), ai_skill_(100) { mapobject_ = _bike; };

	virtual void Serialize(YAML::Emitter& out);

	void Think();
	ControlObjectMove Move();

  private:
	bool Default();
	bool Tunnel();
	
	bool CheckMapObjects(MapTile* _tile);
	bool CheckDirection();
	bool CheckTile(MapTile* _tile);
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
