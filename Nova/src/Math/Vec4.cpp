#include <Math/Vec4.hpp>

#include <math.h>

using namespace Nova::Math;

Vector4::Vector4() :
	x(0.0f),
	y(0.0f),
	z(0.0f),
	w(0.0f)
{
}

Vector4::Vector4(float f) :
	x(f),
	y(f),
	z(f),
	w(f)
{
}

Vector4::Vector4(float x, float y, float z, float w) :
	x(x),
	y(y),
	z(z),
	w(w)
{
}

Vector4::Vector4(const Vector3& v, float w) :
	x(v.x),
	y(v.y),
	z(v.z),
	w(w)
{
}

float Vector4::Length() const
{
    return sqrtf(*this * *this);
}

Vector4& Vector4::Normalize()
{
	float l = Length();
	if (l > 0.0f)
	{
		float k = 1.0f / l;
		return *this *= k;
	}
	return *this;
}

Vector4 Vector4::Normalized() const
{
	float l = Length();
	if (l > 0.0f)
	{
		float k = 1.0f / l;
		return *this * k;
	}
	return *this;
}

Vector4::operator Vector2() const
{
	return { x, y };
}

Vector4::operator Vector3() const
{
	return { x, y, z };
}

const float& Vector4::operator[](unsigned char i) const
{
	return v[i];
}

float& Vector4::operator[](unsigned char i)
{
	return v[i];
}

Vector4 Vector4::operator+(const Vector4& o) const
{
	return { x + o.x, y + o.y, z + o.z, w + o.w };
}

Vector4& Vector4::operator+=(const Vector4& o)
{
	x += o.x;
	y += o.y;
	z += o.z;
	w += o.w;
	return *this;
}

Vector4 Vector4::operator-(const Vector4& o) const
{
	return { x - o.x, y - o.y, z - o.z, w - o.w };
}

Vector4& Vector4::operator-=(const Vector4& o)
{
	x -= o.x;
	y -= o.y;
	z -= o.z;
	w -= o.w;
	return *this;
}

Vector4 Vector4::operator*(const float o) const
{
	return { x * o, y * o, z * o, w * o };
}

Vector4& Vector4::operator*=(const float o) 
{
	x *= o;
	y *= o;
	z *= o;
	w *= o;
	return *this;
}

float Vector4::operator*(const Vector4& o) const
{
	return x * o.x + y * o.y + z * o.z + w * o.w;
}

Vector4 Vector4::Cross(const Vector4& l, const Vector4& r)
{
	return { l[1]*r[2] - l[2]*r[1], l[2]*r[0] - l[0]*r[2], l[0]*r[1] - l[1]*r[0], 1.0f };
}

Vector4 Vector4::Reflect(const Vector4& l, const Vector4& r)
{
	float p = 2.0f * (l * r);
	return { l[0] - p*r[0], l[1] - p*r[1], l[2] - p*r[2], l[3] - p*r[3] };
}
