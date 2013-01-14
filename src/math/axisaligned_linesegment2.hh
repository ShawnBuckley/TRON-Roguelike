// MathLib AxisAligned_LineSegment2.hh

#ifndef __AXISALIGNED_LINESEGMENT2_HH__
#define __AXISALIGNED_LINESEGMENT2_HH__

#include <vector>

#include "vector2.hh"

template <typename t>
class AxisAligned_LineSegment2
{
//  private:
  public:
	t start_;
	t end_;
	t offset_;
	bool vertical_;

  public:
	AxisAligned_LineSegment2() : start_(0), end_(0), offset_(0), vertical_(0) {};
	AxisAligned_LineSegment2(bool _vertical, t _offset, t _start, t _end)
		: start_(_start), end_(_end), offset_(_offset), vertical_(_vertical) {};

	AxisAligned_LineSegment2(Vector2<t> _origin, int _length, bool _vertical) :
		vertical_(_vertical)
	{
		offset_ = vertical_ ? _origin.x() : _origin.y();
		start_ = vertical_ ? _origin.y() : _origin.x();
		end_ =  vertical_ ? _origin.y() + _length : _origin.x() + _length;
	};

	AxisAligned_LineSegment2(std::array<Vector2<t>, 2> _point)
	{
		vertical_ = _point[0].x() == _point[1].x();
		offset_ = vertical_ ? _point[0].x() : _point[0].y();
		start_ = vertical_ ? std::min(_point[0].y(), _point[1].y()) : std::min(_point[0].x(), _point[1].x());
		end_ = vertical_ ? std::max(_point[0].y(), _point[1].y()) : std::max(_point[0].x(), _point[1].x());
	};

	AxisAligned_LineSegment2(Vector2<t> _one, Vector2<t> _two)
	{
		vertical_ = _one.x() == _two.x();
		offset_ = vertical_ ? _one.x() : _one.y();
		start_ = vertical_ ? std::min(_one.y(), _two.y()) : std::min(_one.x(), _two.x());
		end_ = vertical_ ? std::max(_one.y(), _two.y()) : std::max(_one.x(), _two.x());
	};

	inline bool Parallel(const AxisAligned_LineSegment2<t> _other) const { return (vertical_ == _other.vertical_); };
	
	inline t Length() const { return std::abs(end_ - start_); };

	std::vector<t> Slope() const
	{
		std::vector<t> result;

		if(!vertical_)
			result.push_back(0);

		return result;
	};

	Vector2<t> Vertex(const int _vertex) const
	{
		switch(_vertex)
		{
			case 0:
			{
				if(vertical_)
					return Vector2<t>(offset_, start_);
				else
					return Vector2<t>(start_, offset_);
			};
			case 1:
			{
				if(vertical_)
					return Vector2<t>(offset_, end_);
				else
					return Vector2<t>(end_, offset_);
			};
		}
	};

	bool Intersect(const Vector2<t> &_other) const
	{
		if(vertical_)
			return (_other.x() == offset_ && start_ < _other.x() && _other.x() < end_);
		else
			return (_other.y() == offset_ && start_ < _other.y() && _other.y() < end_);
	}

	std::vector<Vector2<t> > Intersect(const AxisAligned_LineSegment2<t> &_other) const
	{
		std::vector<Vector2<t> > result;
		result.reserve(2);
	
		if(Parallel(_other))
		{
			if(offset_ == _other.offset_)
			{
				if(start_ < _other.start_ && _other.start_ < end_)
				{
					if(vertical_)
					{
						result.push_back(Vector2<t>(offset_, _other.start_));
						result.push_back(Vector2<t>(offset_, end_));
					}
					else
					{
						result.push_back(Vector2<t>(_other.start_ , offset_));
						result.push_back(Vector2<t>(end_ , offset_));
					}
				}
				else if(start_ < _other.end_ && _other.end_ < end_)
				{
					if(vertical_)
					{
						result.push_back(Vector2<t>(offset_, _other.end_));
						result.push_back(Vector2<t>(offset_, start_));
					}
					else
					{
						result.push_back(Vector2<t>(_other.end_ , offset_));
						result.push_back(Vector2<t>(start_ , offset_));
					}
				}
				else if(_other.start_ < start_ && start_ < _other.end_)
				{
					if(vertical_)
					{
						result.push_back(Vector2<t>(offset_, start_));
						result.push_back(Vector2<t>(offset_, _other.end_));
					}
					else
					{
						result.push_back(Vector2<t>(start_ , offset_));
						result.push_back(Vector2<t>(_other.end_ , offset_));
					}
				}
				else if(_other.start_ < end_ && end_ < _other.end_)
				{
					if(vertical_)
					{
						result.push_back(Vector2<t>(offset_, end_));
						result.push_back(Vector2<t>(offset_, _other.start_));
					}
					else
					{
						result.push_back(Vector2<t>(end_ , offset_));
						result.push_back(Vector2<t>(_other.start_ , offset_));
					}
				}
			}
		}
		else if(start_ <= _other.offset_ && _other.offset_ <= end_ && _other.start_ <= offset_ && offset_ <= end_)
		{
			if(vertical_)
				result.push_back(Vector2<t>(offset_, _other.offset_));
			else
				result.push_back(Vector2<t>(_other.offset_, offset_));
		}

		return result;
	};

	static std::vector<AxisAligned_LineSegment2<t> > Construct(std::vector<Vector2<t> > _set)
	{
		std::vector<AxisAligned_LineSegment2<t> > result;
		
		if(_set.size() >= 2)
		{
			t start;
			t end;
			t offset;
			bool vertical;
			bool valid = 1;
			
			if(_set[0].x() != _set[1].x())
			{
				vertical = 0;
				
				if(_set[0].y() == _set[0].y())
				{
					offset = _set[0].y();
				}
				else
				{
					valid = 0;
				}
			}
			else if(_set[0].y() != _set[1].y())
			{
				vertical = 1;
				
				if(_set[0].x() == _set[0].x())
				{
					offset = _set[0].x();
				}
				else
				{
					valid = 0;
				}
			}
			else
			{
				valid = 0;
			}
		
			for(int i=2; i<_set.size() && valid; ++i)
			{
				if(vertical)
				{
//					if(
				}
				else
				{
					
				}
				
			}
			
			if(valid)
				result.push_back(AxisAligned_LineSegment2<t>(vertical, offset, start, end));
		}
		
		return result;
	};
};

#endif // __AXISALIGNED_LINESEGMENT2_HH__
