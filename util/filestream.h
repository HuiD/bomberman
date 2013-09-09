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
#ifndef __FILESTREAM_H
#define __FILESTREAM_H

#include "decl.h"
#include "databuffer.h"

#include <stdio.h>
#include <memory>

class FileStream
{
public:
	FileStream();
	~FileStream();

	/// Cache data of @in in a buffer.
	bool cache(const std::string& in);
	/// Write current contents to @out file
	bool write(const std::string& out);

	uint8_t getByte();
	uint16_t getU16();
	uint32_t getU32();
	std::string getString();

	void writeByte(uint8_t byte);
	void writeU16(uint16_t val);
	void writeU32(uint32_t val);
	void writeString(const std::string& str);

	void seek(int pos) { m_readPos = pos; }
	void skip(int count) { m_readPos += count; }
	int getReadPos() const { return m_readPos; }

	int getWritePos() const { return m_writePos; }
	void setWritePos(int newPos) { m_writePos = newPos; }

private:
	int m_readPos;
	int m_writePos;
	int m_size;

	DataBuffer<uint8_t> m_buffer;
};

typedef std::shared_ptr<FileStream> FileStreamPtr;

#endif

