#include "scene_graph_node.h"

SceneGraphNode::SceneGraphNode(const glm::vec3& position, const glm::vec3& orientation, const glm::vec3& scale) :
	m_orientation(orientation),
	m_position(position),
	m_scale(scale),
	m_transform(glm::mat4(1.0f)),
	m_is_dirty(true)
{
}

void SceneGraphNode::set_scale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
	m_is_dirty = true;
}

void SceneGraphNode::set_scale(float uniform_scale)
{
	m_scale = glm::vec3(uniform_scale);
	m_is_dirty = true;
}

void SceneGraphNode::set_orienatation(float x, float y, float z)
{
	m_orientation = glm::angleAxis(glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::angleAxis(glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::angleAxis(glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));

	m_is_dirty = true;
}

void SceneGraphNode::set_orienatation(const glm::mat4& orientation)
{
	m_orientation = glm::quat_cast(orientation);
	m_is_dirty = true;
}

void SceneGraphNode::set_position(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
	m_is_dirty = true;
}

void SceneGraphNode::set_position(const glm::vec3& position)
{
	m_position = position;
	m_is_dirty = true;
}

void SceneGraphNode::update(const glm::mat4& parent_transform, bool is_dirty)
{
	is_dirty = is_dirty | m_is_dirty;

	if (is_dirty)
	{
		m_transform = get_updated_transform();
		m_transform = parent_transform * m_transform;
		m_is_dirty = false;
	}

	for (auto& child : m_children)
	{
		child->update(m_transform, is_dirty);
	}
}

glm::mat4 SceneGraphNode::get_updated_transform() const
{
	glm::mat4 T = glm::translate(glm::mat4(1.0f), m_position);
	glm::mat4 R = glm::mat4_cast(m_orientation);
	glm::mat4 S = glm::scale(glm::mat4(1.0f), m_scale);

	return T * R * S;
}