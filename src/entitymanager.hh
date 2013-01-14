// TRON-Roguelike EntityManager.hh

#ifndef TRON_RLENGINEX_ENTITYMANAGER_HH
#define TRON_RLENGINEX_ENTITYMANAGER_HH

#include <memory>

#include "aibike.hh"
#include "bike.hh"
#include "mapobject.hh"
#include "player.hh"

class EntityManager
{
  public:
	EntityManager() {};
	~EntityManager() {};

	std::shared_ptr<Player> AddPlayerMapobject(Colors _color);
	std::shared_ptr<Player> AddPlayerBike(Colors _color);
	std::shared_ptr<AiBike> AddAiBike(Colors _color);
};

#endif // TRON_RLENGINEX_ENTITYMANAGER_HH
