#ifndef __DECL_H
#define __DECL_H

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

namespace asio = boost::asio;

#include <memory>
#include <string>
#include <stdint.h>
#include <stdlib.h>

class Connection;
class Listener;

typedef std::shared_ptr<Connection> ConnectionPtr;
typedef std::shared_ptr<Listener> ListenerPtr;

#endif

