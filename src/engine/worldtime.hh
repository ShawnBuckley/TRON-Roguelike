// TRON-Roguelike WorldTime.hh

#ifndef TRON_RLENGINEX_WORLDTIME_HH
#define TRON_RLENGINEX_WORLDTIME_HH

#include <boost/date_time/gregorian/gregorian.hpp>

#include <string>

#include <inttypes.h>

#include "gametime.hh"

class WorldTime : GameTime
{
  public:
	WorldTime();

  	void Save(std::stringstream &_save);
  	void Load() {};

	void WorldTurn(uint32_t _time);
	uint64_t Tick() { return tick_; };

	void UpdateSeconds(uint16_t _seconds);
	void UpdateMinutes(uint16_t _minutes);
	void UpdateHours(uint16_t _hours);
	void UpdateDays(uint16_t _days);
	void UpdateMonths(uint16_t _months);
	void UpdateYears(uint16_t _years);

	boost::gregorian::date date_;
	uint8_t hour_;
	uint8_t minute_;
	uint8_t second_;
};

#endif // TRON_RLENGINEX_WORLDTIME_HH
