// TRON-Roguelike AiBike.hh

#ifndef TRON_RLENGINEX_AIBIKE_HH
#define TRON_RLENGINEX_AIBIKE_HH

#include <inttypes.h>

#include "engine/math/vector2.hh"
#include "engine/controlobject.hh"

#include "bike.hh"

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

	void Serialize(Serializer& out);

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
	
	uint8_t tunnel_distance_;

	// Vector2<int8_t> wall_hug_;

	Vector2<int16_t> next_move_;

  private:
	AiBike(uint16_t _id, bool _think, AiState _ai_state, uint8_t _ai_skill,
		uint8_t _tunnel_distance, Vector2<int16_t> _next_move,
		MapObject* _mapobject, std::list<ControlObjectMove> _moves) : 
			think_(_think), ai_state_(_ai_state), ai_skill_(_ai_skill),
			tunnel_distance_(_tunnel_distance)
	{
		id_ = _id;
		mapobject_ = _mapobject;
		moves_ = _moves;
	}

  friend class TronSerializer;
};

#endif // TRON_RLENGINEX_AIBIKE_HH
