#pragma once
#include "Shader.h"
#include "scene/scene_graph_node.h"

class Model
{
private:
	std::shared_ptr<SceneGraphNode> parent;

public:
	virtual ~Model() = default;
	void Draw(Shader& shader);

	void setParentNode(std::shared_ptr<SceneGraphNode> parentNode);
	std::shared_ptr<SceneGraphNode> getParentNode() const;

protected:
	virtual void DrawShape(Shader& shader) = 0;
	glm::mat4 getParentTransform();
};
