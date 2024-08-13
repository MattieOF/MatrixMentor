#pragma once
#include "Core/Layer.h"

class TestSelectionLayer;

class Test : public Layer
{
	friend TestSelectionLayer;

public:
	[[nodiscard]] virtual const char* GetTestName() const = 0;
	[[nodiscard]] virtual const char* GetTestDescription() const = 0;
	virtual Test*                     Create() = 0;

	void OnImGuiRender() override;
	virtual bool OnDrawTestPanel();

	void DestroySelf();

protected:
	bool m_PanelVisible = false;
	TestSelectionLayer* m_TestSelectionLayer = nullptr;
};
