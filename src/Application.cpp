#include <Application.h>

Application::Application() {
  this->init();
}

Application::~Application() {
  this->cleanUp();
}

void Application::init() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(1280, 720, "MyDAW", NULL, NULL);
  if (m_window == NULL) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(m_window);
  glfwSwapInterval(1);
  glfwMaximizeWindow(m_window);

  /* Setup Audio Engine */
  // m_instance = new AudioEngine();
  // m_instance->start();

  /* Setup Audio Callback */
  // Passthrough* passthrough = new Passthrough();
  // m_instance->processCallback(passthrough);
}

void Application::mainLoop() {
  MainWindow mainWindow(m_window);
  while (!glfwWindowShouldClose(m_window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    mainWindow.render();

    glfwSwapBuffers(m_window);
    glfwPollEvents();
  }
}

void Application::cleanUp() {
  // m_instance->stop();
  // delete m_instance;
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

void Application::run() {
  mainLoop();
}

