#pragma once

#include <Math/Matrix.hpp>

namespace Nova
{
	struct NOVA_API Transform
	{
	public:
		enum Orientation : unsigned char
		{
			XYZ,
			XZY,
			YXZ,
			YZX,
			ZXY,
			ZYX
		};

		Nova::Math::Vector3 position = {};
		Nova::Math::Vector3 rotation = {};
		Nova::Math::Vector3 scale = { 1.0f };

		Nova::Math::Matrix3 GetBasis() const;
		Nova::Math::Matrix GetModel() const;
		Nova::Math::Matrix GetLookAt() const;
		Nova::Math::Matrix GetMVP() const;

		Orientation orientation = XYZ;

	private:
		friend class Camera;
		static Nova::Math::Matrix projection;
		static Nova::Math::Matrix view;
	};
}