#ifndef __DECL_H
#define __DECL_H

#include <memory>
#include <list>
#include <string>

class Player;
class Tile;
class Item;

typedef std::shared_ptr<Player> PlayerPtr;
typedef std::shared_ptr<Tile> TilePtr;
typedef std::shared_ptr<Item> ItemPtr;

typedef std::list<ItemPtr> ItemList;

#endif

