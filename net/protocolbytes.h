#ifndef __PROTOCOLBYTES_H
#define __PROTOCOLBYTES_H

enum ProtocolBytes : uint8_t
{
	// Generic
	NET_PING 		= 0x0A,
	NET_PONG 		= 0x0B,
	NET_MSG_STATUS 		= 0x0C,
	NET_MSG_ERROR 		= 0x0D,

	// Protocol Game
	NET_GAME_WELCOME 	= 0x0E,
	NET_GAME_START 		= 0x0F,
	NET_GAME_CANCEL_START 	= 0x10,
	NET_GAME_PLAYER_JOIN 	= 0x11,
	NET_GAME_PLAYER_LEAVE 	= 0x12,
	NET_GAME_PLAYER_DEAD  	= 0x13,
	NET_GAME_PLAYER_MOVE 	= 0x14,
	NET_GAME_FULL 		= 0x15,
};

#endif

