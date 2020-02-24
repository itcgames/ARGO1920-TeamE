#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

//
class Vector2
{
public:
	//
	Vector2(float px = 0, float py = 0) :
		x(px),
		y(py)
	{

	}

	//
	~Vector2()
	{

	}

	//
	Vector2 operator * (const float val) const
	{
		return Vector2(x * val, y * val);
	}

	//
	Vector2 operator - (const Vector2 vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	//
	Vector2 operator + (const Vector2 vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	//
	Vector2 operator / (const float& rhs)
	{
		return Vector2(x / rhs, y / rhs);
	}

	//
	Vector2& operator+=(const Vector2 vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	//
	bool operator!=(const Vector2& rhs)
	{
		return (x != rhs.x || y != rhs.y);
	}

	//
	bool operator==(const Vector2& rhs)
	{
		return (x == rhs.x && y == rhs.y);
	}

	//
	Vector2& operator*=(const float& x)
	{
		this->x *= x;
		this->y *= x;
		return *this;
	}

	//
	Vector2 normalize(Vector2 vector)
	{
		float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));

		// If calulated length is not equal to 0
		if (length != 0)
		{
			return Vector2(vector.x / length, vector.y / length);
		}

		else
		{
			return vector;
		}
	}


	float x, y;
};

#endif // !VECTOR2_H