#pragma once
#include "math.h"
#define X_Epsilon 0.001
namespace Vec2Ex {
	struct vec2D
	{
		union {
			struct {
				float x;
				float y;
			};
			float vec[2];
		};
	};

	class Vector2D : public vec2D
	{
	public:
		Vector2D();
		Vector2D(float x, float y);
		Vector2D(const Vector2D& v);
	public:
		Vector2D operator-(Vector2D& v);
		Vector2D operator+(Vector2D& v);
		Vector2D operator/(float scala);
		Vector2D operator*(float scala);
		bool	 operator>(Vector2D& v);
		bool	 operator<(Vector2D& v);
		bool	 operator<=(Vector2D& v);
		bool	 operator>=(Vector2D& v);
		bool	 operator!=(Vector2D& v);
		bool	 operator==(Vector2D& v);
	public:
		void	 Normalize();
		float	 LengthSqrt();
		float	 Length();
		Vector2D Identity();
	};
}