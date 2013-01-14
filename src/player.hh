// TRON-Roguelike Player.hh

#ifndef TRON_RLENGINEX_PLAYER_HH
#define TRON_RLENGINEX_PLAYER_HH

#include "controlobject.hh"

class Player : public ControlObject
{
  public:
  	void Save(std::stringstream &_save);
  	void Load() {};

	bool Input(char _ch);
};

#endif // TRON_RLENGINEX_PLAYER_HH
