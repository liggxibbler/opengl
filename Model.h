#ifndef MODEL_H_
#define MODEL_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 UV0;
	glm::vec3 Normal;
};

class Model
{
	public:
		Model();
		Model(const char* path);
		void Initialize();
		void InitCube();
		void InitNDCQuad();
		void Bind();
		void Draw(GLenum primitive);
		//void SetMaterial(Material* material);
	private:
		bool m_has_normal;
		//Material* m_material;
		int m_index_count;
		int m_vert_count;
		int m_vert_stride;
		float* m_vertices;
		unsigned int* m_indices;
		unsigned int m_vao;
		unsigned int m_vbo;
		unsigned int m_ebo;	
};

#endif
