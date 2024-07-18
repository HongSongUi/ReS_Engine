#pragma once
#include <d3d11_1.h> 
//#include <d3dx11.h> 
#if !defined(__d3d11_h__) && !defined(__d3d11_x_h__) && !defined(__d3d12_h__) && !defined(__d3d12_x_h__)
#error include d3d11.h or d3d12.h before including TMath.h
#endif

#if !defined(_XBOX_ONE) || !defined(_TITLE)
//#include <dxgi1_2.h>
#endif

#include <functional>
#include <assert.h>
#include <memory.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#ifndef XM_CONSTEXPR
#define XM_CONSTEXPR
#endif

using namespace DirectX;
using namespace DirectX::PackedVector;

namespace X_BASIS_EX
{
	struct H_Vector2;
	struct H_Vector3;
	struct H_Vector4;
	struct H_Matrix;
	struct H_Quaternion;
	struct H_Plane;

	//------------------------------------------------------------------------------
	// 2D rectangle
	struct H_Rectangle
	{
		long x;
		long y;
		long width;
		long height;

		// Creators
		H_Rectangle() noexcept : x(0), y(0), width(0), height(0) {}
		XM_CONSTEXPR H_Rectangle(long ix, long iy, long iw, long ih) : x(ix), y(iy), width(iw), height(ih) {}
		explicit H_Rectangle(const RECT& rct) : x(rct.left), y(rct.top), width(rct.right - rct.left), height(rct.bottom - rct.top) {}

		H_Rectangle(const H_Rectangle&) = default;
		H_Rectangle& operator=(const H_Rectangle&) = default;

		H_Rectangle(H_Rectangle&&) = default;
		H_Rectangle& operator=(H_Rectangle&&) = default;

		operator RECT() { RECT rct; rct.left = x; rct.top = y; rct.right = (x + width); rct.bottom = (y + height); return rct; }
#ifdef __cplusplus_winrt
		operator Windows::Foundation::Rect() { return Windows::Foundation::Rect(float(x), float(y), float(width), float(height)); }
#endif

		// Comparison operators
		bool operator == (const H_Rectangle& r) const { return (x == r.x) && (y == r.y) && (width == r.width) && (height == r.height); }
		bool operator == (const RECT& rct) const { return (x == rct.left) && (y == rct.top) && (width == (rct.right - rct.left)) && (height == (rct.bottom - rct.top)); }

		bool operator != (const H_Rectangle& r) const { return (x != r.x) || (y != r.y) || (width != r.width) || (height != r.height); }
		bool operator != (const RECT& rct) const { return (x != rct.left) || (y != rct.top) || (width != (rct.right - rct.left)) || (height != (rct.bottom - rct.top)); }

		// Assignment operators
		H_Rectangle& operator=(_In_ const RECT& rct) { x = rct.left; y = rct.top; width = (rct.right - rct.left); height = (rct.bottom - rct.top); return *this; }

		// TRectangle operations
		H_Vector2 Location() const;
		H_Vector2 Center() const;

		bool IsEmpty() const { return (width == 0 && height == 0 && x == 0 && y == 0); }

		bool Contains(long ix, long iy) const { return (x <= ix) && (ix < (x + width)) && (y <= iy) && (iy < (y + height)); }
		bool Contains(const H_Vector2& point) const;
		bool Contains(const H_Rectangle& r) const { return (x <= r.x) && ((r.x + r.width) <= (x + width)) && (y <= r.y) && ((r.y + r.height) <= (y + height)); }
		bool Contains(const RECT& rct) const { return (x <= rct.left) && (rct.right <= (x + width)) && (y <= rct.top) && (rct.bottom <= (y + height)); }

		void Inflate(long horizAmount, long vertAmount);

		bool Intersects(const H_Rectangle& r) const { return (r.x < (x + width)) && (x < (r.x + r.width)) && (r.y < (y + height)) && (y < (r.y + r.height)); }
		bool Intersects(const RECT& rct) const { return (rct.left < (x + width)) && (x < rct.right) && (rct.top < (y + height)) && (y < rct.bottom); }

		void Offset(long ox, long oy) { x += ox; y += oy; }

		// Static functions
		static H_Rectangle Intersect(const H_Rectangle& ra, const H_Rectangle& rb);
		static RECT Intersect(const RECT& rcta, const RECT& rctb);

		static H_Rectangle Union(const H_Rectangle& ra, const H_Rectangle& rb);
		static RECT Union(const RECT& rcta, const RECT& rctb);
	};

	//------------------------------------------------------------------------------
	// 2D vector
	struct H_Vector2 : DirectX::XMFLOAT2
	{
		H_Vector2() noexcept : XMFLOAT2(0.f, 0.f) {}
		XM_CONSTEXPR explicit H_Vector2(float x) : XMFLOAT2(x, x) {}
		XM_CONSTEXPR H_Vector2(float _x, float _y) : XMFLOAT2(_x, _y) {}
		explicit H_Vector2(_In_reads_(2) const float *pArray) : XMFLOAT2(pArray) {}
		H_Vector2(XMFLOAT2 V) { x = V.x; y = V.y; }
		H_Vector2(const XMFLOAT2& V) { this->x = V.x; this->y = V.y; }
		explicit H_Vector2(const DirectX::XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; }

		H_Vector2(const H_Vector2&) = default;
		H_Vector2& operator=(const H_Vector2&) = default;

		H_Vector2(H_Vector2&&) = default;
		H_Vector2& operator=(H_Vector2&&) = default;

		operator DirectX::XMVECTOR() const { return XMLoadFloat2(this); }

		// Comparison operators
		bool operator == (const H_Vector2& V) const;
		bool operator != (const H_Vector2& V) const;

		// Assignment operators
		H_Vector2& operator= (const DirectX::XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; return *this; }
		H_Vector2& operator+= (const H_Vector2& V);
		H_Vector2& operator-= (const H_Vector2& V);
		H_Vector2& operator*= (const H_Vector2& V);
		H_Vector2& operator*= (float S);
		H_Vector2& operator/= (float S);

		// Unary operators
		H_Vector2 operator+ () const { return *this; }
		H_Vector2 operator- () const { return H_Vector2(-x, -y); }

		// Vector operations
		bool InBounds(const H_Vector2& Bounds) const;

		float Length() const;
		float LengthSquared() const;

		float Dot(const H_Vector2& V) const;
		void Cross(const H_Vector2& V, H_Vector2& result) const;
		H_Vector2 Cross(const H_Vector2& V) const;

		void Normalize();
		void Normalize(H_Vector2& result) const;

		void Clamp(const H_Vector2& vmin, const H_Vector2& vmax);
		void Clamp(const H_Vector2& vmin, const H_Vector2& vmax, H_Vector2& result) const;

		// Static functions
		static float Distance(const H_Vector2& v1, const H_Vector2& v2);
		static float DistanceSquared(const H_Vector2& v1, const H_Vector2& v2);

		static void Min(const H_Vector2& v1, const H_Vector2& v2, H_Vector2& result);
		static H_Vector2 Min(const H_Vector2& v1, const H_Vector2& v2);

		static void Max(const H_Vector2& v1, const H_Vector2& v2, H_Vector2& result);
		static H_Vector2 Max(const H_Vector2& v1, const H_Vector2& v2);

		static void Lerp(const H_Vector2& v1, const H_Vector2& v2, float t, H_Vector2& result);
		static H_Vector2 Lerp(const H_Vector2& v1, const H_Vector2& v2, float t);

		static void SmoothStep(const H_Vector2& v1, const H_Vector2& v2, float t, H_Vector2& result);
		static H_Vector2 SmoothStep(const H_Vector2& v1, const H_Vector2& v2, float t);

		static void Barycentric(const H_Vector2& v1, const H_Vector2& v2, const H_Vector2& v3, float f, float g, H_Vector2& result);
		static H_Vector2 Barycentric(const H_Vector2& v1, const H_Vector2& v2, const H_Vector2& v3, float f, float g);

		static void CatmullRom(const H_Vector2& v1, const H_Vector2& v2, const H_Vector2& v3, const H_Vector2& v4, float t, H_Vector2& result);
		static H_Vector2 CatmullRom(const H_Vector2& v1, const H_Vector2& v2, const H_Vector2& v3, const H_Vector2& v4, float t);

		static void Hermite(const H_Vector2& v1, const H_Vector2& t1, const H_Vector2& v2, const H_Vector2& t2, float t, H_Vector2& result);
		static H_Vector2 Hermite(const H_Vector2& v1, const H_Vector2& t1, const H_Vector2& v2, const H_Vector2& t2, float t);

		static void Reflect(const H_Vector2& ivec, const H_Vector2& nvec, H_Vector2& result);
		static H_Vector2 Reflect(const H_Vector2& ivec, const H_Vector2& nvec);

		static void Refract(const H_Vector2& ivec, const H_Vector2& nvec, float refractionIndex, H_Vector2& result);
		static H_Vector2 Refract(const H_Vector2& ivec, const H_Vector2& nvec, float refractionIndex);

		static void Transform(const H_Vector2& v, const H_Quaternion& quat, H_Vector2& result);
		static H_Vector2 Transform(const H_Vector2& v, const H_Quaternion& quat);

		static void Transform(const H_Vector2& v, const H_Matrix& m, H_Vector2& result);
		static H_Vector2 Transform(const H_Vector2& v, const H_Matrix& m);
		static void Transform(_In_reads_(count) const H_Vector2* varray, size_t count, const H_Matrix& m, _Out_writes_(count) H_Vector2* resultArray);

		static void Transform(const H_Vector2& v, const H_Matrix& m, H_Vector4& result);
		static void Transform(_In_reads_(count) const H_Vector2* varray, size_t count, const H_Matrix& m, _Out_writes_(count) H_Vector4* resultArray);

		static void TransformNormal(const H_Vector2& v, const H_Matrix& m, H_Vector2& result);
		static H_Vector2 TransformNormal(const H_Vector2& v, const H_Matrix& m);
		static void TransformNormal(_In_reads_(count) const H_Vector2* varray, size_t count, const H_Matrix& m, _Out_writes_(count) H_Vector2* resultArray);

		// Constants
		static const H_Vector2 Zero;
		static const H_Vector2 One;
		static const H_Vector2 UnitX;
		static const H_Vector2 UnitY;
	};

	// Binary operators
	H_Vector2 operator+ (const H_Vector2& V1, const H_Vector2& V2);
	H_Vector2 operator- (const H_Vector2& V1, const H_Vector2& V2);
	H_Vector2 operator* (const H_Vector2& V1, const H_Vector2& V2);
	H_Vector2 operator* (const H_Vector2& V, float S);
	H_Vector2 operator/ (const H_Vector2& V1, const H_Vector2& V2);
	H_Vector2 operator* (float S, const H_Vector2& V);

