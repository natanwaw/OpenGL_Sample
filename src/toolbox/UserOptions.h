#pragma once

#include "models/Shader.h"

constexpr unsigned ORBIT_VERTICES_COUNT = 360;
static const glm::vec3 noLightColor(0.0f, 0.0f, 0.0f);

class UserOptions
{
public:
	glm::vec3 orbitVertices[ORBIT_VERTICES_COUNT];
	glm::vec3 cameraPosition;

	bool showDirLight = true;
	glm::vec3 dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
	glm::vec3 directionalLightAmbientColor = glm::vec3(0.53f, 0.28f, 0.58f);
	glm::vec3 directionalLightDiffuseColor = glm::vec3(0.6f, 0.6f, 0.6f);
	glm::vec3 directionalLightSpecularColor = glm::vec3(0.7f, 0.7f, 0.7f);

	bool showPointLight = true;
	glm::vec3 pointLightPosition;
	glm::vec3 pointLightAmbientColor = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 pointLightDiffuseColor = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 pointLightSpecularColor = glm::vec3(0.0f, 0.0f, 1.0f);

	bool showRefLight[2] = { true, true };

	glm::vec3 spotLightPosition[2] = {
		glm::vec3(40.0f, 70.0f, 100.0f),
		glm::vec3(-40.0f, 55.0f, 100.0f)
	};

	glm::vec3 spotLightDirection[2] = {
		glm::vec3(1.0f, -0.0f, 0.0f),
		glm::vec3(1.0f, -0.0f, 0.0f)
	};

	glm::vec3 spotLightAmbientColor[2] = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	};

	glm::vec3 spotLightDiffuseColor[2] = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	};

	glm::vec3 spotLightSpecularColor[2] = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	};

	glm::mat4 projection;
	glm::mat4 view;

	bool showPointLightPosition = false;
	bool showDirLightPosition = false;
	bool showRefLightPosition[2] = { false, false };

public:
	void updateShader(Shader& shader);
	void generateOrbitPoints(int radius);
	glm::vec3 makeNonZero(const glm::vec3& vector);
};
