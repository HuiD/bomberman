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
#ifndef __OUTPUTMESSAGE_H
#define __OUTPUTMESSAGE_H

#include "decl.h"
#include "../util/databuffer.h"

class OutputMessage
{
public:
	OutputMessage();
	~OutputMessage();

	void addByte(uint8_t byte);
	void addU16(uint16_t val);
	void addU32(uint32_t val);
	void addString(const std::string& str);

	void clear() { m_buffer.clear(); }
	const uint8_t *data() const { return &m_buffer[0]; }
	size_t size() const { return m_size; }

private:
	uint32_t m_pos;
	size_t m_size;

	DataBuffer<uint8_t> m_buffer;
};

#endif

