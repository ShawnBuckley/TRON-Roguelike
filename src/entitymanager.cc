// TRON-Roguelike EntityManager.cc

#include "color.hh"
#include "entitymanager.hh"

std::shared_ptr<Player> EntityManager::AddPlayerMapobject(Colors _color)
{
	std::shared_ptr<Player> player(new Player);
	player->mapobject_ = std::move(std::shared_ptr<MapObject>(new MapObject));
	player->mapobject_->displayobject_ = std::move(std::shared_ptr<DisplayObject>(new DisplayObject('@', '@', kColor[_color])));
	player->mapobject_->flags_ = MapObjectFlags(1, 1, 1, 1);

	player->mapobject_->timeobject_ = std::move(std::shared_ptr<TimeObject>(new TimeObject(6000)));

	return player;
}

std::shared_ptr<Player> EntityManager::AddPlayerBike(Colors _color)
{
	std::shared_ptr<Player> player_bike(new Player);
	player_bike->mapobject_ = std::move(std::shared_ptr<Bike>(new Bike(kColor[_color])));

	player_bike->mapobject_->displayobject_ = std::move(std::shared_ptr<DisplayObject>(new DisplayObject('@', 254, kColor[_color])));
	player_bike->mapobject_->flags_ = MapObjectFlags(1, 1, 1, 1);

	player_bike->mapobject_->timeobject_ = std::move(std::shared_ptr<TimeObject>(new TimeObject(1000)));
	player_bike->mapobject_->timeobject_->mapobject_= player_bike->mapobject_;
	player_bike->mapobject_->timeobject_->controlobject_ = player_bike;

	return player_bike;
}

std::shared_ptr<AiBike> EntityManager::AddAiBike(Colors _color)
{
	std::shared_ptr<AiBike> ai_bike(new AiBike);
	ai_bike->mapobject_ = std::move(std::shared_ptr<Bike>(new Bike(kColor[_color])));

	ai_bike->mapobject_->displayobject_ = std::move(std::shared_ptr<DisplayObject>(new DisplayObject('B', 254, kColor[_color])));
	ai_bike->mapobject_->flags_ = MapObjectFlags(1, 1, 1, 1);

	ai_bike->mapobject_->timeobject_ = std::move(std::shared_ptr<TimeObject>(new TimeObject(1000)));
	ai_bike->mapobject_->timeobject_->mapobject_= ai_bike->mapobject_;
	ai_bike->mapobject_->timeobject_->controlobject_ = ai_bike;

	return ai_bike;
}
