#pragma once

#include "Quat.h"
#include "Model.h"

#include <vector>

using namespace math;

class SceneNode
{
public:
	int nodeId;

	Model* model;

	SceneNode* parentNode;
	std::vector<SceneNode*> childNodes;

	Vec3 position;
	Quat rotation;
	Vec3 scale;

	Mat4 transform;

	bool transformDirty;

public:
	SceneNode();
	SceneNode(int _nodeId);
	~SceneNode();

	void addChild(SceneNode* node);
	void removeChild(int nodeId);

	void updateTransform();
	Vec3 SceneNode::getPosition();
	void SceneNode::setPosition(Vec3& pos);
	Quat SceneNode::getRotation();
	void SceneNode::setRotation(Quat rot);
	Vec3 SceneNode::getScale();
	void SceneNode::setScale(Vec3& sc);

private:

};