#pragma once

#include <PxPhysicsAPI.h>

class Vector3D
{
private:
	float _x, _y, _z;

public:
	Vector3D(float x = 0, float y = 0, float z = 0);
	Vector3D(physx::PxVec3);

	float x() {
		return _x;
	}

	float y() {
		return _y;
	}

	float z() {
		return _z;
	}

	float magnitude() const {

	}

	Vector3D normalize() const {

	}

	Vector3D cross(const Vector3D& v) const {

	}

	float dot(const Vector3D& v) const {

	}

	bool operator=(const Vector3D& other) {

	}

	Vector3D operator+(const Vector3D& other) {

	}

	Vector3D operator-(const Vector3D& other) {

	}

};

