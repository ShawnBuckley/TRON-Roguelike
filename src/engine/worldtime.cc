// TRON-Roguelike WorldTime.cc

#include <stdlib.h>
#include <stdio.h>

#include <string>

#include <yaml-cpp/yaml.h>

#include "worldtime.hh"

WorldTime::WorldTime()
{
	date_ = boost::gregorian::date(1982, 7, 9);

	hour_ = 0;
	minute_ = 0;
	second_ = 0;
}

WorldTime::WorldTime(const YAML::Node& in)
{
	tick_ = in["tick"].as<uint64_t>();
	date_ = boost::gregorian::date(in["year"].as<int>(), in["month"].as<int>(), in["day"].as<int>());
	hour_ = in["hour"].as<int>();
	minute_ = in["minute"].as<int>();
	second_ = in["second"].as<int>();
}

void WorldTime::Serialize(YAML::Emitter& out)
{
	out << YAML::BeginMap;
	out << "type" << "WorldTime";
	out << "tick" << tick_;
	out << "year" << (int)date_.year();
	out << "month" << (int)date_.month();
	out << "day"<< (int)date_.day();
	out << "hour" << (int)hour_;
	out << "minute" << (int)minute_;
	out << "second" << (int)second_;
	out << YAML::EndMap;
}

uint16_t WorldTime::Turn()
{
	UpdateSeconds(GameTime::Turn()/1000);

//	std::cout << date_ << " " << (int)hour_ << ":" << (int)minute_ << ":" << (int)second_ << std::endl;
}

void WorldTime::UpdateSeconds(uint16_t _seconds)
{
	uint16_t sum = second_ + _seconds;

	if(sum/60) UpdateMinutes(sum/60);
	
	second_ = sum % 60;
}

void WorldTime::UpdateMinutes(uint16_t _minutes)
{
	uint16_t sum = minute_ + _minutes;

	if(sum/60) UpdateHours(sum/60);
	
	minute_ = sum % 60;
}

void WorldTime::UpdateHours(uint16_t _hours)
{
	uint16_t sum = hour_ + _hours;

	if(sum/24) UpdateDays(sum/24);
	
	hour_ = sum % 24;
}

void WorldTime::UpdateDays(uint16_t _days)
{
	boost::gregorian::date_duration dd(_days);

	date_ = date_ + dd;
}

void WorldTime::UpdateMonths(uint16_t _months)
{
	boost::gregorian::months months(_months);

	date_ = date_ + months;
}

void WorldTime::UpdateYears(uint16_t _years)
{
	boost::gregorian::years years(_years);

	date_ = date_ + years;
}


