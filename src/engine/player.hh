// TRON-Roguelike Player.hh

#ifndef TRON_RLENGINEX_PLAYER_HH
#define TRON_RLENGINEX_PLAYER_HH

#include "controlobject.hh"

#include "mapobject.hh"
#include "timeobject.hh"

class Player : public ControlObject
{
  public:
	void Think(uint16_t _remaining_time);
	ControlObjectMove Move();

  private:
	bool GameControls(char _ch);
	bool PlayerControls(char _ch);
};

#endif // TRON_RLENGINEX_PLAYER_HH
