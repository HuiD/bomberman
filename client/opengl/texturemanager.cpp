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
#include "texturemanager.h"
#include "../../util/filestream.h"

#include <boost/filesystem.hpp>
#include <SOIL/SOIL.h>

TextureManager g_textures;

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

bool TextureManager::loadUp(const std::string& dir)
{
	boost::filesystem::path path(boost::filesystem::current_path().generic_string() + dir);
	if (!boost::filesystem::exists(path)) {
		g_logger.error(stdext::format("failed to find %s to load textures from", dir));
		return false;
	}

	for (boost::filesystem::directory_iterator it(path), end; it != end; ++it) {
		std::string inode = it->path().filename().string();
		if (boost::filesystem::is_directory(it->status())) {
			loadUp(inode);
			continue;
		}

		TexturePtr texture(new Texture);
		if (!texture->loadFrom(inode))
			g_logger.warning(stdext::format("failed to load texture %s, jumping to next...", inode));
		else
			m_textures.push_back(texture);
	}

	return true;
}

bool TextureManager::cacheInto(const std::string& filename)
{
	FileStreamPtr fs(new FileStream);

	fs->writeByte(TextureManagerVersion);
	for (const TexturePtr& texture : m_textures) {
		fs->writeU16(texture->getWidth());
		fs->writeU16(texture->getHeight());
		fs->writeByte(texture->hasAlphaChannel() ? 1 : 0);

		uint8_t *pixels = texture->getPixels();
		for (uint32_t i = 0; i < texture->getPixelCount(); ++i) {
			fs->writeByte(PixelStart);

			fs->writeByte(pixels[i * 4 + 0]); 	// red
			fs->writeByte(pixels[i * 4 + 1]); 	// green
			fs->writeByte(pixels[i * 4 + 2]); 	// blue
			if (texture->hasAlphaChannel())
				fs->writeByte(pixels[i * 4 + 3]);

			fs->writeByte(PixelEnd);
		}
	}
	fs->writeByte(TexturesEnd);

	bool ret = fs->write(filename);
	if (!ret)
		g_logger.error(stdext::format("failed to cache textures into file %s", filename));
	else
		g_logger.debug(stdext::format("successfully cached textures into %s", filename));

	return ret;
}

bool TextureManager::loadFrom(const std::string& filename)
{
	FileStreamPtr fs(new FileStream);
	if (!fs->cache(filename)) {
		g_logger.error(stdext::format("failed to cache %s into memory", filename));
		return false;
	}

	if (fs->getByte() != TextureManagerVersion)
		g_logger.warning(stdext::format("texture file version is invalid, operation might fail"));

	uint8_t byte;
	while ((byte = fs->getByte()) != TexturesEnd) {
		TexturePtr texture(new Texture);
		texture->setWidth(fs->getU16());
		texture->setHeight(fs->getU16());

		bool hasAlphaChannel   = fs->getByte() != (char)0;
		bool readPixels = false;
		uint16_t currentPixel = 0;
		uint8_t *pixels = texture->getPixels();

		texture->setHasAlphaChannel(hasAlphaChannel);
		while (!readPixels) {
			int x = currentPixel % texture->getWidth();
			int y = currentPixel / texture->getWidth();
			int pos = (y * texture->getWidth() + x);

			if (hasAlphaChannel)
				pos *= 4;
			else
				pos *= 3;

			switch ((byte = fs->getByte())) {
				case PixelStart:
					pixels[pos + 0] = fs->getByte();
					pixels[pos + 1] = fs->getByte();
					pixels[pos + 2] = fs->getByte();

					if (hasAlphaChannel)
						pixels[pos + 3] = fs->getByte();
					break;
				case PixelEnd:
					readPixels = true;
					break;
			}

			++currentPixel;
		}

		m_textures.push_back(texture);
	}

	return true;
}

bool TextureManager::screenshot(const std::string& output, int x, int y, int width, int height)
{
	return !!SOIL_save_screenshot(output.c_str(), SOIL_SAVE_TYPE_BMP, x, y, width, height);
}

