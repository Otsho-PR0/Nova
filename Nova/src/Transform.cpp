#include <Transform.hpp>

using namespace Nova;
using namespace Nova::Math;

Matrix Transform::projection;
Matrix Transform::view;

Matrix3 Transform::GetBasis() const
{
	switch (orientation)
	{
	case XYZ:
		return Matrix::RotateX(rotation.x) * Matrix::RotateY(rotation.y) * Matrix::RotateZ(rotation.z);
		break;
	case XZY:
		return Matrix::RotateX(rotation.x) * Matrix::RotateZ(rotation.z) * Matrix::RotateY(rotation.y);
		break;
	case YXZ:
		return Matrix::RotateY(rotation.y) * Matrix::RotateX(rotation.x) * Matrix::RotateZ(rotation.z);
		break;
	case YZX:
		return Matrix::RotateY(rotation.y) * Matrix::RotateZ(rotation.z) * Matrix::RotateX(rotation.x);
		break;
	case ZXY:
		return Matrix::RotateZ(rotation.z) * Matrix::RotateX(rotation.x) * Matrix::RotateY(rotation.y);
		break;
	case ZYX:
		return Matrix::RotateZ(rotation.z) * Matrix::RotateY(rotation.y) * Matrix::RotateX(rotation.x);
		break;
	}
}

Matrix Transform::GetModel() const
{
	switch (orientation)
	{
	case XYZ:
		return Matrix::Scale(scale) * Matrix::RotateX(rotation.x) * Matrix::RotateY(rotation.y) * Matrix::RotateZ(rotation.z) * Matrix::Translate(position);
		break;
	case XZY:
		return Matrix::Scale(scale) * Matrix::RotateX(rotation.x) * Matrix::RotateZ(rotation.z) * Matrix::RotateY(rotation.y) * Matrix::Translate(position);
		break;
	case YXZ:
		return Matrix::Scale(scale) * Matrix::RotateY(rotation.y) * Matrix::RotateX(rotation.x) * Matrix::RotateZ(rotation.z) * Matrix::Translate(position);
		break;
	case YZX:
		return Matrix::Scale(scale) * Matrix::RotateY(rotation.y) * Matrix::RotateZ(rotation.z) * Matrix::RotateX(rotation.x) * Matrix::Translate(position);
		break;
	case ZXY:
		return Matrix::Scale(scale) * Matrix::RotateZ(rotation.z) * Matrix::RotateX(rotation.x) * Matrix::RotateY(rotation.y) * Matrix::Translate(position);
		break;
	case ZYX:
		return Matrix::Scale(scale) * Matrix::RotateZ(rotation.z) * Matrix::RotateY(rotation.y) * Matrix::RotateX(rotation.x) * Matrix::Translate(position);
		break;
	}
}

Matrix Transform::GetLookAt() const
{
	return Matrix::LookAt(position, position + GetBasis() * Vector3::Forward, GetBasis() * Vector3::Up);
}

Matrix Transform::GetMVP() const
{
	return GetModel() * view * projection;
}