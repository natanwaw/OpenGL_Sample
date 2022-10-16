#include "City.h"

City::City(std::shared_ptr<SceneGraphNode> parentNode,
	LoadedModel& houseModel,
	LoadedModel& roofModel,
	unsigned rowCount,
	unsigned columnCount) :
	houseModel(houseModel),
	roofModel(roofModel),
	rowCount(rowCount),
	columnCount(columnCount)
{


	setParentNode(parentNode);

	unsigned int amount = rowCount * columnCount;

	modelMatrices = new glm::mat4[amount];

	createGrid();

	glGenBuffers(1, &houseVBO);
	glBindBuffer(GL_ARRAY_BUFFER, houseVBO);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	for (unsigned int i = 0; i < houseModel.meshes.size(); i++)
	{
		houseVAO = houseModel.meshes[i].getVAO();

		glBindVertexArray(houseVAO);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));     //aInstancedMatrix 

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}

	glGenBuffers(1, &roofVBO);
	glBindBuffer(GL_ARRAY_BUFFER, roofVBO);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	for (unsigned int i = 0; i < roofModel.meshes.size(); i++)
	{
		roofVAO = roofModel.meshes[i].getVAO();

		glBindVertexArray(roofVAO);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
}

void City::createGrid()
{
	for (unsigned i = 0; i < rowCount; i++)
	{
		for (unsigned j = 0; j < columnCount; j++)
		{
			std::shared_ptr<SceneGraphNode> houseNode(new SceneGraphNode(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
			std::shared_ptr<SceneGraphNode> roofNode(new SceneGraphNode(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));

			const float x = 5000 - i * 50;
			const float z = 5000 - j * 50;

			houseNode->set_position(x, 0.0f, z);
			roofNode->set_position(0.0f, 20.0f, 0.0f);

			getParentNode()->add_child(houseNode);
			houseNode->add_child(roofNode);

			housesNodes.push_back(houseNode);
			roofsNodes.push_back(roofNode);
		}
	}
}

City::~City()
{
	delete[] modelMatrices;
}

void City::DrawShape(Shader& shader)
{
	unsigned amount = rowCount * columnCount;

	// HOUSES modelMatrices 
	for (unsigned i = 0; i < amount; i++) {
		modelMatrices[i] = housesNodes[i]->get_transform();
	}

	// buffer sub data
	glBindBuffer(GL_ARRAY_BUFFER, houseVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, amount * sizeof(glm::mat4), &modelMatrices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// draw houses
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, houseModel.textures_loaded[0].id);
	for (unsigned int i = 0; i < houseModel.meshes.size(); i++)
	{
		glBindVertexArray(houseModel.meshes[i].getVAO());
		glDrawElementsInstanced(GL_TRIANGLES, houseModel.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}


	/*
	// ROOF modelMatrices 
	for (unsigned i = 0; i < amount; i++) {
		modelMatrices[i] = roofsNodes[i]->get_transform();
	}

	// buffer sub data
	glBindBuffer(GL_ARRAY_BUFFER, roofVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, amount * sizeof(glm::mat4), &modelMatrices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// draw roofs
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, roofModel.textures_loaded[0].id);
	for (unsigned int i = 0; i < roofModel.meshes.size(); i++)
	{
		glBindVertexArray(roofModel.meshes[i].getVAO());
		glDrawElementsInstanced(GL_TRIANGLES, roofModel.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}
	*/
}


