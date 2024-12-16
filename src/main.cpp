#include <GLFW/glfw3.h>
#include <Application.h>

int main(int argc, char** argv) {
  if (!glfwInit()) {
    return -1;
  }

  Application app;
  app.run();

  glfwTerminate();
  return 0;
}