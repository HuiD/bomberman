#include "logger.h"

#include <iostream>

Logger g_logger;
extern std::string g_progname;

void Logger::setLogFile(const std::string& file)
{
	m_outFile.open(file.c_str(), std::ios::out | std::ios::app);
	if (!m_outFile.is_open() || !m_outFile.good())
		g_logger.error("unable to save log to " + file);
	else
		m_outFile.flush();
}

void Logger::log(Logger::LogType type, const std::string& message)
{
#ifdef NDEBUG
	if (type == Logger::Debug)
		return;
#endif

	static const std::string logPrefixes[] = { "", "Error: ", "Warning: ", "Fatal error: ", "" };
	std::string out = logPrefixes[type] + message;

	std::clog << g_progname << ": " << out << std::endl;
	if (m_outFile.good()) {
		m_outFile << out << std::endl;
		m_outFile.flush();
	}

	if (type == Logger::Fatal) {
		std::cerr << g_progname << ": error is unrecoverable, terminating now..." << std::endl;
		abort();
	}
}

