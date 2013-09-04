#include "outputmessage.h"

static __inline void pack_u16(unsigned char *addr, uint16_t value)
{
	addr[1] = value >> 8;
	addr[0] = (uint8_t)value;
}

static __inline void pack_u32(unsigned char *addr, uint32_t value)
{
	pack_u16(addr + 2, value >> 16);
	pack_u16(addr,     (uint16_t)value);
}

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
	m_data[m_pos++] = byte;
}

void OutputMessage::addU16(uint16_t val)
{
	pack_u16(&m_data[m_pos], val);
	m_pos += 2;
	m_size += 4;
}

void OutputMessage::addU32(uint32_t val)
{
	pack_u32(&m_data[m_pos], val);
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

