#ifndef MODEL_H_
#define MODEL_H_

#include <glad/glad.h>

class Model
{
	public:
		Model();
		Model(const char* path);
		void Initialize();
		void InitCube();
		void Bind();
		void Draw(GLenum primitive);
	private:
		int m_vert_count;
		int m_vert_stride;
		float* m_vertices;
		unsigned int* m_indices;
		unsigned int m_vao;
		unsigned int m_vbo;
		unsigned int m_ebo;	
};

#endif
