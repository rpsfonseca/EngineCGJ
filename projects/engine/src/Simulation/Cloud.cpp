#include "Cloud.h"

Cloud::Cloud(const math::Vec3 position, const float size) :
	position(position), size(size) {}

void Cloud::move(const float horizontalFactor, const float verticalFactor) {
	// Moves the cloud. Higher clouds move faster.
	position.x += horizontalFactor * (position.y + verticalFactor);
}