#ifndef __ITEM_H
#define __ITEM_H

#include "decl.h"

class Item
{
public:
	Item(uint16_t id);
	~Item();

	uint16_t getID() const { return m_id; }

	std::string getTextureFile() const { return m_textureFile; }
	bool loadTexture(const std::string& filename) { return true; }

private:
	uint16_t m_id;
	std::string m_textureFile;
};

#endif

