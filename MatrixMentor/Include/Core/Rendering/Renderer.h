#pragma once

#include "RawModel.h"

class Renderer
{
public:
	static void Prepare();
	static void RenderModel(const RawModel* model);
};
