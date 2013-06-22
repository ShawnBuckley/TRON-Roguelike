// MathLib Vector2.hh

#ifndef __VECTOR2_HH__
#define __VECTOR2_HH__

#include <vector>
#include <bitset>
#include <cmath>

template <typename t>
class Vector2
{
  public:
	t x;
	t y;

	Vector2() : x(0), y(0) {};
	Vector2(t _x, t _y) : x(_x), y(_y) {};

	t X() const { return x; };
	t Y() const { return y; };
	inline void X(t _abscissa) { x = _abscissa; };
	inline void Y(t _ordinate) { y = _ordinate; };

	inline Vector2 operator-() const { return Vector2<t>(-x, -y); }; 
	inline Vector2 operator~() const { return Vector2<t>(y, x); };
	inline Vector2 operator+(const Vector2<t> &_other) const { return Vector2(x + _other.x, y + _other.y); };
	inline Vector2 operator-(const Vector2<t> &_other) const { return Vector2(x - _other.x, y - _other.y); };

	inline void operator+=(const Vector2<t> &_other) { x = x + _other.x; y = y + _other.y; };
	inline void operator-=(const Vector2<t> &_other) { x = x - _other.x; y = y - _other.y; };
	inline void operator*=(const t _scalar) { x = x * _scalar; y = y * _scalar; };
	inline void operator/=(const t _scalar) { x = x / _scalar; y = y / _scalar; };

	inline bool operator==(const Vector2<t> &_other) const { return (x == _other.x && y == _other.y); };
	inline bool operator!=(const Vector2<t> &_other) const { return (x != _other.x && y != _other.y); };
	
	inline bool operator<(const Vector2<t> &_other) const { return Magnatude() < _other.Magnatude(); };
	inline bool operator>(const Vector2<t> &_other) const { return Magnatude() > _other.Magnatude(); };
	inline bool operator<=(const Vector2<t> &_other) const { return Magnatude() <= _other.Magnatude(); };
	inline bool operator>=(const Vector2<t> &_other) const { return Magnatude() >= _other.Magnatude(); };

	inline bool Intersect(const Vector2<t> &_other) const { return (*this == _other); };
	inline bool Coaxial(const Vector2<t> _other) const { return (_other.x == x || _other.y == y); };
	bool Coaxial(const std::initializer_list<Vector2<t>> _l) const;
	inline bool Collinear(const Vector2<t> &_b, const Vector2<t> &_c) const { return (y - _b.y) * (x - _c.x) == (y - _c.y) * (x - _b.x); };
	bool Collinear(const std::initializer_list<Vector2<t>> _l) const;
	bool Collinear(const std::vector<Vector2<t>> _c) const;

	inline bool LinIndep(const Vector2<t> &_other) const { return ((x * _other.y - _other.x * y) != 0); };
	bool LinIndep(const std::initializer_list<Vector2<t>> _l) const;
	bool LinIndep(const std::vector<Vector2<t>> _l) const;

	inline t Magnatude() const { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); };
	Vector2<t> Normalize() const { t magnatude = Magnatude(); return Vector2<t>(x*magnatude, y*magnatude); };
	inline t Angle() const { return std::atan2(y,x); };

	int Direction() const;


};

template <typename t>
bool Vector2<t>::Coaxial(const std::initializer_list<Vector2<t>> _l) const
{
	for(Vector2<t> other : _l)
	{
		if((x != other.x) && (y != other.y))
			return 0;
	}

	return 1;
}

template <typename t>
bool Vector2<t>::Collinear(const std::initializer_list<Vector2<t>> _l) const
{
	if(_l.size() < 2)
		return 1;

	t angle = Angle();

	for(Vector2<t> vector : _l)
	{
		if(vector.Angle() != angle)
			return 0;
	}

	return 1;
}

// TODO - STL iterators versus a specific container
template <typename t>
bool Vector2<t>::Collinear(const std::vector<Vector2<t>> _v) const
{
	if(_v.size() < 2)
		return 1;

	t angle = Angle();

	for(auto it = _v.begin(); it != _v.end(); ++it)
	{
		if(it->Angle() != angle)
			return 0;
	}

	return 1;
}

template <typename t>
bool Vector2<t>::LinIndep(const std::initializer_list<Vector2<t>> _l) const
{
	Vector2<t> test;

	for(Vector2<t> vector : _l)
		test += vector;

	return ((x * test.y - test.x * y) != 0);
}

template <typename t>
bool Vector2<t>::LinIndep(const std::vector<Vector2<t>> _v) const
{
	Vector2<t> test;

	for(Vector2<t> vector : _v)
		test += test;

	return ((x * test.y - test.x * y) != 0);
}

// TODO - move this out of here
template <typename t>
int Vector2<t>::Direction() const
{
	// Vector2<t> normal = Normalize();

	t xreduce = x/std::fabs(x);
	t yreduce = y/std::fabs(y);

	switch(yreduce)
	{
		case +1: switch(xreduce) { case -1: return 7; case +0: return 8; case +1: return 9; }
		case +0: switch(xreduce) { case -1: return 4; case +0: return 5; case +1: return 6; }
		case -1: switch(xreduce) { case -1: return 1; case +0: return 2; case +1: return 3; }
	}
}

#endif // __VECTOR2_HH__
