// RLengineX Player.hh

#ifndef RLENGINEX_PLAYER_HH
#define RLENGINEX_PLAYER_HH

#include "controlobject.hh"

class Player : public ControlObject
{
  public:
  	void Save(std::stringstream &_save);
  	void Load() {};

	bool Input(char _ch);
};

#endif // RLENGINEX_PLAYER_HH
