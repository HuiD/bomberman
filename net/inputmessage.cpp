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
#include "inputmessage.h"
#include "../util/math.h"

InputMessage::InputMessage(uint8_t *data, size_t size) :
	m_data(data),
	m_size(size),
	m_pos(0)
{
}

InputMessage::InputMessage() :
	m_data(nullptr),
	m_size(0),
	m_pos(0)
{

}

InputMessage::~InputMessage()
{

}

uint8_t InputMessage::getByte()
{
	return m_data[m_pos++];
}

uint16_t InputMessage::getU16()
{
	uint16_t tmp = readLE16(&m_data[m_pos]);
	m_pos += 2;
	return tmp;
}

uint32_t InputMessage::getU32()
{
	uint32_t tmp = readLE32(&m_data[m_pos]);
	m_pos += 4;
	return tmp;
}

std::string InputMessage::getString()
{
	uint16_t len = getU16();
	if (!len)
		return std::string();

	if (m_pos + len > m_size)
		return std::string();

	std::string ret((char *)&m_data[m_pos], len);
	m_pos += len;
	return ret;
}

