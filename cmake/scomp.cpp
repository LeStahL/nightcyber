
// /* cozy - 4k executable gfx entry by NR4/Team210, shown at Under Construction 2k19
//  * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>
//  *
//  * This program is free software: you can redistribute it and/or modify
//  * it under the terms of the GNU General Public License as published by
//  * the Free Software Foundation, either version 3 of the License, or
//  * (at your option) any later version.
//  *
//  * This program is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  * GNU General Public License for more details.
//  *
//  * You should have received a copy of the GNU General Public License
//  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  */

// #include <stdio.h>
// #include <stdlib.h>

// int WINAPI demo(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
// {
//     // char **cmdargs = GetCommandLine();
//     // printf("%d %s\n", nCmdShow, pCmdLine[0]);
//     // printf("Here.\n");
//     // int argc;
//     // LPWSTR *args = CommandLineToArgvW(pCmdLine, &argc);
//     // printf("%s\n", args[0]);
//     // Display demo window
// CHAR WindowClass[] = "T";

// WNDCLASSEX wc = {0};
// wc.cbSize = sizeof(wc);
// wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
// wc.lpfnWndProc = &DefWindowProc;
// wc.cbClsExtra = 0;
// wc.cbWndExtra = 0;
// wc.hInstance = hInstance;
// wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
// wc.hCursor = LoadCursor(NULL, IDC_ARROW);
// wc.hbrBackground = NULL;
// wc.lpszMenuName = NULL;
// wc.lpszClassName = WindowClass;
// wc.hIconSm = NULL;

// RegisterClassEx(&wc);

// HWND hwnd = CreateWindowEx(0, WindowClass, "", WS_POPUP | WS_VISIBLE, 0, 0, 1920, 1080, NULL, NULL, hInstance, 0);

// DEVMODE dm = {0};
// dm.dmSize = sizeof(dm);
// dm.dmPelsWidth = 1920;
// dm.dmPelsHeight = 1080;
// dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

// ShowWindow(hwnd, FALSE);
// UpdateWindow(hwnd);

// PIXELFORMATDESCRIPTOR pfd =
//     {
//         sizeof(PIXELFORMATDESCRIPTOR),
//         1,
//         PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
// PFD_TYPE_RGBA,                                              // The kind of framebuffer. RGBA or palette.
// 32,                                                         // Colordepth of the framebuffer.
//         0, 0, 0, 0, 0, 0,
//         0,
//         0,
//         0,
//         0, 0, 0, 0,
//         24, // Number of bits for the depthbuffer
//         8,  // Number of bits for the stencilbuffer
//         0,  // Number of Aux buffers in the framebuffer.
//         PFD_MAIN_PLANE,
//         0,
//         0, 0, 0};

// HDC hdc = GetDC(hwnd);

// int pf = ChoosePixelFormat(hdc, &pfd);
// SetPixelFormat(hdc, pf, &pfd);

// HGLRC glrc = wglCreateContext(hdc);
// wglMakeCurrent(hdc, glrc);

// glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
// glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
// glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
// glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
// glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");

//     PostQuitMessage(0);

//     return 0;
// }

#include <windows.h>
#include <stdio.h>
#include <shellapi.h>

#include "GL/GL.h"
#include "glext.h"

PFNGLCREATESHADERPROC glCreateShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

int __cdecl main()
{
    LPWSTR *szArglist;
    int nArgs;
    int i;

    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    {
        if (i <= 1)
        {
            printf("==== Error: No command line arguments provided to scomp.exe. Check your call. ====\n");
            ExitProcess(-1);
            return -1;
        }
    }

    HWND hwndC = GetConsoleWindow();
    HINSTANCE hInstance = GetModuleHandle(0);

    CHAR WindowClass[] = "T";

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = &DefWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WindowClass;
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(0, WindowClass, "Team210 shader compiler executable", WS_POPUP | WS_VISIBLE, 0, 0, 1920, 1080, NULL, NULL, hInstance, 0);

    DEVMODE dm = {0};
    dm.dmSize = sizeof(dm);
    dm.dmPelsWidth = 1920;
    dm.dmPelsHeight = 1080;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    ShowWindow(hwnd, TRUE);
    UpdateWindow(hwnd);

    PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
PFD_TYPE_RGBA,                                              // The kind of framebuffer. RGBA or palette.
32,                                                         // Colordepth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24, // Number of bits for the depthbuffer
            8,  // Number of bits for the stencilbuffer
            0,  // Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0, 0, 0};

    HDC hdc = GetDC(hwnd);

    int pf = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pf, &pfd);

    HGLRC glrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, glrc);

    glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
    char buffer[1024];
    sprintf(buffer, "%ws", szArglist[1]);
    FILE *f = fopen(buffer, "rt");
    if (!f)
    {
        printf("==== Error: Could not open file: %ws ====\n", buffer);
        PostQuitMessage(0);
        ExitProcess(-1);
        return -1;
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *shaderSource = (char *)malloc((size + 1) * sizeof(char));
    fread(shaderSource, 1, size, f);
    fclose(f);

    int handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(handle, 1, (const GLchar **)&shaderSource, &size);
    glCompileShader(handle);

    GLint compileStatus;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE)
    {
        printf("==== Error in %s: ====\n\n", buffer);
        GLint errorLogLength;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &errorLogLength);
        GLchar *compilerError = (GLchar*)malloc(errorLogLength*sizeof(GLchar));
        glGetShaderInfoLog(handle, errorLogLength, NULL, compilerError);
        printf("%s\n", compilerError);
        return -1;
        ExitProcess(-1);
    }
    printf("Successfully compiled Shader: %s\n", buffer);

    ExitProcess(0);
    return 0;
}

