#include "Camera.h"
#include <iostream>

Camera::Camera(int width, int height, float fov, float near, float far)
	: m_scr_width(width), m_scr_height(height), m_fov(fov), m_near(near), m_far(far)
{
	m_projection = glm::perspective(glm::radians(m_fov), (float)m_scr_width / m_scr_height, m_near, m_far);
	m_euler = glm::vec3(0.0f, 90.0f, 0.0f);
	m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_right = glm::vec3(-1.0f, 0.0f, 0.0f);
	m_view = glm::lookAt(glm::vec3(0.0,0.0,0.0), m_forward, m_up);
	m_projView = m_projection * m_view;
}

void Camera::Update(float dt, glm::vec3 dEuler, glm::vec3 dPos, float dFov)
{
	bool viewChanged = false;
	bool projChanged = false;
	
	if (dFov != 0)
	{
		projChanged = true;
		m_fov += dFov * dt;

		if (m_fov < 1.0f)
		{
			m_fov = 1.0f;
		}
		else if (m_fov > 45.0f)
		{
			m_fov = 45.0f;
		}

		m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
	}
	
	if (dEuler.x != 0 || dEuler.y != 0)
	{	
		viewChanged = true;
		m_euler += dEuler * dt;
		if (m_euler.x > 89.0f)
		{
			m_euler.x = 89.0f;
		}
		else if (m_euler.x < -89.0f)
		{
			m_euler.x = -89.0f;
		}
	
		float yaw = glm::radians(m_euler.y);
		float pitch = glm::radians(m_euler.x);

		m_forward = glm::vec3( glm::cos(yaw) * glm::cos(pitch), glm::sin(pitch), glm::cos(pitch) * glm::sin(yaw));
		m_right = glm::normalize(glm::cross(m_forward, m_up));
	}
	
	if (dPos.x != 0 || dPos.y != 0 || dPos.z != 0)
	{
		viewChanged = true;
		glm::vec3 delPos = dPos * dt;
		m_pos += delPos.z * m_forward + delPos.x * m_right + delPos.y * m_up;
		std::cout << "Pos " << m_pos.x << " " << m_pos.y << " " << m_pos.z << std::endl;
	}

	if (viewChanged)
	{
		m_view = glm::lookAt(m_pos, m_pos + m_forward, m_up);
		if (projChanged)
		{
			m_projView = m_projection * m_view;
		}
	}
}

glm::mat4& Camera::GetProjection()
{
	return m_projection;
}

glm::mat4& Camera::GetView()
{
	return m_view;
}

glm::mat4& Camera::GetProjView()
{
	return m_projView;
}

void Camera::Dump()
{
	std::cout << "Right is " << m_right.x << ", " << m_right.y << ", " << m_right.z << std::endl;
}

glm::vec3 Camera::GetPos()
{
	return m_pos;
}
