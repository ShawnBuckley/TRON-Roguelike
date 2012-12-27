// Coord2.hh

#ifndef __COORD2_HH__
#define __COORD2_HH__

template <typename T>
struct Coord2
{
	T x;
	T y;

	Coord2() : x(0), y(0) {};
	Coord2(T _x, T _y) : x(_x), y(_y) {};
	Coord2(T _array[2]) : x(_array[0]), y(_array[1]) {};
	Coord2(const Coord2<T>& coord) : x(coord.x), y(coord.y) {};

	void operator=(const Coord2 &coord) { y = coord.y; x = coord.x; };
	Coord2 operator-() { return Coord2<T>(-x, -y); }; 
//	Coord2 operator~() { Coord2<T> complement; complement.x = y; complement.y = x; return complement; };
	Coord2 operator+(const Coord2 &coord) { return Coord2<T>(x + coord.x, y + coord.y); };
	Coord2 operator-(const Coord2 &coord) { return Coord2<T>(x - coord.x, y - coord.y); };

	void operator+=(const Coord2 &coord) { x += coord.x; y += coord.y; };
	void operator-=(const Coord2 &coord) { x -= coord.x; y -= coord.y; };

	void operator*=(const T scalar) { x *= scalar; y *= scalar; };
	void operator/=(const T scalar) { x /= scalar; y /= scalar; };

	bool operator==(const Coord2<T> &coord) const { return (x == coord.x && y == coord.y); };
	bool operator!=(const Coord2<T> &coord) const { return (x != coord.x || y != coord.y); };
	
	bool operator<(const Coord2<T> &coord) const
	{
		if (x < coord.x)
			return true;

		if (coord.x < x)
			return false;

		return y < coord.y;
	};
	
/*	T Direction()
	{
		switch(y)
		{
			case +1: switch(x) { case -1: return 7; case +0: return 8; case +1: return 9; }
			case +0: switch(x) { case -1: return 4; case +0: return 5; case +1: return 6; }
			case -1: switch(x) { case -1: return 1; case +0: return 2; case +1: return 3; }
		}
	}*/
	T Direction()
	{
		T x_reduce = x ? x/abs(x) : 0;
		T y_reduce = y ? y/abs(y) : 0;
	
		switch(y_reduce)
		{
			case +1: switch(x_reduce) { case -1: return 7; case +0: return 8; case +1: return 9; }
			case +0: switch(x_reduce) { case -1: return 4; case +0: return 5; case +1: return 6; }
			case -1: switch(x_reduce) { case -1: return 1; case +0: return 2; case +1: return 3; }
		}
	}
};

#endif
