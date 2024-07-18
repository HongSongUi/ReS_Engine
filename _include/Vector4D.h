#pragma once
#include "math.h"
#define X_Epsilon 0.001
namespace VecEx {
	struct vec4D
	{
		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};
			float vec[4];
		};
	};

	class Vector4D : public vec4D
	{
	public:
		Vector4D();
		Vector4D(float x, float y, float z, float w);
		Vector4D(const Vector4D& v);
	public:
		Vector4D operator-(Vector4D& v);
		Vector4D operator+(Vector4D& v);
		Vector4D operator/(float scala);
		Vector4D operator*(float scala);
		bool	 operator>(Vector4D& v);
		bool	 operator<(Vector4D& v);
		bool	 operator<=(Vector4D& v);
		bool	 operator>=(Vector4D& v);
		bool	 operator!=(Vector4D& v);
		bool	 operator==(Vector4D& v);
	public:
		void	 Normalize();
		float	 LengthSqrt();
		float	 Length();
		Vector4D Identity();
	};
}