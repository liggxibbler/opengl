#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <map>
#include <string>

#include "Shader.h"
#include "Texture2D.h"

class Material
{
	public:
		Material(Shader* shader);
		~Material();
		void Draw();
		void AddTexture();
	private:
		Shader* m_shader;
		Texture2D* m_textures;
};

#endif
