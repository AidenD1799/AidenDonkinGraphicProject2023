#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"

#include "SkyBox.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void startApplication();

private:

	void initialiseApplication();
	void manageInput();
	void appLoop();
	void renderGame();
	


	void linkGeomShader();
	void renderGeomShader();

	void linkEnvMapShader();
	void renderEnvMapShader();



	void linkSunShader();
	void renderSunShader();

	Display _applicationDisplay;
	GameState _applicationState;
	Mesh sunShaderMesh;
	Mesh envMapShaderMesh;
	Mesh geomShaderMesh;
	Camera applicationCamera;

	Shader geomShader;
	Shader sbShader;
	Shader envMapShader;
	Shader sunShader;

	SkyBox applicationSkybox;
	vector <std::string> skyboxSides;

	Texture sunShaderTexture;
	Texture envMapTexture;
	Texture silverTexture;

	
	//Audio audioDevice;

	float timeVar;

};

