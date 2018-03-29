#pragma once
#include <glm\glm.hpp>
class Vector
{
public:
	Vector();
	Vector(const Vector & a);
	Vector(float x, float y, float z);
	Vector& operator = (const Vector & a);
	float getMagnitude();
	const float& getX();
	const float& getY();
	const float& getZ();
	void setVector(float x, float y, float z);
	static Vector calculateNorm(const Vector & a, const Vector & b);
	static float dotProduct(const Vector & a, const Vector & b);
	static float distBetweenPaPb(const Vector & a, const Vector & b);
	static Vector calculateUnitNorm(const Vector & a, const Vector & b);
	static Vector add(const Vector &a, const Vector & b);
	static Vector scalarMultiply(const Vector &a, float multplyValue);
	static Vector subtract(const Vector &a, const Vector & b);
	~Vector();
private: 
	glm::vec3 vectorXYZ;
	float magnitude;
};

