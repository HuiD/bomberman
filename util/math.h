#ifndef __MATH_H
#define __MATH_H

#include "decl.h"

inline uint16_t readLE16(const uchar *addr) { return (uint16_t)addr[1] << 8 | addr[0]; }
inline uint32_t readLE32(const uchar *addr) { return (uint32_t)readLE16(addr + 2) << 16 | readLE16(addr); }
inline uint64_t readLE64(const uchar *addr) { return (uint64_t)readLE32(addr + 4) << 32 | readLE32(addr); }
 
inline void writeLE16(uchar *addr, uint16_t value) { addr[1] = value >> 8; addr[0] = (uint8_t)value; }
inline void writeLE32(uchar *addr, uint32_t value) { writeLE16(addr + 2, value >> 16); writeLE16(addr, (uint16_t)value); }
inline void writeLE64(uchar *addr, uint64_t value) { writeLE32(addr + 4, value >> 32); writeLE32(addr, (uint32_t)value); }

#endif

