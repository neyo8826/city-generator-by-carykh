#include <chrono>
#include <iostream>
#include <iomanip>
#include "Window.h"

Window::Window()
{
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(1280, 1024, "City generator by Carykh", nullptr, nullptr);
  glfwSetWindowUserPointer(m_window, this);
  glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods){
    static_cast<Window*>(glfwGetWindowUserPointer(window))->onKey(key, scancode, action, mods);
  });

  ensureContext();
  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK)
    throw std::runtime_error("Failed to initialize GLEW");

  glfwSwapInterval(0);

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  m_scene.load();
}

Window::~Window()
{
  ensureContext();
  glfwDestroyWindow(m_window);
}

void Window::loop()
{
  ensureContext();
  auto lastTime = std::chrono::steady_clock::now();

  uint64_t fps_frameCounter = 0;
  auto fps_lastTime = lastTime;

  while(!glfwWindowShouldClose(m_window))
  {
    auto const currentTime = std::chrono::steady_clock::now();
    auto const dt = currentTime - lastTime;

    glfwPollEvents();
    m_scene.update(dt);

    glClear(GL_DEPTH_BUFFER_BIT);
    m_camera.draw();
    m_scene.draw();
    glfwSwapBuffers(m_window);
    lastTime = currentTime;

    {
      using namespace std::chrono;
      ++fps_frameCounter;
      auto const fps_dt = currentTime - fps_lastTime;
      if(fps_dt >= seconds(2))
      {
        auto const ms = duration_cast<duration<double, std::milli>>(fps_dt) / fps_frameCounter;
        std::cout << std::fixed << std::setw(8) << std::setprecision(4) << ms.count() << "ms " << std::setw(6) << std::setprecision(0) << 1000.0 / ms.count() << "fps" << std::endl;
        fps_lastTime = currentTime;
        fps_frameCounter = 0;
      }
    }
  }
}

void Window::ensureContext()
{
  if(glfwGetCurrentContext() != m_window)
    glfwMakeContextCurrent(m_window);
}

void Window::onKey(int const key, int const scancode, int const action, int const mods)
{
  if(action == GLFW_PRESS)
    switch(key)
    {
    case GLFW_KEY_ESCAPE:
    case GLFW_KEY_Q:
      glfwSetWindowShouldClose(m_window, GL_TRUE);
      break;
    }
}
