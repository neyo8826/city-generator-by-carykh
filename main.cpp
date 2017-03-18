#include <iostream>
#include "Window.h"

[[noreturn]] static void glfwErrorCallback(int /*error*/, char const *description)
{
  throw std::runtime_error(std::string("GLFW error: ") + description);
}

int main()
{
  glfwSetErrorCallback(&glfwErrorCallback);
  if(!glfwInit())
    return EXIT_FAILURE;

  {
    Window window;
    window.loop();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}
