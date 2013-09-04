
// Included files
#include "oglcontext.h"
#include "oglwindow.h"

OpenGLContext* OpenGLContext::context = nullptr;
OpenGLContext::OpenGLContext(OpenGLWindow* window, const OpenGLContext* sharedContext) :
	m_vertexBuffer(nullptr),
	m_indexBuffer(nullptr),
	m_vertexArray(nullptr),
	m_shaderProgram(nullptr),
	m_drawFrameBuffer(nullptr),
	m_readFrameBuffer(nullptr),
	m_renderBuffer(nullptr)
{
	assert(window != nullptr);
	wxGLContext* shared = nullptr;
	if (sharedContext) {
		shared = sharedContext->m_context;
	}

	m_context = new wxGLContext(window, shared);
	bind(window);
}

OpenGLContext::~OpenGLContext()
{
	if (context == this) {
		context = nullptr;
	}
	delete m_context;
}

OpenGLContext* OpenGLContext::currentContext()
{
	return context;
}

bool OpenGLContext::bind(OpenGLWindow* window)
{
	if (context == this) {
		return true;
	}

	if (window && m_context->SetCurrent(*window)) {
		static bool hasGLEW = false;
		if (!hasGLEW) {
			GLenum err = glewInit();
			if (err != GLEW_OK) {
				std::cout << "Error: " << glewGetErrorString(err) << std::endl;
			} else {
				hasGLEW = true;
			}
		}

		window->m_boundContext = this;
		context = this;
	}
	return context == this;
}
