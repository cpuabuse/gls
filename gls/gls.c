// gls.c
/* Main program file for gls project */

// System headers
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Include main header
#ifndef FROM_DLL
#define FROM_DLL
#endif
#include "gls.h"

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

BOOL glsInitPointers() {
	void* procResult;

	// Vertex arrays
	procResult = wglGetProcAddress("glGenVertexArrays");
	if (procResult == NULL) return(FALSE);
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)procResult;

	procResult = wglGetProcAddress("glBindVertexArray");
	if (procResult == NULL) return(FALSE);
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)procResult;

	procResult = wglGetProcAddress("glBindBuffer");
	if (procResult == NULL) return(FALSE);
	glBindBuffer = (PFNGLBINDBUFFERPROC)procResult;

	procResult = wglGetProcAddress("glGenBuffers");
	if (procResult == NULL) return(FALSE);
	glGenBuffers = (PFNGLGENBUFFERSPROC)procResult;

	procResult = wglGetProcAddress("glDeleteBuffers");
	if (procResult == NULL) return(FALSE);
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)procResult;

	procResult = wglGetProcAddress("glBufferData");
	if (procResult == NULL) return(FALSE);
	glBufferData = (PFNGLBUFFERDATAPROC)procResult;

	procResult = wglGetProcAddress("glDisableVertexAttribArray");
	if (procResult == NULL) return(FALSE);
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)procResult;

	procResult = wglGetProcAddress("glEnableVertexAttribArray");
	if (procResult == NULL) return(FALSE);
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)procResult;

	procResult = wglGetProcAddress("glVertexAttribPointer");
	if (procResult == NULL) return(FALSE);
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)procResult;

	procResult = wglGetProcAddress("glVertexAttribIPointer");
	if (procResult == NULL) return(FALSE);
	glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)procResult;

	// Shaders
	procResult = wglGetProcAddress("glCreateShader");
	if (procResult == NULL) return(FALSE);
	glCreateShader = (PFNGLCREATESHADERPROC)procResult;

	procResult = wglGetProcAddress("glCreateProgram");
	if (procResult == NULL) return(FALSE);
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)procResult;

	procResult = wglGetProcAddress("glShaderSource");
	if (procResult == NULL) return(FALSE);
	glShaderSource = (PFNGLSHADERSOURCEPROC)procResult;

	procResult = wglGetProcAddress("glCompileShader");
	if (procResult == NULL) return(FALSE);
	glCompileShader = (PFNGLCOMPILESHADERPROC)procResult;

	procResult = wglGetProcAddress("glAttachShader");
	if (procResult == NULL) return(FALSE);
	glAttachShader = (PFNGLATTACHSHADERPROC)procResult;

	procResult = wglGetProcAddress("glLinkProgram");
	if (procResult == NULL) return(FALSE);
	glLinkProgram = (PFNGLLINKPROGRAMPROC)procResult;

	procResult = wglGetProcAddress("glDeleteShader");
	if (procResult == NULL) return(FALSE);
	glDeleteShader = (PFNGLDELETESHADERPROC)procResult;

	procResult = wglGetProcAddress("glUseProgram");
	if (procResult == NULL) return(FALSE);
	glUseProgram = (PFNGLUSEPROGRAMPROC)procResult;

	// Shader access
	procResult = wglGetProcAddress("glUniform1f");
	if (procResult == NULL) return(FALSE);
	glUniform1f = (PFNGLUNIFORM1FPROC)procResult;

	procResult = wglGetProcAddress("glUniform3f");
	if (procResult == NULL) return(FALSE);
	glUniform3f = (PFNGLUNIFORM3FPROC)procResult;

	procResult = wglGetProcAddress("glUniform1ui");
	if (procResult == NULL) return(FALSE);
	glUniform1ui = (PFNGLUNIFORM1UIPROC)procResult;

	procResult = wglGetProcAddress("glGetUniformLocation");
	if (procResult == NULL) return(FALSE);
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)procResult;

	// Window and other management
	procResult = wglGetProcAddress("wglChoosePixelFormatARB");
	if (procResult == NULL) return(FALSE);
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)procResult;

	// Matricies
	procResult = wglGetProcAddress("glUniformMatrix4fv");
	if (procResult == NULL) return(FALSE);
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)procResult;

	return(TRUE);
}

