/*
 * Copyright (c) 2013 Ahmed Samy  <f.fallen45@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "map.h"
#include "item.h"
#include "../util/filestream.h"

// Map file structure (Pretty simple)
// 	- Width
// 	- Height
// 	- Tile Count
// 		Loop 0 -> Tile Count
// 			Read Tile Position
// 			Read Count of items in this tile
// 			Loop 0 -> count of items
// 				Read Item ID
// 				Read Item Texture Filename
// 			End Loop
// 			Read boolean (can it hold a player?)
// 		End Loop

TilePtr Map::m_nullTile = TilePtr(new Tile(Position2D(0xFFFF, 0xFFFF)));

Map::Map(uint16_t width, uint16_t height) :
	m_width(width),
	m_height(height)
{

}

Map::~Map()
{
	m_tileBlocks.clear();
}

bool Map::load(const std::string& filename)
{
	FileStreamPtr file(new FileStream());

	if (!file->cache(filename)) {
		g_logger.error(stdext::format("failed to open %s: %s", filename, strerror(errno)));
		return false;
	}

	m_width  = file->getU16();
	m_height = file->getU32();
	if (m_width < 0 || m_height < 0) {
		g_logger.error(stdext::format("Map::load(): width and height are invalid!"));
		return false;
	}

	uint16_t tileCount = file->getU16();
	for (uint16_t i = 0; i < tileCount; i++) {
		Position2D tilePosition;

		tilePosition.x = file->getU16();
		tilePosition.y = file->getU16();

		if (!tilePosition.isValid()) {
			g_logger.error(stdext::format("Invalid tile position at index %d file position: %d", i, file->getReadPos()));
			return false;
		}

		TilePtr newTile = createTile(tilePosition);
		uint16_t itemCount = file->getU16();

		for (uint16_t c = 0; c < itemCount; c++) {
			ItemPtr newItem(new Item(file->getU16()));	

			if (!newItem->loadTexture(file->getString())) {
				g_logger.error(stdext::format("failed to load texture from %s for item %d", newItem->getTextureFile(), newItem->getID()));
				return false;
			}

			newTile->addItem(newItem);
		}

		newTile->setCanHoldPlayers(file->getByte() != (char)0);
	}

	g_logger.debug(stdext::format("successfully loaded map from %s, tile count: %d", filename, tileCount));
	return true;
}

bool Map::save(const std::string& filename)
{
	FileStreamPtr file(new FileStream());

	file->writeU16(m_width);
	file->writeU16(m_height);

	int fpos = file->getWritePos();
	file->setWritePos(fpos + sizeof(uint16_t)); // we will go back later to add the tiles count.

	uint16_t tileCount = 0;
	for (const auto& pair : m_tileBlocks) {
		const TileBlock& block = pair.second;
		for (const TilePtr& tile : block.getTiles()) {
			if (!tile)
				continue;

			++tileCount;
			const Position2D& tilePos = tile->getPosition();

			file->writeU16(tilePos.x);
			file->writeU16(tilePos.y);

			// Write tile items
			// ... but don't forget about the items count.
			int currPos = file->getWritePos();
			uint16_t itemCount = 0;
			file->seek(currPos + sizeof(uint16_t));

			for (const ItemPtr& item : tile->getItems()) {
				if (!item)
					continue;

				file->writeU16(item->getID());
				file->writeString(item->getTextureFile());
				++itemCount;
			}

			file->writeByte(uint8_t(tile->canHoldPlayers()));
			// Write item count
			file->setWritePos(currPos);
			file->writeU16(itemCount);
		}
	}

	file->setWritePos(fpos);
	file->writeU16(tileCount);

	bool ret = file->write(filename.c_str());
	if (!ret)
		g_logger.error(stdext::format("failed to save map to %s", filename));
	else
		g_logger.debug(stdext::format("successfully saved map to %s tile count %d", filename, tileCount));

	return ret;
}

const TilePtr& Map::createTile(const Position2D& pos)
{
	if (pos.x > m_width)
		m_width = pos.x;
	if (pos.y > m_height)
		m_height = pos.y;

	TileBlock& block = m_tileBlocks[getBlockIndex(pos)];
	return block.create(pos);
}

const TilePtr& Map::getTile(const Position2D& pos) const
{
	auto it = m_tileBlocks.find(getBlockIndex(pos));
	if (it != m_tileBlocks.end())
		return it->second.get(pos);

	return m_nullTile;
}

