// TRON-Roguelike LightWall.cc

#include "lightwall.hh"
#include "bike.hh"
#include "engine/maptile.hh"

LightWall::LightWall(DisplayObject* _displayobject, MapLocation _location, uint64_t _time_dropped, Bike *_bike)
{
	displayobject_ = _displayobject;
	stats_ = MapObjectStats(453592, 1000);
	flags_ = MapObjectFlags(1, 1, 1, 1);
	time_dropped_ = _time_dropped;
	bike_ = _bike;
	Rez(_location);
};

void LightWall::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << YAML::Key << "type";
	out << YAML::Value << "LightWall";
	out << YAML::Key << "id";
	out << YAML::Value << id_;
	out << YAML::Key << "linked";
	out << YAML::Value << linked_;
	out << YAML::Key << "displayobject";
	out << YAML::Value << (int)displayobject_->id_;
	out << YAML::Key << "stats";
	stats_.Serialize(out);
	out << YAML::Key << "flags";
	flags_.Serialize(out);
	out << YAML::Key << "location";
	location_.Serialize(out);
	out << YAML::Key << "bike";
	out << YAML::Key << bike_->id_;
	out << YAML::Key << "time_dropped";
	out << YAML::Value << time_dropped_;
	out << YAML::EndMap;
}