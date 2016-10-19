/*
	Matrix.cpp
	Author: Dean Marsinelli
*/

#include <DirectXMath.h>

#include "Matrix.h"

const double kThreshold = 0.001;

const Mat4x4 Mat4x4::Identity = Mat4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

Mat4x4::Mat4x4()
{
	m[0][0] = 0.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 0.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 0.0f;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 0.0f;
}

Mat4x4::Mat4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;

	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;

	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;

	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

Mat4x4::Mat4x4(const Mat4x4& matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = matrix.m[i][j];
		}
	}
}

void Mat4x4::SetPosition(const Vector3F& position)
{
	m[3][0] = position.x;
	m[3][1] = position.y;
	m[3][2] = position.z;
	m[3][3] = 1.0f;
}


void Mat4x4::SetPosition(const Vector4F& position)
{
	m[3][0] = position.x;
	m[3][1] = position.y;
	m[3][2] = position.z;
	m[3][3] = position.w;
}


void Mat4x4::SetScale(const Vector3F& scale)
{
	m[0][0] = scale.x;
	m[1][1] = scale.y;
	m[2][2] = scale.z;
}

void Mat4x4::RotateMatrix(const float yawRadians, const float pitchRadians, const float rollRadians)
{
	// I used direct x math for this to get it done quickly
	using namespace DirectX;
	XMMATRIX xm_mat = XMMatrixRotationRollPitchYaw(pitchRadians, yawRadians, rollRadians);
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, xm_mat);

	Mat4x4 rot;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rot.m[i][j] = float4x4.m[i][j];
		}
	}

	*this = rot * (*this);
}

Vector3F Mat4x4::GetPosition() const
{
	return Vector3F(m[3][0], m[3][1], m[3][2]);
}

Vector3F Mat4x4::GetDirection() const
{
	Mat4x4 justRot = *this;
	justRot.SetPosition(Vector3F(0.0f, 0.0f, 0.0f));
	Vector3F forward = justRot.Transform(Vector3F(0.0f, 0.0f, 1.0f));
	return forward;
}

Vector3F Mat4x4::GetRight() const
{
	Mat4x4 justRot = *this;
	justRot.SetPosition(Vector3F(0.0f, 0.0f, 0.0f));
	Vector3F right = justRot.Transform(Vector3F(1.0f, 0.0f, 0.0f));
	return right;
}

Vector3F Mat4x4::GetUp() const
{
	Mat4x4 justRot = *this;
	justRot.SetPosition(Vector3F(0.0f, 0.0f, 0.0f));
	Vector3F up = justRot.Transform(Vector3F(0.0f, 1.0f, 0.0f));
	return up;
}

Vector3F Mat4x4::GetYawPitchRoll() const
{
	float yaw, pitch, roll;

	pitch = std::asin(-_23);

	double test = std::cos(pitch);
	if (test > kThreshold)
	{
		roll = std::atan2(_21, _22);
		yaw = std::atan2(_13, _33);
	}
	else
	{
		roll = std::atan2(-_12, _11);
		yaw = 0.0f;
	}

	return Vector3F(yaw, pitch, roll);
}

Vector4F Mat4x4::Transform(Vector4F &vec) const
{
	// transform vec by this 4x4 matrix
	return vec * (*this);
}

Vector3F Mat4x4::Transform(Vector3F &vec) const
{
	// transform vec by this 4x4 matrix
	Vector4F input(vec);
	Vector4F output = input * (*this);
	
	return Vector3F(output.x, output.y, output.z);
}

