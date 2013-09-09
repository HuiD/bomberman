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

