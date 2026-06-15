#include <Camera.hpp>

using namespace Nova;

void Camera::Update()
{
	Transform::projection = Math::Matrix::Perspective(fov, aspect, n, f);
	Transform::view = transform.GetLookAt();
}