HWND glsInitWindow(LPCWSTR title, WNDPROC windowProcedure, RSLN windowSides, HINSTANCE hInstance, BOOL fullscreen) {
	HWND		hWindow;
	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		windowRect;

	memset(&wc, 0, sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = windowProcedure;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = title;

	RegisterClass(&wc);

	windowRect.left = 0;
	windowRect.right = windowSides.x;
	windowRect.top = 0;
	windowRect.bottom = windowSides.y;

	if (fullscreen) {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = windowSides.x;
		dmScreenSettings.dmPelsHeight = windowSides.y;
		dmScreenSettings.dmBitsPerPel = 16;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&dmScreenSettings, 4);
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		// ShowCursor(FALSE);
	}
	else {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU;
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	hWindow = CreateWindowEx(dwExStyle, title, title, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, hInstance, NULL);

	// if(!hWnd) return NULL;

	ShowWindow(hWindow, SW_SHOW);
	UpdateWindow(hWindow);
	SetFocus(hWindow);

	return hWindow;
}

int glsGetPixelFormat(HDC* hDeviceContext, UINT mode, PIXELFORMATDESCRIPTOR* pfd) {
	int format;

	int attributes[] = {
	WGL_DRAW_TO_WINDOW_ARB,	GL_TRUE,
	WGL_SUPPORT_OPENGL_ARB,	GL_TRUE,
	WGL_ACCELERATION_ARB,	WGL_FULL_ACCELERATION_ARB,
	WGL_COLOR_BITS_ARB,		32,
	WGL_ALPHA_BITS_ARB,		8,
	WGL_DEPTH_BITS_ARB,		16,
	WGL_STENCIL_BITS_ARB,	0,
	WGL_DOUBLE_BUFFER_ARB,	GL_TRUE,
	WGL_SAMPLE_BUFFERS_ARB,	GL_TRUE,
	WGL_SAMPLES_ARB,		0,
	0,0 };
	float fAttributes[] = { 0,0 };
	UINT nPixCount = 1;


	if ((mode & GLS_FORMAT) == GLS_FORMAT_PLAIN) {
		format = ChoosePixelFormat(*hDeviceContext, pfd);
	}
	else if ((mode & GLS_FORMAT) == GLS_FORMAT_ARB) {
		attributes[19] = (mode & GLS_MULTISAMPLE_BIT);
		wglChoosePixelFormatARB(*hDeviceContext, attributes, fAttributes, 1, &format, &nPixCount);
	}

	return(format);
}

PIXELFORMATDESCRIPTOR glsSetPFD() {
	PIXELFORMATDESCRIPTOR pfd;

	// Set the PFD
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	//pfd.cStencilBits= 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	return(pfd);
}

void glsStart(HWND* hWindow, HDC* hDeviceContext, HGLRC* hRenderingContext, LPCWSTR title, WNDPROC windowProcedure, RSLN windowSides, HINSTANCE hInstance, UINT mode) {
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	BOOL fullscreen = FALSE;

	// Check if device resolution was requested
	if ((mode & GLS_DEVICE_RESOLUTION) == GLS_DEVICE_RESOLUTION) {
		windowSides = getCurrentResolution();
	}

	// Check fullscreen bit
	if ((mode & GLS_FULLSCREEN_MODE) == GLS_FULLSCREEN_MODE) {
		fullscreen = TRUE;
	}

	// Init dummy window
	*hWindow = glsInitWindow(title, windowProcedure, windowSides, hInstance, fullscreen);
	*hDeviceContext = GetDC(*hWindow);

	// Get and set pixel format for dummy
	pfd = glsSetPFD();
	format = glsGetPixelFormat(hDeviceContext, GLS_FORMAT_PLAIN, &pfd);
	SetPixelFormat(*hDeviceContext, format, &pfd);

	// Create RC and make current for dummy
	*hRenderingContext = wglCreateContext(*hDeviceContext);
	wglMakeCurrent(*hDeviceContext, *hRenderingContext);

	// Init pointers
	glsInitPointers();

	// Get pixel format for window
	format = glsGetPixelFormat(hDeviceContext, GLS_FORMAT_ARB | (mode&GLS_MULTISAMPLE_BIT), &pfd);

	// Destroy dummy
	glsDisableWindow(hWindow, hDeviceContext, hRenderingContext);

	// Init window
	*hWindow = glsInitWindow(title, windowProcedure, windowSides, hInstance, fullscreen);
	*hDeviceContext = GetDC(*hWindow);
	SetPixelFormat(*hDeviceContext, format, &pfd);
	*hRenderingContext = wglCreateContext(*hDeviceContext);
	wglMakeCurrent(*hDeviceContext, *hRenderingContext);
}

void glsDisableWindow(HWND* hWindow, HDC* hDeviceContext, HGLRC* hRenderingContext) {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(*hRenderingContext);
	ReleaseDC(*hWindow, *hDeviceContext);
	DestroyWindow(*hWindow);
}

RSLN getCurrentResolution() {
	RSLN resolution;
	resolution.x = GetSystemMetrics(SM_CXSCREEN);
	resolution.y = GetSystemMetrics(SM_CYSCREEN);
	return(resolution);
}

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path, const char * geometry_file_path, UINT mode) {
	char *vs = NULL, *fs = NULL, *gs = NULL;
	GLuint ProgramID;
	GLuint VertexShaderID;
	GLuint FragmentShaderID;
	GLuint geometryShaderID;

	// Create the shaders
	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if ((mode & GLS_COMPILE_G_SHADER) == GLS_COMPILE_G_SHADER) {
		geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		gs = textFileRead(geometry_file_path);
	}

	vs = textFileRead(vertex_file_path);
	fs = textFileRead(fragment_file_path);

	// Compile V Shader
	glShaderSource(VertexShaderID, 1, &vs, NULL);
	glCompileShader(VertexShaderID);

	// Compile G Shader
	if ((mode & GLS_COMPILE_G_SHADER) == GLS_COMPILE_G_SHADER) {
		glShaderSource(geometryShaderID, 1, &gs, NULL);
		glCompileShader(geometryShaderID);
	}

	// Compile F Shader
	glShaderSource(FragmentShaderID, 1, &fs, NULL);
	glCompileShader(FragmentShaderID);

	// Link the program
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	if ((mode & GLS_COMPILE_G_SHADER) == GLS_COMPILE_G_SHADER) {
		glAttachShader(ProgramID, geometryShaderID);
	}
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	if ((mode & GLS_COMPILE_G_SHADER) == GLS_COMPILE_G_SHADER) {
		glDeleteShader(geometryShaderID);
	}
	return ProgramID;
}

