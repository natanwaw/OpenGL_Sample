#ifndef HOUSE_H
#define HOUSE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "LoadedModel.h"
#include "scene/scene_graph_node.h"

class City : public Model
{
	unsigned int houseVAO = 0, houseVBO = 0;
	unsigned int roofVAO = 0, roofVBO = 0;

	unsigned rowCount, columnCount;

	const LoadedModel& houseModel;
	const LoadedModel& roofModel;

	glm::mat4* modelMatrices;
	std::vector<std::shared_ptr<SceneGraphNode>> housesNodes;
	std::vector<std::shared_ptr<SceneGraphNode>> roofsNodes;

public:
	City(std::shared_ptr<SceneGraphNode> parentNode,
		LoadedModel& houseModel,
		LoadedModel& roofModel,
		unsigned rowCount = 200,
		unsigned columnCount = 200);

	virtual ~City();

protected:
	virtual void DrawShape(Shader& shader) override;

private:
	void createGrid();
};

#endif // !HOUSE_H

