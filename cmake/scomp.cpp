
/* scomp - compile a shader and see if it will work in the demo.
 * Copyright (C) 2019  Alexander Kraus <nr4@z10.info>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifdef WIN32
#  define _CRT_SECURE_NO_WARNINGS
#  define WIN32_LEAN_AND_MEAN
#  define VC_EXTRALEAN
#  include <Windows.h>
#  include <shellapi.h>
#endif

#include <stdio.h>
#include <string>

#include <GL/GL.h>

#ifdef WIN32
#  include "GL/wgl.h"
#  include "GL/wglext.h"
#endif

#include "GL/glext.h"

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLDELETESHADERPROC glDeleteShader;

int __cdecl main()
{
  LPWSTR* szArglist;
  int nArgs;

  szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
  {
    if (nArgs <= 1) {
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

  HWND hwnd = CreateWindowEx(
      0, WindowClass, "Team210 shader compiler executable", WS_POPUP | WS_VISIBLE, 0, 0, 1920, 1080, NULL, NULL, hInstance, 0);

  DEVMODE dm = {0};
  dm.dmSize = sizeof(dm);
  dm.dmPelsWidth = 1920;
  dm.dmPelsHeight = 1080;
  dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

  ShowWindow(hwnd, FALSE);
  UpdateWindow(hwnd);

  PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR),
                               1,
                               PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
                               PFD_TYPE_RGBA,                                              // The kind of framebuffer. RGBA or palette.
                               32,                                                         // Colordepth of the framebuffer.
                               0,
                               0,
                               0,
                               0,
                               0,
                               0,
                               0,
                               0,
                               0,
                               0,
                               0,
                               0,
                               0,
                               24, // Number of bits for the depthbuffer
                               8,  // Number of bits for the stencilbuffer
                               0,  // Number of Aux buffers in the framebuffer.
                               PFD_MAIN_PLANE,
                               0,
                               0,
                               0,
                               0};

  HDC hdc = GetDC(hwnd);

  int pf = ChoosePixelFormat(hdc, &pfd);
  SetPixelFormat(hdc, pf, &pfd);

  HGLRC glrc = wglCreateContext(hdc);
  wglMakeCurrent(hdc, glrc);

  wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
  glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
  glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
  glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
  glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
  glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
  glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");

  GLint attribs[] = {WGL_CONTEXT_MAJOR_VERSION_ARB,
                     4,
                     WGL_CONTEXT_MINOR_VERSION_ARB,
                     3,
                     WGL_CONTEXT_PROFILE_MASK_ARB,
                     WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                     0};

  glrc = wglCreateContextAttribsARB(hdc, 0, attribs);
  wglMakeCurrent(hdc, glrc);

  char buffer[2048];

  const std::string STRING_FRAG = ".frag";
  for (int i = 1; i < nArgs; ++i) {
    sprintf(buffer, "%ws\0", szArglist[i]);
    const std::string filename = buffer;
    printf("Processing file: %s\n", buffer);
    bool isFragmentShader = filename.compare(filename.size() - STRING_FRAG.size(), STRING_FRAG.size(), STRING_FRAG) == 0;
    FILE* f = fopen(buffer, "rb");
    if (!f) {
      printf("==== Error: Could not open file: %s ====\n", buffer);
      ExitProcess(-1);
      return -1;
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* shaderSource = (char*)malloc((size + 1) * sizeof(char));
    fread(shaderSource, 1, size, f);
    shaderSource[size] = 0;
    ++size;
    fclose(f);

    int handle = glCreateShader(isFragmentShader ? GL_FRAGMENT_SHADER : GL_COMPUTE_SHADER);
    glShaderSource(handle, 1, (const GLchar**)&shaderSource, &size);
    glCompileShader(handle);

    GLint compileStatus;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
      printf("==== Error in %s: ====\n\n", buffer);
      GLint errorLogLength;
      glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &errorLogLength);
      GLchar* compilerError = (GLchar*)malloc(errorLogLength * sizeof(GLchar));
      glGetShaderInfoLog(handle, errorLogLength, NULL, compilerError);
      printf("%s\n", compilerError);
      free(shaderSource);
      ExitProcess(-1);
      return -1;
    }
    printf("Successfully compiled Shader: %s\n", buffer);
    glDeleteShader(handle);
    free(shaderSource);
  }

  ExitProcess(0);
  return 0;
}
