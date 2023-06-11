#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h" // Needed for logging some types

extern std::shared_ptr<spdlog::logger> s_MatrixMentorLogger;

void InitLog();

#ifndef MM_NO_LOG
	#define MM_TRACE(format, ...)       s_MatrixMentorLogger->trace(format "\n", __VA_ARGS__)
	#define MM_INFO(format, ...)        s_MatrixMentorLogger->info(format "\n", __VA_ARGS__)
	#define MM_WARN(format, ...)        s_MatrixMentorLogger->warn(format "\n", __VA_ARGS__)
	#define MM_ERROR(format, ...)       s_MatrixMentorLogger->error(format "\n", __VA_ARGS__)
	#define MM_CRITICAL(format, ...)    s_MatrixMentorLogger->critical(format "\n", __VA_ARGS__)

	#define MM_TRACE_NO_NEWLINE(format, ...)       s_MatrixMentorLogger->trace(format, __VA_ARGS__)
	#define MM_INFO_NO_NEWLINE(format, ...)        s_MatrixMentorLogger->info(format, __VA_ARGS__)
	#define MM_WARN_NO_NEWLINE(format, ...)        s_MatrixMentorLogger->warn(format, __VA_ARGS__)
	#define MM_ERROR_NO_NEWLINE(format, ...)       s_MatrixMentorLogger->error(format, __VA_ARGS__)
	#define MM_CRITICAL_NO_NEWLINE(format, ...)    s_MatrixMentorLogger->critical(format, __VA_ARGS__)
#else
	#define MM_TRACE(...)      
	#define MM_INFO(...)       
	#define MM_WARN(...)       
	#define MM_ERROR(...)      
	#define MM_CRITICAL(...)

	#define MM_TRACE_NO_NEWLINE(format, ...)     
	#define MM_INFO_NO_NEWLINE(format, ...)      
	#define MM_WARN_NO_NEWLINE(format, ...)      
	#define MM_ERROR_NO_NEWLINE(format, ...)     
	#define MM_CRITICAL_NO_NEWLINE(format, ...)  
#endif
