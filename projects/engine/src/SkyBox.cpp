#include "SkyBox.h"

void Skybox::loadSkybox(std::string t_Front, std::string t_Back, std::string t_Left, std::string t_Right, std::string t_Top, std::string t_Bottom)
{
	textures[0].loadTexture2D(std::string(TEXTURE_PATH) + t_Front);
	textures[1].loadTexture2D(std::string(TEXTURE_PATH) + t_Back);
	textures[2].loadTexture2D(std::string(TEXTURE_PATH) + t_Left);
	textures[3].loadTexture2D(std::string(TEXTURE_PATH) + t_Right);
	textures[4].loadTexture2D(std::string(TEXTURE_PATH) + t_Top);
	textures[5].loadTexture2D(std::string(TEXTURE_PATH) + t_Bottom);


	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);

	glGenBuffers(1, &uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uiBuffer);

	Vec3 vSkyBoxVertices[24] =
	{
		// Front face
		Vec3(50.0f, 50.0f, 50.0f), Vec3(50.0f, -50.0f, 50.0f), Vec3(-50.0f, 50.0f, 50.0f), Vec3(-50.0f, -50.0f, 50.0f),
		// Back face
		Vec3(-50.0f, 50.0f, -50.0f), Vec3(-50.0f, -50.0f, -50.0f), Vec3(50.0f, 50.0f, -50.0f), Vec3(50.0f, -50.0f, -50.0f),
		// Left face
		Vec3(-50.0f, 50.0f, 50.0f), Vec3(-50.0f, -50.0f, 50.0f), Vec3(-50.0f, 50.0f, -50.0f), Vec3(-50.0f, -50.0f, -50.0f),
		// Right face
		Vec3(50.0f, 50.0f, -50.0f), Vec3(50.0f, -50.0f, -50.0f), Vec3(50.0f, 50.0f, 50.0f), Vec3(50.0f, -50.0f, 50.0f),
		// Top face
		Vec3(-50.0f, 50.0f, -50.0f), Vec3(50.0f, 50.0f, -50.0f), Vec3(-50.0f, 50.0f, 50.0f), Vec3(50.0f, 50.0f, 50.0f),
		// Bottom face
		Vec3(50.0f, -50.0f, -50.0f), Vec3(-50.0f, -50.0f, -50.0f), Vec3(50.0f, -50.0f, 50.0f), Vec3(-50.0f, -50.0f, 50.0f),
	};
	Vec2 vSkyBoxTexCoords[4] =
	{
		Vec2(0.0f, 1.0f), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), Vec2(1.0f, 0.0f)
	};

	Vec3 vSkyBoxNormals[6] =
	{
		Vec3(0.0f, 0.0f, -1.0f),
		Vec3(0.0f, 0.0f, 1.0f),
		Vec3(1.0f, 0.0f, 0.0f),
		Vec3(-1.0f, 0.0f, 0.0f),
		Vec3(0.0f, -1.0f, 0.0f),
		Vec3(0.0f, 1.0f, 0.0f)
	};

	for(int i = 0; i<24; i++){
		addData(&vSkyBoxVertices[i], sizeof(Vec3));
		addData(&vSkyBoxTexCoords[i % 4], sizeof(Vec2));
		addData(&vSkyBoxNormals[i / 4], sizeof(Vec3));
	}

	glBufferData(iBufferType, data.size(), &data[0], GL_STATIC_DRAW);
	data.clear();

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vec3) + sizeof(Vec2), 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(Vec3) + sizeof(Vec2), (void*)sizeof(Vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vec3) + sizeof(Vec2), (void*)(sizeof(Vec3) + sizeof(Vec2)));
}

void Skybox::renderSkybox()
{
	glDepthMask(0);
	glBindVertexArray(uiVAO);
	for(int i= 0; i< 6; i++)
	{
		textures[i].bind(0);//maybe bind(i)
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
	}
	glDepthMask(1);
}

void Skybox::releaseSkybox()
{
	for (int i; i < 6; i++) {
		textures[i].releaseTexture();
	}
	glDeleteVertexArrays(1, &uiVAO);
	glDeleteBuffers(1, &uiBuffer);
	data.clear();
}


void Skybox::addData(void* ptrData, GLuint uiDataSize)
{
	data.insert(data.end(), (BYTE*)ptrData, (BYTE*)ptrData + uiDataSize);
}
