#pragma once

#include <Nova.hpp>
#include <Math/Vec3.hpp>

namespace Nova::Math
{
	struct NOVA_API Vector4
	{
		Vector4();
		Vector4(float);
		Vector4(float, float, float, float);
		Vector4(const Vector3&, float);

		union
		{
			struct
			{
				float x, y, z, w;
			};
			struct
			{
				float r, g, b, a;
			};
			struct
			{
				float v[4];
			};
		};

		float Length() const;
		Vector4& Normalize();
		Vector4 Normalized() const;

		static Vector4 Cross(const Vector4&, const Vector4&);
		static Vector4 Reflect(const Vector4&, const Vector4&);

		operator Vector2() const;
		operator Vector3() const;

		const float& operator[](unsigned char) const;
		float& operator[](unsigned char);
		Vector4 operator+(const Vector4&) const;
		Vector4& operator+=(const Vector4&);
		Vector4 operator-(const Vector4&) const;
		Vector4& operator-=(const Vector4&);
		Vector4 operator*(const float) const;
		Vector4& operator*=(const float);
		float operator*(const Vector4&) const;
	};
}