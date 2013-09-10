#ifndef __TEXTUREDITEM_H
#define __TEXTUREDITEM_H

#include "texture.h"

#include <vector>

class TexturedItem
{
public:
	TexturedItem();
	~TexturedItem();

	void addTexture(int frameIndex, const TexturePtr& texture);
	const TexturePtr& getNextTexture() const;

	void update();
	void reset();

private:
	int m_currentFrame;
	std::vector<TexturePtr> m_textures;
};

#endif

