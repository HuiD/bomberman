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