char *textFileRead(const char *fn) {
	FILE *fp;
	char *content = NULL;
	int count = 0;

	if (fn != NULL) {
		fopen_s(&fp, fn, "rt");
		if (fp != NULL) {
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count + 1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

void glsSingleMat4(GLfloat matrix[4][4], DWORD action, GLfloat value) {
	int i, k;
	DWORD operation;

	// Create matrix with diagonal value
	if ((action & GLS_MAT_CREATE) == GLS_MAT_CREATE) {
		matrix[0][0] = value;
		matrix[1][0] = 0.0f;
		matrix[2][0] = 0.0f;
		matrix[3][0] = 0.0f;

		matrix[0][1] = 0.0f;
		matrix[1][1] = value;
		matrix[2][1] = 0.0f;
		matrix[3][1] = 0.0f;

		matrix[0][2] = 0.0f;
		matrix[1][2] = 0.0f;
		matrix[2][2] = value;
		matrix[3][2] = 0.0f;

		matrix[0][3] = 0.0f;
		matrix[1][3] = 0.0f;
		matrix[2][3] = 0.0f;
		matrix[3][3] = value;
	}

	if ((action & GLS_MAT_ZOOM) == GLS_MAT_ZOOM) {
		operation = GLS_MAT_X;
		for (i = 0; i < 4; i++, operation *= 2) {
			if ((action & operation) == operation) {
				glsSingleMat4Zoom(matrix, action, i, value);
			}
		}
	}

	if ((action & GLS_MAT_MOVE) == GLS_MAT_MOVE) {
		operation = GLS_MAT_X;
		for (i = 0; i < 4; i++, operation *= 2) {
			if ((action & operation) == operation) {
				glsSingleMat4Move(matrix, action, i, value);
			}
		}
	}
}

void glsSingleMat4Zoom(GLfloat matrix[4][4], DWORD action, UINT ID, GLfloat value) {
	if ((action & GLS_MAT_SET_TO) == GLS_MAT_SET_TO) {
		matrix[ID][ID] = value;
	}

	if ((action & GLS_MAT_MULTI) == GLS_MAT_MULTI) {
		matrix[ID][ID] *= value;
	}

	if ((action & GLS_MAT_ADD) == GLS_MAT_ADD) {
		matrix[ID][ID] += value;
	}
}

void glsSingleMat4Move(GLfloat matrix[4][4], DWORD action, UINT ID, GLfloat value) {
	if ((action & GLS_MAT_SET_TO) == GLS_MAT_SET_TO) {
		matrix[ID][3] = value;
	}

	if ((action & GLS_MAT_MULTI) == GLS_MAT_MULTI) {
		matrix[ID][3] *= value;
	}

	if ((action & GLS_MAT_ADD) == GLS_MAT_ADD) {
		matrix[ID][3] += value;
	}
}

void glsDoubleMat4(GLfloat targetMatrix[4][4], GLfloat sourceMatrix[4][4], DWORD action) {
	int i, k;
	GLfloat tempMatrix[4][4];
	if ((action & GLS_MAT_SET_TO) == GLS_MAT_SET_TO) {
		for (i = 0; i < 4; i++)
			for (k = 0; k < 4; k++)
				targetMatrix[k][i] = sourceMatrix[k][i];
	}

	if ((action & GLS_MAT_MULTI) == GLS_MAT_MULTI) {
		for (i = 0; i < 4; i++) {
			for (k = 0; k < 4; k++) {
				tempMatrix[k][i] = targetMatrix[0][i] * sourceMatrix[k][0] + targetMatrix[1][i] * sourceMatrix[k][1] + targetMatrix[2][i] * sourceMatrix[k][2] + targetMatrix[3][i] * sourceMatrix[k][3];
			}
		}
		glsDoubleMat4(targetMatrix, tempMatrix, GLS_MAT_SET_TO);
	}
}