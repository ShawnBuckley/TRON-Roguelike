// Roguelike EngineX Color.cc

#include "color.hh"

float Color::curses_multiplier_ = 1000/255;
uint8_t Color::color_count_ = 0;
std::vector<Color*> Color::colors_;

std::shared_ptr<Color> kBlack = std::shared_ptr<Color>(new Color(0,0,0));
std::shared_ptr<Color> kRed = std::shared_ptr<Color>(new Color(255,0,0));
std::shared_ptr<Color> kGreen = std::shared_ptr<Color>(new Color(0,255,0));
std::shared_ptr<Color> kYellow = std::shared_ptr<Color>(new Color(255,255,0));
std::shared_ptr<Color> kBlue = std::shared_ptr<Color>(new Color(0,0,255));
std::shared_ptr<Color> kMagenta = std::shared_ptr<Color>(new Color(255,0,255));
std::shared_ptr<Color> kDarkBlue = std::shared_ptr<Color>(new Color(0,0,64));
std::shared_ptr<Color> kWhite = std::shared_ptr<Color>(new Color(255,255,255));

void Color::Save(std::stringstream &_save)
{
	_save << "color" << " "
		<< "a" << " "
		<< (unsigned int)id_ << " "
		<< (unsigned int)color_id_ << " "
		<< (unsigned int)r_ << " "
		<< (unsigned int)g_ << " "
		<< (unsigned int)b_
		<< std::endl;
}

void Color::Load()
{
}
