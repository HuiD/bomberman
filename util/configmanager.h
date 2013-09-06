/*
 * Copyright (c) 2013 Ahmed Samy  <f.fallen45@gmail.com>
 *
 * This an INI-like parser, but without the section stuff:
 * 	key = value
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
#ifndef __CONFIGMANAGER_H
#define __CONFIGMANAGER_H

#include "decl.h"

#define MAX_KEY_LEN 128
#define MAX_VALUE_LEN 256
#define MAX_BUFFER_LEN 512 /* should be bigger than MAX_KEY_LEN + MAX_VALUE_LEN  */

class ConfigManager
{
public:
	ConfigManager();
	~ConfigManager();

	std::string getString(const std::string& key);
	uint32_t getInt(const std::string& key);

	bool loadFrom(const std::string& file);

protected:
	std::pair<std::string, std::string> parseLine(const std::string& input);

private:
	std::map<std::string, std::string> m_configMap;
};

extern ConfigManager g_config;

#endif

