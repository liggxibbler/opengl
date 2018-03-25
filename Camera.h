#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	public:
		Camera(int width, int height, float fov, float near, float far);
		void Update(float dt, glm::vec3 dEuler, glm::vec3 dPos, float dFov);
		glm::mat4& GetView();
		glm::mat4& GetProjection();
		glm::mat4& GetProjView();
		void Dump();
		glm::vec3 GetPos();
	private:
		float m_fov;
		float m_aspect;
		float m_near;
		float m_far;
		int m_scr_width;
		int m_scr_height;

		glm::vec3 m_euler;
		glm::vec3 m_pos;
		glm::vec3 m_forward;
		glm::vec3 m_up;
		glm::vec3 m_right;
		
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::mat4 m_projView;
};

#endif
