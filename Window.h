#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "lang.h"
#include "Camera.h"
#include "Scene.h"

class Window
{
  DISABLE_COPY_SEMANTICS(Window)
public:
  Window();
  ~Window();
  void loop();

private:
  void ensureContext();
  void onKey(int key, int scancode, int action, int mods);

private:
  GLFWwindow *m_window;
  Camera m_camera;
  Scene m_scene;
};
