#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Model.h"

#define SCR_WIDTH 800.0f
#define SCR_HEIGHT 800.0f

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

glm::vec3 velocity;
glm::vec3 eulerVel;
float zoomVelocity;

glm::vec3 positions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f), 
  glm::vec3( 2.0f,  5.0f, -15.0f), 
  glm::vec3(-1.5f, -2.2f, -2.5f),  
  glm::vec3(-3.8f, -2.0f, -12.3f),  
  glm::vec3( 2.4f, -0.4f, -3.5f),  
  glm::vec3(-1.7f,  3.0f, -7.5f),  
  glm::vec3( 1.3f, -2.0f, -2.5f),  
  glm::vec3( 1.5f,  2.0f, -2.5f), 
  glm::vec3( 1.5f,  0.2f, -1.5f), 
  glm::vec3(-1.3f,  1.0f, -1.5f)  
};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

glm::vec4 light_col(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 light_pos(0.0f, 2.0f, 0.0f);

int main(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (NULL == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	Model cmodel;
	cmodel.InitCube();
	cmodel.Initialize();

	Camera camera(SCR_WIDTH, SCR_HEIGHT, 45.0f, .1f, 100.0f);
	Shader shader("phong.vert", "phong.frag");
	Texture2D texture0("brickwall.jpg");
	Texture2D texture1("container.jpg");
	shader.Use();
	shader.SetInt("texture0", 0);
	shader.SetInt("texture1", 1);

	float lastT = glfwGetTime();
	float dt;

	float shininess = 32.0f;

	while(!glfwWindowShouldClose(window))
	{
		float time1 = glfwGetTime();
		dt = time1 - lastT;
		lastT = time1;

		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		shader.SetVec4("time1", time1, time1, time1, time1);
		texture0.Use(GL_TEXTURE0);
		texture1.Use(GL_TEXTURE1);		

		camera.Update(dt, eulerVel, velocity, zoomVelocity);
		glm::vec3 cameraPos = camera.GetPos();
		shader.SetMatrix("projection", glm::value_ptr(camera.GetProjection()));
		shader.SetMatrix("view", glm::value_ptr(camera.GetView()));
		//shader.SetVec4("light_pos", light_pos.x, light_pos.y, light_pos.z, 1.0f);
		shader.SetVec4("light_pos", cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);
		shader.SetVec4("light_col", light_col.x, light_col.y, light_col.z, light_col.w);
		shader.SetVec4("eye_pos", cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);
		shader.SetVec4("shininess", shininess, shininess, shininess, shininess);

		cmodel.Bind();
		for (int i = 0; i < 10; ++i)
		{			
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, positions[i]);
			model = glm::rotate(model, glm::radians(time1 * 10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			shader.SetMatrix("model", glm::value_ptr(model));
			glm::mat4 normalTrans = glm::transpose(glm::inverse(model));
			shader.SetMatrix("normalTrans", glm::value_ptr(normalTrans));
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			cmodel.Draw(GL_TRIANGLES);
		}
		glBindVertexArray(0);

		glfwSwapBuffers(window);

		eulerVel.x = 0;
		eulerVel.y = 0;
		eulerVel.z = 0;

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	float speed = 2.5f;

	velocity.x = 0.0f;
	velocity.y = 0.0f;
	velocity.z = 0.0f;

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		velocity.z += speed;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		velocity.z -= speed;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		velocity.x += speed;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		velocity.x -= speed;
}

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 2.5f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	//std::cout << xoffset << ", " << yoffset << std::endl;

	eulerVel.x = -yoffset;
	eulerVel.y = xoffset;
}
