#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

MainGame::MainGame()
{
	_applicationState = GameState::PLAY;
	Display* _gameDisplay = new Display(); 
	
}

MainGame::~MainGame()
{
}

void MainGame::startApplication()
{
	initialiseApplication(); 
	appLoop();
}

void MainGame::initialiseApplication()
{
	_applicationDisplay.initDisplay(); 

	
	sunShaderMesh.loadModel("..\\res\\Ball.obj"); //Retrieves 3D objects for shaders to be applied to
	envMapShaderMesh.loadModel("..\\res\\Ball.obj");
	geomShaderMesh.loadModel("..\\res\\Ball.obj");
	
	sunShaderTexture.load ("..\\res\\sunTexture2.jpg"); //Retrieves textures from application files
	envMapTexture.load("..\\res\\wavy.jpg"); 
	silverTexture.load("..\\res\\silver.jpg");
	
	envMapShader.initialiseShader("..\\res\\envMapping.vert", "..\\res\\envMapping.frag"); //Initialises environment mapping shader
	sunShader.initialiseShader("..\\res\\sunShader.vert", "..\\res\\sunShader.frag"); //Initialises sun shader
	geomShader.initialiseGeoShader("..\\res\\shaderGeoText.vert", "..\\res\\shaderGeoText.frag", "..\\res\\shaderGeoText.geom"); //Initialises geometry shader

	applicationCamera.initCamera(glm::vec3(2, 0, -4), 70.0f, (float)_applicationDisplay.getWidth() / _applicationDisplay.getHeight(), 0.01f, 1000.0f); //Initialises application camera

	vector<std::string> skyboxSides //Creates list of skybox sides
	{
		"..\\res\\skybox\\right.jpg", //Retrieves skybox images from application files
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};
	applicationSkybox.init(skyboxSides); //Initialises application skybox


	timeVar = 1.0f; //Assigns time variable
}

void MainGame::appLoop()
{
	while (_applicationState != GameState::EXIT)
	{
		manageInput();
		renderGame();
	}
}

void MainGame::manageInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_applicationState = GameState::EXIT;
				break;
		}
	}
	
}

void MainGame::linkGeomShader() //Function to set up geometry shader
{
	geomShader.setFloat("timeVar", timeVar / 0.1f); //Assigns the time variable to allow movement 

	GLuint diffuseVar = glGetUniformLocation(geomShader.getID(), "diffuseVar"); //Retrieves diffuse variable 
	glUniform1i(diffuseVar, 0);
	glActiveTexture(GL_TEXTURE0); //Assigns active texture
	glBindTexture(GL_TEXTURE_2D, silverTexture.getID()); //Binds correct texture
	
}

void MainGame::linkEnvMapShader() //Function to set up environment mapping shader
{
	GLuint diffuse = glGetUniformLocation(envMapShader.getID(), "diffuse");
	GLuint skybox = glGetUniformLocation(envMapShader.getID(), "skybox");

	envMapShader.setMat4("vertModelMatrix", transform.GetModel()); //Assigns model matrix


	glUniform1i(diffuse, 1);
	glUniform1i(skybox, 0);

	glActiveTexture(GL_TEXTURE0 + 1); //Assigns active texture
	glBindTexture(GL_TEXTURE_2D, envMapTexture.getID()); //Binds correct texture
	
}

void MainGame::linkSunShader() //Function to set up sun shader
{
	GLuint texture = glGetUniformLocation(sunShader.getID(), "textureSamplerVar");

	glUniform1i(texture, 1);

	sunShader.setMat4("model", transform.GetModel()); //Assigns the model matrix 
	sunShader.setMat4("view", applicationCamera.getView()); //Assigns the view matrix
	sunShader.setMat4("projection", applicationCamera.getProjection()); //Assigns the projection matrix
	sunShader.setFloat("timeVarFrag", timeVar / 0.5f); //Assigns the time variable for the fragment shader
	sunShader.setFloat("minBI", 0.1f); //Assigns the minimum intensiy for the bloom effect
	sunShader.setFloat("maxBI", 1.0f); //Assigns the maximum intensity for the bloom effect
	sunShader.setFloat("bFrequency", 1.0); //Assigns the frequency for the bloom effect
	sunShader.setFloat("swirlSeed", 1.0); //Assigns the random seed for the swirl effect
	sunShader.setFloat("timeVar", timeVar/0.5f); //Assigns the time variable for the vertex shader
	sunShader.setFloat("randomConstant", 50000); //Assigns a constant for the semi-random number generation

	glActiveTexture(GL_TEXTURE0 + 1); //Assigns active texture
	glBindTexture(GL_TEXTURE_2D, sunShaderTexture.getID()); //Binds correct texture
}

void MainGame::renderGeomShader() //Function to draw geometry shader
{
	transform.SetPos(glm::vec3(1.5 , 0.0, 1.5));
	transform.SetRot(glm::vec3(0.0, timeVar, 0.0));
	transform.SetScale(glm::vec3(0.5, 0.5, 0.5));

	geomShader.Bind(); //Binds shader

	linkGeomShader(); //Calls corresponding setup function

	geomShader.Update(transform, applicationCamera);

	geomShaderMesh.draw(); //Draws shader in app world space
}

void MainGame::renderEnvMapShader() //Function to drawn environment mapping shader
{
	transform.SetPos(glm::vec3(0, 0.0, -2.0));
	transform.SetRot(glm::vec3(0.0, timeVar, 0.0));
	transform.SetScale(glm::vec3(0.35, 0.35, 0.35));

	envMapShader.Bind();//Binds shader
	linkEnvMapShader(); //Calls corresponding setup function
	envMapShader.Update(transform, applicationCamera);
	envMapShaderMesh.draw(); //Draws shader in app world space
}

void MainGame::renderSunShader() //Function to draw sun shader
{
	transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, timeVar + 5, 0.0));
	transform.SetScale(glm::vec3(0.5, 0.5, 0.5));

	sunShader.Bind(); //Binds shader
	linkSunShader(); //Calls corresponding setup function
	sunShader.Update(transform, applicationCamera);
	sunShaderMesh.draw(); //Draws shader in app world space
}

void MainGame::renderGame()
{
	_applicationDisplay.clearDisplay(0.1f, 0.1f, 0.1f, 1.0f); //Clears app display

	renderGeomShader(); //Draws the three shaders
	renderEnvMapShader();
	renderSunShader();

	applicationCamera.setLook(sunShaderMesh.getSpherePos()); //Directs app camera

	timeVar = timeVar - 0.0002f; //Modifies time variable

	applicationSkybox.draw(&applicationCamera); //Creates skybox

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_applicationDisplay.swapBuffer(); //Swaps active buffers

	
} 