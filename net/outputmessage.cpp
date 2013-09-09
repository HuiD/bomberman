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
#include "outputmessage.h"
#include "../util/math.h"

OutputMessage::OutputMessage()
{
	m_size = 0;
	m_pos = 0;
}

OutputMessage::~OutputMessage()
{

}

void OutputMessage::addByte(uint8_t byte)
{
	m_buffer[m_pos++] = byte;
	++m_size;
}

void OutputMessage::addU16(uint16_t val)
{
	writeLE16(&m_buffer[m_pos], val);
	m_pos += 2;
	m_size += 2;
}

void OutputMessage::addU32(uint32_t val)
{
	writeLE32(&m_buffer[m_pos], val);
	m_pos += 4;
	m_size += 4;
}

void OutputMessage::addString(const std::string& str)
{
	uint16_t len = str.length();

	addU16(len);
	memcpy((char *)&m_buffer[m_pos], str.c_str(), len);
	m_pos += len;
	m_size += len;
}

