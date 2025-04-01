#include <application.h>

Application::Application() {
  this->init();
}

Application::~Application() {
  this->cleanUp();
}

void Application::init() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(1280, 720, "MyDAW", NULL, NULL);
  if (m_window == NULL) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(m_window);
  glfwSwapInterval(1);
  glfwMaximizeWindow(m_window);

  /* Setup Main Window */
  m_mainWindow = new MainWindow(m_window);

  /* If the audio engine is hasn't been setup, then we need to open
   * the startup modal and let the user decide audio configuration */
  if (m_instance == nullptr) {
    m_instance = new AudioEngine();
    m_mainWindow->showStartup(&m_instance);
  }
}

void Application::mainLoop() {
  while (!glfwWindowShouldClose(m_window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    m_mainWindow->render();

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

