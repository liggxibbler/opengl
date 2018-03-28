#ifndef RENDERTEXTURE_H_
#define RENDERTEXTURE_H_

#include <glad/glad.h>

class RenderTexture
{
	public:
		RenderTexture(int width, int height);
		void Bind();
		void Drop();
		void Use(GLenum unit);
	private:
		int m_width;
		int m_height;
		unsigned int m_framebuffer;
		unsigned int m_depth_stencil_buffer;
		unsigned int m_texture;
};

#endif
