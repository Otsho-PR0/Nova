#pragma once

#include <Math/Vec3.hpp>
#include <cmath>
#include <limits>

namespace Nova::Math
{
	constexpr float PI = 3.141592653589793f;
	constexpr float TwoPI = 6.283185307179586f;
	constexpr float HalfPI = 1.570796326794897f;
	constexpr float BreakPoint = 0.00001f;

	inline auto DegToRad(const auto& x)
	{
		return x * (PI / 180.0f);
	}

	inline auto RadToDeg(const auto& x)
	{
		return x * (180.0f / PI);
	}

	inline auto Min(const auto& a, const auto& b)
	{
		return (a < b) ? a : b;
	}

	inline auto Max(const auto& a, const auto& b)
	{
		return (a > b) ? a : b;
	}

	inline auto Lerp(const auto& from, const auto& to, float weight)
	{
		return from + (to - from) * weight;
	}

	inline auto Clamp(const auto& x, const auto& min, const auto& max)
	{
		return Min(Max(x, min), max);
	}

	inline Vector3 Clamp(const Vector3& x, const Vector3& min, const Vector3& max)
	{
		return { Clamp(x.x, min.x, max.x), Clamp(x.y, min.y, max.y), Clamp(x.z, min.z, max.z) };
	}

	inline auto ClampAngle(const auto& x)
	{
		if (!std::isfinite(x)) return x;
		auto r = std::fmod(x + PI, TwoPI);
		if (r < 0.0f) r += TwoPI;
		return r - PI;
	}

	inline Vector3 ClampAngle(const Vector3& x)
	{
		return { ClampAngle(x.x), ClampAngle(x.y), ClampAngle(x.z) };
	}

	inline auto MoveTowards(const auto& from, const auto& to, const auto& step)
	{
		return from + Clamp(to - from, -step, step);
	}

	inline float Lerp(const float& from, const float& to, const float& weight)
	{
		const float difference = to - from;
		if (std::abs(difference) < 0.00001f) return to;
		return from + difference * weight;
	}

	inline Vector3 Lerp(const Vector3& from, const Vector3& to, const float& weight)
	{
		return { Lerp(from.x, to.x, weight), Lerp(from.y, to.y, weight), Lerp(from.z, to.z, weight) };
	}

	inline auto LerpAngle(const auto& from, const auto& to, float weight)
	{
		auto difference = ClampAngle(to - from);
		if (!std::isfinite(difference)) return from;

		return ClampAngle(from + difference * weight);
	}

	inline Vector3 LerpAngle(const Vector3& from, const Vector3& to, float weight)
	{
		return { LerpAngle(from.x, to.x, weight), LerpAngle(from.y, to.y, weight), LerpAngle(from.z, to.z, weight) };
	}
}