	//------------------------------------------------------------------------------
	// 3D vector
	struct H_Vector3 : DirectX::XMFLOAT3
	{
		H_Vector3() noexcept : DirectX::XMFLOAT3(0.f, 0.f, 0.f) {}
		XM_CONSTEXPR explicit H_Vector3(float x) : DirectX::XMFLOAT3(x, x, x) {}
		XM_CONSTEXPR H_Vector3(float _x, float _y, float _z) : DirectX::XMFLOAT3(_x, _y, _z) {}
		H_Vector3(const float *pArray) : DirectX::XMFLOAT3(pArray) {}
		H_Vector3(DirectX::XMFLOAT3 V) { x = V.x; y = V.y; z = V.z; }
		H_Vector3(const DirectX::XMFLOAT3& V) { this->x = V.x; this->y = V.y; this->z = V.z; }
		explicit H_Vector3(const DirectX::XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; }

		H_Vector3(const H_Vector3&) = default;
		H_Vector3& operator=(const H_Vector3&) = default;

		H_Vector3(H_Vector3&&) = default;
		H_Vector3& operator=(H_Vector3&&) = default;

		operator DirectX::XMVECTOR() const { return XMLoadFloat3(this); }

		float operator [](int i)
		{
			if (i == 0) return x;
			if (i == 1) return y;
			if (i == 2) return z;
			return 0.0f;
		}

		// Comparison operators
		bool operator == (const H_Vector3& V) const;
		bool operator != (const H_Vector3& V) const;

		// Assignment operators
		H_Vector3& operator= (const DirectX::XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; return *this; }
		H_Vector3& operator+= (const H_Vector3& V);
		H_Vector3& operator-= (const H_Vector3& V);
		H_Vector3& operator*= (const H_Vector3& V);
		H_Vector3& operator*= (float S);
		H_Vector3& operator/= (float S);

		// Unary operators
		H_Vector3 operator+ () const { return *this; }
		H_Vector3 operator- () const;

		// Vector operations
		bool InBounds(const H_Vector3& Bounds) const;

		float Length() const;
		float LengthSquared() const;

		float Dot(const H_Vector3& V) const;
		void Cross(const H_Vector3& V, H_Vector3& result) const;
		H_Vector3 Cross(const H_Vector3& V) const;

		void Normalize();
		void Normalize(H_Vector3& result) const;

		void Clamp(const H_Vector3& vmin, const H_Vector3& vmax);
		void Clamp(const H_Vector3& vmin, const H_Vector3& vmax, H_Vector3& result) const;

		// Static functions
		static float Distance(const H_Vector3& v1, const H_Vector3& v2);
		static float DistanceSquared(const H_Vector3& v1, const H_Vector3& v2);

		static void Min(const H_Vector3& v1, const H_Vector3& v2, H_Vector3& result);
		static H_Vector3 Min(const H_Vector3& v1, const H_Vector3& v2);

		static void Max(const H_Vector3& v1, const H_Vector3& v2, H_Vector3& result);
		static H_Vector3 Max(const H_Vector3& v1, const H_Vector3& v2);

		static void Lerp(const H_Vector3& v1, const H_Vector3& v2, float t, H_Vector3& result);
		static H_Vector3 Lerp(const H_Vector3& v1, const H_Vector3& v2, float t);

		static void SmoothStep(const H_Vector3& v1, const H_Vector3& v2, float t, H_Vector3& result);
		static H_Vector3 SmoothStep(const H_Vector3& v1, const H_Vector3& v2, float t);

		static void Barycentric(const H_Vector3& v1, const H_Vector3& v2, const H_Vector3& v3, float f, float g, H_Vector3& result);
		static H_Vector3 Barycentric(const H_Vector3& v1, const H_Vector3& v2, const H_Vector3& v3, float f, float g);

		static void CatmullRom(const H_Vector3& v1, const H_Vector3& v2, const H_Vector3& v3, const H_Vector3& v4, float t, H_Vector3& result);
		static H_Vector3 CatmullRom(const H_Vector3& v1, const H_Vector3& v2, const H_Vector3& v3, const H_Vector3& v4, float t);

		static void Hermite(const H_Vector3& v1, const H_Vector3& t1, const H_Vector3& v2, const H_Vector3& t2, float t, H_Vector3& result);
		static H_Vector3 Hermite(const H_Vector3& v1, const H_Vector3& t1, const H_Vector3& v2, const H_Vector3& t2, float t);

		static void Reflect(const H_Vector3& ivec, const H_Vector3& nvec, H_Vector3& result);
		static H_Vector3 Reflect(const H_Vector3& ivec, const H_Vector3& nvec);

		static void Refract(const H_Vector3& ivec, const H_Vector3& nvec, float refractionIndex, H_Vector3& result);
		static H_Vector3 Refract(const H_Vector3& ivec, const H_Vector3& nvec, float refractionIndex);

		static void Transform(const H_Vector3& v, const H_Quaternion& quat, H_Vector3& result);
		static H_Vector3 Transform(const H_Vector3& v, const H_Quaternion& quat);

		static void Transform(const H_Vector3& v, const H_Matrix& m, H_Vector3& result);
		static H_Vector3 Transform(const H_Vector3& v, const H_Matrix& m);
		static void Transform(_In_reads_(count) const H_Vector3* varray, size_t count, const H_Matrix& m, _Out_writes_(count) H_Vector3* resultArray);

		static void Transform(const H_Vector3& v, const H_Matrix& m, H_Vector4& result);
		static void Transform(_In_reads_(count) const H_Vector3* varray, size_t count, const H_Matrix& m, _Out_writes_(count) H_Vector4* resultArray);

		static void TransformNormal(const H_Vector3& v, const H_Matrix& m, H_Vector3& result);
		static H_Vector3 TransformNormal(const H_Vector3& v, const H_Matrix& m);
		static void TransformNormal(_In_reads_(count) const H_Vector3* varray, size_t count, const H_Matrix& m, _Out_writes_(count) H_Vector3* resultArray);

		// Constants
		static const H_Vector3 Zero;
		static const H_Vector3 One;
		static const H_Vector3 UnitX;
		static const H_Vector3 UnitY;
		static const H_Vector3 UnitZ;
		static const H_Vector3 Up;
		static const H_Vector3 Down;
		static const H_Vector3 Right;
		static const H_Vector3 Left;
		static const H_Vector3 Forward;
		static const H_Vector3 Backward;
	};

	// Binary operators
	H_Vector3 operator+ (const H_Vector3& V1, const H_Vector3& V2);
	H_Vector3 operator- (const H_Vector3& V1, const H_Vector3& V2);
	H_Vector3 operator* (const H_Vector3& V1, const H_Vector3& V2);
	H_Vector3 operator* (const H_Vector3& V, float S);
	H_Vector3 operator/ (const H_Vector3& V1, const H_Vector3& V2);
	H_Vector3 operator* (float S, const H_Vector3& V);

