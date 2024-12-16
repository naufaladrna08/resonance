#ifndef APPLICATION_H
#define APPLICATION_H
#include <GLFW/glfw3.h>
#include <GUI/MainWindow.h>
#include <AudioEngine.h>
#include <iostream>
#include <memory>
#include <Callbacks/Passthrough.h>

class Application {
  public:
    Application();
    ~Application();
    void run();

  private:
    GLFWwindow* m_window;
    AudioEngine* m_instance;

    void init();
    void mainLoop();
    void cleanUp();
};

#endif