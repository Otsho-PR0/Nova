#pragma once

#include <Nova.hpp>
#include <Math/Vec4.hpp>

namespace Nova::Math
{
	struct NOVA_API Matrix3
	{
		Matrix3(float = 0.0f);
		Matrix3(const Vector3&, const Vector3&, const Vector3&);

		union
		{
			struct
			{
				Vector3 v[3];
			};
		};

		Matrix3& Transpose();
		Matrix3 Transposed() const;

		const Vector3& operator[](unsigned char) const;
		Vector3& operator[](unsigned char);
		Matrix3 operator*(const Matrix3&) const;
		Vector3 operator*(const Vector3&) const;
	};

	struct NOVA_API Matrix
	{
		Matrix(float = 0.0f);
		Matrix(const Vector4&, const Vector4&, const Vector4&, const Vector4&);

		union
		{
			struct
			{
				Vector4 v[4];
			};
		};

		Matrix& Transpose();
		Matrix Transposed() const;

		operator Matrix3() const;

		const Vector4& operator[](unsigned char) const;
		Vector4& operator[](unsigned char);
		Matrix operator*(const Matrix&) const;
		Vector4 operator*(const Vector4&) const;

		static Matrix Translate(float x, float y, float z);
		static Matrix Translate(const Vector3&);
		static Matrix RotateX(float angle);
		static Matrix RotateY(float angle);
		static Matrix RotateZ(float angle);
		static Matrix Scale(float x, float y, float z);
		static Matrix Scale(const Vector3&);
		static Matrix Perspective(float fov, float aspect, float n, float f);
		static Matrix LookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
	};
}