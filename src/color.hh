// TRON-Roguelike Color.hh

#ifndef TRON_RLENGINEX_COLOR_HH
#define TRON_RLENGINEX_COLOR_HH

#include <cstdint>
#include <cstdio>
#include <memory>
#include <vector>

#include "object.hh"

enum Colors
{
	black = 0,
	red,
	green,
	yellow,
	blue,
	magenta,
	dark_blue,
	white
};

struct Color : public Object
{
	Color(uint8_t _r, uint8_t _g, uint8_t _b) : r_(_r), g_(_g), b_(_b) { color_id_ = color_count_++; Color::colors_.push_back(this); };
//	~Color() { --color_count_; };

	void Save(std::stringstream &_save);
	void Load();

	static float curses_multiplier_;
	static uint8_t color_count_;
	static std::vector<Color*> colors_;

	uint8_t color_id_;

	uint8_t r_;
	uint8_t g_;
	uint8_t b_;
};

extern std::vector<std::shared_ptr<Color> > kColor;

#endif // TRON_RLENGINEX_COLOR_HH
