// Roguelike EngineX xColor.hh

#ifndef ENGINE_XCOLOR_HH
#define ENGINE_XCOLOR_HH

#include <cstdint>
#include <cstdio>
#include <memory>
#include <vector>

#include "object.hh"

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

extern std::shared_ptr<Color> kBlack;
extern std::shared_ptr<Color> kRed;
extern std::shared_ptr<Color> kGreen;
extern std::shared_ptr<Color> kYellow;
extern std::shared_ptr<Color> kBlue;
extern std::shared_ptr<Color> kMagenta;
extern std::shared_ptr<Color> kDarkBlue;
extern std::shared_ptr<Color> kWhite;

#endif
