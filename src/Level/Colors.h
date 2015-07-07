#ifndef COLORS_H
#define COLORS_H

#include <glm/glm.hpp>

namespace Color
{
   const glm::vec4 RED = glm::vec4(1,0,0,1);
   const glm::vec4 BLUE = glm::vec4(0,0,1,1);
   const glm::vec4 GREEN = glm::vec4(0,0.75f,0,1);
   const glm::vec4 YELLOW = glm::vec4(1,1,0,1);
   const glm::vec4 PURPLE = glm::vec4(1,0,1,1);
   const glm::vec4 WHITE = glm::vec4(1,1,1,1);
   const glm::vec4 BLACK = glm::vec4(0,0,0,1);
   const glm::vec4 ORANGE = glm::vec4(224.0f/256.0f, 115.0f/256.0f, 42.0f/256.0f,1);
   const glm::vec4 GRAY = glm::vec4(100.0f/256.0f, 100.0f/256.0f, 100.0f/256.0f,1);
   const glm::vec4 PINK = glm::vec4(224.0f/256.0f, 115.0f/256.0f, 1.0f,1);
}

#endif