#pragma once

class RenderTarget
{
public:
	unsigned int mRT_ID;
	unsigned int mWidth;
	unsigned int mHeight;

	RenderTarget(unsigned int width, unsigned int height);
	~RenderTarget();
};

