#ifndef __MAIN_FRAME_H
#define __MAIN_FRAME_H

#include "decl.h"
#include "oglwindow.h"

class MainFrame: public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~MainFrame();

	void OnStart();

private:
	OpenGLWindow* m_openGLWindow;
	OpenGLContext* m_openGLContext;
};

#endif //__MAIN_FRAME_H

