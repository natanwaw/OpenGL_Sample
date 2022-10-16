#include "UserOptions.h"

#define _USE_MATH_DEFINES
#include <math.h>

void UserOptions::updateShader(Shader& shader)
{
	static unsigned iterations = 0;

	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setVec3("viewPos", cameraPosition);
	shader.setFloat("material.shininess", 16.0f);

	// directional light
	shader.setVec3("dirLight.direction", dirLightDirection);

	if (showDirLight) {
		shader.setVec3("dirLight.ambient", directionalLightAmbientColor);
		shader.setVec3("dirLight.diffuse", directionalLightDiffuseColor);
		shader.setVec3("dirLight.specular", directionalLightSpecularColor);
	}
	else {
		shader.setVec3("dirLight.ambient", noLightColor);
		shader.setVec3("dirLight.diffuse", noLightColor);
		shader.setVec3("dirLight.specular", noLightColor);
	}

	pointLightPosition = orbitVertices[iterations];
	iterations = (iterations + 1) % ORBIT_VERTICES_COUNT;

	// point light
	shader.setVec3("pointLight.position", pointLightPosition);
	if (showPointLight) {
		shader.setVec3("pointLight.ambient", pointLightAmbientColor);
		shader.setVec3("pointLight.diffuse", pointLightDiffuseColor);
		shader.setVec3("pointLight.specular", pointLightSpecularColor);
	}
	else {
		shader.setVec3("pointLight.ambient", noLightColor);
		shader.setVec3("pointLight.diffuse", noLightColor);
		shader.setVec3("pointLight.specular", noLightColor);
	}
	shader.setFloat("pointLight.constant", 1.0f);
	shader.setFloat("pointLight.linear", 0.01);
	shader.setFloat("pointLight.quadratic", 0.004);

	// spotLight 1
	shader.setVec3("spotLights[0].position", spotLightPosition[0]);
	shader.setVec3("spotLights[0].direction", spotLightDirection[0]);
	if (showRefLight[0]) {
		shader.setVec3("spotLights[0].ambient", spotLightAmbientColor[0]);
		shader.setVec3("spotLights[0].diffuse", spotLightDiffuseColor[0]);
		shader.setVec3("spotLights[0].specular", spotLightSpecularColor[0]);
	}
	else {
		shader.setVec3("spotLights[0].ambient", noLightColor);
		shader.setVec3("spotLights[0].diffuse", noLightColor);
		shader.setVec3("spotLights[0].specular", noLightColor);
	}
	shader.setFloat("spotLights[0].constant", 1.0f);
	shader.setFloat("spotLights[0].linear", 0.005); //0.09
	shader.setFloat("spotLights[0].quadratic", 0.002); //0.032
	shader.setFloat("spotLights[0].cutOff", glm::cos(glm::radians(8.0f)));
	shader.setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(12.0f)));

	// spotLight 2
	shader.setVec3("spotLights[1].position", spotLightPosition[1]);
	shader.setVec3("spotLights[1].direction", spotLightDirection[1]);
	if (showRefLight[1]) {
		shader.setVec3("spotLights[1].ambient", spotLightAmbientColor[1]);
		shader.setVec3("spotLights[1].diffuse", spotLightDiffuseColor[1]);
		shader.setVec3("spotLights[1].specular", spotLightSpecularColor[1]);
	}
	else {
		shader.setVec3("spotLights[1].ambient", noLightColor);
		shader.setVec3("spotLights[1].diffuse", noLightColor);
		shader.setVec3("spotLights[1].specular", noLightColor);
	}
	shader.setFloat("spotLights[1].constant", 1.0f);
	shader.setFloat("spotLights[1].linear", 0.01); //0.09
	shader.setFloat("spotLights[1].quadratic", 0.004); //0.032
	shader.setFloat("spotLights[1].cutOff", glm::cos(glm::radians(8.0f)));
	shader.setFloat("spotLights[1].outerCutOff", glm::cos(glm::radians(12.0f)));

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
}

void UserOptions::generateOrbitPoints(int radius)
{
	for (int i = 0; i < ORBIT_VERTICES_COUNT; i++)
	{
		float x = sinf(i * M_PI / 180) * radius;
		float y = 3.0f;
		float z = cosf(i * M_PI / 180) * radius;

		orbitVertices[i] = glm::vec3(x, y, z);
	}
}

glm::vec3 UserOptions::makeNonZero(const glm::vec3& vector)
{
	glm::vec3 result = vector;

	if (result.length() == 0.0f)
		result.x = 0.1f;

	return result;
}