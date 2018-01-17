#include "CloudRenderManager.h"

#include <iostream>

#include "Cube.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "OpenGLError.h"

CloudRenderManager::CloudRenderManager() :	windowTitle("CGJ - Final Delivery"), 
											nearPlane(0.001f), farPlane(100.0f), 
											fieldOfView(75.0f), 
											tanFOV(tan(fieldOfView / 2.0f / 360.0f * 2.0f * 3.14f)),
											showVRC(true)
{
	camera = Camera(math::Vec3(0.0f, 0.5f, 0.5f), math::Vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);
	perspectiveProjection = math::Mat4::perspective(fieldOfView, (float)1400.0 / (float)700.0, nearPlane, farPlane);
	lightShaftsToggled = true;
};

bool CloudRenderManager::initialize(const int gridX, const int gridY, const int gridZ) {

	// Initialize GLFW and opens a window
	if (glfwInit() != GL_TRUE) {
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // not resizable
	
	window = glfwCreateWindow(1400, 700, windowTitle, NULL, NULL);
	if (!window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW: " <<
			glewGetErrorString(err) << "\n";
		return false;
	}

	std::cout << "Running OpenGL version " << glGetString(GL_VERSION) << "\n";


	// Load and compile shaders
	raycasterShaderProgram = shaderManager.createFromFile("RaycasterShader.vert", "RaycasterShader.frag");
	guiShaderProgram = shaderManager.createFromFile("GUIshader.vert", "GUIShader.frag");

	initializeTextures(volumeTexture, planarTextures);
	OpenGLError::checkOpenGLError("ERROR: init tex");

	glGenVertexArrays(2, VAOs);

	// Define the raycasting VAO
	glBindVertexArray(VAOs[0]);

	// Create cube that encapsulates the grid for ray casting
	float cubeVertices[24];
	getCubeVertices(0, 1, 0, 1, 0, 1, cubeVertices);

	cubeVBO = createVBO(cubeVertices, sizeof(cubeVertices));
	defineRaycasterLayout(raycasterShaderProgram);

	int cubeElements[36];
	getCubeElements(cubeElements);
	createEBO(cubeElements, sizeof(cubeElements));

	//Define the GUI VAO
	glBindVertexArray(VAOs[1]);
	glBindTexture(GL_TEXTURE_2D, planarTextures[0]);
	OpenGLError::checkOpenGLError("ERROR: planar tex");

	float vertices[] = {
		//   Pos, Texcoords
		0.0f, 0.0f, // Top-left
		1.0f, 0.0f, // Top-right
		1.0f, 1.0f, // Bottom-right
		0.0f, 1.0f  // Bottom-left
	};

	createVBO(vertices, sizeof(vertices));

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	defineGUILayout(guiShaderProgram);

	interpolatedData = new float **[gridX];
	for (int i = 0; i != gridX; ++i) {
		interpolatedData[i] = new float*[gridY];
		for (int j = 0; j != gridY; ++j)
			interpolatedData[i][j] = new float[gridZ];
	}

	// Initialize the sliders
	glUseProgram(guiShaderProgram);
	OpenGLError::checkOpenGLError("ERROR: before tex");
	controls.addSlider("Density Cutoff", "densityCutoff", 0.0f, 0.2f, 0.06f);
	controls.addSlider("Density Factor", "densityFactor", 0.0f, 1.0f, 0.35f);
	controls.addSlider("Color Multiplier", "colorMultiplier", 1.0f, 10.0f, 5.0f);
	controls.addSlider("Attenuation Factor", "attenuationFactor", 0.0f, 0.5f, 0.15f);
	controls.addSlider("Light ColorRed", "lightColorRed", 0.0f, 1.0f, 1.0f);
	controls.addSlider("Light ColorGreen", "lightColorGreen", 0.0f, 1.0f, 1.0f);
	controls.addSlider("Light ColorBlue", "lightColorBlue", 0.0f, 1.0f, 1.0f);
	controls.addSlider("Shade ColorRed", "shadeColorRed", 0.0f, 1.0f, 0.0f);
	controls.addSlider("Shade ColorGreen", "shadeColorGreen", 0.0f, 1.0f, 0.0f);
	controls.addSlider("Shade ColorBlue", "shadeColorBlue", 0.0f, 1.0f, 0.2f);
	controls.addSlider("Sun PositionX", "sunPositionX", -1.0f, 1.0f, 0.0f);
	controls.addSlider("Sun PositionY", "sunPositionY", -1.0f, 1.0f, 0.5f);
	controls.addSlider("Sun PositionZ", "sunPositionZ", -1.0f, 1.0f, 0.5f);
	controls.addSlider("View Samples", "viewSamplesF", 1.0f, 1024.0f, 128.0f);
	controls.addSlider("Light Samples", "lightSamplesF", 1.0f, 64.0f, 64.0f);
	
	glUseProgram(0);
	lightShafts = new LightShafts(shaderManager.createFromFile("light_shafts_vs.glsl", "light_shafts_fs.glsl"));
	// Update the buffer object of the lightshafts effect
	// (because parameters can be changed)
	lightShafts->UpdateUniformBuffer();

	return true;

}

void CloudRenderManager::defineRaycasterLayout(const GLuint raycasterShaderProgram) {

	GLint posAttrib = glGetAttribLocation(raycasterShaderProgram,"cubeVert");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
}

void CloudRenderManager::defineGUILayout(const GLuint guiShaderProgram) {

	GLint texAttrib = glGetAttribLocation(guiShaderProgram, "coord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),0);

}

void CloudRenderManager::draw(const SimData& data, std::mutex& simMutex, const double time) {
	static int counter = 0, frames = 0;
	static double fps = 0;

	// Clear the screen with background (sky) color
	//glClearColor(67 / 256.0f, 128 / 256.0f, 183 / 256.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Lock mutex because we will use data, which is shared with simulation
	simMutex.lock();

	interpolateCloudData(data, time);

	if (lightShaftsToggled)
	{
		lightShafts->StartDrawingNormal();
	}
	renderRayCastingClouds(data, time, false);
	if (lightShaftsToggled)
	{
		lightShafts->StartDrawingOcclusion();
		renderRayCastingClouds(data, time, true);
		lightShafts->DrawLightShafts(camera);
	}

	simMutex.unlock();

	glUseProgram(raycasterShaderProgram);
	controls.update(window);

	if (showVRC) renderGUI();

	counter++;
	frames++;
	fps = (double)frames / time;
	if (counter > 100) { 
		std::cout << fps << " - fps" << std::endl;
		counter = 0;

	}

	rightButtonUpdates();
	arrowUpdates(1.0f/fps);

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		lightShaftsToggled = lightShaftsToggled == true ? false : true;
	}

	// Check for errors
	GLint glErr = glGetError();
	if (glErr) std::cout << "OpenGL error " << glErr << "!\n";

	// Swap the buffer
	glfwSwapBuffers(window);

	glfwPollEvents();

}

void CloudRenderManager::interpolateCloudData(const SimData & data, const double time) {

	int x = data.getGridLength();
	int y = data.getGridWidth();
	int z = data.getGridHeight();

	// Calculate relative difference for linear interpolation
	float relDiff = (time - data.nextTime) / (data.nextTime - data.prevTime);
	if (relDiff > 1.0f) relDiff = 1.0f;

	for (int i = 0; i < x; ++i)
		for (int j = 0; j < y; ++j)
			for (int k = 0; k < z; ++k)
				if (data.prevDen[i][j][k] > 0.0f) {
					// Lineary interpolate the density
					interpolatedData[i][j][k] = data.prevDen[i][j][k] + relDiff * (data.nextDen[i][j][k] - data.prevDen[i][j][k]);
				}
				else {
					interpolatedData[i][j][k] = 0.0f;
				}
}


void CloudRenderManager::renderRayCastingClouds(const SimData & data, const double time, bool occlusion) {

	glBindVertexArray(VAOs[0]);
	glUseProgram(raycasterShaderProgram);
	setUniform("view", camera.getViewMatrix());
	setUniform("viewInverse", camera.getViewMatrix()); //inverting this in shader
	setUniform("proj", perspectiveProjection);
	setUniform("tanFOV", tanFOV);
	setUniform("screenSize", math::Vec2(1400.0,700.0));
	setUniform("eyePosition", camera.Position);
	setUniform("near", nearPlane);
	setUniform("far", farPlane);
	setUniform("occlusion", occlusion);

	glDisable(GL_CULL_FACE);

	int x = data.getGridLength();
	int y = data.getGridWidth();
	int z = data.getGridHeight();

	// Convert float*** to float* (stream of data)
	float* texData = new float[x*y*z];
	int pos = 0;
	for (int i = 0; i != x; ++i)
		for (int j = 0; j != y; ++j)
			for (int k = 0; k != z; ++k) {
				texData[pos] = interpolatedData[i][j][k];
				++pos;
			}

	// Fill the data into 3D texture. A texture cell includes only one
	// component (GL_RED = density, float). 
	glTexImage3D(GL_TEXTURE_3D, 0, GL_R32F, x, y, z, 0, GL_RED,GL_FLOAT, texData);

	delete[] texData;

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void CloudRenderManager::renderGUI() {

	glBindVertexArray(VAOs[1]);
	OpenGLError::checkOpenGLError("ERROR: vao tex");
	glUseProgram(guiShaderProgram);
	OpenGLError::checkOpenGLError("ERROR: use tex");

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Render the controls in orthographic mode
	controls.render(planarTextures);
	OpenGLError::checkOpenGLError("ERROR: render tex");

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

}

void CloudRenderManager::terminate() {

	shaderManager.terminate();
	glDeleteVertexArrays(2, VAOs);
	deleteTextures(volumeTexture, planarTextures);
	delete lightShafts;

	// Terminate GLFW
	glfwTerminate();

}

void CloudRenderManager::rightButtonUpdates() {
	
	static double prevMouseX, prevMouseY;
	static bool prevMousePressed;


	float rotationFactor = 0.2f;
	if (glfwGetMouseButton(window, 1)) {
		if (prevMousePressed) {
			// Right mouse button has been pressed for more than 1 frame
			double newMouseX, newMouseY;
			glfwGetCursorPos(window, &newMouseX, &newMouseY);

			double diffX = newMouseX - prevMouseX;
			double diffY = newMouseY - prevMouseY;
			camera.processMouseMovement(diffX, diffY);
		}

		prevMousePressed = true;
		glfwGetCursorPos(window,&prevMouseX, &prevMouseY);

	}
	else
		prevMousePressed = false;

}

void CloudRenderManager::arrowUpdates(float deltaTime)
{

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, 'W') == GLFW_PRESS)
	{
		camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
	}
	if (glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, 'S') == GLFW_PRESS)
	{
		camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, 'A') == GLFW_PRESS)
	{
		camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, 'D') == GLFW_PRESS)
	{
		camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
	}

}

