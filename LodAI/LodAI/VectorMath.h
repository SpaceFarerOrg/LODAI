#pragma once
#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace VectorMath
{

	static float Length2(const sf::Vector2f& Vector)
	{
		return (Vector.x * Vector.x) + (Vector.y * Vector.y);
	}

	static float Length(const sf::Vector2f& Vector)
	{
		return sqrtf(Length2(Vector));
	}

	static float DistanceBetween(const sf::Vector2f& VectorOne, const sf::Vector2f& VectorTwo)
	{
		return Length(VectorOne - VectorTwo);
	}

	static float IsEqual(const sf::Vector2f& Vector, const sf::Vector2f& VectorTwo, float InPrecision = 0.0001f)
	{
		return DistanceBetween(Vector, VectorTwo) <= InPrecision ? true : false;
	}

	static void Normalize(sf::Vector2f& VectorToNormalize)
	{
		const float VectorLenght = Length(VectorToNormalize);

		if (VectorLenght < 0.0001f)
		{
			return;
		}

		VectorToNormalize.x /= VectorLenght;
		VectorToNormalize.y /= VectorLenght;
	}
}