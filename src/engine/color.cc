// TRON-Roguelike Color.cc

#include "color.hh"

float Color::curses_multiplier_ = 1000/255;
uint8_t Color::color_count_ = 0;
std::vector<Color*> Color::colors_;
std::vector<std::shared_ptr<Color>> kColor;