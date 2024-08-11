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

	void DestroySelf();

private:
	TestSelectionLayer* m_TestSelectionLayer = nullptr;
};
