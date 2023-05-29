#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h" // Needed for logging some types

extern std::shared_ptr<spdlog::logger> s_MatrixMentorLogger;

void InitLog();

#ifndef MM_NO_LOG
	#define MM_TRACE(...)       s_MatrixMentorLogger->trace(__VA_ARGS__)
	#define MM_INFO(...)        s_MatrixMentorLogger->info(__VA_ARGS__)
	#define MM_WARN(...)        s_MatrixMentorLogger->warn(__VA_ARGS__)
	#define MM_ERROR(...)       s_MatrixMentorLogger->error(__VA_ARGS__)
	#define MM_CRITICAL(...)    s_MatrixMentorLogger->critical(__VA_ARGS__)
#else			 
	#define MM_TRACE(...)      
	#define MM_INFO(...)       
	#define MM_WARN(...)       
	#define MM_ERROR(...)      
	#define MM_CRITICAL(...)   
#endif
