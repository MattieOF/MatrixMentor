#include "mmpch.h"
#include "Tests/Test.h"

#include "Tests/TestSelectionLayer.h"

void Test::DestroySelf()
{
	MM_ASSERT_ERROR(m_TestSelectionLayer, "Test::PopSelf called without a valid TestSelectionLayer!");

	m_TestSelectionLayer->DestroyCurrentTest();
}
