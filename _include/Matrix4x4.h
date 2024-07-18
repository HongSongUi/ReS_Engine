#pragma once
#include "Vector3D.h"
#define X_PI  3.141592f
#define DegreeToRadian(x) (x*(X_PI/180.0f))
#define RadianToDegree(x)(x*(180.0f/X_PI))
class Quat;
namespace MatrixEx {

	struct float4x4 {
		union {
			struct {
				float m11, m12, m13, m14;
				float m21, m22, m23, m24;
				float m31, m32, m33, m34;
				float m41, m42, m43, m44;
			};
			float mtx[4][4];
		};
	};
	class Matrix4x4 :public float4x4
	{
	public:
		Matrix4x4();
		void Identity();
		void RotationX(float rad);
		void RotationY(float rad);
		void RotationZ(float rad);
		void Scale(float x, float y, float z);
		void Translation(float x, float y, float z);
		Matrix4x4 Transpose();
		void ObjectLookAt(Vec3Ex::Vector3D& pos, Vec3Ex::Vector3D& target, Vec3Ex::Vector3D& up);
		Matrix4x4 ViewLookAt(Vec3Ex::Vector3D& pos, Vec3Ex::Vector3D& target, Vec3Ex::Vector3D& up);
		Matrix4x4 PerspectiveFovLH(float Near, float Far, float FoVy, float Aspect);
		Matrix4x4 OrthoLH(float width, float height, float Near, float Far);
		Matrix4x4 OrthoOffCenterLH(float left, float top, float right, float bottom, float Near, float Far);
		void CreateAxisAngle(Vec3Ex::Vector3D& axis, float rad);
		/*void MatrixAffineTransformation(Matrix4x4* Matout, float scale, Vec3Ex::Vector3D* Rc, 
			QuatEx::Quat* RotationQuat, Vec3Ex::Vector3D* translation);*/

	public:
		Matrix4x4 operator*(Matrix4x4& mat);
	};
}