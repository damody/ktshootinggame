#pragma once
#include <cmath>

template <class T>
struct TPos
{
	T x,y;
	TPos(void){}
	TPos(T _x, T _y):x(_x),y(_y){}
	TPos(const T* v):x(v[0]),y(v[1]){}
	TPos<T> operator+(const TPos<T>& pos) const
	{
		TPos<T> tmp;
		tmp.x = x + pos.x;
		tmp.y = y + pos.y;
		return tmp;
	};
	TPos<T>& operator+=(const TPos<T>& pos)
	{
		x += pos.x;
		y += pos.y;
		return *this;
	};
	TPos<T> operator-(const TPos<T>& pos) const
	{
		TPos<T> tmp;
		tmp.x = x - pos.x;
		tmp.y = y - pos.y;
		return tmp;
	};
	TPos<T>& operator-=(const TPos<T>& pos)
	{
		x -= pos.x;
		y -= pos.y;
		return *this;
	};
	TPos<T> operator*(const T num) const
	{
		return TPos<T>(x * num, y * num);
	};
	TPos<T>& operator*=(const T num)
	{
		x *= num;
		y *= num;
		return *this;
	};
	TPos<T> operator/(const T num) const
	{
		T fInv = T(1)/num;
		return TPos<T>(x * fInv, y * fInv);
	};
	TPos<T>& operator/=(const T num)
	{
		T fInv = T(1)/num;
		x *= fInv;
		y *= fInv;
		return *this;
	};
	TPos<T>& operator=(const TPos<T>& pos)
	{
		x = pos.x;
		y = pos.y;
		return *this;
	};
	bool operator==(const TPos<T>& pos) const
	{
		return (pos.x == x) && (pos.y == y);
	};
	bool operator!=(const TPos<T>& pos) const
	{
		return (pos.x != x) || (pos.y != y);
	};
	TPos<T>& inverse()
	{
		x = -x;
		y = -y;
		return *this;
	}
	double length() const
	{
		return sqrt((double)(x*x+y*y));
	};
	double squaredLength() const
	{
		return x*x+y*y;
	};
	double distance(const TPos<T>& pos) const
	{
		return (*this - pos).length();
	}
	double normalise()
	{
		double fLength = length();
		if ( fLength > 1e-08 )
		{
			double fInvLength = 1.0 / fLength;
			x *= fInvLength;
			y *= fInvLength;
		}
		return fLength;
	}
	TPos<T> midPoint( const TPos<T>& vec ) const
	{
		return TPos<T>(
			( x + vec.x ) * 0.5,
			( y + vec.y ) * 0.5 );
	}
	T dotProduct(const TPos<T>& vec) const
	{
		return x * vec.x + y * vec.y;
	}
	T crossProduct( const TPos<T>& rkVector ) const
	{
		return x * rkVector.y - y * rkVector.x;
	}
	TPos<T> reflect(const TPos<T>& normal) const
	{
		return TPos<T>( *this - ( 2 * this->dotProduct(normal) * normal ) );
	}
};
typedef TPos<int> Posi;
typedef TPos<float> Posf;
typedef TPos<double> Posd;

template <class T>
struct TRect
{
	T left, top, right, bottom;

