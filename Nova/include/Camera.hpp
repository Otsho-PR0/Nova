#pragma once

#include <Nova.hpp>
#include <Transform.hpp>

namespace Nova
{
	struct NOVA_API Camera
	{
		void Update();

		float fov;
		float aspect;
		float n;
		float f;
		Transform transform;
	};
}