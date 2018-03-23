#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include <glad/glad.h>
#include "stb_image.h"

class Texture2D
{
	public:
		Texture2D(const char* path);
		void Use();
	private:
		unsigned char* m_data;
		int m_width;
		int m_height;
		int m_nrChannels;
		unsigned int m_texture;
};

#endif
