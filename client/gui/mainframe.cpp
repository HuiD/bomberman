
// Included files
#include "mainframe.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) :
	wxFrame(nullptr, wxID_ANY, title, pos, size),
	m_openGLWindow(nullptr),
	m_openGLContext(nullptr)
{
	SetSizer(new wxBoxSizer(wxHORIZONTAL));
	SetAutoLayout(true);
}

MainFrame::~MainFrame()
{
	if (m_openGLContext)
		delete m_openGLContext;
}

void MainFrame::OnStart()
{
	wxPanel *panel = new wxPanel(this, wxID_ANY);
	panel->SetSizer(new wxBoxSizer(wxHORIZONTAL));

	m_openGLWindow = new OpenGLWindow(panel, _("OpenGLWindow"));
	new wxButton(m_openGLWindow, wxID_ANY, "Test Button", wxPoint(50, 50), wxSize(100, 24));

	wxSizer *panelSizer = panel->GetSizer();
	panelSizer->Add(m_openGLWindow, wxSizerFlags(1).Expand());
	panelSizer->Layout();

	wxSizer *sizer = GetSizer();
	sizer->Add(panel, wxSizerFlags(1).Expand());
	sizer->Layout();

	m_openGLWindow->SetSize(panel->GetSize());
	m_openGLContext = new OpenGLContext(m_openGLWindow);
	m_openGLWindow->Refresh(false);
}

