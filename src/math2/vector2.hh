// MathLib Vector2.hh

#ifndef __VECTOR2_HH__
#define __VECTOR2_HH__

#include <array>
#include <cmath>

template <typename t>
class Vector2
{
  public:
	t x;
	t y;

	Vector2() {};
	Vector2(t _x, t _y) : x(_x), y(_y) {};
	Vector2(std::initializer_list<t> _l)
	{
		auto it = _l.begin();
		x = *it;
		y = ++(*it);
	};

	void operator=(const Vector2<t> &_other) { coordinate = _other.coordinate; };
	Vector2 operator-() const { return Vector2<t>(-x, -y); }; 
	Vector2 operator~() const { return Vector2<t>(y, x); };
	Vector2 operator+(const Vector2<t> &_other) const { return Vector2(x + _other.x, y + _other.y); };
	Vector2 operator-(const Vector2<t> &_other) const { return Vector2(x - _other.x, y - _other.y); };

	void operator+=(const Vector2<t> &_other) { x = x + _other.x; y = y + _other.y; };
	void operator-=(const Vector2<t> &_other) { x = x - _other.x; y = y - _other.y; };
	void operator*=(const t _scalar) { x = x * _scalar; y = y * _scalar; };
	void operator/=(const t _scalar) { x = x / _scalar; y = y / _scalar; };

	bool operator==(const Vector2<t> &_other) const { return (x == _other.x && y == _other.y); };
	bool operator!=(const Vector2<t> &_other) const { return (x != _other.x && y != _other.y); };
	
	bool operator<(const Vector2<t> &_other) const { return (x < _other.x && y < _other.y); };
	bool operator>(const Vector2<t> &_other) const { return (x > _other.x && y > _other.y); };
	bool operator<=(const Vector2<t> &_other) const { return (x <= _other.x && y <= _other.y); };
	bool operator>=(const Vector2<t> &_other) const { return (x >= _other.x && y >= _other.y); };

	bool Intersect(const Vector2<t> &_other) const { return (x == _other.x && y == _other.y); };

	bool Coaxial(const Vector2<t> _other) const
	{
		return (_other.x == x || _other.y == y);
	};

	bool Coaxial(const std::initializer_list<Vector2<t>> _l) const
	{
		bool result_x = 1;
		bool result_y = 1;

		for(Vector2<t> other : _l)
		{
			if(other.x != x)
				result_x = 0;

			if(other.x != x)
				result_x = 0;
		}

		return (result_x || result_y);
	};
/*
	bool Collinear(const std::initializer_list<t> _l) const
	{
		if(_l.size() < 3)
			return 1;

		// TODO
	};

/*	incomplete
	bool LinIndep(const Vector2<t> &_other) const
	{
		return (x != _other.x && y != _other.y);
	};*/

	Vector2<t> Normalize() const
	{
		t norm = std::sqrt(x*x + y*y);

		return Vector2<t>(x*norm, y*norm);
	};

	int Direction() const
	{
//		Vector2<t> normal = Normalize();

		t x_reduce = x/std::abs(x);
		t y_reduce = y/std::abs(y);

		switch(y_reduce)
		{
			case +1: switch(x_reduce) { case -1: return 7; case +0: return 8; case +1: return 9; }
			case +0: switch(x_reduce) { case -1: return 4; case +0: return 5; case +1: return 6; }
			case -1: switch(x_reduce) { case -1: return 1; case +0: return 2; case +1: return 3; }
		}
	};
};

#endif // __other2_HH__
