#include "Vector.h"

Vector::Vector()
{
	vectorXYZ.x = 0;
	vectorXYZ.y = 0;
	vectorXYZ.z = 0;
	magnitude = 0;
}
Vector::Vector(const Vector &a)
{
	vectorXYZ.x = a.vectorXYZ.x;
	vectorXYZ.y = a.vectorXYZ.y;
	vectorXYZ.z = a.vectorXYZ.z;
}
Vector::Vector(float x, float y, float z)
{
	vectorXYZ.x = x;
	vectorXYZ.y = y;
	vectorXYZ.z = z;
	magnitude = glm::length(vectorXYZ);
}

Vector & Vector::operator=(const Vector & a)
{
	if (this == &a)
	{
		return *this;
	}
	this->vectorXYZ.x = a.vectorXYZ.x;
	this->vectorXYZ.y = a.vectorXYZ.y;
	this->vectorXYZ.z = a.vectorXYZ.z;
	this->magnitude = glm::length(vectorXYZ);
	return *this;
}

float Vector::getMagnitude()
{
	return magnitude;
}

const float& Vector::getX()
{
	return vectorXYZ.x;
}

const float& Vector::getY()
{
	return vectorXYZ.y;
}

const float& Vector::getZ()
{
	return vectorXYZ.z;
}

Vector Vector::calculateNorm(const Vector & a, const Vector & b)
{
	Vector norm;
	norm.vectorXYZ = glm::cross(a.vectorXYZ, b.vectorXYZ);
	return norm;
}

float Vector::dotProduct(const Vector & a, const Vector & b)
{
	return glm::dot(a.vectorXYZ, b.vectorXYZ);
}

float Vector::distBetweenPaPb(const Vector &a, const Vector &b)
{
	return glm::distance(a.vectorXYZ, b.vectorXYZ);
}

Vector Vector::calculateUnitNorm(const Vector & a, const Vector & b)
{
	Vector unitNorm;
	unitNorm.vectorXYZ = glm::cross(a.vectorXYZ, b.vectorXYZ);
	unitNorm.vectorXYZ = glm::normalize(unitNorm.vectorXYZ);
	return unitNorm; 
}

Vector Vector::add(const Vector &a, const Vector & b)
{
	Vector result;
	result.vectorXYZ.x = a.vectorXYZ.x + b.vectorXYZ.x;
	result.vectorXYZ.y = a.vectorXYZ.y + b.vectorXYZ.y;
	result.vectorXYZ.z = a.vectorXYZ.z + b.vectorXYZ.z;
	return result;
}

Vector Vector::scalarMultiply(const Vector & a, float multplyValue)
{
	Vector holder(a.vectorXYZ.x*multplyValue, a.vectorXYZ.y*multplyValue, a.vectorXYZ.z*multplyValue);
	return holder;
}



void Vector::setVector(float x, float y, float z)
{
	vectorXYZ.x = x;
	vectorXYZ.y = y;
	vectorXYZ.z = z;
	magnitude = glm::length(vectorXYZ);
}


Vector Vector::subtract(const Vector & a, const Vector & b)
{
	Vector result;
	result.vectorXYZ.x = a.vectorXYZ.x - b.vectorXYZ.x;
	result.vectorXYZ.y = a.vectorXYZ.y - b.vectorXYZ.y;
	result.vectorXYZ.z = a.vectorXYZ.z - b.vectorXYZ.z;
	return result;
}

Vector::~Vector()
{
}
