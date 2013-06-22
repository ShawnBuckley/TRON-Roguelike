// TRON-Roguelike Game.hh

#ifndef TRON_RLENGINEX_GAME_HH
#define TRON_RLENGINEX_GAME_HH

#include <memory>

#include "entitymanager.hh"
#include "player.hh"

#include "io.hh"
#include "map.hh"
#include "worldtime.hh"

struct GameFlags
{
	GameFlags() : run_(1), paused_(0), realtime_(0) {};

	bool run_;
	bool paused_;
	bool realtime_;
};

class Game
{
  public:
	Game();

	void Start();
	void Run();
	void End();

	void Pause();

	void Save();
	void Load();

	void SetRealtime(bool _realtime);

	uint32_t speed_;
	EntityManager entity_manager_;
	GameFlags game_flags_;

	std::unique_ptr<IO> io_;
	std::unique_ptr<Map> map_;
	std::unique_ptr<WorldTime> worldtime_;

	std::vector<std::shared_ptr<ControlObject> > entities_;

	std::shared_ptr<Player> player_;
};

#endif // TRON_RLENGINEX_GAME_HH
