
// Included files
#include "oglwindow.h"
#include "oglcontext.h"

BEGIN_EVENT_TABLE(OpenGLWindow, wxGLCanvas)
    EVT_PAINT(OpenGLWindow::OnPaint)
END_EVENT_TABLE()

static const int32_t attribList[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 32};
OpenGLWindow::OpenGLWindow(wxWindow* parent, const wxString& title) :
	wxGLCanvas(parent, wxID_ANY, attribList, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, title, wxNullPalette),
	m_boundContext(nullptr)
{
	// Empty
	freopen("test.txt", "w", stdout);
}

OpenGLWindow::~OpenGLWindow()
{
	// Empty
}

void OpenGLWindow::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	Render();
}

void OpenGLWindow::Render()
{
	if (!m_boundContext) {
		return;
	}

	m_boundContext->bind(this);
	wxPaintDC(this);

	const auto& size = GetSize();
	glViewport(0, 0, size.GetWidth(), size.GetHeight());

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SwapBuffers();
}
