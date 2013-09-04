#ifndef __OUTPUTMESSAGE_H
#define __OUTPUTMESSAGE_H

#include "decl.h"
#include <util/databuffer.h>

class OutputMessage
{
public:
	OutputMessage();
	~OutputMessage();

	void addByte(uint8_t byte);
	void addU16(uint16_t val);
	void addU32(uint32_t val);
	void addString(const std::string& str);

	const uint8_t *data() const { return &m_data[0]; }
	size_t size() const { return m_size; }

private:
	DataBuffer<uint8_t> m_data;
	uint32_t m_pos;
	size_t m_size;
};

#endif

