
#ifndef __OGL_WINDOW_HPP__
#define __OGL_WINDOW_HPP__

#include "oglcontext.h"

class OpenGLWindow : public wxGLCanvas
{
	public:
		OpenGLWindow(wxWindow* parent, const wxString& title);
		~OpenGLWindow();

		void OnPaint(wxPaintEvent& event);

	protected:
		DECLARE_EVENT_TABLE()
		void Render();

	private:
		OpenGLContext* m_boundContext;
		friend class OpenGLContext;
};

#endif //__OGL_WINDOW_HPP__
