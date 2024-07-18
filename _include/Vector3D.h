#pragma once
#include "math.h"
class Matrix4x4;
namespace Vec3Ex {
	struct vec3D
	{
		union {
			struct {
				float x;
				float y;
				float z;
			};
			float vec[3];
		};
	};

	class Vector3D : public vec3D
	{
	public:
		Vector3D();
		Vector3D(float x, float y, float z);
		Vector3D(const Vector3D& v);
	public:
		Vector3D operator-(Vector3D& v);
		Vector3D operator+(Vector3D& v);
		Vector3D operator/(float scala);
		Vector3D operator*(float scala);
		bool	 operator>(Vector3D& v);
		bool	 operator<(Vector3D& v);
		bool	 operator<=(Vector3D& v);
		bool	 operator>=(Vector3D& v);
		bool	 operator!=(Vector3D& v);
		bool	 operator==(Vector3D& v);
		float operator| (Vector3D& v);
		Vector3D operator^(Vector3D& v);
		//Vector3D operator*(Matrix4x4& v);
	public:
		void	 Normalize();
		float	 LengthSqrt();
		float	 Length();
		Vector3D Identity();
	};
}