#ifndef __OGL_CONTEXT_H
#define __OGL_CONTEXT_H

#include <map>

#include "decl.h"
#include <wx/glcanvas.h>

class OpenGLWindow;
class OpenGLTexture;
class OpenGLVertexBuffer;
class OpenGLIndexBuffer;
class OpenGLVertexArray;
class OpenGLShaderProgram;
class OpenGLFrameBuffer;
class OpenGLRenderBuffer;

class OpenGLContext
{
public:
	OpenGLContext(OpenGLWindow* window, const OpenGLContext* sharedContext = nullptr);
	~OpenGLContext();

	static OpenGLContext* currentContext();

	bool bind(OpenGLWindow* window);

	template<class T>
	T* getTexture(GLenum type)
	{
		return static_cast<T*>(m_texture[type]);
	}

private:
	wxGLContext* m_context;
	std::map<GLenum, OpenGLTexture*> m_texture;

	OpenGLVertexBuffer* m_vertexBuffer;
	OpenGLIndexBuffer* m_indexBuffer;
	OpenGLVertexArray* m_vertexArray;
	OpenGLShaderProgram* m_shaderProgram;
	OpenGLFrameBuffer *m_drawFrameBuffer, *m_readFrameBuffer;
	OpenGLRenderBuffer* m_renderBuffer;

private:
	static OpenGLContext* context;

	friend class OpenGLVertexBuffer;
	friend class OpenGLIndexBuffer;
	friend class OpenGLVertexArray;

	friend class OpenGLFrameBuffer;
	friend class OpenGLDrawFrameBuffer;
	friend class OpenGLReadFrameBuffer;
	friend class OpenGLRenderBuffer;

	friend class OpenGLShader;
	friend class OpenGLShaderProgram;

	friend class OpenGLTexture;
	friend class OpenGLTexture2D;
	friend class OpenGLTexture2DArray;
	friend class OpenGLTexture3D;
};

#endif //__OGL_CONTEXT_H

