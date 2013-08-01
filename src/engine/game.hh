// TRON-Roguelike Game.hh

#ifndef TRON_RLENGINEX_GAME_HH
#define TRON_RLENGINEX_GAME_HH

#include <memory>
#include <list>

#include <boost/archive/basic_archive.hpp>

#include "player.hh"

#include "io.hh"
#include "map.hh"
#include "worldtime.hh"

class Game
{
  public:
	Game();
	virtual ~Game() {};

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{

	};

	virtual void Start();
	void Run();
	void End();

	void Pause();

	void Save();
	void Load();

	void SetRealtime(bool _realtime);

	DisplayObject* AddDisplayObject(const DisplayObject _displayobject);
	TileType* AddTileType(const TileType _tiletype);
	void AddMapobject(MapObject* _mapobject);
	void AddControlObject(ControlObject* _controlobject);
	Player* AddPlayerMapobject(uint8_t _color);

	bool run_;
	bool paused_;
	bool realtime_;

	uint32_t speed_;


	Player* player_;

	std::unique_ptr<IO> io_;
	std::unique_ptr<Map> map_;
	std::unique_ptr<WorldTime> worldtime_;

	std::vector<std::unique_ptr<DisplayObject>> displayobjects_;
	std::list<uint16_t> displayobject_open_id_;

	std::vector<std::unique_ptr<TileType>> tiletypes_;
	std::list<uint16_t> tiletype_open_id_;

	std::vector<std::unique_ptr<MapObject>> mapobjects_;
	std::list<uint16_t> mapobject_open_id_;

	std::vector<std::unique_ptr<ControlObject>> entities_;
	std::list<uint16_t> entity_open_id_;

	// std::vector<std::unique_ptr<ControlObject>> controlobjects_;
};

Game* game();

#endif // TRON_RLENGINEX_GAME_HH
