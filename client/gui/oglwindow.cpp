
// Included files
#include <wx/dcbuffer.h>
#include "oglwindow.h"
#include "oglcontext.h"

BEGIN_EVENT_TABLE(OpenGLWindow, wxGLCanvas)
	EVT_PAINT(OpenGLWindow::OnPaint)
	EVT_SIZE(OpenGLWindow::OnResize)
END_EVENT_TABLE()

#ifdef _WIN32
static const int32_t attribList[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 32, 0};
#else
static const int32_t attribList[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
#endif

OpenGLWindow::OpenGLWindow(wxWindow* parent, const wxString& title) :
	wxGLCanvas(parent, wxID_ANY, attribList, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, title, wxNullPalette),
	m_boundContext(nullptr),
	m_renderFunction(nullptr),
	m_renderFlags(RenderFlag_Initialize)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	m_renderFunction = [this](){ Render(); };
}

OpenGLWindow::~OpenGLWindow()
{
	// Empty
}

void OpenGLWindow::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	if (!m_boundContext || !m_boundContext->bind(this)) {
		return;
	}

	wxAutoBufferedPaintDC(this);
	if (m_renderFunction) {
		m_renderFunction();
	}
	SwapBuffers();
}

void OpenGLWindow::OnResize(wxSizeEvent& WXUNUSED(event))
{
	m_renderFlags |= RenderFlag_Resize;
}

void OpenGLWindow::Render()
{
	if (m_renderFlags & RenderFlag_Initialize) {
		glClearColor(0.f, 0.f, 0.f, 0.f);

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		// Shader
		//auto frustum = glm::frustum(0.f, 800.f, 600.f, 0.f, 0.f, 65535.f);
		//glUniformMatrix4fv(glGetUniformLocation(0, "Projection"), 1, GL_FALSE, glm::value_ptr(frustum));

		// Wait until everything finish
		m_renderFlags &= ~RenderFlag_Initialize;
		glFinish();
	}

	if (m_renderFlags & RenderFlag_Resize) {
		const auto& size = GetSize();
		glViewport(0, 0, size.GetWidth(), size.GetHeight());

		m_renderFlags &= ~RenderFlag_Resize;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
