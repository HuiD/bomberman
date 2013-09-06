#ifndef __ITEM_H
#define __ITEM_H

#include "decl.h"

class Item
{
public:
	Item();
	~Item();

	bool blocksPath() const { return false; }
};

#endif