	//------------------------------------------------------------------------------
	// 4D vector
	struct H_Vector4 : public XMFLOAT4
	{
		H_Vector4() noexcept : XMFLOAT4(0.f, 0.f, 0.f, 0.f) {}
		XM_CONSTEXPR explicit H_Vector4(float x) : XMFLOAT4(x, x, x, x) {}
		XM_CONSTEXPR H_Vector4(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
		explicit H_Vector4(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
		H_Vector4(XMFLOAT4 V) { x = V.x; y = V.y; z = V.z; w = V.w; }
		H_Vector4(const XMFLOAT4& V) { this->x = V.x; this->y = V.y; this->z = V.z; this->w = V.w; }
		explicit H_Vector4(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		H_Vector4(const H_Vector4&) = default;
		H_Vector4& operator=(const H_Vector4&) = default;

		H_Vector4(H_Vector4&&) = default;
		H_Vector4& operator=(H_Vector4&&) = default;

		operator XMVECTOR() const { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator == (const H_Vector4& V) const;
		bool operator != (const H_Vector4& V) const;

		// Assignment operators
		H_Vector4& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
		H_Vector4& operator+= (const H_Vector4& V);
		H_Vector4& operator-= (const H_Vector4& V);
		H_Vector4& operator*= (const H_Vector4& V);
		H_Vector4& operator*= (float S);
		H_Vector4& operator/= (float S);

		// Unary operators
		H_Vector4 operator+ () const { return *this; }
		H_Vector4 operator- () const;

		// Vector operations
		bool InBounds(const H_Vector4& Bounds) const;

		float Length() const;
		float LengthSquared() const;

		float Dot(const H_Vector4& V) const;
		void Cross(const H_Vector4& v1, const H_Vector4& v2, H_Vector4& result) const;
		H_Vector4 Cross(const H_Vector4& v1, const H_Vector4& v2) const;

		void Normalize();
		void Normalize(H_Vector4& result) const;

		void Clamp(const H_Vector4& vmin, const H_Vector4& vmax);
		void Clamp(const H_Vector4& vmin, const H_Vector4& vmax, H_Vector4& result) const;

		// Static functions
		static float Distance(const H_Vector4& v1, const H_Vector4& v2);
		static float DistanceSquared(const H_Vector4& v1, const H_Vector4& v2);

		static void Min(const H_Vector4& v1, const H_Vector4& v2, H_Vector4& result);
		static H_Vector4 Min(const H_Vector4& v1, const H_Vector4& v2);

		static void Max(const H_Vector4& v1, const H_Vector4& v2, H_Vector4& result);
		static H_Vector4 Max(const H_Vector4& v1, const H_Vector4& v2);

		static void Lerp(const H_Vector4& v1, const H_Vector4& v2, float t, H_Vector4& result);
		static H_Vector4 Lerp(const H_Vector4& v1, const H_Vector4& v2, float t);

		static void SmoothStep(const H_Vector4& v1, const H_Vector4& v2, float t, H_Vector4& result);
		static H_Vector4 SmoothStep(const H_Vector4& v1, const H_Vector4& v2, float t);

		static void Barycentric(const H_Vector4& v1, const H_Vector4& v2, const H_Vector4& v3, float f, float g, H_Vector4& result);
		static H_Vector4 Barycentric(const H_Vector4& v1, const H_Vector4& v2, const H_Vector4& v3, float f, float g);

		static void CatmullRom(const H_Vector4& v1, const H_Vector4& v2, const H_Vector4& v3, const H_Vector4& v4, float t, H_Vector4& result);
		static H_Vector4 CatmullRom(const H_Vector4& v1, const H_Vector4& v2, const H_Vector4& v3, const H_Vector4& v4, float t);

		static void Hermite(const H_Vector4& v1, const H_Vector4& t1, const H_Vector4& v2, const H_Vector4& t2, float t, H_Vector4& result);
		static H_Vector4 Hermite(const H_Vector4& v1, const H_Vector4& t1, const H_Vector4& v2, const H_Vector4& t2, float t);

		static void Reflect(const H_Vector4& ivec, const H_Vector4& nvec, H_Vector4& result);
		static H_Vector4 Reflect(const H_Vector4& ivec, const H_Vector4& nvec);

		static void Refract(const H_Vector4& ivec, const H_Vector4& nvec, float refractionIndex, H_Vector4& result);
		static H_Vector4 Refract(const H_Vector4& ivec, const H_Vector4& nvec, float refractionIndex);

		static void Transform(const H_Vector2& v, const H_Quaternion& quat, H_Vector4& result);
		static H_Vector4 Transform(const H_Vector2& v, const H_Quaternion& quat);

		static void Transform(const H_Vector3& v, const H_Quaternion& quat, H_Vector4& result);
		static H_Vector4 Transform(const H_Vector3& v, const H_Quaternion& quat);

		static void Transform(const H_Vector4& v, const H_Quaternion& quat, H_Vector4& result);
		static H_Vector4 Transform(const H_Vector4& v, const H_Quaternion& quat);

		static void Transform(const H_Vector4& v, const H_Matrix& m, H_Vector4& result);
		static H_Vector4 Transform(const H_Vector4& v, const H_Matrix& m);
		static void Transform(_In_reads_(count) const H_Vector4* varray, size_t count, const H_Matrix& m, _Out_writes_(count) H_Vector4* resultArray);

		// Constants
		static const H_Vector4 Zero;
		static const H_Vector4 One;
		static const H_Vector4 UnitX;
		static const H_Vector4 UnitY;
		static const H_Vector4 UnitZ;
		static const H_Vector4 UnitW;
	};

	// Binary operators
	H_Vector4 operator+ (const H_Vector4& V1, const H_Vector4& V2);
	H_Vector4 operator- (const H_Vector4& V1, const H_Vector4& V2);
	H_Vector4 operator* (const H_Vector4& V1, const H_Vector4& V2);
	H_Vector4 operator* (const H_Vector4& V, float S);
	H_Vector4 operator/ (const H_Vector4& V1, const H_Vector4& V2);
	H_Vector4 operator* (float S, const H_Vector4& V);

	//------------------------------------------------------------------------------
	// 4x4 TMatrix (assumes right-handed cooordinates)
	struct H_Matrix : public XMFLOAT4X4
	{
		H_Matrix() noexcept
			: XMFLOAT4X4(1.f, 0, 0, 0,
				0, 1.f, 0, 0,
				0, 0, 1.f, 0,
				0, 0, 0, 1.f) {}
		XM_CONSTEXPR H_Matrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
			: XMFLOAT4X4(m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33) {}
		explicit H_Matrix(const H_Vector3& r0, const H_Vector3& r1, const H_Vector3& r2)
			: XMFLOAT4X4(r0.x, r0.y, r0.z, 0,
				r1.x, r1.y, r1.z, 0,
				r2.x, r2.y, r2.z, 0,
				0, 0, 0, 1.f) {}
		explicit H_Matrix(const H_Vector4& r0, const H_Vector4& r1, const H_Vector4& r2, const H_Vector4& r3)
			: XMFLOAT4X4(r0.x, r0.y, r0.z, r0.w,
				r1.x, r1.y, r1.z, r1.w,
				r2.x, r2.y, r2.z, r2.w,
				r3.x, r3.y, r3.z, r3.w) {}
		H_Matrix(const XMFLOAT4X4& M) { memcpy_s(this, sizeof(float) * 16, &M, sizeof(XMFLOAT4X4)); }
		H_Matrix(const XMFLOAT3X3& M);
		H_Matrix(const XMFLOAT4X3& M);

		explicit H_Matrix(_In_reads_(16) const float *pArray) : XMFLOAT4X4(pArray) {}
		H_Matrix(CXMMATRIX M) { XMStoreFloat4x4(this, M); }

		H_Matrix(const H_Matrix&) = default;
		H_Matrix& operator=(const H_Matrix&) = default;

		H_Matrix(H_Matrix&&) = default;
		H_Matrix& operator=(H_Matrix&&) = default;

		operator XMFLOAT4X4() const { return *this; }

		// Comparison operators
		bool operator == (const H_Matrix& M) const;
		bool operator != (const H_Matrix& M) const;

		// Assignment operators
		H_Matrix& operator= (const XMFLOAT3X3& M);
		H_Matrix& operator= (const XMFLOAT4X3& M);
		H_Matrix& operator+= (const H_Matrix& M);
		H_Matrix& operator-= (const H_Matrix& M);
		H_Matrix& operator*= (const H_Matrix& M);
		H_Matrix& operator*= (float S);
		H_Matrix& operator/= (float S);

		H_Matrix& operator/= (const H_Matrix& M);
		// Element-wise divide

		// Unary operators
		H_Matrix operator+ () const { return *this; }
		H_Matrix operator- () const;

		// Properties
		H_Vector3 Up() const { return H_Vector3(_21, _22, _23); }
		void Up(const H_Vector3& v) { _21 = v.x; _22 = v.y; _23 = v.z; }

		H_Vector3 Down() const { return H_Vector3(-_21, -_22, -_23); }
		void Down(const H_Vector3& v) { _21 = -v.x; _22 = -v.y; _23 = -v.z; }

		H_Vector3 Right() const { return H_Vector3(_11, _12, _13); }
		void Right(const H_Vector3& v) { _11 = v.x; _12 = v.y; _13 = v.z; }

		H_Vector3 Left() const { return H_Vector3(-_11, -_12, -_13); }
		void Left(const H_Vector3& v) { _11 = -v.x; _12 = -v.y; _13 = -v.z; }

		H_Vector3 Forward() const { return H_Vector3(-_31, -_32, -_33); }
		void Forward(const H_Vector3& v) { _31 = -v.x; _32 = -v.y; _33 = -v.z; }

		H_Vector3 Backward() const { return H_Vector3(_31, _32, _33); }
		void Backward(const H_Vector3& v) { _31 = v.x; _32 = v.y; _33 = v.z; }

		H_Vector3 Translation() const { return H_Vector3(_41, _42, _43); }
		void Translation(const H_Vector3& v) { _41 = v.x; _42 = v.y; _43 = v.z; }

		// TMatrix operations
		bool Decompose(H_Vector3& scale, H_Quaternion& rotation, H_Vector3& translation);

		H_Matrix Transpose() const;
		void Transpose(H_Matrix& result) const;

		H_Matrix Invert() const;
		void Invert(H_Matrix& result) const;

		float Determinant() const;

		// Static functions
		static H_Matrix CreateBillboard(const H_Vector3& object, const H_Vector3& cameraPosition, const H_Vector3& cameraUp, _In_opt_ const H_Vector3* cameraForward = nullptr);

		static H_Matrix CreateConstrainedBillboard(const H_Vector3& object, const H_Vector3& cameraPosition, const H_Vector3& rotateAxis,
			_In_opt_ const H_Vector3* cameraForward = nullptr, _In_opt_ const H_Vector3* objectForward = nullptr);

		static H_Matrix CreateTranslation(const H_Vector3& position);
		static H_Matrix CreateTranslation(float x, float y, float z);

		static H_Matrix CreateScale(const H_Vector3& scales);
		static H_Matrix CreateScale(float xs, float ys, float zs);
		static H_Matrix CreateScale(float scale);

		static H_Matrix CreateRotationX(float radians);
		static H_Matrix CreateRotationY(float radians);
		static H_Matrix CreateRotationZ(float radians);

		static H_Matrix CreateFromAxisAngle(const H_Vector3& axis, float angle);

		static H_Matrix CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane);
		static H_Matrix CreatePerspective(float width, float height, float nearPlane, float farPlane);
		static H_Matrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane);
		static H_Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
		static H_Matrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);

		static H_Matrix CreateLookAt(const H_Vector3& position, const H_Vector3& target, const H_Vector3& up);
		static H_Matrix CreateWorld(const H_Vector3& position, const H_Vector3& forward, const H_Vector3& up);

		static H_Matrix CreateFromQuaternion(const H_Quaternion& quat);

		static H_Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);

		static H_Matrix CreateShadow(const H_Vector3& lightDir, const H_Plane& plane);

		static H_Matrix CreateReflection(const H_Plane& plane);

		static void Lerp(const H_Matrix& M1, const H_Matrix& M2, float t, H_Matrix& result);
		static H_Matrix Lerp(const H_Matrix& M1, const H_Matrix& M2, float t);

		static void Transform(const H_Matrix& M, const H_Quaternion& rotation, H_Matrix& result);
		static H_Matrix Transform(const H_Matrix& M, const H_Quaternion& rotation);

		// Constants
		static const H_Matrix Identity;
	};

	// Binary operators
	H_Matrix operator+ (const H_Matrix& M1, const H_Matrix& M2);
	H_Matrix operator- (const H_Matrix& M1, const H_Matrix& M2);
	H_Matrix operator* (const H_Matrix& M1, const H_Matrix& M2);
	H_Matrix operator* (const H_Matrix& M, float S);
	H_Matrix operator/ (const H_Matrix& M, float S);
	H_Matrix operator/ (const H_Matrix& M1, const H_Matrix& M2);
	// Element-wise divide
	H_Matrix operator* (float S, const H_Matrix& M);


