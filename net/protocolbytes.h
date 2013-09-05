#ifndef __PROTOCOLBYTES_H
#define __PROTOCOLBYTES_H

enum ProtocolBytes : uint8_t
{
	NET_CHAT_WELCOME 	= 0x0A,
	NET_CHAT_MESSAGE 	= 0x0B,
	NET_CHAT_NICKCHANGE 	= 0x0C,
	NET_CHAT_LEAVE 		= 0x0D,

	NET_PING 		= 0x0E,
	NET_PONG 		= 0x0F
};

#endif

