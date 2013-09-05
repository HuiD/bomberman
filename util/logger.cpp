#include "logger.h"

#include <iostream>

Logger g_logger;

void Logger::log(Logger::LogType type, const std::string& message)
{
#ifdef NDEBUG
	if (type == Logger::Debug)
		return;
#endif

	static const std::string logPrefixes[] = { "", "", "Warning: ", "Error: ", "Fatal error: " };
	std::string out = logPrefixes[type] + message;

	std::clog << out << std::endl;
	if (m_outFile.good()) {
		m_outFile << out << std::endl;
		m_outFile.flush();
	}

	if (type == Logger::Fatal)
		abort();
}