	TRect(T _left, T _top, T _right, T _bottom):
	left(_left),right(_right),top(_top),bottom(_bottom){}
	TRect(){}
	TRect(const T* v):left(v[0]),right(v[1]),top(v[2]),bottom(v[3]){}
	TRect<T> Move(const T x, const T y)
	{
		left += x;
		right += x;
		top += y;
		bottom += y;
		return *this;
	};
	T GetWidth() const
	{
		return fabs(right-left);
	};
	T GetHeight() const
	{
		return fabs(bottom-top);
	};
	TRect<T> intersect(const TRect<T>& lhs, const TRect<T>& rhs) const
	{
		TRect r;
		r.left   = lhs.left   > rhs.left   ? lhs.left   : rhs.left;
		r.top    = lhs.top    > rhs.top    ? lhs.top    : rhs.top;
		r.right  = lhs.right  < rhs.right  ? lhs.right  : rhs.right;
		r.bottom = lhs.bottom < rhs.bottom ? lhs.bottom : rhs.bottom;

		return r;
	}
	TRect<T> operator+(const TRect<T>& rect)
	{
		TRect<T> tmp;
		tmp.left = left + rect.left;
		tmp.right = right + rect.right;
		tmp.top = top + rect.top;
		tmp.bottom = bottom + rect.bottom;
		return tmp;
	};
	TRect<T> operator+(const typename TPos<T>& pos)
	{
		TRect<T> tmp;
		tmp.left = left + pos.x;
		tmp.right = right + pos.x;
		tmp.top = top + pos.y;
		tmp.bottom = bottom + pos.y;
		return tmp;
	};
	TRect<T>& operator+=(const TRect<T>& rect)
	{
		left += rect.left;
		right += rect.right;
		top += rect.top;
		bottom += rect.bottom;
		return *this;
	};
	TRect<T>& operator+=(const typename TPos<T>& pos)
	{
		left += pos.x;
		right += pos.x;
		top += pos.y;
		bottom += pos.y;
		return *this;
	};
	TRect<T> operator-(const TRect<T>& rect)
	{
		TRect<T> tmp;
		tmp.left = left - rect.left;
		tmp.right = right - rect.right;
		tmp.top = top - rect.top;
		tmp.bottom = bottom - rect.bottom;
		return tmp;
	};
	TRect<T> operator-(const typename TPos<T>& pos)
	{
		TRect<T> tmp;
		tmp.left = left - pos.x;
		tmp.right = right - pos.x;
		tmp.top = top - pos.y;
		tmp.bottom = bottom - pos.y;
		return tmp;
	};
	TRect<T>& operator-=(const TRect<T>& rect)
	{
		left -= rect.left;
		right -= rect.right;
		top -= rect.top;
		bottom -= rect.bottom;
		return *this;
	};
	TRect<T>& operator-=(const typename TPos<T>& pos)
	{
		left -= pos.x;
		right -= pos.x;
		top -= pos.y;
		bottom -= pos.y;
		return *this;
	};
	TRect<T> operator*(const T num)
	{
		TRect<T> tmp;
		tmp.left = left * num;
		tmp.right = right * num;
		tmp.top = top * num;
		tmp.bottom = bottom * num;
		return tmp;
	};
	TRect<T>& operator*=(const T num)
	{
		left *= num;
		right *= num;
		top *= num;
		bottom *= num;
		return *this;
	};
	TRect<T> operator/(const T num)
	{
		TRect<T> tmp;
		tmp.left = left / num;
		tmp.right = right / num;
		tmp.top = top / num;
		tmp.bottom = bottom / num;
		return tmp;
	};
	TRect<T>& operator/=(const T num)
	{
		left /= num;
		right /= num;
		top /= num;
		bottom /= num;
		return *this;
	};
	TRect<T>& operator=(const TRect<T>& rect)
	{
		left = rect.left;
		right = rect.right;
		top = rect.top;
		bottom = rect.bottom;
		return *this;
	};
	bool operator==(const TRect<T>& rect)
	{
		return (left == rect.left && right == rect.right && top == rect.top && bottom == rect.bottom);
	};
	bool operator!=(const TRect<T>& rect)
	{
		return !operator==(rect);
	};
	bool isCollision(const TRect<T>& rect)
	{
		if ((left > rect.left && left < rect.right) || (right > rect.left && left < rect.right))
		{
			if ((top > rect.top && top < rect.top) || (bottom > rect.bottom && top < rect.bottom))
			{
				return true;
			}
		}
		else if ((rect.left > left && rect.left < right) || (rect.right > left && rect.left < right))
		{
			if ((rect.top > top && rect.top < bottom) || (rect.bottom > top && rect.bottom < bottom))
			{
				return true;
			}
		}
		return false;
	}
	bool isCollision(const TPos<T>& pos)
	{
		if ((pos.x > left && pos.x < right))
		{
			if ((pos.y > top && pos.y < bottom))
			{
				return true;
			}
		}
		return false;
	}
};

typedef TRect<float> Rectf;
typedef TRect<double> Rectd;
typedef TRect<int> Recti;

template <class T>
struct TCircle
{
	TPos<T> pos;
	T radius;
	TCircle():radius(0), pos(TPos<T>(0,0))
	{
	}
	TCircle(T x, T y, T _radius):radius(_radius), pos(TPos<T>(x,y))
	{
	}
	TCircle(TPos<T>& _pos, T _radius):radius(_radius), pos(_pos)
	{
	}

	TCircle<T> operator+(const TPos<T>& _pos) const
	{
		return pos + _pos;
	};
	TCircle<T>& operator+=(const TPos<T>& _pos)
	{
		pos += _pos;
		return *this;
	};
	TCircle<T> operator-(const TPos<T>& _pos) const
	{
		return pos - _pos;
	};
	TCircle<T>& operator-=(const TPos<T>& _pos)
	{
		pos -= _pos;
		return *this;
	};
	TCircle<T>& operator=(const TCircle<T>& cir)
	{
		pos = cir.pos;
		radius = cir.radius;
		return *this;
	};
	bool operator==(const TPos<T>& _pos) const
	{
		return pos == _pos;
	};
	bool operator!=(const TPos<T>& _pos) const
	{
		return pos != _pos;
	};
};
