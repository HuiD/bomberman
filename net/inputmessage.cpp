#include "inputmessage.h"

static __inline uint16_t unpack_u16(unsigned char *addr)
{
	return addr[1] << 8 | addr[0];
}

static __inline uint32_t unpack_u32(unsigned char *addr)
{
	return unpack_u16(addr + 2) << 16 | unpack_u16(addr);
}

InputMessage::InputMessage(uint8_t *data, size_t size) :
	m_data(data),
	m_size(size),
	m_pos(0)
{
}

InputMessage::~InputMessage()
{

}

uint8_t InputMessage::getByte()
{
	return m_data[m_pos++];
}

uint16_t InputMessage::getU16()
{
	uint16_t tmp = unpack_u16(&m_data[m_pos]);
	m_pos += 2;
	return tmp;
}

uint32_t InputMessage::getU32()
{
	uint32_t tmp = unpack_u32(&m_data[m_pos]);
	m_pos += 4;
	return tmp;
}

std::string InputMessage::getString()
{
	uint16_t len = getU16();
	if (!len)
		return std::string();

	if (m_pos + len > m_data.size())
		return std::string();

	std::string ret((char *)&m_data[m_pos], len);
	m_pos += len;
	return ret;
}

