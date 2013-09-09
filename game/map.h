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
#ifndef __MAP_H
#define __MAP_H

#include "tile.h"

#include <unordered_map>
#include <array>

#define DEFAULT_MAP_WIDTH 800
#define DEFAULT_MAP_HEIGHT 600
#define BLOCK_SIZE 32

class TileBlock
{
	typedef std::array<TilePtr, BLOCK_SIZE * BLOCK_SIZE> TileArray;
public:
	TileBlock()
	{
		m_tiles.fill(nullptr);
	}

	const TileArray& getTiles() const { return m_tiles; }
	const TilePtr& create(const Position2D& pos)
	{
		TilePtr& tile = m_tiles[getTileIndex(pos)];
		tile = TilePtr(new Tile(pos));
		return tile;
	}
	const TilePtr& get(const Position2D& pos) const { return m_tiles[getTileIndex(pos)]; }
	void remove(const Position2D& pos) { m_tiles[getTileIndex(pos)] = nullptr; }

protected:
	uint getTileIndex(const Position2D& pos) const { return ((pos.y % BLOCK_SIZE) * BLOCK_SIZE) + (pos.x % BLOCK_SIZE); }

private:
	TileArray m_tiles;
};

class Map
{
public:
	Map(uint16_t width = DEFAULT_MAP_WIDTH, uint16_t height = DEFAULT_MAP_HEIGHT);
	~Map();

	bool load(const std::string& filename);
	bool save(const std::string& filename);
	void clean();

	const TilePtr& createTile(const Position2D& pos);
	const TilePtr& getTile(const Position2D& pos) const;

protected:
	inline bool isInRange(const Position2D& pos) const
	{
		return m_width >= pos.x && m_height >= pos.y;
	}
	uint getBlockIndex(const Position2D& pos) const
	{
		return ((pos.y / BLOCK_SIZE) * (65536 / BLOCK_SIZE)) + (pos.x / BLOCK_SIZE);
	}

private:
	uint16_t m_width;
	uint16_t m_height;

	static TilePtr m_nullTile;
	std::unordered_map<uint, TileBlock> m_tileBlocks;
};

#endif

