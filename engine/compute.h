#ifndef COMPUTE_H
#define COMPUTE_H

#include "platform.h"
#include "renderer.h"

static void cResetBuffer(GLuint buffer, size_t size, GLenum usagePattern = GL_DYNAMIC_DRAW, void* data = NULL)
{
  glNamedBufferData(buffer, size, data, usagePattern);
}

static GLuint cAllocateBuffer(size_t size, GLenum usagePattern = GL_DYNAMIC_DRAW, void* data = NULL)
{
  GLuint buffer;
  glCreateBuffers(1, &buffer);
  cResetBuffer(buffer, size, usagePattern, data);
  return buffer;
}

static void cFreeBuffer(GLuint buffer) { glDeleteBuffers(1, &buffer); }

static void* cMapBuffer(GLuint buffer, GLenum readWrite = GL_READ_WRITE) { return glMapNamedBuffer(buffer, readWrite); }

static void cUnMapBuffer(GLuint buffer) { glUnmapNamedBuffer(buffer); }

static void cCopyFromBuffer(GLuint buffer, void* dest, size_t length)
{
  void* src = cMapBuffer(buffer, GL_READ_ONLY);
  memcpy(dest, src, length);
  cUnMapBuffer(buffer);
}

static void cBindBuffer(GLuint index, GLuint buffer) { glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, buffer); }

static void cDispatchCompute(GLuint shaderHandle, GLuint gridX, GLuint gridY = 1, GLuint gridZ = 1)
{
  glUseProgram(shaderHandle);
  glDispatchCompute(gridX, gridY, gridZ);
}

static void cMemoryBarrier() { glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT); }

#endif