#ifndef __NET_DECL_H
#define __NET_DECL_H

#include "../decl.h"
#include "protocolbytes.h"

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

namespace asio = boost::asio;

#define DATA_SIZE 10240

class Connection;
class Listener;
class ProtocolGame;

typedef std::shared_ptr<Connection> ConnectionPtr;
typedef std::shared_ptr<Listener> ListenerPtr;
typedef std::shared_ptr<ProtocolGame> ProtocolGamePtr;

#endif

