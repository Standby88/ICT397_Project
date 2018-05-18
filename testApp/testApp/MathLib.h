#pragma once
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
typedef glm::vec3 V3;
typedef glm::vec2 V2;
typedef glm::mat3 M3;
typedef glm::mat4 M4;
class MathLib
{
public:
	static M4 perspective(float const & fovy, float const & aspect, float const & near, float const & far)
	{
		return glm::perspective(fovy, aspect, near, far);
	}
	static V3 cross(V3 const & A, V3 const & B)
	{
		return glm::cross(A, B);
	}
	static V3 normalize(V3 const & A)
	{
		return glm::normalize(A);
	}
	static float radians(float const & A)
	{
		return glm::radians(A);
	}
	static M4 lookAt(V3 const & A, V3 const & B, V3 const & C)
	{
		return glm::lookAt(A,B,C);
	}
	template <typename T>
	static T value_ptr(M4 const & V)
	{
		return glm::value_ptr(V);
	}
	static M4 rotate(M4 const & A, float const & B, V3 const & C)
	{
		return glm::rotate(A, B, C);
	}
	static M4 translate(M4 const & A, V3 const & C)
	{
		return glm::translate(A, C);
	}
	static M4 scale(M4 const & A, V3 const & C)
	{
		return glm::scale(A, C);
	}

};

