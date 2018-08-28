#include "Transform.h"



Transform::Transform()
{
	m_model = glm::mat4(1);
	m_worldPosition = m_model[3];
	m_localPosition = m_model[3];
	for (int col = 0; col < 3; col++)
	{
		m_worldRotation[col] = m_model[col].xyz;
		m_localRotation[col] = m_model[col].xyz;
	}
	m_worldScale = glm::vec3(m_model[0].x, m_model[1].y, m_model[2].z);
	m_localScale = glm::vec3(m_model[0].x, m_model[1].y, m_model[2].z);
}


Transform::~Transform()
{
}

glm::mat4 Transform::Translate(glm::vec3 move)
{
	glm::mat4 translation = glm::mat4(1);
	translation[3].xyz = move;
	m_model += translation;
	return m_model;
}

glm::mat4 Transform::Rotate(float radians, glm::vec3 axis)
{
	auto cosine = cos(radians);
	auto sine = sin(radians);
	//if x rotate
	if (axis == glm::vec3(1, 0, 0))
	{
		//rotating along x means x doesnt change
		m_model[1].y = cosine;
		m_model[1].z = sine;
		m_model[2].y = -sin(radians);
		m_model[2].z = cosine;
	}
	//if y rotate
	if (axis == glm::vec3(0, 1, 0))
	{
		m_model[0].x = cosine;
		m_model[0].z = -sin(radians);
		m_model[2].x = sine;
		m_model[2].z = cosine;
	}
	//if z rotate
	if (axis == glm::vec3(0, 0, 1))
	{
		m_model[0].x = cosine;
		m_model[0].y = -sin(radians);
		m_model[1].x = sine;
		m_model[1].y = cosine;
	}
	return m_model;
}

glm::mat4 Transform::Scale(float size)
{
	glm::mat4 scale = glm::mat4(1);
	scale[0].x = size;
	scale[1].y = size;
	scale[2].z = size;
	m_model *= scale;
	return m_model;
}
