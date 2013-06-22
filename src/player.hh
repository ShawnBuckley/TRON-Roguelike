// TRON-Roguelike Player.hh

#ifndef TRON_RLENGINEX_PLAYER_HH
#define TRON_RLENGINEX_PLAYER_HH

#include "controlobject.hh"

class Player : public ControlObject
{
  public:
  	void Save(std::stringstream &_save);
  	void Load() {};

	uint32_t Input(char _ch);

  private:
	bool GameControls(char _ch);
	uint32_t PlayerControls(char _ch);
};

#endif // TRON_RLENGINEX_PLAYER_HH
