#pragma once

#include <Nova.hpp>
#include <Math/Vec2.hpp>

namespace Nova::Math
{
	struct NOVA_API Vector3
	{
		Vector3();
		Vector3(float);
		Vector3(float, float, float);
		Vector3(const Vector2&, float);

		union
		{
			struct
			{
				float x, y, z;
			};
			struct
			{
				float r, g, b;
			};
			struct
			{
				float v[3];
			};
		};

		float Length() const;
		Vector3& Normalize();
		Vector3 Normalized() const;

		static Vector3 Cross(const Vector3&, const Vector3&);
		static Vector3 Reflect(const Vector3&, const Vector3&);

		static Vector3 Forward;
		static Vector3 Backward;
		static Vector3 Up;
		static Vector3 Down;
		static Vector3 Right;
		static Vector3 Left;

		operator Vector2() const;

		const float& operator[](unsigned char) const;
		float& operator[](unsigned char);;
		bool operator==(const Vector3&) const;
		Vector3 operator+(const Vector3&) const;
		Vector3& operator+=(const Vector3&);
		Vector3 operator-() const;
		Vector3 operator-(const Vector3&) const;
		Vector3& operator-=(const Vector3&);
		Vector3 operator*(const float) const;
		Vector3& operator*=(const float);
		float operator*(const Vector3&) const;
	};
}