//----------------------------------------------


GLuint VBOs[5];
GLuint numVBOs;
GLuint EBOs[5];
GLuint numEBOs;

GLuint createVBO(float vertices[], int size) {

	glGenBuffers(1, &VBOs[numVBOs]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[numVBOs]);
	glBufferData(GL_ARRAY_BUFFER, size, vertices,
		GL_STATIC_DRAW);
	return VBOs[numVBOs++];

}

GLuint createEBO(int elements[], int size) {

	glGenBuffers(1, &EBOs[numEBOs]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[numEBOs]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elements,
		GL_STATIC_DRAW);
	return EBOs[numEBOs++];

}

void deleteVBOs() {
	glDeleteBuffers(numVBOs, VBOs);
}

void deleteEBOs() {
	glDeleteBuffers(numEBOs, EBOs);
}

void initializeTextures(GLuint volumeTexture, GLuint * planarTextures) {
	// We need one 3D texture and several 2D textures

	// Generate the 2D textures using pngs

	glGenTextures(3, planarTextures);

	int width, height, channels;
	unsigned char* image;

	const char* files[] = { "SliderHandle.png", "SliderIndicator.png", "SliderNormal.png" };
	for (int i = 0; i < 3; ++i) {
		image = stbi_load(files[i], &width, &height, &channels, STBI_rgb_alpha);
		if (image)
		{
			std::cout << files[i] << " --> " << image << std::endl;
		}
		else
		{
			std::cout << "Texture failed to load at path: " << files[i] << std::endl;
			stbi_image_free(image);
		}
		GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;
		glBindTexture(GL_TEXTURE_2D, planarTextures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,GL_UNSIGNED_BYTE, image);
		stbi_image_free(image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	// Generate the 3D textures
	glGenTextures(1, &volumeTexture);
	glBindTexture(GL_TEXTURE_3D, volumeTexture);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_3D);

}

void deleteTextures(GLuint volumeTexture, GLuint* planarTextures) {
	glDeleteTextures(1, &volumeTexture);
	glDeleteTextures(2, planarTextures);
}

void setUniform(const std::string name, const bool value) {

	GLuint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&program);
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform1i(location, value);

}

