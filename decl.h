#ifndef __ROOT_DECL_H
#define __ROOT_DECL_H

#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#include <string>
#include <memory>
#include <functional>
#include <algorithm>
#include <list>
#include <vector>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "util/logger.h"
#include "util/format.h"
#include "util/configmanager.h"

/* Short naming  */
typedef unsigned char uchar;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#ifdef _MSC_VER
#pragma warning(disable:4800)
#endif
#endif

