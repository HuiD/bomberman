#ifndef __DECL_H
#define __DECL_H

#include "../decl.h"

#include "../util/position.h"
#include "../util/scheduler.h"

class Player;
class Tile;
class Item;

typedef std::shared_ptr<Player> PlayerPtr;
typedef std::shared_ptr<Tile> TilePtr;
typedef std::shared_ptr<Item> ItemPtr;

typedef std::list<ItemPtr> ItemList;

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif

#endif

