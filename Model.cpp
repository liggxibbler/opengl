#include "Model.h"
#include <iostream>

Model::Model()
{
}

Model::Model(const char* path)
{
}

void Model::Initialize()
{
	//std::cout << "m_vao before: " << m_vao << std::endl;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	//std::cout << "m_vao after: " << m_vao << std::endl;
	
	//glGenBuffers(1, &m_ebo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vert_count * m_vert_stride, m_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_vert_stride * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, m_vert_stride * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	if(m_has_normal)
	{
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, m_vert_stride * sizeof(float), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
}

void Model::Bind()
{
	glBindVertexArray(m_vao);
}

void Model::Draw(GLenum primitive)
{
	glDrawArrays(primitive, 0, m_vert_count);
}

void Model::InitNDCQuad()
{
	m_vert_count = 6;
	m_vert_stride = 5;
	m_has_normal = false;

	m_vertices = new float[m_vert_count * m_vert_stride] {
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,

		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f
	};
}

void Model::InitCube()
{
	m_vert_count = 36;
	m_vert_stride = 8;
	m_has_normal = true;

	m_vertices = new float[m_vert_count * m_vert_stride] {
    -0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f, 0.0f, -1.0f, 
     0.5f, -0.5f, -0.5f,  	1.0f, 0.0f, 	0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 	0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 	0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  	0.0f, 1.0f, 	0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  	0.0f, 0.0f, 	0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 	0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  	1.0f, 0.0f, 	0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 	0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 	0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  	0.0f, 1.0f, 	0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 	0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 	-1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 	-1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 	-1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 	-1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 	-1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 	-1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 	1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 	1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 	1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 	1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 	1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 	1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 	0.0f, -1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  	1.0f, 1.0f, 	0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  	1.0f, 0.0f, 	0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  	1.0f, 0.0f, 	0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 	0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 	0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  	0.0f, 1.0f, 	0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 	0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 	0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 	0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  	0.0f, 0.0f, 	0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  	0.0f, 1.0f, 	0.0f, 1.0f, 0.0f
	};
}
