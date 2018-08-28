#pragma once
#define GLM_FORCE_SWIZZLE
#include <glm/glm/glm.hpp>
#include <glm/glm/fwd.hpp>
#include <glm/glm/ext.hpp>

class Transform
{
public:
	Transform();
	~Transform();

	glm::mat4 Translate(glm::vec3 move);
	glm::mat4 Rotate(float radians, glm::vec3 axis);
	glm::mat4 Scale(float size);
	void SetModel(glm::mat4 newModel);
	glm::mat4 GetModel();
private:
	/*
	xyzw
	1000
	0100
	0010
	0001
	*/
	glm::mat4 m_model; //The matrix representing the object. Starts as a identity matrix.

	glm::vec3 m_worldPosition; // Takes in the w column values
	glm::vec3 m_localPosition; //

	glm::mat3 m_worldRotation; // 3x3 matrix that takes in the top left values of the identity matrix
	glm::mat3 m_localRotation; //

	glm::vec3 m_worldScale; // Takes in the diagonals of the matrix
	glm::vec3 m_localScale; //
	
	
};