	//-----------------------------------------------------------------------------
	// TPlane
	struct H_Plane : public XMFLOAT4
	{
		H_Plane() noexcept : XMFLOAT4(0.f, 1.f, 0.f, 0.f) {}
		XM_CONSTEXPR H_Plane(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
		H_Plane(const H_Vector3& normal, float d) : XMFLOAT4(normal.x, normal.y, normal.z, d) {}
		H_Plane(const H_Vector3& point1, const H_Vector3& point2, const H_Vector3& point3);
		H_Plane(const H_Vector3& point, const H_Vector3& normal);
		explicit H_Plane(const H_Vector4& v) : XMFLOAT4(v.x, v.y, v.z, v.w) {}
		explicit H_Plane(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
		H_Plane(XMFLOAT4 V) { x = V.x; y = V.y; z = V.z; w = V.w; }
		H_Plane(const XMFLOAT4& p) { this->x = p.x; this->y = p.y; this->z = p.z; this->w = p.w; }
		explicit H_Plane(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		H_Plane(const H_Plane&) = default;
		H_Plane& operator=(const H_Plane&) = default;

		H_Plane(H_Plane&&) = default;
		H_Plane& operator=(H_Plane&&) = default;

		operator XMVECTOR() const { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator == (const H_Plane& p) const;
		bool operator != (const H_Plane& p) const;

		// Assignment operators
		H_Plane& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }

		// Properties
		H_Vector3 Normal() const { return H_Vector3(x, y, z); }
		void Normal(const H_Vector3& normal) { x = normal.x; y = normal.y; z = normal.z; }

		float D() const { return w; }
		void D(float d) { w = d; }

		// TPlane operations
		void Normalize();
		void Normalize(H_Plane& result) const;

		float Dot(const H_Vector4& v) const;
		float DotCoordinate(const H_Vector3& position) const;
		float DotNormal(const H_Vector3& normal) const;

		// Static functions
		static void Transform(const H_Plane& plane, const H_Matrix& M, H_Plane& result);
		static H_Plane Transform(const H_Plane& plane, const H_Matrix& M);

		static void Transform(const H_Plane& plane, const H_Quaternion& rotation, H_Plane& result);
		static H_Plane Transform(const H_Plane& plane, const H_Quaternion& rotation);
		// Input quaternion must be the inverse transpose of the transformation
	};

	//------------------------------------------------------------------------------
	// TQuaternion
	struct H_Quaternion : public XMFLOAT4
	{
		H_Quaternion() noexcept : XMFLOAT4(0, 0, 0, 1.f) {}
		XM_CONSTEXPR H_Quaternion(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
		H_Quaternion(const H_Vector3& v, float scalar) : XMFLOAT4(v.x, v.y, v.z, scalar) {}
		explicit H_Quaternion(const H_Vector4& v) : XMFLOAT4(v.x, v.y, v.z, v.w) {}
		explicit H_Quaternion(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
		H_Quaternion(XMFLOAT4 V) { x = V.x; y = V.y; z = V.z; w = V.w; }
		H_Quaternion(const XMFLOAT4& q) { this->x = q.x; this->y = q.y; this->z = q.z; this->w = q.w; }
		explicit H_Quaternion(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		H_Quaternion(const H_Quaternion&) = default;
		H_Quaternion& operator=(const H_Quaternion&) = default;

		H_Quaternion(H_Quaternion&&) = default;
		H_Quaternion& operator=(H_Quaternion&&) = default;

		//operator int () const { return 0; }
		//SampleClass f;
		//int i = f; //  f.operator int () 를 호출하고 초기화 및 반한됨.
		operator XMVECTOR() const { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator == (const H_Quaternion& q) const;
		bool operator != (const H_Quaternion& q) const;

		// Assignment operators
		H_Quaternion& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
		H_Quaternion& operator+= (const H_Quaternion& q);
		H_Quaternion& operator-= (const H_Quaternion& q);
		H_Quaternion& operator*= (const H_Quaternion& q);
		H_Quaternion& operator*= (float S);
		H_Quaternion& operator/= (const H_Quaternion& q);

		// Unary operators
		H_Quaternion operator+ () const { return *this; }
		H_Quaternion operator- () const;

		// TQuaternion operations
		float Length() const;
		float LengthSquared() const;

		void Normalize();
		void Normalize(H_Quaternion& result) const;

		void Conjugate();
		void Conjugate(H_Quaternion& result) const;

		void Inverse(H_Quaternion& result) const;

		float Dot(const H_Quaternion& Q) const;

		// Static functions
		static H_Quaternion CreateFromAxisAngle(const H_Vector3& axis, float angle);
		static H_Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static H_Quaternion CreateFromRotationMatrix(const H_Matrix& M);

		static void Lerp(const H_Quaternion& q1, const H_Quaternion& q2, float t, H_Quaternion& result);
		static H_Quaternion Lerp(const H_Quaternion& q1, const H_Quaternion& q2, float t);

		static void Slerp(const H_Quaternion& q1, const H_Quaternion& q2, float t, H_Quaternion& result);
		static H_Quaternion Slerp(const H_Quaternion& q1, const H_Quaternion& q2, float t);

		static void Concatenate(const H_Quaternion& q1, const H_Quaternion& q2, H_Quaternion& result);
		static H_Quaternion Concatenate(const H_Quaternion& q1, const H_Quaternion& q2);

		// Constants
		static const H_Quaternion Identity;
	};

	// Binary operators
	H_Quaternion operator+ (const H_Quaternion& Q1, const H_Quaternion& Q2);
	H_Quaternion operator- (const H_Quaternion& Q1, const H_Quaternion& Q2);
	H_Quaternion operator* (const H_Quaternion& Q1, const H_Quaternion& Q2);
	H_Quaternion operator* (const H_Quaternion& Q, float S);
	H_Quaternion operator/ (const H_Quaternion& Q1, const H_Quaternion& Q2);
	H_Quaternion operator* (float S, const H_Quaternion& Q);

	//------------------------------------------------------------------------------
	// TColor
	struct H_Color : public XMFLOAT4
	{
		H_Color() noexcept : XMFLOAT4(0, 0, 0, 1.f) {}
		XM_CONSTEXPR H_Color(float _r, float _g, float _b) : XMFLOAT4(_r, _g, _b, 1.f) {}
		XM_CONSTEXPR H_Color(float _r, float _g, float _b, float _a) : XMFLOAT4(_r, _g, _b, _a) {}
		explicit H_Color(const H_Vector3& clr) : XMFLOAT4(clr.x, clr.y, clr.z, 1.f) {}
		explicit H_Color(const H_Vector4& clr) : XMFLOAT4(clr.x, clr.y, clr.z, clr.w) {}
		explicit H_Color(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
		H_Color(XMFLOAT3 V) { x = V.x; y = V.y; z = V.z; }
		H_Color(const XMFLOAT4& c) { this->x = c.x; this->y = c.y; this->z = c.z; this->w = c.w; }
		explicit H_Color(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		explicit H_Color(const DirectX::PackedVector::XMCOLOR& Packed);
		// BGRA Direct3D 9 D3DCOLOR packed color

		explicit H_Color(const DirectX::PackedVector::XMUBYTEN4& Packed);
		// RGBA XNA Game Studio packed color

		H_Color(const H_Color&) = default;
		H_Color& operator=(const H_Color&) = default;

		H_Color(H_Color&&) = default;
		H_Color& operator=(H_Color&&) = default;

		operator XMVECTOR() const { return XMLoadFloat4(this); }
		operator const float*() const { return reinterpret_cast<const float*>(this); }

		// Comparison operators
		bool operator == (const H_Color& c) const;
		bool operator != (const H_Color& c) const;

		// Assignment operators
		H_Color& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
		H_Color& operator= (const DirectX::PackedVector::XMCOLOR& Packed);
		H_Color& operator= (const DirectX::PackedVector::XMUBYTEN4& Packed);
		H_Color& operator+= (const H_Color& c);
		H_Color& operator-= (const H_Color& c);
		H_Color& operator*= (const H_Color& c);
		H_Color& operator*= (float S);
		H_Color& operator/= (const H_Color& c);

		// Unary operators
		H_Color operator+ () const { return *this; }
		H_Color operator- () const;

		// Properties
		float R() const { return x; }
		void R(float r) { x = r; }

		float G() const { return y; }
		void G(float g) { y = g; }

		float B() const { return z; }
		void B(float b) { z = b; }

		float A() const { return w; }
		void A(float a) { w = a; }

		// TColor operations
		DirectX::PackedVector::XMCOLOR BGRA() const;
		DirectX::PackedVector::XMUBYTEN4 RGBA() const;

		H_Vector3 ToVector3() const;
		H_Vector4 ToVector4() const;

		void Negate();
		void Negate(H_Color& result) const;

		void Saturate();
		void Saturate(H_Color& result) const;

		void Premultiply();
		void Premultiply(H_Color& result) const;

		void AdjustSaturation(float sat);
		void AdjustSaturation(float sat, H_Color& result) const;

		void AdjustContrast(float contrast);
		void AdjustContrast(float contrast, H_Color& result) const;

		// Static functions
		static void Modulate(const H_Color& c1, const H_Color& c2, H_Color& result);
		static H_Color Modulate(const H_Color& c1, const H_Color& c2);

		static void Lerp(const H_Color& c1, const H_Color& c2, float t, H_Color& result);
		static H_Color Lerp(const H_Color& c1, const H_Color& c2, float t);
	};

	// Binary operators
	H_Color operator+ (const H_Color& C1, const H_Color& C2);
	H_Color operator- (const H_Color& C1, const H_Color& C2);
	H_Color operator* (const H_Color& C1, const H_Color& C2);
	H_Color operator* (const H_Color& C, float S);
	H_Color operator/ (const H_Color& C1, const H_Color& C2);
	H_Color operator* (float S, const H_Color& C);

	//------------------------------------------------------------------------------
	// TRay
	class H_Ray
	{
	public:
		H_Vector3 position;
		H_Vector3 direction;

		H_Ray() noexcept : position(0, 0, 0), direction(0, 0, 1) {}
		H_Ray(const H_Vector3& pos, const H_Vector3& dir) : position(pos), direction(dir) {}

		H_Ray(const H_Ray&) = default;
		H_Ray& operator=(const H_Ray&) = default;

		H_Ray(H_Ray&&) = default;
		H_Ray& operator=(H_Ray&&) = default;

		// Comparison operators
		bool operator == (const H_Ray& r) const;
		bool operator != (const H_Ray& r) const;

		// TRay operations
		bool Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const;
		bool Intersects(const BoundingBox& box, _Out_ float& Dist) const;
		bool Intersects(const H_Vector3& tri0, const H_Vector3& tri1, const H_Vector3& tri2, _Out_ float& Dist) const;
		bool Intersects(const H_Plane& plane, _Out_ float& Dist) const;
	};

	//------------------------------------------------------------------------------
	// TViewport
	class H_Viewport
	{
	public:
		float x;
		float y;
		float width;
		float height;
		float minDepth;
		float maxDepth;

		H_Viewport() noexcept :
			x(0.f), y(0.f), width(0.f), height(0.f), minDepth(0.f), maxDepth(1.f) {}
		XM_CONSTEXPR H_Viewport(float ix, float iy, float iw, float ih, float iminz = 0.f, float imaxz = 1.f) :
			x(ix), y(iy), width(iw), height(ih), minDepth(iminz), maxDepth(imaxz) {}
		explicit H_Viewport(const RECT& rct) :
			x(float(rct.left)), y(float(rct.top)),
			width(float(rct.right - rct.left)),
			height(float(rct.bottom - rct.top)),
			minDepth(0.f), maxDepth(1.f) {}

#if defined(__d3d11_h__) || defined(__d3d11_x_h__)
		// Direct3D 11 interop
		explicit H_Viewport(const D3D11_VIEWPORT& vp) :
			x(vp.TopLeftX), y(vp.TopLeftY),
			width(vp.Width), height(vp.Height),
			minDepth(vp.MinDepth), maxDepth(vp.MaxDepth) {}

		operator D3D11_VIEWPORT() { return *reinterpret_cast<const D3D11_VIEWPORT*>(this); }
		const D3D11_VIEWPORT* Get11() const { return reinterpret_cast<const D3D11_VIEWPORT*>(this); }
		H_Viewport& operator= (const D3D11_VIEWPORT& vp);
#endif

#if defined(__d3d12_h__) || defined(__d3d12_x_h__)
		// Direct3D 12 interop
		explicit TViewport(const D3D12_VIEWPORT& vp) :
			x(vp.TopLeftX), y(vp.TopLeftY),
			width(vp.Width), height(vp.Height),
			minDepth(vp.MinDepth), maxDepth(vp.MaxDepth) {}

		operator D3D12_VIEWPORT() { return *reinterpret_cast<const D3D12_VIEWPORT*>(this); }
		const D3D12_VIEWPORT* Get12() const { return reinterpret_cast<const D3D12_VIEWPORT*>(this); }
		TViewport& operator= (const D3D12_VIEWPORT& vp);
#endif

		H_Viewport(const H_Viewport&) = default;
		H_Viewport& operator=(const H_Viewport&) = default;

		H_Viewport(H_Viewport&&) = default;
		H_Viewport& operator=(H_Viewport&&) = default;

		// Comparison operators
		bool operator == (const H_Viewport& vp) const;
		bool operator != (const H_Viewport& vp) const;

		// Assignment operators
		H_Viewport& operator= (const RECT& rct);

		// TViewport operations
		float AspectRatio() const;

		H_Vector3 Project(const H_Vector3& p, const H_Matrix& proj, const H_Matrix& view, const H_Matrix& world) const;
		void Project(const H_Vector3& p, const H_Matrix& proj, const H_Matrix& view, const H_Matrix& world, H_Vector3& result) const;

		H_Vector3 Unproject(const H_Vector3& p, const H_Matrix& proj, const H_Matrix& view, const H_Matrix& world) const;
		void Unproject(const H_Vector3& p, const H_Matrix& proj, const H_Matrix& view, const H_Matrix& world, H_Vector3& result) const;

		// Static methods
		static RECT __cdecl ComputeDisplayArea(DXGI_SCALING scaling, UINT backBufferWidth, UINT backBufferHeight, int outputWidth, int outputHeight);
		static RECT __cdecl ComputeTitleSafeArea(UINT backBufferWidth, UINT backBufferHeight);
	};

	
	///////////////////////////////////////// static ///////////////////////////////////////////
	//https://docs.microsoft.com/en-us/windows/win32/dxmath/pg-xnamath-migration-d3dx
	//--------------------------
	// 2D Vector
	//--------------------------

	static float D3DXVec2Length(CONST H_Vector2 *pV)
	{
		return pV->Length();
	}

	static float D3DXVec2LengthSq(CONST H_Vector2 *pV)
	{
		return 0.0f;
	}

	static float D3DXVec2Dot(CONST H_Vector2 *pV1, CONST H_Vector2 *pV2)
	{
		return 0.0f;
	}

	// Z component of ((x1,y1,0) cross (x2,y2,0))
	static float D3DXVec2CCW(CONST H_Vector2 *pV1, CONST H_Vector2 *pV2)
	{
		return 0.0f;
	}

	static H_Vector2* D3DXVec2Add(H_Vector2 *pOut, CONST H_Vector2 *pV1, CONST H_Vector2 *pV2)
	{
		return pOut;
	}

	static H_Vector2* D3DXVec2Subtract(H_Vector2 *pOut, CONST H_Vector2 *pV1, CONST H_Vector2 *pV2)
	{
		return pOut;
	}

	// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
	static H_Vector2* D3DXVec2Minimize(H_Vector2 *pOut, CONST H_Vector2 *pV1, CONST H_Vector2 *pV2)
	{
		return pOut;
	}

	// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
	static H_Vector2* D3DXVec2Maximize(H_Vector2 *pOut, CONST H_Vector2 *pV1, CONST H_Vector2 *pV2)
	{
		return pOut;
	}

	static H_Vector2* D3DXVec2Scale(H_Vector2 *pOut, CONST H_Vector2 *pV, float s)
	{
		return pOut;
	}

	// Linear interpolation. V1 + s(V2-V1)
	static H_Vector2* D3DXVec2Lerp(H_Vector2 *pOut, CONST H_Vector2 *pV1, CONST H_Vector2 *pV2,
		float s)
	{
		*pOut = H_Vector2::Lerp(*pV1, *pV2, s);
		return pOut;
	}
	static H_Vector2* D3DXVec2Normalize(H_Vector2 *pOut, CONST H_Vector2 *pV)
	{
		return pOut;
	}

	// Hermite interpolation between position V1, tangent T1 (when s == 0)
	// and position V2, tangent T2 (when s == 1).
	static H_Vector2* D3DXVec2Hermite(H_Vector2 *pOut, CONST H_Vector2 *pV1, CONST H_Vector2 *pT1,
		CONST H_Vector2 *pV2, CONST H_Vector2 *pT2, float s)
	{
		return pOut;
	}

	// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
	static H_Vector2* D3DXVec2CatmullRom(H_Vector2 *pOut, CONST H_Vector2 *pV0, CONST H_Vector2 *pV1,
		CONST H_Vector2 *pV2, CONST H_Vector2 *pV3, float s)
	{
		return pOut;
	}

	// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
	static H_Vector2* D3DXVec2BaryCentric(H_Vector2 *pOut, CONST H_Vector2 *pV1, CONST H_Vector2 *pV2,
		CONST H_Vector2 *pV3, float f, float g)
	{
		return pOut;
	}

	// Transform (x, y, 0, 1) by matrix.
	static H_Vector4* D3DXVec2Transform(H_Vector4 *pOut, CONST H_Vector2 *pV, CONST H_Matrix *pM)
	{
		return pOut;
	}

	// Transform (x, y, 0, 1) by matrix, project result back into w=1.
	static H_Vector2* D3DXVec2TransformCoord(H_Vector2 *pOut, CONST H_Vector2 *pV, CONST H_Matrix *pM)
	{
		return pOut;
	}

	// Transform (x, y, 0, 0) by matrix.
	static H_Vector2* D3DXVec2TransformNormal(H_Vector2 *pOut, CONST H_Vector2 *pV, CONST H_Matrix *pM)
	{
		return pOut;
	}

	// Transform Array (x, y, 0, 1) by matrix.
	static H_Vector4* D3DXVec2TransformArray(H_Vector4 *pOut, UINT OutStride, CONST H_Vector2 *pV, UINT VStride, CONST H_Matrix *pM, UINT n)
	{
		return pOut;
	}

	// Transform Array (x, y, 0, 1) by matrix, project result back into w=1.
	static H_Vector2* D3DXVec2TransformCoordArray(H_Vector2 *pOut, UINT OutStride, CONST H_Vector2 *pV, UINT VStride, CONST H_Matrix *pM, UINT n)
	{
		return pOut;
	}

	// Transform Array (x, y, 0, 0) by matrix.
	static H_Vector2* D3DXVec2TransformNormalArray(H_Vector2 *pOut, UINT OutStride, CONST H_Vector2 *pV, UINT VStride, CONST H_Matrix *pM, UINT n)
	{
		return pOut;
	}
	//--------------------------
	// 3D Vector
	//--------------------------

	static  float D3DXVec3Dot(CONST H_Vector3 *pV1, CONST H_Vector3 *pV2)
	{
		return pV1->Dot(*pV2);
	}
	static H_Vector3* D3DXVec3Cross(H_Vector3 *pOut, CONST H_Vector3 *pV1, CONST H_Vector3 *pV2)
	{
		*pOut = pV1->Cross(*pV2);
		return pOut;
	}
	static H_Vector3* D3DXVec3Normalize(H_Vector3 *pOut, CONST H_Vector3 *pV)
	{
		pV->Normalize(*pOut);
		return pOut;
	}
	static H_Vector3* D3DXVec3TransformCoord(H_Vector3 *pOut, CONST H_Vector3 *pV, CONST H_Matrix *pM)
	{
		*pOut = H_Vector3::Transform(*pV, *pM);
		return pOut;
	}
	static float D3DXVec3Length(CONST H_Vector3 *pV)
	{
		return pV->Length();
	}



	static float D3DXVec3LengthSq(CONST H_Vector3 *pV)
	{
		return pV->LengthSquared();
	}


	static H_Vector3* D3DXVec3Add(H_Vector3 *pOut, CONST H_Vector3 *pV1, CONST H_Vector3 *pV2)
	{
		*pOut = *pV1 + *pV2;
		return pOut;
	}

	static H_Vector3* D3DXVec3Subtract(H_Vector3 *pOut, CONST H_Vector3 *pV1, CONST H_Vector3 *pV2)
	{
		*pOut = *pV1 - *pV2;
		return pOut;
	}

	// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
	static H_Vector3* D3DXVec3Minimize(H_Vector3 *pOut, CONST H_Vector3 *pV1, CONST H_Vector3 *pV2) {
	}

	// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
	static H_Vector3* D3DXVec3Maximize(H_Vector3 *pOut, CONST H_Vector3 *pV1, CONST H_Vector3 *pV2)
	{
		return pOut;
	}

	static H_Vector3* D3DXVec3Scale(H_Vector3 *pOut, CONST H_Vector3 *pV, float s)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(pV);
		XMVECTOR X = XMVectorScale(v1, s);
		H_Vector3 R;
		XMStoreFloat3(&R, X);
		*pOut = R;
		return pOut;
	}

	// Linear interpolation. V1 + s(V2-V1)
	static H_Vector3* D3DXVec3Lerp(H_Vector3 *pOut, CONST H_Vector3 *pV1, CONST H_Vector3 *pV2, float s)
	{		
		*pOut = H_Vector3::Lerp(*pV1, *pV2, s);
		return pOut;
	}


	// Hermite interpolation between position V1, tangent T1 (when s == 0)
	// and position V2, tangent T2 (when s == 1).
	static H_Vector3* D3DXVec3Hermite(H_Vector3 *pOut, CONST H_Vector3 *pV1, CONST H_Vector3 *pT1,
		CONST H_Vector3 *pV2, CONST H_Vector3 *pT2, float s)
	{
		*pOut = H_Vector3::Hermite(*pV1, *pT1, *pV2, *pT2, s);
		return pOut;
	}

	// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
	static H_Vector3* D3DXVec3CatmullRom(H_Vector3 *pOut, CONST H_Vector3 *pV0, CONST H_Vector3 *pV1,
		CONST H_Vector3 *pV2, CONST H_Vector3 *pV3, float s)
	{
		*pOut = H_Vector3::CatmullRom(*pV0, *pV1, *pV2, *pV3, s);
		return pOut;
	}

	// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
	static H_Vector3* D3DXVec3BaryCentric(H_Vector3 *pOut, CONST H_Vector3 *pV1, CONST H_Vector3 *pV2,
		CONST H_Vector3 *pV3, float f, float g)
	{
		*pOut = H_Vector3::Barycentric(*pV1, *pV2, *pV3, f, g);
		return pOut;
	}

	// Transform (x, y, z, 1) by matrix.
	static H_Vector4* D3DXVec3Transform(H_Vector4 *pOut, CONST H_Vector3 *pV, CONST H_Matrix *pM)
	{
		return pOut;
	}

	// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
	// non-affine matrix, the matrix you pass to this function should be the 
	// transpose of the inverse of the matrix you would use to transform a coord.
	static H_Vector3* D3DXVec3TransformNormal(H_Vector3 *pOut, CONST H_Vector3 *pV, CONST H_Matrix *pM)
	{
		*pOut = H_Vector3::TransformNormal(*pV, *pM);
		return pOut;
	}


	// Transform Array (x, y, z, 1) by matrix. 
	static H_Vector4* D3DXVec3TransformArray(H_Vector4 *pOut, UINT OutStride, CONST H_Vector3 *pV, UINT VStride, CONST H_Matrix *pM, UINT n)
	{
		return pOut;
	}

	// Transform Array (x, y, z, 1) by matrix, project result back into w=1.
	static H_Vector3* D3DXVec3TransformCoordArray(H_Vector3 *pOut, UINT OutStride, CONST H_Vector3 *pV, UINT VStride, CONST H_Matrix *pM, UINT n)
	{
		return pOut;
	}

	// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
	// non-affine matrix, the matrix you pass to this function should be the 
	// transpose of the inverse of the matrix you would use to transform a coord.
	static H_Vector3* D3DXVec3TransformNormalArray(H_Vector3 *pOut, UINT OutStride, CONST H_Vector3 *pV, UINT VStride, CONST H_Matrix *pM, UINT n)
	{
		return pOut;
	}

	// Project vector from object space into screen space
	static H_Vector3* D3DXVec3Project(H_Vector3 *pOut, CONST H_Vector3 *pV, CONST D3D10_VIEWPORT *pViewport,
		CONST H_Matrix *pProjection, CONST H_Matrix *pView, CONST H_Matrix *pWorld)
	{
		//*pOut = TViewport::Project();
		return pOut;
	}

	// Project vector from screen space into object space
	static H_Vector3* D3DXVec3Unproject(H_Vector3 *pOut, CONST H_Vector3 *pV, CONST D3D10_VIEWPORT *pViewport,
		CONST H_Matrix *pProjection, CONST H_Matrix *pView, CONST H_Matrix *pWorld)
	{
		//*pOut = TViewport::Unproject();
		return pOut;
	}

	// Project vector Array from object space into screen space
	static H_Vector3* D3DXVec3ProjectArray(H_Vector3 *pOut, UINT OutStride, CONST H_Vector3 *pV, UINT VStride, CONST D3D10_VIEWPORT *pViewport,
		CONST H_Matrix *pProjection, CONST H_Matrix *pView, CONST H_Matrix *pWorld, UINT n)
	{
		return pOut;
	}

	// Project vector Array from screen space into object space
	static H_Vector3* D3DXVec3UnprojectArray(H_Vector3 *pOut, UINT OutStride, CONST H_Vector3 *pV, UINT VStride, CONST D3D10_VIEWPORT *pViewport,
		CONST H_Matrix *pProjection, CONST H_Matrix *pView, CONST H_Matrix *pWorld, UINT n)
	{
		return pOut;
	}

	//--------------------------
	// 4D Vector
	//--------------------------

	static float D3DXVec4Length(CONST H_Vector4 *pV)
	{
		return pV->Length();
	}


	static float D3DXVec4LengthSq(CONST H_Vector4 *pV)
	{
		return 0.0f;
	}

	static float D3DXVec4Dot(CONST H_Vector4 *pV1, CONST H_Vector4 *pV2)
	{
		return 0.0f;
	}
	static H_Vector4* D3DXVec4Add(H_Vector4 *pOut, CONST H_Vector4 *pV1, CONST H_Vector4 *pV2)
	{
		return pOut;
	}

	static H_Vector4* D3DXVec4Subtract(H_Vector4 *pOut, CONST H_Vector4 *pV1, CONST H_Vector4 *pV2)
	{
		return pOut;
	}

	// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
	static H_Vector4* D3DXVec4Minimize(H_Vector4 *pOut, CONST H_Vector4 *pV1, CONST H_Vector4 *pV2)
	{
		return pOut;
	}

	// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
	static H_Vector4* D3DXVec4Maximize(H_Vector4 *pOut, CONST H_Vector4 *pV1, CONST H_Vector4 *pV2)
	{
		return pOut;
	}
	static H_Vector4* D3DXVec4Scale(H_Vector4 *pOut, CONST H_Vector4 *pV, float s) {
		return pOut;
	}

	// Linear interpolation. V1 + s(V2-V1)
	static H_Vector4* D3DXVec4Lerp(H_Vector4 *pOut, CONST H_Vector4 *pV1, CONST H_Vector4 *pV2, float s)
	{
		*pOut = H_Vector4::Lerp(*pV1, *pV2, s);
		return pOut;
	}

	// Cross-product in 4 dimensions.
	static H_Vector4* D3DXVec4Cross(H_Vector4 *pOut, CONST H_Vector4 *pV1, CONST H_Vector4 *pV2,
		CONST H_Vector4 *pV3)
	{
		return pOut;
	}

	static H_Vector4* D3DXVec4Normalize(H_Vector4 *pOut, CONST H_Vector4 *pV)
	{
		return pOut;
	}

	// Hermite interpolation between position V1, tangent T1 (when s == 0)
	// and position V2, tangent T2 (when s == 1).
	static H_Vector4* D3DXVec4Hermite(H_Vector4 *pOut, CONST H_Vector4 *pV1, CONST H_Vector4 *pT1,
		CONST H_Vector4 *pV2, CONST H_Vector4 *pT2, float s)
	{
		return pOut;
	}

	// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
	static H_Vector4* D3DXVec4CatmullRom(H_Vector4 *pOut, CONST H_Vector4 *pV0, CONST H_Vector4 *pV1,
		CONST H_Vector4 *pV2, CONST H_Vector4 *pV3, float s)
	{
		return pOut;
	}

	// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
	static H_Vector4* D3DXVec4BaryCentric(H_Vector4 *pOut, CONST H_Vector4 *pV1, CONST H_Vector4 *pV2,
		CONST H_Vector4 *pV3, float f, float g)
	{
		return pOut;
	}

	// Transform vector by matrix.
	static H_Vector4* D3DXVec4Transform(H_Vector4 *pOut, CONST H_Vector4 *pV, CONST H_Matrix *pM)
	{
		return pOut;
	}

	// Transform vector array by matrix.
	static H_Vector4* D3DXVec4TransformArray(H_Vector4 *pOut, UINT OutStride, CONST H_Vector4 *pV, UINT VStride, CONST H_Matrix *pM, UINT n)
	{
		return pOut;
	}


	static H_Matrix* D3DXMatrixIdentity(H_Matrix *pOut)
	{
		XMStoreFloat4x4(pOut, XMMatrixIdentity());
		return pOut;
	}
	static H_Matrix* D3DXMatrixRotationQuaternion(H_Matrix *pOut, CONST H_Quaternion *pQ)
	{
		*pOut = H_Matrix::CreateFromQuaternion(*pQ);
		return pOut;
	}
	static H_Quaternion* D3DXQuaternionRotationMatrix(H_Quaternion *pOut, CONST H_Matrix *pM)
	{
		*pOut = H_Quaternion::CreateFromRotationMatrix(*pM);
		return pOut;
	}

	static float D3DXMatrixDeterminant(CONST H_Matrix *pM) {
		return pM->Determinant();
	}

	static HRESULT D3DXMatrixDecompose(H_Vector3 *pOutScale, H_Quaternion *pOutRotation,
		H_Vector3 *pOutTranslation, H_Matrix *pM)
	{
		if (pM->Decompose(*pOutScale, *pOutRotation, *pOutTranslation) == false)
		{
			return S_FALSE;
		}
		return S_OK;
	}

	static H_Matrix* D3DXMatrixTranspose(H_Matrix *pOut, CONST H_Matrix *pM) {

		*pOut = pM->Transpose();
		return pOut;
	}

	// Matrix multiplication.  The result represents the transformation M2
	// followed by the transformation M1.  (Out = M1 * M2)
	static H_Matrix*  D3DXMatrixMultiply(H_Matrix *pOut, CONST H_Matrix *pM1, CONST H_Matrix *pM2) {
		*pOut = (*pM1) * (*pM2);
		return pOut;
	}

	// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
	static H_Matrix*  D3DXMatrixMultiplyTranspose(H_Matrix *pOut, CONST H_Matrix *pM1, CONST H_Matrix *pM2) {

		*pOut = (*pM1) * (*pM2);
		pOut->Transpose();
		return pOut;
	}

	// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
	// be returned.  The determinant of pM is also returned it pfDeterminant
	// is non-NULL.
	static H_Matrix*  D3DXMatrixInverse(H_Matrix *pOut, float *pDeterminant, CONST H_Matrix *pM) {
		pM->Invert(*pOut);
		if (pDeterminant != nullptr)
		{
			*pDeterminant = pM->Determinant();
		}
		return pOut;
	}

	// Build a matrix which scales by (sx, sy, sz)
	static H_Matrix*  D3DXMatrixScaling(H_Matrix *pOut, float sx, float sy, float sz) {
		*pOut = H_Matrix::CreateScale(sx, sy, sz);
		return pOut;
	}

	// Build a matrix which translates by (x, y, z)
	static H_Matrix*  D3DXMatrixTranslation(H_Matrix *pOut, float x, float y, float z) {
		*pOut = H_Matrix::CreateTranslation(x, y, z);
		return pOut;
	}

	// Build a matrix which rotates around the X axis
	static H_Matrix*  D3DXMatrixRotationX(H_Matrix *pOut, float Angle) {
		*pOut = H_Matrix::CreateRotationX(Angle);
		return pOut;
	}

	// Build a matrix which rotates around the Y axis
	static H_Matrix*  D3DXMatrixRotationY(H_Matrix *pOut, float Angle) {
		*pOut = H_Matrix::CreateRotationY(Angle);
		return pOut;
	}

	// Build a matrix which rotates around the Z axis
	static H_Matrix*  D3DXMatrixRotationZ(H_Matrix *pOut, float Angle) {
		*pOut = H_Matrix::CreateRotationZ(Angle);
		return pOut;
	}

	// Build a matrix which rotates around an arbitrary axis
	static H_Matrix*  D3DXMatrixRotationAxis(H_Matrix *pOut, CONST H_Vector3 *pV, float Angle) {
		*pOut = H_Matrix::CreateFromAxisAngle(*pV, Angle);
		return pOut;
	}

	// Yaw around the Y axis, a pitch around the X axis,
	// and a roll around the Z axis.
	static H_Matrix*  D3DXMatrixRotationYawPitchRoll(H_Matrix *pOut, float Yaw, float Pitch, float Roll) {
		*pOut = H_Matrix::CreateFromYawPitchRoll(Yaw, Pitch, Roll);
		return pOut;
	}

	// Build transformation matrix.  NULL arguments are treated as identity.
	// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
	static H_Matrix*  D3DXMatrixTransformation(H_Matrix *pOut, CONST H_Vector3 *pScalingCenter,
		CONST H_Quaternion *pScalingRotation, CONST H_Vector3 *pScaling,
		CONST H_Vector3 *pRotationCenter, CONST H_Quaternion *pRotation,
		CONST H_Vector3 *pTranslation)
	{
		return pOut;
	}

	// Build 2D transformation matrix in XY plane.  NULL arguments are treated as identity.
	// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
	static H_Matrix*  D3DXMatrixTransformation2D(H_Matrix *pOut, CONST H_Vector2* pScalingCenter,
		float ScalingRotation, CONST H_Vector2* pScaling,
		CONST H_Vector2* pRotationCenter, float Rotation,
		CONST H_Vector2* pTranslation) {
		return pOut;
	}

	// Build affine transformation matrix.  NULL arguments are treated as identity.
	// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
	static H_Matrix*  D3DXMatrixAffineTransformation(H_Matrix *pOut, float Scaling, CONST H_Vector3 *pRotationCenter,
		CONST H_Quaternion *pRotation, CONST H_Vector3 *pTranslation) 
	{
		XMVECTOR S = XMVectorReplicate(Scaling);//XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		XMVECTOR O = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		if (pRotationCenter != NULL)
		{
			O = DirectX::XMLoadFloat3(pRotationCenter);
		}		
		XMVECTOR P = DirectX::XMLoadFloat3(pTranslation);
		XMVECTOR Q = DirectX::XMLoadFloat4(pRotation);
		*pOut = DirectX::XMMatrixAffineTransformation(S, O, Q, P);
		return pOut;
	}

	// Build 2D affine transformation matrix in XY plane.  NULL arguments are treated as identity.
	// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
	static H_Matrix*  D3DXMatrixAffineTransformation2D(H_Matrix *pOut, float Scaling, CONST H_Vector2* pRotationCenter,
		float Rotation, CONST H_Vector2* pTranslation) {
		return pOut;
	}

	// Build a lookat matrix. (right-handed)
	static H_Matrix*  D3DXMatrixLookAtRH(H_Matrix *pOut, CONST H_Vector3 *pEye, CONST H_Vector3 *pAt, CONST H_Vector3 *pUp) {
		return pOut;
	}

	// Build a lookat matrix. (left-handed)
	static H_Matrix*  D3DXMatrixLookAtLH(H_Matrix *pOut, CONST H_Vector3 *pEye, CONST H_Vector3 *pAt, CONST H_Vector3 *pUp) {
		*pOut = H_Matrix::CreateLookAt(*pEye, *pAt, *pUp);
		return pOut;
	}

	// Build a perspective projection matrix. (right-handed)
	static H_Matrix*  D3DXMatrixPerspectiveRH(H_Matrix *pOut, float w, float h, float zn, float zf) {
		return pOut;
	}

	// Build a perspective projection matrix. (left-handed)
	static H_Matrix*  D3DXMatrixPerspectiveLH(H_Matrix *pOut, float w, float h, float zn, float zf) {
		*pOut = H_Matrix::CreatePerspective(w, h, zn, zf);
		return pOut;
	}

	// Build a perspective projection matrix. (right-handed)
	static H_Matrix*  D3DXMatrixPerspectiveFovRH(H_Matrix *pOut, float fovy, float Aspect, float zn, float zf) 
	{
		using namespace DirectX;		
		XMStoreFloat4x4(pOut, XMMatrixPerspectiveFovRH(fovy, Aspect, zn, zf));
		return pOut;
	}

	// Build a perspective projection matrix. (left-handed)
	static H_Matrix*  D3DXMatrixPerspectiveFovLH(H_Matrix *pOut, float fovy, float Aspect, float zn, float zf) 
	{
		using namespace DirectX;
		*pOut = H_Matrix::CreatePerspectiveFieldOfView(fovy, Aspect, zn, zf);
		return pOut;
	}

	// Build a perspective projection matrix. (right-handed)
	static H_Matrix*  D3DXMatrixPerspectiveOffCenterRH(H_Matrix *pOut, float l, float r, float b, float t, float zn, float zf) {		
		return pOut;
	}

	// Build a perspective projection matrix. (left-handed)
	static H_Matrix*  D3DXMatrixPerspectiveOffCenterLH(H_Matrix *pOut, float l, float r, float b, float t, float zn, float zf) {
		*pOut = H_Matrix::CreatePerspectiveOffCenter(l, r, b, t, zn, zf);
		return pOut;
	}

	// Build an ortho projection matrix. (right-handed)
	static H_Matrix*  D3DXMatrixOrthoRH(H_Matrix *pOut, float w, float h, float zn, float zf) {
		return pOut;
	}

	// Build an ortho projection matrix. (left-handed)
	static H_Matrix*  D3DXMatrixOrthoLH(H_Matrix *pOut, float w, float h, float zn, float zf) {
		*pOut = H_Matrix::CreateOrthographic(w, h, zn, zf);
		return pOut;
	}

	// Build an ortho projection matrix. (right-handed)
	static H_Matrix*  D3DXMatrixOrthoOffCenterRH(H_Matrix *pOut, float l, float r, float b, float t, float zn, float zf) {
		return pOut;
	}

	// Build an ortho projection matrix. (left-handed)
	static H_Matrix*  D3DXMatrixOrthoOffCenterLH(H_Matrix *pOut, float l, float r, float b, float t, float zn, float zf) {
		*pOut = H_Matrix::CreateOrthographicOffCenter(l, r, b, t, zn, zf);
		return pOut;
	}

	// Build a matrix which flattens geometry into a plane, as if casting
	// a shadow from a light.
	static H_Matrix*  D3DXMatrixShadow(H_Matrix *pOut, CONST H_Vector4 *pLight, CONST H_Plane *pPlane) 
	{
		CONST H_Vector3 pLightLight = H_Vector3(pLight->x, pLight->y, pLight->z);
		*pOut = H_Matrix::CreateShadow(pLightLight, *pPlane);
		return pOut;
	}

	// Build a matrix which reflects the coordinate system about a plane
	static H_Matrix*  D3DXMatrixReflect(H_Matrix *pOut, CONST H_Plane *pPlane) {
		*pOut = H_Matrix::CreateReflection(*pPlane);
		return pOut;
	}

	//--------------------------
	// Quaternion
	//--------------------------

	// inline

	static float D3DXQuaternionLength(CONST H_Quaternion *pQ)
	{
		return pQ->Length();
	};

	// Length squared, or "norm"
	static float D3DXQuaternionLengthSq(CONST H_Quaternion *pQ) 
	{
		return pQ->LengthSquared();
	};

	static float D3DXQuaternionDot(CONST H_Quaternion *pQ1, CONST H_Quaternion *pQ2) 
	{		
		return pQ1->Dot(*pQ2);;
	};

	// (0, 0, 0, 1)
	static H_Quaternion* D3DXQuaternionIdentity(H_Quaternion *pOut) {
		//*pOut = TQuaternion::Identity;
		XMStoreFloat4(pOut, XMQuaternionIdentity());
		return pOut;
	};

	static BOOL D3DXQuaternionIsIdentity(CONST H_Quaternion *pQ) {
		return TRUE;
	};

	// (-x, -y, -z, w)
	static H_Quaternion* D3DXQuaternionConjugate(H_Quaternion *pOut, CONST H_Quaternion *pQ) {
		return pOut;
	};


	// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
	static void D3DXQuaternionToAxisAngle(CONST H_Quaternion *pQ, H_Vector3 *pAxis, float *pAngle) 
	{
		
	};

	static H_Quaternion* D3DXQuaternionRotationAxis(H_Quaternion *pOut, CONST H_Vector3 *pV, FLOAT Angle)
	{
		*pOut = H_Quaternion::CreateFromAxisAngle(*pV, Angle);
		return pOut;
	}

	// Yaw around the Y axis, a pitch around the X axis,
	// and a roll around the Z axis.
	static H_Quaternion* D3DXQuaternionRotationYawPitchRoll(H_Quaternion *pOut, float Yaw, float Pitch, float Roll) 
	{
		*pOut = H_Quaternion::CreateFromYawPitchRoll(Yaw,Pitch,Roll);
		return pOut;
	};

	// Quaternion multiplication.  The result represents the rotation Q2
	// followed by the rotation Q1.  (Out = Q2 * Q1)
	static H_Quaternion* D3DXQuaternionMultiply(H_Quaternion *pOut, CONST H_Quaternion *pQ1,
		CONST H_Quaternion *pQ2) 
	{
		*pOut = *pQ1 * *pQ2;
		return pOut;
	};

	static H_Quaternion* D3DXQuaternionNormalize(H_Quaternion *pOut, CONST H_Quaternion *pQ)
	{
		*pOut = *pQ;
		pOut->Normalize();
		return pOut;
	};

	// Conjugate and re-norm
	static H_Quaternion* D3DXQuaternionInverse(H_Quaternion *pOut, CONST H_Quaternion *pQ) 
	{
		H_Quaternion qRet = *pQ;
		pQ->Inverse(qRet);
		*pOut = qRet;
		return pOut;
	};

	// Expects unit quaternions.
	// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
	static H_Quaternion* D3DXQuaternionLn(H_Quaternion *pOut, CONST H_Quaternion *pQ) {
		return pOut;
	};

	// Expects pure quaternions. (w == 0)  w is ignored in calculation.
	// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
	static H_Quaternion* D3DXQuaternionExp(H_Quaternion *pOut, CONST H_Quaternion *pQ) {
		return pOut;
	};

	// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
	// Expects unit quaternions.
	static H_Quaternion* D3DXQuaternionSlerp(H_Quaternion *pOut, CONST H_Quaternion *pQ1,	CONST H_Quaternion *pQ2, float t) 
	{
		*pOut = H_Quaternion::Slerp(*pQ1, *pQ2, t);
		return pOut;
	};

	// Spherical quadrangle interpolation.
	// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
	static H_Quaternion* D3DXQuaternionSquad(H_Quaternion *pOut, CONST H_Quaternion *pQ1,
		CONST H_Quaternion *pA, CONST H_Quaternion *pB,
		CONST H_Quaternion *pC, float t) {
		return pOut;
	};

	// Setup control points for spherical quadrangle interpolation
	// from Q1 to Q2.  The control points are chosen in such a way 
	// to ensure the continuity of tangents with adjacent segments.
	static void D3DXQuaternionSquadSetup(H_Quaternion *pAOut, H_Quaternion *pBOut, H_Quaternion *pCOut,
		CONST H_Quaternion *pQ0, CONST H_Quaternion *pQ1,
		CONST H_Quaternion *pQ2, CONST H_Quaternion *pQ3) {
	};

	// Barycentric interpolation.
	// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
	static H_Quaternion* D3DXQuaternionBaryCentric(H_Quaternion *pOut, CONST H_Quaternion *pQ1,
		CONST H_Quaternion *pQ2, CONST H_Quaternion *pQ3,
		float f, float g) {
		return pOut;
	};


	//--------------------------
	// Plane
	//--------------------------

	// inline

	// ax + by + cz + dw
	static float D3DXPlaneDot(CONST H_Plane *pP, CONST H_Vector4 *pV) {
		return 0.0f;
	};
	// ax + by + cz + d
	static float D3DXPlaneDotCoord(CONST H_Plane *pP, CONST H_Vector3 *pV) {
		return 0.0f;
	};
	// ax + by + cz
	static float D3DXPlaneDotNormal(CONST H_Plane *pP, CONST H_Vector3 *pV) {
		return 0.0f;
	};
	static H_Plane* D3DXPlaneScale(H_Plane *pOut, CONST H_Plane *pP, float s) {
		return pOut;
	};


	// Normalize plane (so that |a,b,c| == 1)
	static H_Plane* D3DXPlaneNormalize(H_Plane *pOut, CONST H_Plane *pP) {
		return pOut;
	};

	// Find the intersection between a plane and a line.  If the line is
	// parallel to the plane, NULL is returned.
	static H_Vector3* D3DXPlaneIntersectLine(H_Vector3 *pOut, CONST H_Plane *pP, CONST H_Vector3 *pV1,
		CONST H_Vector3 *pV2) {
		return pOut;
	};

	// Construct a plane from a point and a normal
	static H_Plane* D3DXPlaneFromPointNormal(H_Plane *pOut, CONST H_Vector3 *pPoint, CONST H_Vector3 *pNormal) {
		return pOut;
	};

	// Construct a plane from 3 points
	static H_Plane* D3DXPlaneFromPoints(H_Plane *pOut, CONST H_Vector3 *pV1, CONST H_Vector3 *pV2,
		CONST H_Vector3 *pV3) {
		return pOut;
	};

	// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
	// M should be the inverse transpose of the transformation desired.
	static H_Plane* D3DXPlaneTransform(H_Plane *pOut, CONST H_Plane *pP, CONST H_Matrix *pM) {
		return pOut;
	};
	// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
	static H_Plane* D3DXPlaneTransformArray(H_Plane *pOut, UINT OutStride, CONST H_Plane *pP, UINT PStride, CONST H_Matrix *pM, UINT n) {
		return pOut;
	};



	//--------------------------
	// Color
	//--------------------------

	// inline

	// (1-r, 1-g, 1-b, a)
	static H_Color* D3DXColorNegative(H_Color *pOut, CONST H_Color *pC) {
		return pOut;
	};

	static H_Color* D3DXColorAdd(H_Color *pOut, CONST H_Color *pC1, CONST H_Color *pC2) {
		return pOut;
	};

	static H_Color* D3DXColorSubtract(H_Color *pOut, CONST H_Color *pC1, CONST H_Color *pC2) {
		return pOut;
	};

	static H_Color* D3DXColorScale(H_Color *pOut, CONST H_Color *pC, float s) {
		return pOut;
	};

	// (r1*r2, g1*g2, b1*b2, a1*a2)
	static H_Color* D3DXColorModulate(H_Color *pOut, CONST H_Color *pC1, CONST H_Color *pC2) {
		return pOut;
	};

	// Linear interpolation of r,g,b, and a. C1 + s(C2-C1)
	static H_Color* D3DXColorLerp(H_Color *pOut, CONST H_Color *pC1, CONST H_Color *pC2, float s) {
		return pOut;
	};


	// Interpolate r,g,b between desaturated color and color.
	// DesaturatedColor + s(Color - DesaturatedColor)
	static H_Color* D3DXColorAdjustSaturation(H_Color *pOut, CONST H_Color *pC, float s) {
		return pOut;
	};
	// Interpolate r,g,b between 50% grey and color.  Grey + s(Color - Grey)
	static H_Color* D3DXColorAdjustContrast(H_Color *pOut, CONST H_Color *pC, float c) {
		return pOut;
	};





	//--------------------------
	// Misc
	//--------------------------
		// Calculate Fresnel term given the cosine of theta (likely obtained by
		// taking the dot of two normals), and the refraction index of the material.
	static float D3DXFresnelTerm(float CosTheta, float RefractionIndex)
	{
		return 0.0f;
	};
}

//  ------------------------------------------------------------------------------
// Support for TMath and Standard C++ Library containers
namespace std
{
	template<> struct less<X_BASIS_EX::H_Rectangle>
	{
		bool operator()(const X_BASIS_EX::H_Rectangle& r1, const X_BASIS_EX::H_Rectangle& r2) const
		{
			return ((r1.x < r2.x)
				|| ((r1.x == r2.x) && (r1.y < r2.y))
				|| ((r1.x == r2.x) && (r1.y == r2.y) && (r1.width < r2.width))
				|| ((r1.x == r2.x) && (r1.y == r2.y) && (r1.width == r2.width) && (r1.height < r2.height)));
		}
	};

	template<> struct less<X_BASIS_EX::H_Vector2>
	{
		bool operator()(const X_BASIS_EX::H_Vector2& V1, const X_BASIS_EX::H_Vector2& V2) const
		{
			return ((V1.x < V2.x) || ((V1.x == V2.x) && (V1.y < V2.y)));
		}
	};

	template<> struct less<X_BASIS_EX::H_Vector3>
	{
		bool operator()(const X_BASIS_EX::H_Vector3& V1, const X_BASIS_EX::H_Vector3& V2) const
		{
			return ((V1.x < V2.x)
				|| ((V1.x == V2.x) && (V1.y < V2.y))
				|| ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z)));
		}
	};

	template<> struct less<X_BASIS_EX::H_Vector4>
	{
		bool operator()(const X_BASIS_EX::H_Vector4& V1, const X_BASIS_EX::H_Vector4& V2) const
		{
			return ((V1.x < V2.x)
				|| ((V1.x == V2.x) && (V1.y < V2.y))
				|| ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z))
				|| ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z == V2.z) && (V1.w < V2.w)));
		}
	};

	template<> struct less<X_BASIS_EX::H_Matrix>
	{
		bool operator()(const X_BASIS_EX::H_Matrix& M1, const X_BASIS_EX::H_Matrix& M2) const
		{
			if (M1._11 != M2._11) return M1._11 < M2._11;
			if (M1._12 != M2._12) return M1._12 < M2._12;
			if (M1._13 != M2._13) return M1._13 < M2._13;
			if (M1._14 != M2._14) return M1._14 < M2._14;
			if (M1._21 != M2._21) return M1._21 < M2._21;
			if (M1._22 != M2._22) return M1._22 < M2._22;
			if (M1._23 != M2._23) return M1._23 < M2._23;
			if (M1._24 != M2._24) return M1._24 < M2._24;
			if (M1._31 != M2._31) return M1._31 < M2._31;
			if (M1._32 != M2._32) return M1._32 < M2._32;
			if (M1._33 != M2._33) return M1._33 < M2._33;
			if (M1._34 != M2._34) return M1._34 < M2._34;
			if (M1._41 != M2._41) return M1._41 < M2._41;
			if (M1._42 != M2._42) return M1._42 < M2._42;
			if (M1._43 != M2._43) return M1._43 < M2._43;
			if (M1._44 != M2._44) return M1._44 < M2._44;

			return false;
		}
	};

	template<> struct less<X_BASIS_EX::H_Plane>
	{
		bool operator()(const X_BASIS_EX::H_Plane& P1, const X_BASIS_EX::H_Plane& P2) const
		{
			return ((P1.x < P2.x)
				|| ((P1.x == P2.x) && (P1.y < P2.y))
				|| ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z < P2.z))
				|| ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z == P2.z) && (P1.w < P2.w)));
		}
	};

	template<> struct less<X_BASIS_EX::H_Quaternion>
	{
		bool operator()(const X_BASIS_EX::H_Quaternion& Q1, const X_BASIS_EX::H_Quaternion& Q2) const
		{
			return ((Q1.x < Q2.x)
				|| ((Q1.x == Q2.x) && (Q1.y < Q2.y))
				|| ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z < Q2.z))
				|| ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z == Q2.z) && (Q1.w < Q2.w)));
		}
	};

	template<> struct less<X_BASIS_EX::H_Color>
	{
		bool operator()(const X_BASIS_EX::H_Color& C1, const X_BASIS_EX::H_Color& C2) const
		{
			return ((C1.x < C2.x)
				|| ((C1.x == C2.x) && (C1.y < C2.y))
				|| ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z < C2.z))
				|| ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z == C2.z) && (C1.w < C2.w)));
		}
	};

	template<> struct less<X_BASIS_EX::H_Ray>
	{
		bool operator()(const X_BASIS_EX::H_Ray& R1, const X_BASIS_EX::H_Ray& R2) const
		{
			if (R1.position.x != R2.position.x) return R1.position.x < R2.position.x;
			if (R1.position.y != R2.position.y) return R1.position.y < R2.position.y;
			if (R1.position.z != R2.position.z) return R1.position.z < R2.position.z;

			if (R1.direction.x != R2.direction.x) return R1.direction.x < R2.direction.x;
			if (R1.direction.y != R2.direction.y) return R1.direction.y < R2.direction.y;
			if (R1.direction.z != R2.direction.z) return R1.direction.z < R2.direction.z;

			return false;
		}
	};

	template<> struct less<X_BASIS_EX::H_Viewport>
	{
		bool operator()(const X_BASIS_EX::H_Viewport& vp1, const X_BASIS_EX::H_Viewport& vp2) const
		{
			if (vp1.x != vp2.x) return (vp1.x < vp2.x);
			if (vp1.y != vp2.y) return (vp1.y < vp2.y);

			if (vp1.width != vp2.width) return (vp1.width < vp2.width);
			if (vp1.height != vp2.height) return (vp1.height < vp2.height);

			if (vp1.minDepth != vp2.minDepth) return (vp1.minDepth < vp2.minDepth);
			if (vp1.maxDepth != vp2.maxDepth) return (vp1.maxDepth < vp2.maxDepth);

			return false;
		}
	};


};
using namespace X_BASIS_EX;
