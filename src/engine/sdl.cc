// TRON-Roguelike SDL.cc

#include <assert.h>
#include <SDL/SDL.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "linux.hh"

#include "io.hh"
#include "sdl.hh"
#include "game.hh"
#include "map.hh"
#include "maptile.hh"
#include "tiletype.hh"
#include "mapobject.hh"
#include "player.hh"
#include "displayobject.hh"
#include "sector.hh"

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
	
	viewport_ = AxisAligned_Rectangle2<int16_t>(Vector2<int16_t>(0,0), screen_->w/xwidth_, screen_->h/yheight_);
	
	printf("viewport: (%i %i) %i %i\n", viewport_.Vertex(0).x, viewport_.Vertex(0).y, viewport_.Width(), viewport_.Height());
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

	for(auto color = colors_.begin(); color != colors_.end(); ++color)
	{
		// if(*color == NULL) continue;

		texture = SDL_ConvertSurface(load, load->format, load->flags);
		SDL_FillRect(texture, &texture->clip_rect, SDL_MapRGB(texture->format, (*color).r_, (*color).g_, (*color).b_));
		SDL_BlitSurface(load, NULL, texture, NULL);
		SDL_SetColorKey(texture, SDL_SRCCOLORKEY, SDL_MapRGB(load->format, 0, 0, 0));

		texture_.push_back(texture);
//		SDL_FreeSurface(texture);
	}

	SDL_FreeSurface(load);

	return 1;
}

void SDL::LoadFont(int _x, int _y, int _xwidth, int _yheight)
{
	SDL_Rect character;

	uint8_t x = 0;
	uint8_t y = 0;

	xwidth_ = _xwidth;
	yheight_ = _yheight;

	y_ = screen_->h/yheight_-4;
	x_ = screen_->w/xwidth_;

	character_.reserve(_x * _y);

	for(int i=0; i<_x; ++i)
	{
		for(int j=0; j<_y; ++j)
		{
			character.x = x;
			character.y = y;
			character.h = yheight_;
			character.w = xwidth_;

			character_.push_back(character);
			x += xwidth_;
		}
		x = 0; y += yheight_;
	}
}

uint32_t SDL::Input()
{
	SDL_Event event;

	while(realtime_ ? SDL_PollEvent(&event) : SDL_WaitEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
			{
				keystrokes_.push_back(event.key.keysym.sym); return 0;
			}; break;
			//return game()->player_->Input(event.key.keysym.sym);
//			case SDL_VIDEORESIZE: DisplayResize(Event.resize.w, Event.resize.h); game()->Display->Map(); break;
			case SDL_QUIT: game()->End(); return 0;
		}
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

void SDL::Render(const DisplayObject& _displayobject)
{
	// if(_displayobject != NULL)
	// {
		Print(_displayobject.sprite_ ? _displayobject.sprite_ : _displayobject.print_, _displayobject.color_);
	// }
	// else
	// {
	// 	Print('!', red);
	// }
}

void SDL::Print(uint8_t _print, uint8_t _color)
{
	SDL_BlitSurface(texture_[_color], &character_[_print], screen_, &offset_);
}

void SDL::AddSpace()
{
	offset_.x += xwidth_;
}

void SDL::NewLine()
{
	offset_.y += yheight_;
	offset_.x = 0;
}

void SDL::Move(int16_t _y, int16_t _x)
{
	offset_.y = _y * yheight_;
	offset_.x = _x * xwidth_;
}

void SDL::Map()
{
	uint32_t difference;
	uint32_t delay;
	boost::posix_time::ptime now;
	static boost::posix_time::ptime last_frame;

	Vector2<int16_t> coord;
	Vector2<int16_t> camera;

	if(camera_mapobject_)
		camera = camera_mapobject_->location_.rectangle_.Vertex(0);
	else
		camera = camera_location_;

	Clear();

	// viewport_.Origin(Vector2<int16_t>(
	// 	game()->player_->mapobject_->location_.maptile_[0][0]->location_.x - x_/2,
	// 	game()->player_->mapobject_->location_.maptile_[0][0]->location_.y - y_/2
	// ));

	viewport_.Origin(Vector2<int16_t>(
		camera.x - x_/2,
		camera.y - y_/2
	));

//	printf("viewport %i %i\n", viewport_.Vertex(0).x, viewport_.Vertex(0).y);
/*
	for(auto sector = game()->map_->sector_.begin();
		sector != game()->map_->sector_.end(); ++sector)
	{
		if((*sector) != NULL)
		{
			Vector2<int16_t> coord;
			std::vector<Vector2<int16_t> > result = viewport_.Intersect((*sector)->rectangle_);
			
			std::vector<AxisAligned_Rectangle2<int16_t> > clip_rect = AxisAligned_Rectangle2<int16_t>::Construct(result);

			if(!clip_rect.size())
				continue;

			printf("%p (%i %i) %i %i\n",(*sector).get(), clip_rect[0].Vertex(0).x, clip_rect[0].Vertex(0).y, clip_rect[0].Width(), clip_rect[0].Height());

			Move(clip_rect[0].Vertex(0).y, clip_rect[0].Vertex(0).x);

			for(coord.y(clip_rect[0].Vertex(0).y); coord.y < clip_rect[0].Height(); coord.y(coord.y+1))
			{	for(coord.x(clip_rect[0].Vertex(0).x); coord.x < clip_rect[0].Width(); coord.x(coord.x+1))
			{
				std::shared_ptr<MapTile> tile = (*sector)->Tile(coord);

//	 			if(tile != NULL)
//					continue;

//				printf("%i %i\n", coord.x, coord.y);

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

				AddSpace();
			} NewLine();
			}
		}
	}
/*
	for(auto sector = game()->map_->sector_.begin();
		sector != game()->map_->sector_.end(); ++sector)
	{
		Vector2<int16_t> coord;
	
		Move(
	
		for(coord.y((*sector)->rectangle_.Vertex(0).y); coord.y < (*sector)->rectangle_.Height(); coord.y(coord.y+1))
		{	for(coord.x((*sector)->rectangle_.Vertex(0).x); coord.x < (*sector)->rectangle_.Width(); coord.x(coord.x+1))
		{
			if(game()->map_->CoordValid(coord))
			{
				std::shared_ptr<MapTile> tile = game()->map_->Tile(coord);

	 			if(tile != NULL)
				{
					Render(tile->tiletype_->displayobject_);

					if(!tile->Empty())
					{
						for(auto mapobject = tile->mapobject_list_.rbegin();
							mapobject != tile-> mapobject_list_.rend(); ++mapobject)
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
	}
/*/
	for(coord.y = viewport_.Vertex(0).y; coord.y < viewport_.Height(); coord.y += 1)
	{	for(coord.x = viewport_.Vertex(0).x; coord.x < viewport_.Width(); coord.x += 1)
	{
		if(game()->map_->CoordValid(coord))
		{
			MapTile* tile = game()->map_->Tile(coord);

 			if(tile != NULL)
			{
				Render(tile->tiletype_->displayobject_);

				if(!tile->Empty())
				{
					for(std::list<MapObject*>::reverse_iterator mapobject = tile->mapobject_list_.rbegin();
						mapobject != tile-> mapobject_list_.rend(); ++mapobject)
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

	Move(camera.x, camera.y);


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
