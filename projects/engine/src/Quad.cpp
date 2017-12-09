#include "Quad.h"

Quad::Quad()
{
	vertices = { 
		Vertex{{-0.5f, -0.5f, 0.0f}},
		Vertex{{0.5f, -0.5f, 0.0f}}, 
		Vertex{{0.5f, 0.5f, 0.0f}},
		Vertex{{-0.5f, 0.5f, 0.0f}}
	};

	indices = {
		0,1,2,
		0,2,3
	};

	setupMesh();
}

Quad::~Quad() {}