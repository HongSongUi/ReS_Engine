#pragma once
#include "Vector3D.h"
#include "Matrix4x4.h"

namespace QuatEx {
	struct quart {
		union
		{
			struct {
				float w;
				float x;
				float y;
				float z;
			};
			float quar[4];
		};
	};

	class Quat : public quart
	{
	private:
		void SetData(float w, float x, float y, float z);
		void SetData(float w, Vec3Ex::Vector3D& v);
	public:
		Quat();
		Quat(float w, float x, float y, float z);
		Quat(float w, Vec3Ex::Vector3D& v);
	public:
		Quat operator+(Quat& q);
		Quat operator-(Quat& q);
		Quat operator*(Quat& q);
		Quat operator*(float scala);
		Quat operator/ (float f);
		float operator| (Quat& q);
	public:
		void QuaternionToMatrixRotation(MatrixEx::Matrix4x4& mat);
		float Magnitude();
		Quat ConQuat();
		Quat Inverse();
		Quat Normalize();
		Quat CreateFromAxisAngle(Vec3Ex::Vector3D& axis, float rad);
		Quat CreateFromYawRollPitch(float yaw, float roll, float pitch);
	};

}