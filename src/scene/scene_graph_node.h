#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

#include <memory>
#include <vector>

class SceneGraphNode
{
public:
	SceneGraphNode(const glm::vec3& position = glm::vec3(0.0f),
					const glm::vec3& orientation = glm::vec3(0.0f, 0.0f, 0.0f),
					const glm::vec3& scale = glm::vec3(1.0f));

	void set_scale(float x, float y, float z);
	void set_scale(float uniform_scale);

	void set_orienatation(float x, float y, float z);
	void set_orienatation(const glm::mat4& orientation);

	void set_position(float x, float y, float z);
	void set_position(const glm::vec3& position);

	glm::quat orientation() const { return m_orientation; }
	glm::vec3 position() const { return m_position; }
	glm::vec3 scale() const { return m_scale; }
	glm::mat4 get_transform() const { return m_transform; }

	void add_child(const std::shared_ptr<SceneGraphNode>& child)
	{
		m_children.push_back(child);
	}

	void update(const glm::mat4& parent_transform, bool is_dirty);

private:
	glm::mat4 get_updated_transform() const;

	std::vector<std::shared_ptr<SceneGraphNode>> m_children;

	glm::mat4 m_transform;

	glm::quat m_orientation;
	glm::vec3 m_position;
	glm::vec3 m_scale;

	bool m_is_dirty;
};