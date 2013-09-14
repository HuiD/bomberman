/*
 * Copyright (c) 2013 Ahmed Samy  <f.fallen45@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "configmanager.h"
#include "logger.h"
#include "format.h"

#include <stdio.h>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

ConfigManager g_config;

static char *strtrim(char *str)
{
	while (isspace(*str))
		str++;

	if (*str == '\0')
		return str;

	char *end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
		end--;

	*(end + 1) = '\0';
	return str;
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
	char buffer[MAX_BUFFER_LEN], *p;

	while (fgets(buffer, sizeof(buffer), fp)) {
		++currentLine;

		p = buffer;
		while (isspace(*p))
			p++;

		if (*p == '\0' || *p == '#')
			continue;

		auto parsed = parseLine(p);
		if (parsed.first.empty()) {
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

	if (    sscanf(val, "%[^=] = \"%[^\"]\"", key, value) == 2
	    ||  sscanf(val, "%[^=] = '%[^\']'",   key, value) == 2
	    ||  sscanf(val, "%[^=] = %[^;#]",     key, value) == 2) {
		;
	} else if (sscanf(val, "%[^=] = %[;#]", key, value) == 2 
		||  sscanf(val, "%[^=] %[=]", key, value) == 2) {
		value[0] = '\0';
	}

	strcpy(key, strtrim(key));
	strcpy(value, strtrim(value));
	if (!strcmp(value, "\"\"") || !strcmp(value, "''"))
		value[0] = '\0';

	return std::make_pair(key, value);
}

