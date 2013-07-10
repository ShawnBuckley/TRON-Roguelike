// TRON-Roguelike EntityManager.hh

#ifndef TRON_RLENGINEX_ENTITYMANAGER_HH
#define TRON_RLENGINEX_ENTITYMANAGER_HH

#include <memory>

#include "engine/mapobject.hh"
#include "engine/player.hh"

#include "aibike.hh"
#include "bike.hh"

class EntityManager
{
  public:
	EntityManager() {};
	~EntityManager() {};

	static std::shared_ptr<Player> AddPlayerMapobject(Colors _color);
	static std::shared_ptr<Player> AddPlayerBike(Colors _color);
	static std::shared_ptr<AiBike> AddAiBike(Colors _color);
};

#endif // TRON_RLENGINEX_ENTITYMANAGER_HH
