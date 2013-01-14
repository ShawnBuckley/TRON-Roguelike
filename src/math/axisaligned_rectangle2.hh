// MathLib AxisAligned_Rectange2.hh

#ifndef __AXISALIGNED_RECTANGLE2_HH__
#define __AXISALIGNED_RECTANGLE2_HH__

#include <vector>

#include "vector2.hh"
#include "axisaligned_linesegment2.hh"

template <typename t>
class AxisAligned_Rectangle2
{
  private:
	Vector2<t> origin_;
	t width_;
	t height_;

  public:
	AxisAligned_Rectangle2() : origin_(Vector2<t>(0,0)), width_(0), height_(0) {};
	AxisAligned_Rectangle2(Vector2<t> _origin, t _width, t _height) :
		origin_(_origin), width_(_width), height_(_height) {};

	t Width() { return width_; };
	t Height() { return height_; };

	void Origin(Vector2<t> _origin) { origin_ = _origin; };
	void Height(t _height) { height_ = _height; };
	void Width(t _width) { width_ = _width; };

	Vector2<t> Vertex(const int _vertex) const
	{
		switch(_vertex)
		{
			case 0: return Vector2<t>(origin_);
			case 1: return Vector2<t>(origin_.x() + width_, origin_.y());
			case 2: return Vector2<t>(origin_.x() + width_, origin_.y() + height_);
			case 3: return Vector2<t>(origin_.x(), origin_.y() + height_);
		}
	};

	AxisAligned_LineSegment2<t> Edge(const int _edge) const
	{
		switch(_edge)
		{
			case 0: return AxisAligned_LineSegment2<t>(origin_, width_, false);		// South
			case 1: return AxisAligned_LineSegment2<t>(Vertex(1), height_, true);	// East
			case 2: return AxisAligned_LineSegment2<t>(Vertex(3), width_, false);	// North
			case 3: return AxisAligned_LineSegment2<t>(origin_, height_, true);		// West
		}
	};

	// non working for all cases
	bool CheckIntersect(const AxisAligned_Rectangle2<t> &_other) const
	{
		Vector2<t> this_vertex0 = Vertex(0);
		Vector2<t> this_vertex2 = Vertex(2);
		Vector2<t> other_vertex0 = _other.Vertex(0);
		Vector2<t> other_vertex2 = _other.Vertex(2);

		return !((this_vertex2.x() < other_vertex0.x())
			|| (other_vertex2.x() < this_vertex0.x())
			|| (this_vertex2.y() < other_vertex2.y())
			|| (other_vertex2.y() < this_vertex0.y()));
	};
	
	bool Intersect(const Vector2<t> &_other) const
	{
		return (origin_.x() <= _other.x() && _other.x() <= origin_.x()+width_
			&& origin_.y() <= _other.y() && _other.y() <= origin_.y()+height_);
	};

	std::vector<Vector2<t> > Intersect(const AxisAligned_Rectangle2<t> &_other) const
	{
		std::vector<Vector2<t> > result;
		result.reserve(4);

		Vector2<t> this_vertex0 = Vertex(0);
		Vector2<t> this_vertex2 = Vertex(2);
		Vector2<t> other_vertex0 = _other.Vertex(0);
		Vector2<t> other_vertex2 = _other.Vertex(2);

		// Checks if the two rectangles are equal
		if(origin_ == _other.origin_ && width_ == _other.width_ && height_ == _other.height_)
		{
			result.push_back(this_vertex0);
			result.push_back(this_vertex2);
			
			return result;
		}

		// Checks if this rect is in other
		if(this_vertex0.x() > other_vertex0.x() && this_vertex0.y() > other_vertex0.y() &&
			this_vertex2.x() < other_vertex2.x() && this_vertex2.y() < other_vertex2.y())
		{
			result.push_back(this_vertex0);
			result.push_back(this_vertex2);
		
			return result;
		}

		// Checks if other rect is in this
		if(other_vertex0.x() > this_vertex0.x() && other_vertex0.y() > this_vertex0.y() &&
			other_vertex2.x() < this_vertex2.x() && other_vertex2.y() < this_vertex2.y())
		{
			result.push_back(other_vertex0);
			result.push_back(other_vertex2);

			return result;
		}

		// calculates if any vertex intersects with the opposite rectangle
		if(Intersect(other_vertex0))
			result.push_back(other_vertex0);
		if(Intersect(_other.Vertex(1)))
			result.push_back(_other.Vertex(1));
		if(Intersect(other_vertex2))
			result.push_back(other_vertex2);
		if(Intersect(_other.Vertex(3)))
			result.push_back(_other.Vertex(3));

		if(_other.Intersect(this_vertex0))
			result.push_back(this_vertex0);
		if(_other.Intersect(Vertex(1)))
			result.push_back(Vertex(1));
		if(_other.Intersect(this_vertex2))
			result.push_back(this_vertex2);
		if(_other.Intersect(Vertex(3)))
			result.push_back(Vertex(3));

		// Calculates the resulting line segment intersects
		AxisAligned_LineSegment2<t> this_edge;
		AxisAligned_LineSegment2<t> other_edge;

		std::vector<Vector2<t> > intersect;

		for(int i = 0; i < 4; ++i)
		{
			this_edge = Edge(i);

			for(int j = 0; j < 4; ++j)
			{
				other_edge = _other.Edge(j);

				intersect = this_edge.Intersect(other_edge);

				for(int k=0; k<intersect.size(); ++k)
					result.push_back(intersect[k]);
			}
		}

		return result;		
	};
	
	static std::vector<AxisAligned_Rectangle2<t> > Construct(std::vector<Vector2<t> > _set)
	{
		std::vector<AxisAligned_Rectangle2<t> > result;
	
		if(_set.size() == 2)
		{
			if(_set[0].x() != _set[1].x() && _set[0].y() != _set[1].y())
			{
				Vector2<t> origin;
				Vector2<t> opposite;

				if(std::abs(_set[0].x()) <= std::abs(_set[1].x()) && std::abs(_set[0].y()) <= std::abs(_set[1].y()))
				{
					origin = _set[0];
					opposite = _set[1];
				}
				else
				{
					origin = _set[1];
					opposite = _set[0];
				}
				
				if(origin.Collinear(opposite))
					result.push_back(AxisAligned_Rectangle2<t>(origin, opposite.x() - origin.x(), opposite.y() - origin.y()));
			}
		}
		else if(_set.size() == 4)
		{
			bool valid = 1;
			Vector2<t> origin(_set[0]);
			Vector2<t> opposite(_set[0]);

			for(int i=0; i<4; ++i)
			{
				if(std::abs(_set[i].x()) <= std::abs(origin.x()) && std::abs(_set[i].y()) <= std::abs(origin.y()))
					origin = _set[i];

				if(std::abs(_set[i].x()) >= std::abs(opposite.x()) && std::abs(_set[i].y()) >= std::abs(opposite.y()))
					opposite = _set[i];
			}
			
			for(int i=0; i<4; ++i)
			{
				if(_set[i] != opposite)
					if(!origin.Collinear(_set[i]))
						valid = 0;

				if(_set[i] != origin)
					if(!opposite.Collinear(_set[i]))
						valid = 0;
			}
			
			if(valid)
				result.push_back(AxisAligned_Rectangle2<t>(origin, opposite.x() - origin.x(), opposite.y() - origin.y()));
		}
		
		return result;
	};
};

#endif // __AxisAligned_RECTANGLE2_HH__
