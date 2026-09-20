#pragma once

#include <PxPhysicsAPI.h>
#include <cmath>

class Vector3D
{

public:
	float x, y, z;

	//Constructores
	Vector3D(float x = 0, float y = 0, float z = 0);
	Vector3D(const physx::PxVec3& v);

	float magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector3D normalize() const {
		float m = magnitude();
		if (m == 0)
		{
			return Vector3D();
		}

		return Vector3D(x / m, y / m, z / m);
	}

	Vector3D cross(const Vector3D& v) const {
		return Vector3D
		(
			y *v.z - z * v.y,
			z *v.x - x * v.z,
			x *v.y -y * v.x
		);
	}

	float dot(const Vector3D& v) const {
		return x * v.x + y * v.y + z* v.z;
	}

	Vector3D& operator=(const Vector3D& v) {
		x = v.x;
		y = v.y;
		z= v.z;

		return *this;
	}

	Vector3D operator+(const Vector3D& v) const {
		return Vector3D
		(
			x + v.x,
			y + v.y,
			z + v.z
		);
	}

	Vector3D operator-(const Vector3D& v) const {
		return Vector3D
		(
			x - v.x,
			y - v.y,
			z - v.z
		);

	}

	Vector3D operator*(float escalar) const {
		return Vector3D
		(
			x * escalar,
			y * escalar,
			z * escalar
		);
	}

	Vector3D& operator+=(const Vector3D& v) {
		x +=v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	//conversin a physx
	operator physx::PxVec3() const {
		return physx::PxVec3(x, y, z);
	}

};

