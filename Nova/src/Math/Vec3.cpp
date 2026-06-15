#include <Math/Vec3.hpp>

#include <math.h>

using namespace Nova::Math;

Vector3 Vector3::Forward  = {  0.0f,  0.0f,  1.0f };
Vector3 Vector3::Backward = {  0.0f,  0.0f, -1.0f };
Vector3 Vector3::Up       = {  0.0f,  1.0f,  0.0f };
Vector3 Vector3::Down     = {  0.0f, -1.0f,  0.0f };
Vector3 Vector3::Right    = {  1.0f,  0.0f,  0.0f };
Vector3 Vector3::Left     = { -1.0f,  0.0f,  0.0f };

Vector3::Vector3() :
	x(0.0f),
	y(0.0f),
	z(0.0f)
{
}

Vector3::Vector3(float f) :
	x(f),
	y(f),
	z(f)
{
}

Vector3::Vector3(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{
}

Vector3::Vector3(const Vector2& v, float z) :
	x(v.x),
	y(v.y),
	z(z)
{
}

float Vector3::Length() const
{
    return sqrtf(*this * *this);
}

Vector3& Vector3::Normalize()
{
	float l = Length();
	if (l > 0.0f)
	{
		float k = 1.0f / l;
		return *this *= k;
	}
	return *this;
}

Vector3 Vector3::Normalized() const
{
	float l = Length();
	if (l > 0.0f)
	{
		float k = 1.0f / l;
		return *this * k;
	}
	return *this;
}

Vector3 Vector3::Cross(const Vector3& l, const Vector3& r)
{
	return { l[1] * r[2] - l[2] * r[1], l[2] * r[0] - l[0] * r[2], l[0] * r[1] - l[1] * r[0] };
}

Vector3 Vector3::Reflect(const Vector3& l, const Vector3& r)
{
	float p = 2.0f * (l * r);
	return { l[0] - p * r[0], l[1] - p * r[1], l[2] - p * r[2] };
}


Vector3::operator Vector2() const
{
	return { x, y };
}

const float& Vector3::operator[](unsigned char i) const
{
	return v[i];
}

float& Vector3::operator[](unsigned char i)
{
	return v[i];
}

bool Vector3::operator==(const Vector3& o) const
{
	return x == o.x and y == o.y and z == o.z;
}

Vector3 Vector3::operator+(const Vector3& o) const
{
	return { x + o.x, y + o.y, z + o.z };
}

Vector3& Vector3::operator+=(const Vector3& o)
{
	x += o.x;
	y += o.y;
	z += o.z;
	return *this;
}

Vector3 Vector3::operator-() const
{
	return { -x, -y, -z };
}

Vector3 Vector3::operator-(const Vector3& o) const
{
	return { x - o.x, y - o.y, z - o.z };
}

Vector3& Vector3::operator-=(const Vector3& o)
{
	x -= o.x;
	y -= o.y;
	z -= o.z;
	return *this;
}

Vector3 Vector3::operator*(const float o) const
{
	return { x * o, y * o, z * o };
}

Vector3& Vector3::operator*=(const float o) 
{
	x *= o;
	y *= o;
	z *= o;
	return *this;
}

float Vector3::operator*(const Vector3& o) const
{
	return x * o.x + y * o.y + z * o.z;
}