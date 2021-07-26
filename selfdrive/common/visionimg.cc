#include "selfdrive/common/visionimg.h"

#include <cassert>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2ext.h>

#ifdef QCOM
#include <gralloc_priv.h>
#include <system/graphics.h>
#include <ui/GraphicBuffer.h>
#include <ui/PixelFormat.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2ext.h>
using namespace android;

EGLImageTexture::EGLImageTexture(const VisionBuf *buf) {
  const int bpp = 3;
  assert((buf->len % buf->stride) == 0);
  assert((buf->stride % bpp) == 0);

  const int format = HAL_PIXEL_FORMAT_RGB_888;
  private_handle = new private_handle_t(buf->fd, buf->len,
                             private_handle_t::PRIV_FLAGS_USES_ION|private_handle_t::PRIV_FLAGS_FRAMEBUFFER,
                             0, format,
                             buf->stride/bpp, buf->len/buf->stride,
                             buf->width, buf->height);

  // GraphicBuffer is ref counted by EGLClientBuffer(ANativeWindowBuffer), no need and not possible to release.
  GraphicBuffer* gb = new GraphicBuffer(buf->width, buf->height, (PixelFormat)format,
                                        GraphicBuffer::USAGE_HW_TEXTURE, buf->stride/bpp, (private_handle_t*)private_handle, false);

  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  assert(display != EGL_NO_DISPLAY);

  EGLint img_attrs[] = {EGL_IMAGE_PRESERVED_KHR, EGL_TRUE, EGL_NONE};
  img_khr = eglCreateImageKHR(display, EGL_NO_CONTEXT,
                              EGL_NATIVE_BUFFER_ANDROID, gb->getNativeBuffer(), img_attrs);
  assert(img_khr != EGL_NO_IMAGE_KHR);

  glGenTextures(1, &frame_tex);
  glBindTexture(GL_TEXTURE_2D, frame_tex);
  glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, img_khr);
}

EGLImageTexture::~EGLImageTexture() {
  glDeleteTextures(1, &frame_tex);
  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  assert(display != EGL_NO_DISPLAY);
  eglDestroyImageKHR(display, img_khr);
  delete (private_handle_t*)private_handle;
}

#else // ifdef QCOM

EGLImageTexture::EGLImageTexture(const VisionBuf *buf) {
  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  assert(display != EGL_NO_DISPLAY);

  eglInitialize(display, NULL, NULL);
  std::cout << "egl error: " << eglGetError() << std::endl;

	EGLint img_attrs[] = {
		EGL_WIDTH, buf->width,
		EGL_HEIGHT, buf->height,
		EGL_LINUX_DRM_FOURCC_EXT, DRM_FORMAT_RGB888,
		EGL_DMA_BUF_PLANE0_FD_EXT, buf->fd,
		EGL_DMA_BUF_PLANE0_OFFSET_EXT, 0,
		EGL_DMA_BUF_PLANE0_PITCH_EXT, buf->width * 3,
		EGL_NONE
	};

	EGLImageKHR img_khr = eglCreateImageKHR(display, EGL_NO_CONTEXT, EGL_LINUX_DMA_BUF_EXT, 0, img_attrs);

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "OpenGL error: " << err << std::endl;
  }
  std::cout << "egl error: " << eglGetError() << std::endl;
  assert(img_khr != EGL_NO_IMAGE_KHR);

  glGenTextures(1, &frame_tex);
  glBindTexture(GL_TEXTURE_2D, frame_tex);
  glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, img_khr);
}

EGLImageTexture::~EGLImageTexture() {
  glDeleteTextures(1, &frame_tex);
  EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  assert(display != EGL_NO_DISPLAY);
  eglDestroyImageKHR(display, img_khr);
}

#endif // ifdef QCOM
