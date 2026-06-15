#pragma once

#include <Nova.hpp>

namespace Nova::Math
{
	struct NOVA_API Vector2
	{
		Vector2(float);
		Vector2(float, float);

		union
		{
			struct
			{
				float x, y;
			};
			struct
			{
				float v[2];
			};
		};

		float Length() const;
		Vector2& Normalize();
		Vector2 Normalized() const;

		const float& operator[](unsigned char) const;
		float& operator[](unsigned char);
		Vector2 operator+(const Vector2&) const;
		Vector2& operator+=(const Vector2&);
		Vector2 operator-(const Vector2&) const;
		Vector2& operator-=(const Vector2&);
		Vector2 operator*(const float) const;
		Vector2& operator*=(const float);
		float operator*(const Vector2&) const;
	};
}