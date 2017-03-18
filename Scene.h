#pragma once

#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Scene
{
public:
  using Dt = std::chrono::duration<float, std::milli>;

  ~Scene();

  void load();
  void unload();
  void update(Dt dt);
  void draw();

private:
};
