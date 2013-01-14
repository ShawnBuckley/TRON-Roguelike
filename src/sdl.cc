// TRON-Roguelike SDL.cc

#include <assert.h>
#include <SDL/SDL.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "linux.hh"

#include "main.hh"
#include "color.hh"
#include "io.hh"
#include "sdl.hh"
#include "game.hh"
#include "map.hh"
#include "maptile.hh"
#include "tiletype.hh"
#include "mapobject.hh"
#include "player.hh"
#include "bike.hh"
#include "displayobject.hh"

void SDL::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
	screen_ = SDL_SetVideoMode(0, 0, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("Roguelike EngineX SDL", NULL);

	SDL_EnableKeyRepeat(200,60);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	Clear();

	assert(LoadTexture("font.bmp"));
	LoadFont(16, 16, 12, 12);
}

SDL::~SDL()
{
	for(int i=0; i<texture_.size(); ++i)
		SDL_FreeSurface(texture_[i]);
		
	SDL_FreeSurface(screen_);
	SDL_Quit();
}

bool SDL::LoadTexture(std::string _file)
{
	SDL_Surface *load;
	SDL_Surface *texture;
	
	load = SDL_LoadBMP("font.bmp");
	load = SDL_DisplayFormat(load);

	SDL_SetColorKey(load, SDL_SRCCOLORKEY, SDL_MapRGB(load->format, 255, 255, 255));

	for(std::vector<Color*>::iterator color = Color::colors_.begin(); color != Color::colors_.end(); ++color)
	{
		if(*color == NULL) continue;

		texture = SDL_ConvertSurface(load, load->format, load->flags);
		SDL_FillRect(texture, &texture->clip_rect, SDL_MapRGB(texture->format, (*color)->r_, (*color)->g_, (*color)->b_));
		SDL_BlitSurface(load, NULL, texture, NULL);
		SDL_SetColorKey(texture, SDL_SRCCOLORKEY, SDL_MapRGB(load->format, 0, 0, 0));

		texture_.push_back(texture);
//		SDL_FreeSurface(texture);
	}

	SDL_FreeSurface(load);

	return 1;
}

void SDL::LoadFont(int _x, int _y, int _xwidth, int _yhieght)
{
	SDL_Rect character;

	uint8_t x = 0;
	uint8_t y = 0;

	xwidth_ = _xwidth;
	yhieght_ = _yhieght;

	y_ = screen_->h/yhieght_-4;
	x_ = screen_->w/xwidth_;

	character_.reserve(_x * _y);

	for(int i=0; i<_x; ++i)
	{
		for(int j=0; j<_y; ++j)
		{
			character.x = x;
			character.y = y;
			character.h = yhieght_;
			character.w = xwidth_;

			character_.push_back(character);
			x += xwidth_;
		}
		x = 0; y += yhieght_;
	}
}

bool SDL::Input()
{
	if(realtime_)
		return PollInput();
	else
		return WaitInput();
}

bool SDL::WaitInput()
{
	SDL_Event event;

	while(SDL_WaitEvent(&event))
	{
		HandleEvent(event);
	}

	return 0;
}

bool SDL::PollInput()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		HandleEvent(event);
	}

	return 0;
}

bool SDL::HandleEvent(SDL_Event &event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN: return game.player_->Input(event.key.keysym.sym);
//		case SDL_VIDEORESIZE: DisplayResize(Event.resize.w, Event.resize.h); Game.Display->Map(); break;
		case SDL_QUIT: game.End(); return 0;
	}
}

void SDL::Clear()
{
	SDL_FillRect(screen_, &screen_->clip_rect, SDL_MapRGB(screen_->format,0,0,0));

	offset_.x = 0;
	offset_.y = 0;
}

void SDL::Refresh()
{
	SDL_Flip(screen_);
}

void SDL::Render(const std::shared_ptr<DisplayObject> _displayobject)
{
	if(_displayobject != NULL)
	{
		Print(_displayobject->sprite_ ? _displayobject->sprite_ : _displayobject->print_, _displayobject->color_);
	}
	else
	{
		Print('!', kColor[red]);
	}
}

void SDL::Print(uint8_t _print, std::shared_ptr<Color> _color)
{
	SDL_BlitSurface(texture_[_color->color_id_], &character_[_print], screen_, &offset_);
}

void SDL::AddSpace()
{
	offset_.x += xwidth_;
}

void SDL::NewLine()
{
	offset_.y += yhieght_;
	offset_.x = 0;
}

void SDL::Move(int16_t _y, int16_t _x)
{
	offset_.y = _y * yhieght_;
	offset_.x = _x * xwidth_;
}

void SDL::Map()
{
	uint32_t difference;
	uint32_t delay;
	boost::posix_time::ptime now;
	static boost::posix_time::ptime last_frame;

	Vector2<int16_t> coord;

	Clear();

	int16_t x_start = game.player_->mapobject_->maptile_->location_.x() - x_/2;
	int16_t x_limit = game.player_->mapobject_->maptile_->location_.x() + x_/2+1;
	int16_t y_start = game.player_->mapobject_->maptile_->location_.y() - y_/2;
	int16_t y_limit = game.player_->mapobject_->maptile_->location_.y() + y_/2+1;
	
	for(coord.y(y_start); coord.y() < y_limit; coord.y(coord.y()+1))
	{	for(coord.x(x_start); coord.x() < x_limit; coord.x(coord.x()+1))
	{
		if(game.map_->CoordValid(coord))
		{
			std::shared_ptr<MapTile> tile = game.map_->Tile(coord);

 			if(tile != NULL)
			{
				Render(tile->tiletype_->displayobject_);

				if(!tile->Empty())
				{
					for(std::list<MapObject*>::reverse_iterator mapobject = tile->mapobject_list_.rbegin();
						mapobject != tile-> mapobject_list_.rend(); --mapobject)
					{
						if((*mapobject) != NULL && (*mapobject)->flags_.visible_)
						{
							Render((*mapobject)->displayobject_);
						}
					}
				}
			}
		}
		AddSpace();
	} NewLine();
	}

	if(game.player_->mapobject_)
	{
		Move(game.player_->mapobject_->maptile_->location_.y(), game.player_->mapobject_->maptile_->location_.x());
	}

	Refresh();

	if(realtime_)
	{
		now = boost::posix_time::microsec_clock::universal_time();

		difference = (now - last_frame).total_microseconds();
		delay = 1000000/fps_;

		if(difference < delay)
		{
//			printf("Delay: %i\n", delay - difference);
			Delay(delay - difference);
		}
//		else
//			printf("Behind: %i\n", (signed int)(delay - difference));
	
		last_frame = boost::posix_time::microsec_clock::universal_time();
	}
}
