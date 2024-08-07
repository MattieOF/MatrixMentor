#pragma once

#define SPDLOG_EOL ""

// Utility functions and types
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

// Data types
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Assertion
#include "ppk_assert.h"

// GLM
#include "glm.hpp"
#include "gtc/type_ptr.hpp"

// Core project files
#include "Core/MatrixMentorCore.h"
#include "Core/MatrixMentorLog.h"

// Platform specific
#ifdef MM_PLATFORM_WINDOWS
	#include "Windows.h"
#endif
