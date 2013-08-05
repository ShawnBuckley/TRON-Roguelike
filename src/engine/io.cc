// TRON-Roguelike

#include <yaml-cpp/yaml.h>

#include "io.hh"
#include "mapobject.hh"

void IO::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << "realtime" << realtime_;
	out << "fps" << fps_;
	out << "x" << (int)x_;
	out << "y" << (int)y_;
	out << "camera_mapobject";
	if(camera_mapobject_)
		out << camera_mapobject_->id_;
	else
		out << -1;	
	out << "camera_location" << YAML::Flow << YAML::BeginSeq;
	out << (int)camera_location_.x << (int)camera_location_.y << YAML::EndSeq;
	out << "old_color" << (int)old_color_;
	// out << "viewport" << YAML::Flow << YAML::BeginSeq;
	// out << viewport_.Vertex(0).x;
	// out << viewport_.Vertex(0).y;
	// out << viewport_.Width();
	// out << viewport_.Height();
	// out << YAML::EndSeq;
	out << "keystrokes" << YAML::Flow << YAML::BeginSeq;
	for(char key : keystrokes_)
		out << key;
	out << YAML::EndSeq;
	out << YAML::EndMap;
}