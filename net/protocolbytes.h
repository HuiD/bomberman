#ifndef __PROTOCOLBYTES_H
#define __PROTOCOLBYTES_H

enum ProtocolBytes : uint8_t
{
	NET_CHAT_WELCOME 	= 0x0A,
	NET_CHAT_MESSAGE 	= 0x0B,

	NET_PING 		= 0x0C,
	NET_PONG 		= 0x0D
};

#endif

