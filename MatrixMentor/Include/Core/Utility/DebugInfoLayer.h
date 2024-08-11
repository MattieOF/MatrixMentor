#pragma once

#include "Core/Layer.h"

class DebugInfoLayer : public Layer
{
public:
	void OnUpdate(double deltaSeconds) override;
	void OnImGuiRender() override;

private:
	bool m_IsVisible = false;
};
