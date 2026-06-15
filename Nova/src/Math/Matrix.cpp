#include <Math/Matrix.hpp>

#include <math.h>

using namespace Nova::Math;

Matrix::Matrix(float f)	:
	v()
{
	for (int i = 0; i < 4; i++)
		v[i][i] = f;
}

Matrix::Matrix(const Vector4& r1, const Vector4& r2, const Vector4& r3, const Vector4& r4)
{
	v[0] = r1;
	v[1] = r2;
	v[2] = r3;
	v[3] = r4;
}

Matrix& Matrix::Transpose()
{
	Matrix c = *this;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			v[i][j] = c[j][i];
	return *this;
}

Matrix Matrix::Transposed() const
{
	Matrix c;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			c[i][j] = v[j][i];
	return c;
}

Matrix::operator Matrix3() const
{
	return { v[0], v[1], v[2] };
}

const Vector4& Matrix::operator[](unsigned char i) const
{
	return v[i];
}

Vector4& Matrix::operator[](unsigned char i)
{
	return v[i];
}

Matrix Matrix::operator*(const Matrix& o) const
{
	Matrix r;
	for(int i=0; i < 4; i++)
		for(int k=0; k < 4; k++)
			for(int j=0; j < 4; j++)
				r[i][j] += v[i][k] * o[k][j];
	return r;
}

Vector4 Matrix::operator*(const Vector4& o) const
{
	Vector4 r;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r[j] += o[i] * v[i][j];
	return r;
}

Matrix Matrix::Translate(float x, float y, float z)
{
	Matrix r(1.0f);
	r[3][0] = x;
	r[3][1] = y;
	r[3][2] = z;
	return r;
}

Matrix Matrix::Translate(const Vector3& t)
{
	Matrix r(1.0f);
	r[3][0] = t.x;
	r[3][1] = t.y;
	r[3][2] = t.z;
	return r;
}

Matrix Matrix::RotateX(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	Matrix r =
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f,    c,   -s, 0.0f },
		{ 0.0f,    s,    c, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	return r;
}

Matrix Matrix::RotateY(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	Matrix r =
	{
		{    c, 0.0f,    s, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{   -s, 0.0f,    c, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	return r;
}

Matrix Matrix::RotateZ(float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	Matrix r =
	{
		{    c,   -s, 0.0f, 0.0f },
		{    s,    c, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	return r;
}

Matrix Matrix::Scale(float x, float y, float z)
{
	Matrix r =
	{
		{    x, 0.0f, 0.0f, 0.0f },
		{ 0.0f,    y, 0.0f, 0.0f },
		{ 0.0f, 0.0f,    z, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	return r;
}

Matrix Matrix::Scale(const Vector3& s)
{
	Matrix r =
	{
		{  s.x, 0.0f, 0.0f, 0.0f },
		{ 0.0f,  s.y, 0.0f, 0.0f },
		{ 0.0f, 0.0f,  s.z, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	return r;
}

Matrix Matrix::Perspective(float fov, float aspect, float n, float f)
{
	Matrix r;
	float const a = 1.0f / tanf(fov / 2.0f);

	r[0][0] = a / aspect;
	r[0][1] = 0.0f;
	r[0][2] = 0.0f;
	r[0][3] = 0.0f;

	r[1][0] = 0.0f;
	r[1][1] = a;
	r[1][2] = 0.0f;
	r[1][3] = 0.0f;

	r[2][0] = 0.0f;
	r[2][1] = 0.0f;
	r[2][2] = f / (f - n);
	r[2][3] = 1.0f;

	r[3][0] = 0.0f;
	r[3][1] = 0.0f;
	r[3][2] = -(f * n) / (f - n);
	r[3][3] = 0.0f;

	return r;
}

Matrix Matrix::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
{
	Vector3 f = (center - eye).Normalized();
	Vector3 s = Vector3::Cross(up, f).Normalized();
	Vector3 t = Vector3::Cross(f, s);

	Matrix r(1.0f);
	r[0][0] = s[0]; r[0][1] = t[0]; r[0][2] = f[0];
	r[1][0] = s[1]; r[1][1] = t[1]; r[1][2] = f[1];
	r[2][0] = s[2]; r[2][1] = t[2]; r[2][2] = f[2];

	return Matrix::Translate(-eye.x, -eye.y, -eye.z) * r;
}

Matrix3::Matrix3(float f) :
	v()
{
	for (int i = 0; i < 3; i++)
		v[i][i] = f;
}

Matrix3::Matrix3(const Vector3& r1, const Vector3& r2, const Vector3& r3)
{
	v[0] = r1;
	v[1] = r2;
	v[2] = r3;
}

Matrix3& Matrix3::Transpose()
{
	Matrix3 c = *this;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			v[i][j] = c[j][i];
	return *this;
}

Matrix3 Matrix3::Transposed() const
{
	Matrix3 c;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			c[i][j] = v[j][i];
	return c;
}

const Vector3& Matrix3::operator[](unsigned char i) const
{
	return v[i];
}

Vector3& Matrix3::operator[](unsigned char i)
{
	return v[i];
}

Matrix3 Matrix3::operator*(const Matrix3& o) const
{
	Matrix3 r;
	for (int i = 0; i < 3; i++)
		for (int k = 0; k < 3; k++)
			for (int j = 0; j < 3; j++)
				r[i][j] += v[i][k] * o[k][j];
	return r;
}

Vector3 Matrix3::operator*(const Vector3& o) const
{
	Vector3 r;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			r[j] += o[i] * v[i][j];
	return r;
}