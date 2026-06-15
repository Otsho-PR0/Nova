#include <Math/Vec2.hpp>

#include <math.h>

using namespace Nova::Math;

Vector2::Vector2(float f) :
	x(f),
	y(f)
{
}

Vector2::Vector2(float x, float y) :
	x(x),
	y(y)
{
}

float Vector2::Length() const
{
    return sqrtf(*this * *this);
}

Vector2& Vector2::Normalize()
{
	float l = Length();
	if (l > 0.0f)
	{
		float k = 1.0f / l;
		return *this *= k;
	}
	return *this;
}

Vector2 Vector2::Normalized() const
{
	float l = Length();
	if (l > 0.0f)
	{
		float k = 1.0f / l;
		return *this * k;
	}
	return *this;
}

const float& Vector2::operator[](unsigned char i) const
{
	return v[i];
}

float& Vector2::operator[](unsigned char i)
{
	return v[i];
}

Vector2 Vector2::operator+(const Vector2& o) const
{
	return { x + o.x, y + o.y };
}

Vector2& Vector2::operator+=(const Vector2& o)
{
	x += o.x;
	y += o.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& o) const
{
	return { x - o.x, y - o.y };
}

Vector2& Vector2::operator-=(const Vector2& o)
{
	x -= o.x;
	y -= o.y;
	return *this;
}

Vector2 Vector2::operator*(const float o) const
{
	return { x * o, y * o };
}

Vector2& Vector2::operator*=(const float o) 
{
	x *= o;
	y *= o;
	return *this;
}

float Vector2::operator*(const Vector2& o) const
{
	return x * o.x + y * o.y;
}
