/*
	Matrix.h
	Author: Dean Marsinelli

	This file contains definitions for 4x4 matrices.
*/

#pragma once

#include "Vector.h"

class Mat4x4
{
public:
	Mat4x4();

	Mat4x4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	/// Copy constructor
	Mat4x4(const Mat4x4& matrix);

	/// Set a 3D Position
	void SetPosition(const Vector3F& position);

	/// Set a 4D Position
	void SetPosition(const Vector4F& position);

	/// Set the scale elements
	void SetScale(const Vector3F& scale);

	/// Return the x, y, z position values
	Vector3F GetPosition() const;

	/// Return the forward vector for the matrix
	Vector3F GetDirection() const;

	/// Return the right vector for the matrix
	Vector3F GetRight() const;

	/// Return the yaw, pitch and roll values
	Vector3F GetYawPitchRoll() const;

	/// Transform a Vector4F by this matrix
	Vector4F Transform(Vector4F& vec) const;

	/// Transform a Vector3F by this matrix
	Vector3F Transform(Vector3F& vec) const;

	/// Return the Inverse and determinant of this matrix
	Mat4x4 Inverse(float& det) const;

	/// Return the Transpose of this matrix
	Mat4x4 Transpose() const;

	/// Overloaded assignment operator
	Mat4x4& operator=(const Mat4x4& rhs);

	/// Overloaded equals operator
	bool operator==(const Mat4x4& rhs) const;

	/// Overloaded not equal operator
	bool operator!=(const Mat4x4& rhs) const;

	float operator() (size_t Row, size_t Column) const { return m[Row][Column]; }

	float& operator() (size_t Row, size_t Column) { return m[Row][Column]; }

public:
	union 
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
		float m_[16];
	};

	/// The identity matrix
	static const Mat4x4 Identity;
};

inline Mat4x4 operator*(const Mat4x4& lhs, const Mat4x4& rhs)
{
	Mat4x4 output;

	float x = lhs.m[0][0];
	float y = lhs.m[0][1];
	float z = lhs.m[0][2];
	float w = lhs.m[0][3];
	output.m[0][0] = (rhs.m[0][0] * x) + (rhs.m[1][0] * y) + (rhs.m[2][0] * z) + (rhs.m[3][0] * w);
	output.m[0][1] = (rhs.m[0][1] * x) + (rhs.m[1][1] * y) + (rhs.m[2][1] * z) + (rhs.m[3][1] * w);
	output.m[0][2] = (rhs.m[0][2] * x) + (rhs.m[1][2] * y) + (rhs.m[2][2] * z) + (rhs.m[3][2] * w);
	output.m[0][3] = (rhs.m[0][3] * x) + (rhs.m[1][3] * y) + (rhs.m[2][3] * z) + (rhs.m[3][3] * w);

	x = lhs.m[1][0];
	y = lhs.m[1][1];
	z = lhs.m[1][2];
	w = lhs.m[1][3];
	output.m[1][0] = (rhs.m[0][0] * x) + (rhs.m[1][0] * y) + (rhs.m[2][0] * z) + (rhs.m[3][0] * w);
	output.m[1][1] = (rhs.m[0][1] * x) + (rhs.m[1][1] * y) + (rhs.m[2][1] * z) + (rhs.m[3][1] * w);
	output.m[1][2] = (rhs.m[0][2] * x) + (rhs.m[1][2] * y) + (rhs.m[2][2] * z) + (rhs.m[3][2] * w);
	output.m[1][3] = (rhs.m[0][3] * x) + (rhs.m[1][3] * y) + (rhs.m[2][3] * z) + (rhs.m[3][3] * w);

	x = lhs.m[2][0];
	y = lhs.m[2][1];
	z = lhs.m[2][2];
	w = lhs.m[2][3];
	output.m[2][0] = (rhs.m[0][0] * x) + (rhs.m[1][0] * y) + (rhs.m[2][0] * z) + (rhs.m[3][0] * w);
	output.m[2][1] = (rhs.m[0][1] * x) + (rhs.m[1][1] * y) + (rhs.m[2][1] * z) + (rhs.m[3][1] * w);
	output.m[2][2] = (rhs.m[0][2] * x) + (rhs.m[1][2] * y) + (rhs.m[2][2] * z) + (rhs.m[3][2] * w);
	output.m[2][3] = (rhs.m[0][3] * x) + (rhs.m[1][3] * y) + (rhs.m[2][3] * z) + (rhs.m[3][3] * w);

	x = lhs.m[3][0];
	y = lhs.m[3][1];
	z = lhs.m[3][2];
	w = lhs.m[3][3];
	output.m[3][0] = (rhs.m[0][0] * x) + (rhs.m[1][0] * y) + (rhs.m[2][0] * z) + (rhs.m[3][0] * w);
	output.m[3][1] = (rhs.m[0][1] * x) + (rhs.m[1][1] * y) + (rhs.m[2][1] * z) + (rhs.m[3][1] * w);
	output.m[3][2] = (rhs.m[0][2] * x) + (rhs.m[1][2] * y) + (rhs.m[2][2] * z) + (rhs.m[3][2] * w);
	output.m[3][3] = (rhs.m[0][3] * x) + (rhs.m[1][3] * y) + (rhs.m[2][3] * z) + (rhs.m[3][3] * w);
	
	return output;
}

inline Vector4F operator*(const Vector4F& rowVec, const Mat4x4& matrix)
{
	Vector4F output;

	output.x = rowVec.x * matrix.m[0][0] + rowVec.y * matrix.m[1][0] +
		rowVec.z * matrix.m[2][0] + rowVec.w * matrix.m[3][0];
	output.y = rowVec.x * matrix.m[0][1] + rowVec.y * matrix.m[1][1] +
		rowVec.z * matrix.m[2][1] + rowVec.w * matrix.m[3][1];
	output.z = rowVec.x * matrix.m[0][2] + rowVec.y * matrix.m[1][2] +
		rowVec.z * matrix.m[2][2] + rowVec.w * matrix.m[3][2];
	output.w = rowVec.x * matrix.m[0][3] + rowVec.y * matrix.m[1][3] +
		rowVec.z * matrix.m[2][3] + rowVec.w * matrix.m[3][3];

	return output;
}
