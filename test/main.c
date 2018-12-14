#include "../gls/gls.h"

LRESULT CALLBACK WndProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	default:
		return DefWindowProc(hWindow, message, wParam, lParam);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {
	BOOL quit = FALSE;
	MSG msg;
	HWND hWnd;
	HGLRC hRC;
	HDC hDC;

	// Start OpenGl
	glsStart(&hWnd, &hDC, &hRC, TEXT("hex001"), WndProc, defaultResolution, hInstance, GLS_WINDOWED_MODE | GLS_DEVICE_RESOLUTION | 8);

	//wglSwapIntervalEXT(1);

	// Main loop
	while (!quit) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { if (msg.message == WM_QUIT) { quit = TRUE; } else { TranslateMessage(&msg); DispatchMessage(&msg); } }
		else {
			//glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			SwapBuffers(hDC);
		}
	}
	glsDisableWindow(&hWnd, &hDC, &hRC); return (int)msg.wParam;
}