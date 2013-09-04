
#ifndef __MAIN_FRAME_H__
#define __MAIN_FRAME_H__

#include "decl.h"
#include "oglwindow.h"

class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
		void OnStart();

	private:
		OpenGLWindow* m_openGLWindow;
		OpenGLContext* m_openGLContext;
};

#endif //__MAIN_FRAME_H__
