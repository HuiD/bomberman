#ifndef __INPUTMESSAGE_H
#define __INPUTMESSAGE_H

#include "decl.h"

class InputMessage
{
public:
	InputMessage(uint8_t *data, size_t size);
	InputMessage();
	~InputMessage();

	void setData(uint8_t *d) { m_data = d; }
	void setSize(size_t size) { m_size = size; }

	uint8_t getByte();
	uint16_t getU16();
	uint32_t getU32();
	std::string getString();

private:
	uint8_t *m_data;
	size_t m_size;
	uint32_t m_pos;
};

#endif

