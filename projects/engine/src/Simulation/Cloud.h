// Cloud data, used in cloud simulation

#ifndef CLOUD_H
#define CLOUD_H

#include "../../include/Vec3.h"

class Cloud {
public:
	Cloud(const math::Vec3 position, const float size);
	inline math::Vec3 getPosition() const { return position; };
	void move(const float horizontalFactor, const float hightFactor);
	inline float getSize() const { return size; };
private:
	math::Vec3 position;
	float size;
};

#endif
