#include "Model.h"
#include <glm/gtc/type_ptr.hpp>

void Model::setParentNode(std::shared_ptr<SceneGraphNode> parentNode)
{
	parent = parentNode;
}

std::shared_ptr<SceneGraphNode> Model::getParentNode() const
{
	return parent;
}

glm::mat4 Model::getParentTransform()
{
	if (parent == nullptr)
		return glm::mat4(1.0f);
	return parent->get_transform();
}

void Model::Draw(Shader& shader)
{
	glm::mat4 trans = getParentTransform();
	shader.use();
	shader.setMat4("model", trans);
	DrawShape(shader);
}
