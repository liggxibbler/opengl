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
	glGenVertexArrays(1, &m_vao);	
	glGenBuffers(1, &m_ebo);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vert_count * m_vert_stride, m_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_count * sizeof(m_indices), m_indices, GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_vert_stride * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, m_vert_stride * sizeof(float), (void*)(3 * sizeof(float)));

	if(m_has_normal)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, m_vert_stride * sizeof(float), (void*)(5 * sizeof(float)));
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

	m_indices = new unsigned int [m_vert_count * 3];
	for (int i = 0; i < m_vert_count * 3; ++i)
	{
		m_indices[i] = i;
	}

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

	m_indices = new unsigned int [m_vert_count * 3];
	for (int i = 0; i < m_vert_count * 3; ++i)
	{
		m_indices[i] = i;
	}

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
