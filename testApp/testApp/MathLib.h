#pragma once
#include <glm\gtc\type_ptr.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
typedef glm::vec3 V3;
typedef glm::vec2 V2;
typedef glm::mat3 M3;
typedef glm::mat4 M4;

/**
* @class MathLib
* @brief Used to facade glm 
*
*
* @author 
* @version 1
* @date
*
* @todo
*
* @bug
*/
class MathLib
{
public:

	/**
	* @brief returns perspective matrix
	* @param float const&, float const&, float const&, float const&
	* @return M4
	*/
	static M4 perspective(float const & fovy, float const & aspect, float const & near, float const & far)
	{
		return glm::perspective(fovy, aspect, near, far);
	}

	/**
	* @brief returns the cross product of two 3D vectors
	* @param V3 const&, V3 const&
	* @return V3
	*/
	static V3 cross(V3 const & A, V3 const & B)
	{
		return glm::cross(A, B);
	}

	/**
	* @brief normalises a 3D vector
	* @param V3 const&
	* @return V3
	*/
	static V3 normalize(V3 const & A)
	{
		return glm::normalize(A);
	}

	/**
	* @brief converts degrees to radians
	* @param float const&
	* @return float
	*/
	static float radians(float const & A)
	{
		return glm::radians(A);
	}

	/**
	* @brief set
	* @param
	* @return
	*/
	static M4 lookAt(V3 const & A, V3 const & B, V3 const & C)
	{
		return glm::lookAt(A,B,C);
	}

	/**
	* @brief
	* @param M4 const&
	* @return T
	*/
	template <typename T>
	static T value_ptr(M4 const & V)
	{
		return glm::value_ptr(V);
	}

	/**
	* @brief rotates a matrix
	* @param M4 const&, float const&, V3 const&
	* @return M4
	*/
	static M4 rotate(M4 const & A, float const & B, V3 const & C)
	{
		return glm::rotate(A, B, C);
	}

	/**
	* @brief translates a matrix
	* @param M4 const&, V3 const&
	* @return M4
	*/
	static M4 translate(M4 const & A, V3 const & C)
	{
		return glm::translate(A, C);
	}

	/**
	* @brief scales a matrix
	* @param M4 const&, V3 const&
	* @return M4
	*/
	static M4 scale(M4 const & A, V3 const & C)
	{
		return glm::scale(A, C);
	}

};

