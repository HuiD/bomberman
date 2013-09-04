#ifndef __OUTPUTMESSAGE_H
#define __OUTPUTMESSAGE_H

#include "decl.h"

class OutputMessage
{
public:
	OutputMessage();
	~OutputMessage();

	void addByte(uint8_t byte);
	void addU16(uint16_t val);
	void addU32(uint32_t val);
	void addString(const std::string& str);

	uint8_t *data() const { return &m_data[0]; }

private:
	std::vector<uint8_t> m_data;
	uint32_t m_pos;
	size_t m_size;
};

#endif

