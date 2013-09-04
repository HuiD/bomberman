
// Included files
#include "mainframe.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) :
	wxFrame(nullptr, wxID_ANY, title, pos, size),
	m_openGLWindow(nullptr),
	m_openGLContext(nullptr)
{
	m_openGLWindow = new OpenGLWindow(this, _("OpenGLWindow"));

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	const wxSizerFlags& flags = wxSizerFlags(1).Expand();
	sizer->Add(m_openGLWindow, flags);

	SetSizer(sizer);
	SetAutoLayout(true);
}

void MainFrame::OnStart()
{
	m_openGLContext = new OpenGLContext(m_openGLWindow);
	new wxButton(m_openGLWindow, wxID_ANY, "Test Button", wxPoint(50, 50), wxSize(100, 24));

	m_openGLWindow->Refresh(false);
}