// TRON-Roguelike WorldTime.hh

#ifndef TRON_RLENGINEX_WORLDTIME_HH
#define TRON_RLENGINEX_WORLDTIME_HH

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>

#include <string>

#include <inttypes.h>

#include "gametime.hh"

namespace YAML
{
	class Emitter;
	class Node;
}

class Serializer;

class WorldTime : public GameTime
{
  public:
	WorldTime();

	void Serialize(Serializer& out);

	uint16_t Turn();

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

  private:
	WorldTime(uint64_t _tick, int _year, int _month, int _day,
		uint8_t _hour, uint8_t _minute, uint8_t _second);

  friend class Serializer;
};

#endif // TRON_RLENGINEX_WORLDTIME_HH
