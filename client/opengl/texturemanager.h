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
#ifndef __TEXTUREMANAGER_H
#define __TEXTUREMANAGER_H

#include <string>
#include <list>

#include "texture.h"

class TextureManager
{
	enum {
		TextureManagerVersion 	= 0x00,
		PixelStart 		= 0xFE,
		PixelEnd 		= 0xFF,
		TexturesEnd 		= 0xED
	};

public:
	TextureManager();
	~TextureManager();

	/// Load up a directory recursively lookin out for
	/// textures
	bool loadUp(const std::string& dir);
	/// Cache all textures in `m_textures' into binary form
	/// filename
	bool cacheInto(const std::string& filename);
	/// Load from cached texture file filename
	bool loadFrom(const std::string& filename);

	bool screenshot(const std::string& output, int x, int y, int width, int height);

private:
	std::list<TexturePtr> m_textures;
};

extern TextureManager g_textures;

#endif

