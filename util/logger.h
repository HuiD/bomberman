#ifndef __LOGGER_H
#define __LOGGER_H

#include <fstream>

class Logger
{
	enum LogType {
		Debug,
		Error,
		Warning,
		Fatal,
		Information
	};

	void log(LogType type, const std::string& message);

public:
	void debug(const std::string& what) { log(Debug, what); }
	void info(const std::string& what) { log(Information, what); }
	void warning(const std::string& what) { log(Warning, what); }
	void error(const std::string& what) { log(Error, what); }
	void fatal(const std::string& what) { log(Fatal, what); }

	void setLogFile(const std::string& file);

private:
	std::ofstream m_outFile;
};

extern Logger g_logger;

#endif

