#ifndef VEC_2
#define VEC_2

namespace DonkeyKong 
{
    struct Vec2 
    {
        Vec2() = default;
        Vec2(float);
		Vec2(float, float);
		Vec2(int);
		Vec2(int, int);
		~Vec2() = default;

        Vec2 operator+(const Vec2&) const;
        Vec2 operator-(const Vec2 &) const;
		Vec2 operator*(const double &);
        Vec2 & operator+=(const Vec2 &);


        float x;
        float y;
    };
}

#endif
