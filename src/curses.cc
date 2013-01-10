// TRON-Roguelike Curses.cc

#include <curses.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "linux.hh"

#include "main.hh"
#include "color.hh"
#include "curses.hh"
#include "game.hh"
#include "map.hh"
#include "maptile.hh"
#include "tiletype.hh"
#include "mapobject.hh"
#include "player.hh"
#include "bike.hh"
#include "displayobject.hh"

void Curses::Init()
{
	window_ = initscr();
	noecho();
	nodelay(window_, 1);
	getmaxyx(window_, y_, x_);
	
	y_ -= 2;
	x_ -= 2;
	
//	color_ = 0;
	LoadColors();
}

Curses::~Curses()
{
	endwin();
}

void Curses::LoadColors()
{
	color_ = start_color();

	if(color_)
	{
		start_color();

		for(std::vector<Color*>::iterator color = Color::colors_.begin(); color != Color::colors_.end(); ++color)
		{
			if(*color == NULL) continue;

			init_color((*color)->color_id_, (int)(*color)->r_ * Color::curses_multiplier_, (int)(*color)->g_ * Color::curses_multiplier_, (int)(*color)->b_ * Color::curses_multiplier_);
			init_pair((*color)->color_id_, (*color)->color_id_, 0);
		}
	}
}

bool Curses::Input()
{
	return game.player_->Input(getch());
}

void Curses::SetRealtime(bool _realtime)
{
	nodelay(window_, _realtime);
}

void Curses::Clear()
{
	clear();
}

void Curses::Refresh()
{
	refresh();
}

void Curses::SetColor(std::shared_ptr<Color> _color)
{
	if(_color != NULL)
	{
		attron(_color->color_id_);
	}
}

void Curses::EndColor(std::shared_ptr<Color> _color)
{
	if(_color != NULL)
	{
		attroff(_color->color_id_);
	}
}

void Curses::Render(const DisplayObject *_displayobject)
{
	if(_displayobject)
	{
		Print(_displayobject->print_, _displayobject->color_);
	}
	else
	{
		addch('!');
	}
}

void Curses::Print(uint8_t _print, std::shared_ptr<Color> _color)
{
	if(color_) SetColor(_color);
	addch(_print);
	if(color_) EndColor(_color);
}

void Curses::AddSpace()
{
	printw(" ");
}

void Curses::NewLine()
{
	printw("\n");
}

void Curses::Move(uint8_t _y, uint8_t _x)
{
	move(_y, _x);
}

void Curses::Map()
{
	uint32_t difference;
	uint32_t delay;
	boost::posix_time::ptime now;
	static boost::posix_time::ptime last_frame;

	Coord2<uint8_t> coord;

	Clear();

	for(coord.y=0; coord.y<game.map_->y_; ++coord.y) { for(coord.x=0; coord.x<game.map_->x_; ++coord.x)
	{
		if(game.map_->CoordValid(coord) && game.map_->Tile(coord) == NULL)
			AddSpace();
		
		if(!game.map_->Tile(coord)->Empty())
		{
			Render(game.map_->Tile(coord)->VisibleMapObject().get());
		}
		else
		{
			Render(game.map_->Tile(coord)->tiletype_->displayobject_.get());
		}
	} NewLine(); }

	if(game.player_->mapobject_)
	{
		Move(game.player_->mapobject_->maptile_->location_.y, game.player_->mapobject_->maptile_->location_.x);
	}

	Refresh();

	now = boost::posix_time::microsec_clock::universal_time();

	difference = (now - last_frame).total_microseconds();
	delay = 1000000/fps_;

	if(difference < delay)
		Delay(delay - difference);
	
	last_frame = boost::posix_time::microsec_clock::universal_time();
}
