// MathLib Vector2.hh

#ifndef __VECTOR2_HH__
#define __VECTOR2_HH__

#include <array>
#include <cmath>

template <typename t>
class Vector2
{
  private:
	std::array<t, 2> coordinate;

  public:
	Vector2() {};
	Vector2(t _x, t _y)
	{
		coordinate[0] = _x;
		coordinate[1] = _y;
	};
	Vector2(std::array<t, 2> _coordinate) { coordinate = _coordinate; };

	t x() const { return coordinate[0]; };
	t y() const { return coordinate[1]; };
	void x(t _abscissa) { coordinate[0] = _abscissa; };
	void y(t _ordinate) { coordinate[1] = _ordinate; };

	void operator=(const Vector2<t> &_other) { coordinate = _other.coordinate; };
	Vector2 operator-() const { return Vector2<t>(-x(), -y()); }; 
	Vector2 operator~() const { return Vector2<t>(y(), x()); };
	Vector2 operator+(const Vector2<t> &_other) const { return Vector2(x() + _other.x(), y() + _other.y()); };
	Vector2 operator-(const Vector2<t> &_other) const { return Vector2(x() - _other.x(), y() - _other.y()); };

	void operator+=(const Vector2<t> &_other) { x(x() + _other.x()); y(y() + _other.y()); };
	void operator-=(const Vector2<t> &_other) { x(x() - _other.x()); y(y() - _other.y()); };
	void operator*=(const t _scalar) { x(x() * _scalar); y(y() * _scalar); };
	void operator/=(const t _scalar) { x(x() / _scalar); y(y() / _scalar); };

	bool operator==(const Vector2<t> &_other) const { return (x() == _other.x() && y() == _other.y()); };
	bool operator!=(const Vector2<t> &_other) const { return (x() != _other.x() && y() != _other.y()); };
	
	bool operator<(const Vector2<t> &_other) const { return (x() < _other.x() && y() < _other.y()); };
	bool operator>(const Vector2<t> &_other) const { return (x() > _other.x() && y() > _other.y()); };
	bool operator<=(const Vector2<t> &_other) const { return (x() <= _other.x() && y() <= _other.y()); };
	bool operator>=(const Vector2<t> &_other) const { return (x() >= _other.x() && y() >= _other.y()); };

	bool Intersect(const Vector2<t> &_other) const { return (x() == _other.x() && y() == _other.y()); };
	bool Collinear(const Vector2<t> &_other) const { return (x() == _other.x() || y() == _other.y()); };
	bool LinIndep(const Vector2<t> &_other) const { return (x() != _other.x() && y() != _other.y()); };

	Vector2<t> Normalize() const
	{
		t norm = std::sqrt(x()*x() + y()*y());

		return Vector2<t>(x()*norm, y()*norm);
	};

	Vector2<t> Reduce() const { return Vector2<t>(x() ? x()/std::abs(x()) : 0, y() ? y()/std::abs(y()) : 0); };

	t Direction() const
	{
		Vector2<t> reduce = Reduce();

		switch(reduce.y())
		{
			case +1: switch(reduce.x()) { case -1: return 7; case +0: return 8; case +1: return 9; }
			case +0: switch(reduce.x()) { case -1: return 4; case +0: return 5; case +1: return 6; }
			case -1: switch(reduce.x()) { case -1: return 1; case +0: return 2; case +1: return 3; }
		}
	};
};

#endif // __other2_HH__
