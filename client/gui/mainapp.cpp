
// Included files
#include "mainapp.h"
#include "mainframe.h"

#include "../../util/scheduler.h"

IMPLEMENT_APP(MainApp)
extern Scheduler g_sched;

bool MainApp::OnInit()
{
	if (!wxApp::OnInit()) {
		return false;
	}

	MainFrame* mainFrame = new MainFrame(
		_("Bomberman"),
		wxDefaultPosition,
		wxSize(800, 600)
	);
	SetTopWindow(mainFrame);

	mainFrame->Show();
	mainFrame->OnStart();
	return true;
}

int MainApp::OnExit()
{
	g_sched.stop();
	return wxApp::OnExit();
}
