#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
  void draw();
  void forward(float amount);

private:
  glm::mat4 m_view;
  glm::mat4 m_proj;
};
