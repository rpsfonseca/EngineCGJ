#include "LightShafts.h"
#include "Vec2.h"
#include "Vec4.h"
#include "Camera.h"
#include "OpenGLError.h"

using namespace math;

GLfloat rect[12] =
{
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f,

	-1.0f, -1.0f,
	1.0f, 1.0f,
	-1.0f, 1.0f
};

GLfloat texcoords[12] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
};


LightShafts::LightShafts(GLuint shaderId)
{

	backLightColor = (GLfloat)0.16f;
	exposure = (GLfloat)0.0034f;
	decay = (GLfloat)0.995f;
	density = (GLfloat)0.84f;
	weight = (GLfloat)6.65f;
	samples = 100;
	
	glGenTextures(1, &renderTextureArrayColor);
	glGenTextures(1, &renderTextureArrayDepth);

	glBindTexture(GL_TEXTURE_2D_ARRAY, renderTextureArrayColor);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 1400, 700, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);


	glBindTexture(GL_TEXTURE_2D_ARRAY, renderTextureArrayDepth);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, 1400, 700, 2, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);


	glGenFramebuffers(2, frameBuffers);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[0]);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTextureArrayColor, 0, 0);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, renderTextureArrayDepth, 0, 0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[1]);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTextureArrayColor, 0, 1);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, renderTextureArrayDepth, 0, 1);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	shader = shaderId;

	vertex_loc = glGetAttribLocation(shader, "inPosition");
	texcoord_loc = glGetAttribLocation(shader, "inTexCoord");
	GLuint shaftsParamsIndex = glGetUniformBlockIndex(shader, "ShaftsParams");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(1, &UBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
	glVertexAttribPointer(vertex_loc, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vertex_loc);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
	glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(texcoord_loc);

	glBindVertexArray(0);


	glBindBuffer(GL_UNIFORM_BUFFER, UBO);

	GLint shaftsParamsSize;
	glGetActiveUniformBlockiv(shader, shaftsParamsIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &shaftsParamsSize);
	glBufferData(GL_UNIFORM_BUFFER, shaftsParamsSize, NULL, GL_DYNAMIC_DRAW);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
	glUniformBlockBinding(shader, shaftsParamsIndex, 0);

	GLuint uniformsIndex[SHAFTS_UNIFORM_SIZE];
	const GLchar *uniformsName[SHAFTS_UNIFORM_SIZE] =
	{
		"samples",
		"exposure",
		"decay",
		"density",
		"weight"
	};

	glGetUniformIndices(shader, SHAFTS_UNIFORM_SIZE, uniformsName, uniformsIndex);
	glGetActiveUniformsiv(shader, SHAFTS_UNIFORM_SIZE, uniformsIndex, GL_UNIFORM_OFFSET, uniformsOffset);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	UpdateUniformBuffer();
}


void LightShafts::UpdateUniformBuffer()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, uniformsOffset[0], 4, &samples);
	glBufferSubData(GL_UNIFORM_BUFFER, uniformsOffset[1], 4, &exposure);
	glBufferSubData(GL_UNIFORM_BUFFER, uniformsOffset[2], 4, &decay);
	glBufferSubData(GL_UNIFORM_BUFFER, uniformsOffset[3], 4, &density);
	glBufferSubData(GL_UNIFORM_BUFFER, uniformsOffset[4], 4, &weight);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, 0);
}


void LightShafts::StartDrawingOcclusion()
{
	// Bind and clear the buffer for rendering occlusion
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[0]);
	glViewport(0, 0, 1400, 700);
	glClearColor(backLightColor,
		backLightColor,
		backLightColor,
		backLightColor);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void LightShafts::StartDrawingNormal()
{
	// Bind and clear the buffer for rendering normal scene
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffers[1]);
	glViewport(0, 0, 1400, 700);
	glClearColor(67 / 256.0f, 128 / 256.0f, 183 / 256.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void LightShafts::DrawLightShafts(Camera camera)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, 1400, 700);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	Vec4 lightNDCPosition = camera.getViewMatrix() * Vec4(0.0f, 0.5f, 0.5f, 1.0f);
	lightNDCPosition.x /= lightNDCPosition.w;
	Vec2 lightScreenPosition = Vec2(
		(lightNDCPosition.x + 1) * 0.5,
		(lightNDCPosition.y + 1) * 0.5
	);

	glUseProgram(shader);

	glBindTexture(GL_TEXTURE_2D_ARRAY, renderTextureArrayColor);
	glUniform1i(glGetUniformLocation(shader, "tex"), 0);
	/*
	shader.setVec2("lightScreenPos", lightScreenPosition);
	glUniform2fv(glGetUniformLocation(shader, "lightScreenPos"), 1, glm::value_ptr(lightScreenPosition));
	*/
	glUniform2f(glGetUniformLocation(shader, "lightScreenPos"), lightScreenPosition.x, lightScreenPosition.y);

	glBindVertexArray(VAO);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	glUseProgram(0);
}


LightShafts::~LightShafts()
{
	//Shaders::DeleteShaders(shader);
	glDeleteProgram(shader);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(1, &UBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &renderTextureArrayColor);
	glDeleteTextures(1, &renderTextureArrayDepth);
}