void setUniform(const std::string name, const float value) {

	GLuint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&program);
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform1f(location, value);

}

void setUniform(const std::string name, const math::Vec2 vector) {

	GLuint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&program);
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform2f(location, vector.x, vector.y);

}

void setUniform(const std::string name, const math::Vec3 vector) {

	GLuint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&program);
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform3f(location, vector.x, vector.y, vector.z);

}

void setUniform(const std::string name, const math::Mat4 matrix) {

	GLuint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&program);
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix.matrix);
}

float convertXToRelative(const int x) {
	return (static_cast<float>(x) / 1400.0) * 2.0f - 1.0f;
}

float convertYToRelative(const int y) {
	return -((static_cast<float>(y) / 700.0) * 2.0f - 1.0f);
}


//----------------------------------------------------------


Slider::Slider(	const std::string text, const std::string shaderProperty,
				const float min, const float max, const float initial,
				const float sliderPositionY) :
					text(text),
					shaderProperty(shaderProperty),
					min(min),
					max(max),
					currentPercentage((initial - min) / (max - min)),
					sliderPosition(slider_consts::sliderPositionX, slider_consts::sliderPositionY + sliderPositionY),
					buttonPosition(Position(sliderPosition.X + slider_consts::sliderLength * (-0.5f + currentPercentage), sliderPosition.Y)),
					buttonPressed(false)
{

	OpenGLError::checkOpenGLError("ERROR: before tex");
	setUniform(shaderProperty, min + currentPercentage * (max - min));
	OpenGLError::checkOpenGLError("ERROR: controls tex");
}

