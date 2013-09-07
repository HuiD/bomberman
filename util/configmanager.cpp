#include "configmanager.h"
#include "logger.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

ConfigManager g_config;

static char *strlwc(const char *s)
{
	static char line[512];
	int i =0;

	if (!s)
		return NULL;

	memset(line, 0, sizeof(line));
	while (s[i] && i < 512) {
		line[i] = tolower(s[i]);
		i++;
	}

	line[512] = '\0';
	return line;
}

static char *strstrip(char *s)
{
	static char line[512];
	char *end;

	if (!s)
		return NULL;

	while (isspace(*s) && *s)
		s++;

	strncpy(line, s, sizeof(line));
	end = line + strlen(line);
	while (end > line) {
		if (!isspace(*(end - 1)))
			break;

		end--;
	}

	*end = '\0';
	return line;
}

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{

}

bool ConfigManager::loadFrom(const std::string& file)
{
	FILE *fp = fopen(file.c_str(), "r");
	if (!fp)
		return false;

	int currentLine = 0;
	char buffer[MAX_BUFFER_LEN];

	while (fgets(buffer, sizeof(buffer), fp)) {
		++currentLine;
		if (*buffer == '#')
			continue;

		auto parsed = parseLine(buffer);
		if (parsed.first.empty() || parsed.second.empty()) {
			g_logger.error(stdext::format("Failed to parse key=val from line %d, escaping...", currentLine));
			continue;
		}

		m_configMap.insert(parsed);
	}

	fclose(fp);
	return true;
}

std::string ConfigManager::getString(const std::string& key)
{
	return m_configMap[key];
}

uint32_t ConfigManager::getInt(const std::string& key)
{
	std::string s = getString(key);
	if (s.empty())
		return 0;

	return strtoul(s.c_str(), NULL, 10);
}

std::pair<std::string, std::string> ConfigManager::parseLine(const std::string& input)
{
	/* Hacked off somewhere on the interwebs.  */
	const char *val = input.c_str();
	char key[MAX_KEY_LEN], value[MAX_VALUE_LEN];
	std::pair<std::string, std::string> ret;

	if (    sscanf (val, "%[^=] = \"%[^\"]\"", key, value) == 2
	    ||  sscanf (val, "%[^=] = '%[^\']'",   key, value) == 2
	    ||  sscanf (val, "%[^=] = %[^;#]",     key, value) == 2) {
		strcpy(key, strstrip(key));
		strcpy(key, strlwc(key));
		strcpy(value, strstrip(value));

		if (!strcmp(value, "\"\"") || !strcmp(value, "''"))
			value[0] = '\0';
	} else if (sscanf(val, "%[^=] = %[;#]", key, value) == 2 
		  ||  sscanf(val, "%[^=] %[=]", key, value) == 2) {
		strcpy(key, strstrip(key));
		strcpy(key, strlwc(key));
		value[0] = '\0';

	}

	if (!strcmp(value, "\"\""))
		memset(value, '\0', sizeof value);

	return std::make_pair(key, value);
}

