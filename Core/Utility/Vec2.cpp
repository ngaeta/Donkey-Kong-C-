#include "Vec2.h"

namespace DonkeyKong 
{
    Vec2::Vec2(float value)
        : x{value}, y{value} 
    {}

    Vec2::Vec2(float px_, float py_)
        : x{px_}, y{py_}
    {}

	Vec2::Vec2(int value) : x{ (float) value }, y{ (float) value }
	{
	}

	Vec2::Vec2(int px_, int py_) : x{ (float) px_ }, y{(float) py_ }
	{
	}

    Vec2 Vec2::operator+(const Vec2 &other) const 
    {
        return Vec2{x + other.x, y + other.y};
    }

	Vec2 Vec2::operator-(const Vec2& other) const
	{
        return Vec2{ x - other.x, y - other.y };
	}

	Vec2 Vec2::operator*(const double & other)
	{
		float other_ = static_cast<float>(other);
		return Vec2{ x * other_, y * other_ };
	}

    Vec2 & Vec2::operator+=(const Vec2 &other) 
    {
        x += other.x;
        y += other.y;
        return *this;
    }
}
