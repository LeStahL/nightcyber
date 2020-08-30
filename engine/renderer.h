#ifndef RENDERER_H
#define RENDERER_H

#ifdef WIN32
#  define WIN32_LEAN_AND_MEAN
#  define VC_EXTRALEAN
#  include <Windows.h>
#endif

#include <gl/GL.h>

#ifndef GL_GLEXT_VERSION
#  include "GL/glext.h"
#endif

static unsigned int w = 1920, h = 1080;

// OpenGL extensions
static PFNGLGETPROGRAMIVPROC glGetProgramiv;
static PFNGLGETSHADERIVPROC glGetShaderiv;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
static PFNGLCREATESHADERPROC glCreateShader;
static PFNGLCREATEPROGRAMPROC glCreateProgram;
static PFNGLSHADERSOURCEPROC glShaderSource;
static PFNGLCOMPILESHADERPROC glCompileShader;
static PFNGLATTACHSHADERPROC glAttachShader;
static PFNGLLINKPROGRAMPROC glLinkProgram;
static PFNGLUSEPROGRAMPROC glUseProgram;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
static PFNGLUNIFORM2FPROC glUniform2f;
static PFNGLUNIFORM1FPROC glUniform1f;
static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
static PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
static PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
static PFNGLNAMEDRENDERBUFFERSTORAGEPROC glNamedRenderbufferStorageEXT;
static PFNGLUNIFORM1IPROC glUniform1i;
#ifdef WIN32
static PFNGLACTIVETEXTUREPROC glActiveTexture;
#endif
// Compute
static PFNGLCREATEBUFFERSPROC glCreateBuffers;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers;
static PFNGLNAMEDBUFFERDATAPROC glNamedBufferData;
static PFNGLBINDBUFFERBASEPROC glBindBufferBase;
static PFNGLDISPATCHCOMPUTEPROC glDispatchCompute;
static PFNGLMEMORYBARRIERPROC glMemoryBarrier;
static PFNGLMAPNAMEDBUFFERPROC glMapNamedBuffer;
static PFNGLUNMAPNAMEDBUFFERPROC glUnmapNamedBuffer;

static void rInitializeRenderer()
{
#ifdef DEBUG_SHADER
  log_info("OpenGL version %s\n", glGetString(GL_VERSION));
  log_info("GLSL version   %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

  // OpenGL extensions
  glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
  glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
  glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
  glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
  glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
  glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
  glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
  glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
  glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
  glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
  glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
  glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
  glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
  glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
  glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
  glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
  glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
  glNamedRenderbufferStorageEXT = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glNamedRenderbufferStorage");
  glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
  glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
  // Compute
  glCreateBuffers = (PFNGLCREATEBUFFERSPROC)wglGetProcAddress("glCreateBuffers");
  glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
  glNamedBufferData = (PFNGLNAMEDBUFFERDATAPROC)wglGetProcAddress("glNamedBufferData");
  glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)wglGetProcAddress("glBindBufferBase");
  glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)wglGetProcAddress("glDispatchCompute");
  glMemoryBarrier = (PFNGLMEMORYBARRIERPROC)wglGetProcAddress("glMemoryBarrier");
  glMapNamedBuffer = (PFNGLMAPNAMEDBUFFERPROC)wglGetProcAddress("glMapNamedBuffer");
  glUnmapNamedBuffer = (PFNGLUNMAPNAMEDBUFFERPROC)wglGetProcAddress("glUnmapNamedBuffer");
}

int flip_buffers();

void quad()
{
  glBegin(GL_QUADS);
  glVertex3f(-1, -1, 0);
  glVertex3f(-1, 1, 0);
  glVertex3f(1, 1, 0);
  glVertex3f(1, -1, 0);
  glEnd();
  glFlush();
}

#endif // RENDERER_H
