// TRON-Roguelike GL.cc

#include <iostream>
#include <fstream>

#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include <png.h>

#include "main.hh"

#include "color.hh"
#include "io.hh"
#include "gl.hh"
#include "game.hh"
#include "map.hh"
#include "maptile.hh"
#include "tiletype.hh"
#include "mapobject.hh"
#include "player.hh"
#include "bike.hh"
#include "displayobject.hh"

#define PNGSIGSIZE 8

void UserReadData(png_structp png_ptr, png_bytep texture_, png_size_t length) {
	//Here we get our IO pointer back from the read struct.
	//This is the parameter we passed to the png_set_read_fn() function.
	//Our std::istream pointer.
	png_voidp a = png_get_io_ptr(png_ptr);
	//Cast the pointer to std::istream* and read 'length' bytes into 'texture_'
	((std::istream*)a)->read((char*)texture_, length);
}

void GL::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
	screen_ = SDL_SetVideoMode(0, 0, 32, SDL_OPENGL);
	SDL_WM_SetCaption("Roguelike EngineX GL", NULL);

	SDL_EnableKeyRepeat(200,60);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screen_->w, screen_->h, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Clear();

	assert(LoadTexture("font.png"));
	LoadFont(16, 16, 12, 12);
}

GL::~GL()
{
	glDeleteTextures(1, texture_);
	SDL_FreeSurface(screen_);
	SDL_Quit();
}

bool GL::LoadTexture(std::string _file)
{
	png_byte pngsig[PNGSIGSIZE];
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int interlace_type;

	std::ifstream file(_file.c_str(), std::ios::in|std::ios::binary);//|std::ios::ate);
//	file.seekg(std::ios::beg);

	if(!file.is_open())
	{
		printf("file not open\n");
		return 0;
	}
		
	file.read((char*)pngsig, PNGSIGSIZE);

	if(!file.good())
	{
		printf("file not good\n");
		return 0;
	}

	//Here we create the png read struct. The 3 NULL's at the end can be used
	//for your own custom error handling functions, but we'll just use the default.
	//if the function fails, NULL is returned. Always check the return values!
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		return 0;
	}

	//Here we create the png info struct.
	//Note that this time, if this function fails, we have to clean up the read struct!
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp)0, (png_infopp)0);
		return 0;
	}
	
	//Here I've defined 2 pointers up front, so I can use them in error handling.
	//I will explain these 2 later. Just making sure these get deleted on error.
	png_bytep* row_ptrs = NULL;

	if (setjmp(png_jmpbuf(png_ptr))) {
		//An error occured, so clean up what we have allocated so far...
		png_destroy_read_struct(&png_ptr, &info_ptr,(png_infopp)0);
		if (row_ptrs != NULL) delete [] row_ptrs;
		if (texture_ != NULL) delete [] texture_;

		//Make sure you return here. libPNG will jump to here if something
		//goes wrong, and if you continue with your normal code, you might
		//End up with an infinite loop.
		return 0; // Do your own error handling here.
	}

	png_set_read_fn(png_ptr,(png_voidp)&file, UserReadData);
	
	//Set the amount signature bytes we've already read:
	//We've defined PNGSIGSIZE as 8;
	png_set_sig_bytes(png_ptr, PNGSIGSIZE);

	//Now call png_read_info with our png_ptr as image handle, and info_ptr to receive the file info.
	png_read_info(png_ptr, info_ptr);

	png_uint_32 width =  png_get_image_width(png_ptr, info_ptr);
	png_uint_32 height = png_get_image_height(png_ptr, info_ptr);

	//bits per CHANNEL! note: not per pixel!
	png_uint_32 bitdepth   = png_get_bit_depth(png_ptr, info_ptr);
	//Number of channels
	png_uint_32 channels   = png_get_channels(png_ptr, info_ptr);
	//Color type. (RGB, RGBA, Luminance, luminance alpha... palette... etc)
	png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

	switch (color_type) {
		case PNG_COLOR_TYPE_PALETTE:
			png_set_palette_to_rgb(png_ptr);
			//Don't forget to update the channel info (thanks Tom!)
			//It's used later to know how big a buffer we need for the image
			channels = 3;		   
			break;
		case PNG_COLOR_TYPE_GRAY:
			if (bitdepth < 8)
			png_set_expand_gray_1_2_4_to_8(png_ptr);
			//And the bitdepth info
			bitdepth = 8;
			break;
	}

	// if the image has a transperancy set.. convert it to a full Alpha channel..
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(png_ptr);
		channels+=1;
	}

	//We don't support 16 bit precision.. so if the image Has 16 bits per channel
	//precision... round it down to 8.
	if (bitdepth == 16)
		png_set_strip_16(png_ptr);
		
	//Here's one of the pointers we've defined in the error handler section:
	//Array of row pointers. One for every row.
	row_ptrs = new png_bytep[height];

	//Alocate a buffer with enough space.
	//(Don't use the stack, these blocks get big easilly)
	//This pointer was also defined in the error handling section, so we can clean it up on error.
	texture_ = new GLuint[width * height * bitdepth * channels / 8];
	//This is the length in bytes, of one row.
	const unsigned int stride = width * bitdepth * channels / 8;

	//A little for-loop here to set all the row pointers to the starting
	//Adresses for every row in the buffer

	for (size_t i = 0; i < height; i++)
	{
		//Set the pointer to the texture_ pointer + i times the row stride.
		//Notice that the row order is reversed with q.
		//This is how at least OpenGL expects it,
		//and how many other image loaders present the texture_.
//		png_uint_32 q = (height-i-1) * stride;
//		row_ptrs[i] = (png_bytep)texture_ + q;

		png_uint_32 q = (height-i-1) * stride;
		row_ptrs[i] = (png_bytep)texture_ + q;

	}

	//And here it is! The actuall reading of the image!
	//Read the imagedata and write it to the adresses pointed to
	//by row_ptrs (in other words: our image databuffer)
	png_read_image(png_ptr, row_ptrs);
	
	//Delete the row pointers array....
	delete[] (png_bytep)row_ptrs;
	//And don't forget to clean up the read and info structs !
	png_destroy_read_struct(&png_ptr, &info_ptr,(png_infopp)0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);

	return 1;
}

