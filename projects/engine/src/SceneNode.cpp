#include "SceneNode.h"

SceneNode::SceneNode()
{
	parentNode = NULL;
	transform = Mat4::Identity;
	transformDirty = false;
}

SceneNode::SceneNode(int _nodeId)
	: nodeId(_nodeId)
{
	parentNode = NULL;
	transform = Mat4::Identity;
	transformDirty = false;
}

SceneNode::~SceneNode()
{
}

void SceneNode::addChild(SceneNode* node)
{
	if (node->parentNode != NULL)
	{
		node->parentNode->removeChild(node->nodeId);
	}

	node->parentNode = this;
	childNodes.push_back(node);
}

void SceneNode::removeChild(int nodeId)
{
	for (int i = 0; i < childNodes.size(); i++)
	{
		if (nodeId == childNodes[i]->nodeId)
		{
			childNodes.erase(childNodes.begin() + i);
			i = childNodes.size();
		}
	}
}

void SceneNode::updateTransform()
{
	if (transformDirty)
	{
		transform = transform.TranslationMatrix(position);
		//transform = transform * transform.RotationMatrixAboutAxis(Axis::AxisZ, 0.0f);
		transform = transform * rotation.getMatrix();
		transform = transform * transform.ScaleMatrix(scale);

		if (parentNode != NULL)
		{
			transform = parentNode->transform * transform;
		}
	}

	for (int i = 0; i < childNodes.size(); ++i)
	{
		if (transformDirty)
		{
			childNodes[i]->transformDirty = true;
		}
		childNodes[i]->updateTransform();
	}
	transformDirty = false;
}

Vec3 SceneNode::getPosition()
{
	return position;
}

void SceneNode::setPosition(Vec3& pos)
{
	position = Vec3(pos);
	transformDirty = true;
}

Quat SceneNode::getRotation()
{
	return rotation;
}

void SceneNode::setRotation(Quat rot)
{
	rotation = rot;
	transformDirty = true;
}

Vec3 SceneNode::getScale()
{
	return scale;
}

void SceneNode::setScale(Vec3& sc)
{
	scale = Vec3(sc);
	transformDirty = true;
}
