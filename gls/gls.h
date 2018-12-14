// gls.h

/* Header file for gls.c/gls.dll */

#include <windows.h>
#include <stdlib.h>
#include <GL\glcorearb.h>
#include <GL\wglext.h>

#ifndef GLS_H
#define GLS_H

struct uIntBoxSides{
	UINT x;
	UINT y;
};

typedef struct uIntBoxSides RSLN; // Resolution

#define DLLEXP __declspec( dllexport )
#define DLLIMP __declspec( dllimport )

#ifndef FROM_DLL
#define DLLEX __declspec( dllimport )
DLLEX const RSLN defaultResolution;
GLAPI void APIENTRY				glDrawArrays (GLenum mode, GLint first, GLsizei count);
WINGDIAPI void APIENTRY			glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
WINGDIAPI void APIENTRY			glClear (GLbitfield mask);
WINGDIAPI void APIENTRY			glEnable (GLenum cap);
WINGDIAPI void APIENTRY			glBlendFunc (GLenum sfactor, GLenum dfactor);
WINGDIAPI void APIENTRY			glDepthFunc (GLenum func);
WINGDIAPI void APIENTRY			glDepthMask (GLboolean flag);
WINGDIAPI void APIENTRY			glDepthRange (GLclampd zNear, GLclampd zFar);
WINGDIAPI void APIENTRY			glClearDepth (GLclampd depth);
#else
#define DLLEX __declspec( dllexport )
DLLEX const RSLN defaultResolution={640,480};
#endif



//RSLN defaultResolution={640,480};


// VAO
DLLEX	PFNGLBINDVERTEXARRAYPROC			glBindVertexArray;
DLLEX	PFNGLBINDBUFFERPROC					glBindBuffer;
DLLEX	PFNGLGENBUFFERSPROC					glGenBuffers;
DLLEX	PFNGLDELETEBUFFERSPROC				glDeleteBuffers;
DLLEX	PFNGLBUFFERDATAPROC					glBufferData;
DLLEX	PFNGLDISABLEVERTEXATTRIBARRAYPROC	glDisableVertexAttribArray;
DLLEX	PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray;
DLLEX	PFNGLVERTEXATTRIBPOINTERPROC		glVertexAttribPointer;
DLLEX	PFNGLVERTEXATTRIBIPOINTERPROC		glVertexAttribIPointer;
DLLEX	PFNGLGENVERTEXARRAYSPROC			glGenVertexArrays;

// Shaders
DLLEX	PFNGLCREATESHADERPROC		glCreateShader;
DLLEX	PFNGLCREATEPROGRAMPROC		glCreateProgram;
DLLEX	PFNGLSHADERSOURCEPROC		glShaderSource;
DLLEX	PFNGLCOMPILESHADERPROC		glCompileShader;
DLLEX	PFNGLATTACHSHADERPROC		glAttachShader;
DLLEX	PFNGLLINKPROGRAMPROC		glLinkProgram;
DLLEX	PFNGLDELETESHADERPROC		glDeleteShader;
DLLEX	PFNGLUSEPROGRAMPROC			glUseProgram;	

// Shader access
DLLEX	PFNGLGETUNIFORMLOCATIONPROC		glGetUniformLocation;
DLLEX	PFNGLUNIFORM1FPROC				glUniform1f;
DLLEX	PFNGLUNIFORM1UIPROC				glUniform1ui;
DLLEX	PFNGLUNIFORM3FPROC				glUniform3f;

// Window and other management
DLLEX	PFNWGLCHOOSEPIXELFORMATARBPROC	wglChoosePixelFormatARB;

// Matricies
DLLEX	PFNGLUNIFORMMATRIX4FVPROC	glUniformMatrix4fv;

DLLEXP BOOL glsInitPointers();

DLLEXP HWND glsInitWindow(LPCWSTR title, WNDPROC windowProcedure, RSLN windowSides, HINSTANCE hInstance, BOOL fullscreen);

DLLEXP void glsDisableWindow(HWND* hWindow, HDC* hDeviceContext, HGLRC* hRenderingContext);

DLLEXP RSLN getCurrentResolution();

DLLEXP PIXELFORMATDESCRIPTOR glsSetPFD();

DLLEXP void glsStart(HWND* hWindow, HDC* hDeviceContext, HGLRC* hRenderingContext, LPCWSTR title, WNDPROC windowProcedure, RSLN windowSides, HINSTANCE hInstance, UINT mode);
#define GLS_DEVICE_RESOLUTION	0x0010
#define GLS_FULLSCREEN_MODE		0x0020
#define GLS_WINDOWED_MODE		0x0000

DLLEXP int glsGetPixelFormat(HDC* hDeviceContext, UINT AAMODE, PIXELFORMATDESCRIPTOR* pfd);
#define GLS_FORMAT_PLAIN		0x0000
#define GLS_FORMAT_ARB			0x0010
#define GLS_FORMAT				0x0010
#define GLS_MULTISAMPLE_BIT		0x000F

DLLEXP GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path, const char * geometry_file_path, UINT mode);
#define GLS_COMPILE_G_SHADER 0x0001
DLLEXP char *textFileRead(const char *fn);

DLLEXP void glsSingleMat4(GLfloat matrix[4][4], DWORD action, GLfloat value);
#define GLS_MAT_CREATE		0x00000001
#define GLS_MAT_ZOOM		0x00000002
#define GLS_MAT_ZOOM_ALL	0x00008002
#define GLS_MAT_MOVE		0x00000004
#define GLS_MAT_ROTATE		0x00000008

// SET_TO - set to value, MULTI - multiplicate by value, ADD - add the value; executed in this order, if more than one operation requested; if none requested - nothing will happen;
#define GLS_MAT_SET_TO		0x00000010
#define GLS_MAT_MULTI		0x00000020
#define GLS_MAT_ADD			0x00000040


#define GLS_MAT_X			0x00001000
#define GLS_MAT_Y			0x00002000
#define GLS_MAT_Z			0x00004000
#define GLS_MAT_W			0x00008000

DLLEXP void glsSingleMat4Zoom(GLfloat matrix[4][4], DWORD action, UINT ID, GLfloat value);

DLLEXP void glsSingleMat4Move(GLfloat matrix[4][4], DWORD action, UINT ID, GLfloat value);

DLLEXP void glsDoubleMat4(GLfloat targetMatrix[4][4], GLfloat sourceMatrix[4][4], DWORD action);

#endif