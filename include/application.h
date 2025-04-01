#ifndef APPLICATION_H
#define APPLICATION_H
#include <GLFW/glfw3.h>
#include <ui/main_window.h>
#include <audio_engine.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <callbacks/passthrough.h>

class Application {
  public:
    Application();
    ~Application();
    void run();

  private:
    GLFWwindow* m_window;
    AudioEngine* m_instance = nullptr;
    MainWindow* m_mainWindow;

    void init();
    void mainLoop();
    void cleanUp();
};

#endif