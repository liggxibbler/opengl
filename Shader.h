#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

class Shader
{
	public:
		Shader(const char* vertexShader, const char* fragmentShader);
		void Use();
		void SetFloat(const std::string& name, float value) const;
		void SetVec4(const std::string& name, float x, float y, float z, float w) const;
		//SetInt(std::string name, int value) const;
		//SetBoolean(std::string name, bool value) const;
	private:
		unsigned int m_id;
};

#endif
