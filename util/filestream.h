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

