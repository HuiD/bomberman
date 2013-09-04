#ifndef __DECL_H
#define __DECL_H

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

namespace asio = boost::asio;

#include <memory>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

class Connection;
class Listener;

typedef std::shared_ptr<Connection> ConnectionPtr;
typedef std::shared_ptr<Listener> ListenerPtr;

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif

#endif