void Slider::update(GLFWwindow* window) {
	double newMouseX, newMouseY;
	glfwGetCursorPos(window, &newMouseX, &newMouseY);

	float relativeMouseX = convertXToRelative(newMouseX);
	float relativeMouseY = convertYToRelative(newMouseY);


	bool bigExpr =	(relativeMouseX - buttonPosition.X) * (relativeMouseX - buttonPosition.X) + 
					(relativeMouseY - buttonPosition.Y) * (relativeMouseY - buttonPosition.Y)
					< slider_consts::buttonSize * slider_consts::buttonSize || buttonPressed;

	// Check if mouse press is on button
	if (!glfwGetMouseButton(window, 0)) {
		buttonPressed = false;
	}
	else if (bigExpr) {
		std::cout << "dibfdhfjhd" << std::endl;
		buttonPressed = true;
		buttonPosition.X = relativeMouseX;
		float minPos = sliderPosition.X - slider_consts::sliderLength / 2;
		float maxPos = sliderPosition.X + slider_consts::sliderLength / 2;
		if (buttonPosition.X < minPos) {
			buttonPosition.X = minPos;
		}
		if (buttonPosition.X > maxPos) {
			buttonPosition.X = maxPos;
		}

		currentPercentage = (buttonPosition.X - minPos) / (maxPos - minPos);
		setUniform(shaderProperty, min + currentPercentage * (max - min));
		OpenGLError::checkOpenGLError("ERROR: before tex");
	}

}

void Slider::render(const GLuint * textures) {

	// Render the left part of the slider
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	float minPos = sliderPosition.X - slider_consts::sliderLength / 2;
	setUniform("positionX", (minPos + buttonPosition.X) / 2);
	setUniform("positionY", buttonPosition.Y);
	setUniform("sizeX", (buttonPosition.X - minPos) / 2);
	setUniform("sizeY", slider_consts::sliderHeight);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	OpenGLError::checkOpenGLError("ERROR: render 1 tex");

	// Render the right part of the slider
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	float maxPos = sliderPosition.X + slider_consts::sliderLength / 2;
	setUniform("positionX", (maxPos + buttonPosition.X) / 2);
	setUniform("positionY", buttonPosition.Y);
	setUniform("sizeX", (maxPos - buttonPosition.X) / 2);
	setUniform("sizeY", slider_consts::sliderHeight);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	OpenGLError::checkOpenGLError("ERROR: render 2 tex");

	// Render the handle
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	setUniform("positionX", buttonPosition.X);
	setUniform("positionY", buttonPosition.Y);
	setUniform("sizeX", slider_consts::buttonSize);
	setUniform("sizeY", slider_consts::buttonSize);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	OpenGLError::checkOpenGLError("ERROR: render 3 tex");

}

float Slider::getPercentage() {
	return (currentPercentage - min) / (max - min);
}

//-------------------------------------------------------------


void GUIControls::addSlider(const std::string text, const std::string shaderProperty, const float min, const float max, const float initial) 
{
	Slider slider = Slider(text, shaderProperty, min, max, initial, sliders.size() * slider_consts::sliderOffsetY * -1);
	sliders.push_back(slider);
}

void GUIControls::update(GLFWwindow* window) {
	for (Slider &s : sliders) {
		s.update(window);
	}
}

void GUIControls::render(const GLuint * textures) {
	float offset = 0;
	for (Slider &s : sliders) {
		s.render(textures);
	}
}