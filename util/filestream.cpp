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
#include "filestream.h"
#include "math.h"

FileStream::FileStream() :
	m_readPos(0),
	m_writePos(0),
	m_size(0)
{

}

FileStream::~FileStream()
{

}

bool FileStream::cache(const std::string& filename)
{
	FILE *fp = fopen(filename.c_str(), "wb");
	if (!fp)
		return false;

	fseek(fp, 0L, SEEK_END);
	size_t fileSize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	if (fread(m_buffer.data(), fileSize, 1, fp) != fileSize) {
		g_logger.error(stdext::format("failed to cache file into buffer"));
		fclose(fp);
		return false;
	}

	fclose(fp);
	return true;
}

bool FileStream::write(const std::string& filename)
{
	FILE *fp = fopen(filename.c_str(), "wb");
	if (!fp) {
		g_logger.error(stdext::format("failed to open %s for writing", filename));
		return false;
	}

	if (fwrite(m_buffer.data(), m_size, 1, fp) != m_size)
		g_logger.warning(stdext::format("failed to write whole data to %s", filename));

	fclose(fp);
	return true;
}

uint8_t FileStream::getByte()
{
	return m_buffer[m_readPos++];
}

uint16_t FileStream::getU16()
{
	uint16_t tmp = readLE16(&m_buffer[m_readPos]);
	m_readPos += 2;
	return tmp;
}

uint32_t FileStream::getU32()
{
	uint32_t tmp = readLE32(&m_buffer[m_readPos]);
	m_readPos += 4;
	return tmp;
}

std::string FileStream::getString()
{
	uint16_t len = getU16();
	if (m_readPos + len > m_buffer.size()) {
		g_logger.error(stdext::format("FileStream::getString(): would read beyond buffer size"));
		return std::string();
	}

	std::string ret((char *)&m_buffer[m_readPos], len);
	m_readPos += len;
	return ret;
}

void FileStream::writeByte(uint8_t byte)
{
	m_buffer[m_writePos++] = byte;
	++m_size;
}

void FileStream::writeU16(uint16_t val)
{
	writeLE16(&m_buffer[m_writePos], val);
	m_writePos += 2;
	m_size += 2;
}

void FileStream::writeU32(uint32_t val)
{
	writeLE32(&m_buffer[m_writePos], val);
	m_writePos += 4;
	m_size += 4;
}

void FileStream::writeString(const std::string& str)
{
	uint16_t strLen = str.length();

	writeU16(strLen);
	memcpy(&m_buffer[m_writePos], str.c_str(), strLen);

	m_writePos += strLen;
	m_size += strLen;
}

