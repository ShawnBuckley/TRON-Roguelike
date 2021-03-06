// TRON-Roguelike Player.hh

#ifndef TRON_RLENGINEX_PLAYER_HH
#define TRON_RLENGINEX_PLAYER_HH

#include <unordered_map>
#include <string>

#include "controlobject.hh"

#include "mapobject.hh"
#include "timeobject.hh"

namespace YAML
{
	class Emitter;
	class Node;
}

class Game;
class Player;
class Serializer;

typedef void(Game::*GameMethod)(void);

struct PlayerControl
{
	PlayerControl() : player_(NULL), game_control_(0) {};
	PlayerControl(Player* _player, GameMethod _callback) : player_(_player), game_control_(1), callback_(_callback) {};
	PlayerControl(Player* _player, ControlObjectMoveType _move_type, Vector2<int16_t> _vector) :
		player_(_player), move_type_(_move_type), game_control_(0), vector_(_vector) {};

	Player* player_;
	bool game_control_;
	ControlObjectMoveType move_type_;
	Vector2<int16_t> vector_;
	GameMethod callback_;
};

class Player : public ControlObject
{
  public:
	static std::unordered_map<char, PlayerControl> mapped_controls_;

  	Player(MapObject* _mapobject) { mapobject_ = _mapobject; };

	void Serialize(Serializer& out);

  	void LoadControls(std::string _filename);
  	bool Controls(char _ch);

	void Think() {};
	void Controls();
	ControlObjectMove Move();

  private:
	Player(uint16_t _id, MapObject* _mapobject, std::list<ControlObjectMove> _moves)
	{
		id_ = _id;
		mapobject_ = _mapobject;
		moves_ = _moves;
	}

  friend class Serializer;
};

#endif // TRON_RLENGINEX_PLAYER_HH
