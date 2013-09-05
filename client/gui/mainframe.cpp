
// Included files
#include "mainframe.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) :
	wxFrame(nullptr, wxID_ANY, title, pos, size),
	m_openGLWindow(nullptr),
	m_openGLContext(nullptr)
{
	m_openGLWindow = new OpenGLWindow(this, _("OpenGLWindow"));

	SetSizer(new wxBoxSizer(wxHORIZONTAL));
	SetAutoLayout(true);
}

MainFrame::~MainFrame()
{
	if (m_openGLContext) {
		delete m_openGLContext;
	}
}

void MainFrame::OnStart()
{
	GetSizer()->Add(m_openGLWindow, wxSizerFlags(1).Expand());

	m_openGLContext = new OpenGLContext(m_openGLWindow);
	new wxButton(m_openGLWindow, wxID_ANY, "Test Button", wxPoint(50, 50), wxSize(100, 24));

	m_openGLWindow->Refresh(false);
}