void GL::LoadFont(int _x, int _y, int _xwidth, int _yhieght)
{
	float x = 0;
	float y = 0;
	float offset_x = 1.0/_x;
	float offset_y = 1.0/_y;

	xwidth_ = _xwidth;
	yhieght_ = _yhieght;

	y_ = screen_->h/yhieght_-4;
	x_ = screen_->w/xwidth_;


	FontRect font;

	for(int i=0; i<_x; ++i)
	{
		for(int j=0; j<_y; ++j)
		{
			font.a = x;
			font.b = y;
			font.d = y + offset_y;
			x += offset_x;
			font.c = x;

			font_.push_back(font);			
		}
		x = 0; y += offset_y;
	}
}

void GL::SetState()
{
	glBegin(GL_QUADS);
}

void GL::EndState()
{
	glEnd();
}

void GL::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	offset_.x = 0;
	offset_.y = 0;
}

void GL::Refresh()
{
	SDL_GL_SwapBuffers();
}

void GL::SetColor(std::shared_ptr<Color> _color)
{
	if(_color != NULL && _color != old_color_)
	{
		glColor3ub(_color->r_, _color->g_, _color->b_);
	}
}

void GL::Print(uint8_t _print, std::shared_ptr<Color> _color)
{
	SetColor(_color);

	glTexCoord2f(font_[_print].a, font_[_print].b); glVertex2f(offset_.x, offset_.y);
	glTexCoord2f(font_[_print].a, font_[_print].d); glVertex2f(offset_.x, offset_.y+yhieght_);
	glTexCoord2f(font_[_print].c, font_[_print].d); glVertex2f(offset_.x + xwidth_, offset_.y+yhieght_);
	glTexCoord2f(font_[_print].c, font_[_print].b); glVertex2f(offset_.x + xwidth_, offset_.y);
}
