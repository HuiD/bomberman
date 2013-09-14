#include "mainwindow.h"

#include "../../util/logger.h"

MainWindow g_window;

MainWindow::MainWindow() :
	m_width(800),
	m_height(600),
	m_window(nullptr),
	m_renderer(nullptr)
{

}

MainWindow::~MainWindow()
{
	close();
}

void MainWindow::init()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 4);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);

#ifdef OPENGL_ES
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_ES);
#endif

	m_window = SDL_CreateWindow("Bomberman Client",
					SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					m_width, m_height,
					SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
	if (!m_window)
		g_logger.fatal("unrecoverable error, cannot create main window!");

	SDL_GetWindowSize(m_window, &m_width, &m_height);
	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context)
		g_logger.fatal("unrecoverable error, failed to create GL context!");

	SDL_GL_MakeCurrent(m_window, m_context);
}

void MainWindow::close()
{
	if (m_context)
		SDL_GL_DeleteContext(m_context);
	if (m_renderer)
		SDL_DestroyRenderer(m_renderer);
	if (m_window)
		SDL_DestroyWindow(m_window);

	m_window = nullptr;
	SDL_Quit();
}

void MainWindow::setVisible(bool visibile)
{
	if (visibile)
		show();
	else
		hide();
}

void MainWindow::resize(int width, int height)
{
	if (width < 0 || height < 0)
		return;

	SDL_SetWindowSize(m_window, width, height);
	if (m_resizeCallback)
		m_resizeCallback(width, height);

	m_width = width;
	m_height = height;
}

void MainWindow::show()
{
	SDL_ShowWindow(m_window);
	if (m_renderCallback)
		m_renderCallback();
}

void MainWindow::hide()
{
	SDL_HideWindow(m_window);
}

void MainWindow::poll()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
					case SDL_WINDOWEVENT_SHOWN:
						m_visible = true;
						break;
					case SDL_WINDOWEVENT_HIDDEN:
						m_visible = false;
						break;
					case SDL_WINDOWEVENT_RESIZED:
						resize(event.window.data1, event.window.data2);
						break;
					case SDL_WINDOWEVENT_CLOSE:
						close();
						break;
					default:
						break;
				}
				break;
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				if (m_keyPressCallback)
					m_keyPressCallback(event.key.keysym.sym);
				break;
			case SDL_TEXTINPUT:
				break;
			case SDL_MOUSEWHEEL:
				if (m_wheelCallback)
					m_wheelCallback(event.wheel.x, event.wheel.y);
				break;
			case SDL_QUIT:
				break;
		}
	}
}

void MainWindow::swapBuffers()
{
	SDL_GL_SwapWindow(m_window);
}

void MainWindow::setTitle(const std::string& title)
{
	SDL_SetWindowTitle(m_window, title.c_str());
}

void MainWindow::setFullScreen(bool full)
{
	if (m_fullscreen == full)
		return;

	SDL_SetWindowFullscreen(m_window, (SDL_bool)full);
	m_fullscreen = full;
}

void MainWindow::setVerticalSync(bool enable)
{
	SDL_GL_SetSwapInterval(enable);
}