Mat4x4 Mat4x4::Inverse(float& det) const
{
	det = 0.0f;
	Mat4x4 inverse;
	int i;

	inverse.m_[0] = m_[5] * m_[10] * m_[15] -
		m_[5] * m_[11] * m_[14] -
		m_[9] * m_[6] * m_[15] +
		m_[9] * m_[7] * m_[14] +
		m_[13] * m_[6] * m_[11] -
		m_[13] * m_[7] * m_[10];

	inverse.m_[4] = -m_[4] * m_[10] * m_[15] +
		m_[4] * m_[11] * m_[14] +
		m_[8] * m_[6] * m_[15] -
		m_[8] * m_[7] * m_[14] -
		m_[12] * m_[6] * m_[11] +
		m_[12] * m_[7] * m_[10];

	inverse.m_[8] = m_[4] * m_[9] * m_[15] -
		m_[4] * m_[11] * m_[13] -
		m_[8] * m_[5] * m_[15] +
		m_[8] * m_[7] * m_[13] +
		m_[12] * m_[5] * m_[11] -
		m_[12] * m_[7] * m_[9];

	inverse.m_[12] = -m_[4] * m_[9] * m_[14] +
		m_[4] * m_[10] * m_[13] +
		m_[8] * m_[5] * m_[14] -
		m_[8] * m_[6] * m_[13] -
		m_[12] * m_[5] * m_[10] +
		m_[12] * m_[6] * m_[9];

	inverse.m_[1] = -m_[1] * m_[10] * m_[15] +
		m_[1] * m_[11] * m_[14] +
		m_[9] * m_[2] * m_[15] -
		m_[9] * m_[3] * m_[14] -
		m_[13] * m_[2] * m_[11] +
		m_[13] * m_[3] * m_[10];

	inverse.m_[5] = m_[0] * m_[10] * m_[15] -
		m_[0] * m_[11] * m_[14] -
		m_[8] * m_[2] * m_[15] +
		m_[8] * m_[3] * m_[14] +
		m_[12] * m_[2] * m_[11] -
		m_[12] * m_[3] * m_[10];

	inverse.m_[9] = -m_[0] * m_[9] * m_[15] +
		m_[0] * m_[11] * m_[13] +
		m_[8] * m_[1] * m_[15] -
		m_[8] * m_[3] * m_[13] -
		m_[12] * m_[1] * m_[11] +
		m_[12] * m_[3] * m_[9];

	inverse.m_[13] = m_[0] * m_[9] * m_[14] -
		m_[0] * m_[10] * m_[13] -
		m_[8] * m_[1] * m_[14] +
		m_[8] * m_[2] * m_[13] +
		m_[12] * m_[1] * m_[10] -
		m_[12] * m_[2] * m_[9];

	inverse.m_[2] = m_[1] * m_[6] * m_[15] -
		m_[1] * m_[7] * m_[14] -
		m_[5] * m_[2] * m_[15] +
		m_[5] * m_[3] * m_[14] +
		m_[13] * m_[2] * m_[7] -
		m_[13] * m_[3] * m_[6];

	inverse.m_[6] = -m_[0] * m_[6] * m_[15] +
		m_[0] * m_[7] * m_[14] +
		m_[4] * m_[2] * m_[15] -
		m_[4] * m_[3] * m_[14] -
		m_[12] * m_[2] * m_[7] +
		m_[12] * m_[3] * m_[6];

	inverse.m_[10] = m_[0] * m_[5] * m_[15] -
		m_[0] * m_[7] * m_[13] -
		m_[4] * m_[1] * m_[15] +
		m_[4] * m_[3] * m_[13] +
		m_[12] * m_[1] * m_[7] -
		m_[12] * m_[3] * m_[5];

	inverse.m_[14] = -m_[0] * m_[5] * m_[14] +
		m_[0] * m_[6] * m_[13] +
		m_[4] * m_[1] * m_[14] -
		m_[4] * m_[2] * m_[13] -
		m_[12] * m_[1] * m_[6] +
		m_[12] * m_[2] * m_[5];

	inverse.m_[3] = -m_[1] * m_[6] * m_[11] +
		m_[1] * m_[7] * m_[10] +
		m_[5] * m_[2] * m_[11] -
		m_[5] * m_[3] * m_[10] -
		m_[9] * m_[2] * m_[7] +
		m_[9] * m_[3] * m_[6];

	inverse.m_[7] = m_[0] * m_[6] * m_[11] -
		m_[0] * m_[7] * m_[10] -
		m_[4] * m_[2] * m_[11] +
		m_[4] * m_[3] * m_[10] +
		m_[8] * m_[2] * m_[7] -
		m_[8] * m_[3] * m_[6];

	inverse.m_[11] = -m_[0] * m_[5] * m_[11] +
		m_[0] * m_[7] * m_[9] +
		m_[4] * m_[1] * m_[11] -
		m_[4] * m_[3] * m_[9] -
		m_[8] * m_[1] * m_[7] +
		m_[8] * m_[3] * m_[5];

	inverse.m_[15] = m_[0] * m_[5] * m_[10] -
		m_[0] * m_[6] * m_[9] -
		m_[4] * m_[1] * m_[10] +
		m_[4] * m_[2] * m_[9] +
		m_[8] * m_[1] * m_[6] -
		m_[8] * m_[2] * m_[5];

	det = m_[0] * inverse.m_[0] + m_[1] * inverse.m_[4] + m_[2] * inverse.m_[8] + m_[3] * inverse.m_[12];

	if (det == 0)
		return Mat4x4();

	det = 1.0f / det;

	for (i = 0; i < 16; i++)
		inverse.m_[i] = inverse.m_[i] * det;

	return inverse;
}

Mat4x4 Mat4x4::Transpose() const
{
	Mat4x4 output;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			output.m[i][j] = this->m[j][i];
		}
	}

	return output;
}

Mat4x4& Mat4x4::operator=(const Mat4x4& rhs)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = rhs.m[i][j];
		}
	}

	return *this;
}

bool Mat4x4::operator==(const Mat4x4& rhs) const
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((m[i][j] > rhs.m[i][j] + kThreshold) || (m[i][j] < rhs.m[i][j] - kThreshold))
			{
				return false;
			}
		}
	}
	return true;
}

bool Mat4x4::operator!=(const Mat4x4& rhs) const
{
	return (!(*this == rhs));
}
