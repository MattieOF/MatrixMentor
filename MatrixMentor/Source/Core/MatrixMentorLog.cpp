#include "mmpch.h"
#include "Core/MatrixMentorLog.h"

#include <iomanip>

#include "spdlog/sinks/basic_file_sink.h"

std::shared_ptr<spdlog::logger> s_MatrixMentorLogger;

void InitLog()
{
	if (!s_MatrixMentorLogger) 
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		std::vector<spdlog::sink_ptr> sinks;

		std::stringstream buffer;
		const std::time_t t = std::time(nullptr);
		const std::tm tm = *std::localtime(&t);
		buffer << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
		sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("Logs/{}.txt", buffer.str())));

		sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		s_MatrixMentorLogger = std::make_shared<spdlog::logger>("MatrixMentorLog", std::begin(sinks), std::end(sinks));
		s_MatrixMentorLogger->set_level(spdlog::level::trace);
	}
}
