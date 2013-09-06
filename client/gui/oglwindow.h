#ifndef __OGL_WINDOW_H
#define __OGL_WINDOW_H

#include <functional>
#include "oglcontext.h"

enum RenderFlags
{
	RenderFlag_None = 0,
	RenderFlag_Initialize = 1,
	RenderFlag_Resize = 2
};

class OpenGLWindow : public wxGLCanvas
{
public:
	OpenGLWindow(wxWindow* parent, const wxString& title);
	~OpenGLWindow();

	void OnPaint(wxPaintEvent& event);
	void OnResize(wxSizeEvent& event);

protected:
	DECLARE_EVENT_TABLE()
	void Render();

private:
	OpenGLContext* m_boundContext;
	std::function<void()> m_renderFunction;
	uint32_t m_renderFlags;

	friend class OpenGLContext;
};

#endif //__OGL_WINDOW_H
