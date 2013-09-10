#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include "decl.h"

#include <functional>

class MainWindow
{
	typedef std::function<void()> RenderCallback;
	typedef std::function<void(int, int)> ResizeCallback;
	typedef std::function<void(int)> KeyPressCallback;
	typedef std::function<void(int, int)> WheelCallback;

public:
	MainWindow();
	~MainWindow();

	// Initialise stuff, do not show up yet.
	void init();
	// Close the window, this includes exiting the whole application
	void close();

	int width() const { return m_width; }
	int height() const { return m_height; }
	void resize(int width, int height);

	void show();
	void hide();
	void poll();
	void swapBuffers();

	void setTitle(const std::string& tile);
	void setVerticalSync(bool enable);

	void setRenderCallback(const RenderCallback& cb) { m_renderCallback = cb; }
	void setResizeCallback(const ResizeCallback& cb) { m_resizeCallback = cb; }
	void setKeypressCallback(const KeyPressCallback& cb) { m_keyPressCallback = cb; }
	void setWheelCallback(const WheelCallback& cb) { m_wheelCallback = cb; }

	bool isClosed() const { return !m_window; }
	bool isVisible() const { return m_visible; }
	void setVisible(bool visible);

	bool isFullscreen() const { return m_fullscreen; }
	void setFullScreen(bool full);

private:
	int m_width;
	int m_height;

	bool m_visible;
	bool m_fullscreen;

	RenderCallback m_renderCallback;
	ResizeCallback m_resizeCallback;
	KeyPressCallback m_keyPressCallback;
	WheelCallback m_wheelCallback;

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_GLContext m_context;
};

extern MainWindow g_window;

#endif

