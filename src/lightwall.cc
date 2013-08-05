// TRON-Roguelike LightWall.cc

#include "lightwall.hh"
#include "bike.hh"

#include "engine/game.hh"
#include "engine/maptile.hh"

LightWall::LightWall(DisplayObject* _displayobject, uint64_t _time_dropped, Bike *_bike)
{
	displayobject_ = _displayobject;
	stats_ = MapObjectStats(453592, 1000);
	flags_ = MapObjectFlags(1, 1, 1, 1);
	time_dropped_ = _time_dropped;
	bike_ = _bike;
};

LightWall::LightWall(const YAML::Node& in)
{
	id_ = in["id"].as<int>();
	// linked_ = in["linked"].as<bool>();
	linked_ = 1;
	displayobject_ = game().GetDisplayObject(in["displayobject"].as<int>());
	stats_ = MapObjectStats(in["stats"]);
	flags_ = MapObjectFlags(in["flags"]);
	location_ = MapLocation(in["location"]);
	bike_ = (Bike*)game().GetMapObject(in["bike"].as<int>());
	time_dropped_ = in["time_dropped"].as<int>();
}

void LightWall::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << "type" << "LightWall";
	out << "id" << id_;
	out << "linked" << linked_;
	out << "displayobject" << (int)displayobject_->id_;
	out << "stats"; stats_.Serialize(out);
	out << "flags"; flags_.Serialize(out);
	out << "location"; location_.Serialize(out);
	out << "bike" << bike_->id_;
	out << "time_dropped" << time_dropped_;
	out << YAML::EndMap;
}