// TRON-Roguelike Player.hh

#ifndef TRON_RLENGINEX_PLAYER_HH
#define TRON_RLENGINEX_PLAYER_HH

#include <unordered_map>
#include <string>

#include "controlobject.hh"

#include "mapobject.hh"
#include "timeobject.hh"

class Game;

typedef void(Game::*GameMethod)(void);

struct PlayerControl
{
	PlayerControl() {};
	PlayerControl(GameMethod _callback) : game_control_(1), callback_(_callback) {};
	PlayerControl(ControlObjectMoveType _move_type, Vector2<int16_t> _vector) :
		move_type_(_move_type), game_control_(0), vector_(_vector) {};

	bool game_control_;
	ControlObjectMoveType move_type_;
	Vector2<int16_t> vector_;
	GameMethod callback_;
};

class Player : public ControlObject
{
  public:
  	void LoadControls();//(std::string _filename);
  	bool Controls(char _ch);

	void Think(uint16_t _remaining_time);
	ControlObjectMove Move();

  private:
	std::unordered_map<char, PlayerControl> controls_;

};

#endif // TRON_RLENGINEX_PLAYER_HH
