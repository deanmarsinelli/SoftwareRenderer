/*
	Vector.h
	Author: Dean Marsinelli

	This file contains definitions for 2D, 3D,
	and 4D vectors.
*/

#pragma once

#include <cmath>

// Vec2 class declaration for 2D vector
template<typename T>
class Vec2
{
public:
	T x, y;

public:
	// Constructors
	Vec2();
	Vec2(const Vec2<T>& vec);
	Vec2(const T& x, const T& y);

	// Setters and Getters
	void Set(const T& x, const T& y);
	void Set(const Vec2<T>& vec);

	// Translate the Vector
	void Translate(const T& x, const T& y);

	Vec2<T> Negate() const;

	// Overloaded operators
	Vec2<T> operator+(const Vec2<T>& rhs) const;
	Vec2<T> operator-(const Vec2<T>& rhs) const;
	Vec2<T> operator*(const T rhs) const;
	Vec2<T>& operator+=(const Vec2<T>& vec);
	Vec2<T>& operator-=(const Vec2<T>& vec);
	Vec2<T>& operator*=(const Vec2<T>& vec);
	Vec2<T>& operator/=(const Vec2<T>& vec);
	bool operator==(const Vec2<T>& vec) const;
	bool operator!=(const Vec2<T>& vec) const;
	Vec2<T>& operator=(const Vec2<T>& vec);

	// Formulas
	T Distance(const Vec2<T>& vec) const;
	T Length() const;
	T DotProduct(const Vec2<T>& vec) const;
	Vec2<T> Normalize() const;
};


// Vec3 class declaration for 3D vector
template<typename T>
class Vec3
{
public:
	T x, y, z;

public:
	// Constructors
	Vec3();
	Vec3(const Vec3<T>& vec);
	Vec3(const T& x, const T& y, const T& z);

	// Setters and Getters
	void Set(const T& x, const T& y, const T& z);
	void Set(const Vec3<T>& vec);

	// Translate the Vector
	void Translate(const T& x, const T& y, const T& z);

	Vec3<T> Negate() const;

	// Overloaded operators
	Vec3<T> operator+(const Vec3<T>& rhs) const;
	Vec3<T> operator-(const Vec3<T>& rhs) const;
	Vec3<T> operator*(const T rhs) const;
	Vec3<T>& operator+=(const Vec3<T>& vec);
	Vec3<T>& operator-=(const Vec3<T>& vec);
	Vec3<T>& operator*=(const Vec3<T>& vec);
	Vec3<T>& operator/=(const Vec3<T>& vec);
	bool operator==(const Vec3<T>& vec) const;
	bool operator!=(const Vec3<T>& vec) const;
	Vec3<T>& operator=(const Vec3<T>& vec);

	// Formulas
	T Distance(const Vec3<T>& vec) const;
	T Length() const;
	T DotProduct(const Vec3<T>& vec) const;

	Vec3<T> CrossProduct(const Vec3<T>& vec) const;
	Vec3<T> Normalize() const;
};


// Vec4 class declaration for 4D vector
template<typename T>
class Vec4
{
public:
	T x, y, z, w;

public:
	// Constructors
	Vec4();
	Vec4(const Vec3<T>& vec);
	Vec4(const Vec4<T>& vec);
	Vec4(const T& x, const T& y, const T& z, const T& w = 1.0);

	// Setters and Getters
	void Set(const T& x, const T& y, const T& z, const T& w);
	void Set(const Vec4<T>& vec);

	// Translate the Vector
	void Translate(const T& x, const T& y, const T& z);
	void Translate(const T& x, const T& y, const T& z, const T& w);

	Vec4<T> Negate() const;

	// Overloaded operators
	Vec4<T> operator+(const Vec4<T>& rhs) const;
	Vec4<T> operator-(const Vec4<T>& rhs) const;
	Vec4<T> operator*(const T rhs) const;
	Vec4<T>& operator+=(const Vec4<T>& vec);
	Vec4<T>& operator-=(const Vec4<T>& vec);
	Vec4<T>& operator*=(const Vec4<T>& vec);
	Vec4<T>& operator/=(const Vec4<T>& vec);
	bool operator==(const Vec4<T>& vec) const;
	bool operator!=(const Vec4<T>& vec) const;
	Vec4<T>& operator=(const Vec4<T>& vec);

	// Formulas
	T Distance(const Vec4<T>& vec) const;
	T Length() const;
	T DotProduct(const Vec4<T>& vec) const;

	Vec4<T> Normalize() const;
};


#include "Vector.inl"

typedef Vec2<double> Vector2D;
typedef Vec2<float> Vector2F;

typedef Vec3<double> Vector3D;
typedef Vec3<float> Vector3F;

typedef Vec4<double> Vector4D;
typedef Vec4<float> Vector4F;


// component wise multiplication
template <typename T>
inline Vec4<T> operator*(const Vec4<T>& lhs, const Vec4<T>& rhs)
{
	Vec4<T> result;
	result.x = lhs.x * rhs.x;
	result.y = lhs.y * rhs.y;
	result.z = lhs.z * rhs.z;
	result.w = lhs.w * rhs.w;

	return result;
}
