#pragma once
#include <vector>
#include <GL\glew.h>
#include "../Lab1/stb_image.h"
#include "../Lab1/Shader.h"
#include <iostream>
#include "../Lab1/Camera.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox();
	void init(std::vector<std::string> faces);
	void draw(Camera* myCamera);

	unsigned int textureID;
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;

private:
	GLuint vbo;
	GLuint vao;
	Shader skyboxShader;
};

