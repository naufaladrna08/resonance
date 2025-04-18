#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>
#include <ui/icons_lucide.h>
#include <ui/components/toolbar.h>
#include <imnodes.h>
#include <audio_engine.h>

class MainWindow {
  public:
    MainWindow(GLFWwindow* window);
    ~MainWindow();
    
    void render();
    void createMenu();
    void showStartup(AudioEngine** instance);

    void NodeEditorInitialize();
    void NodeEditorShow();
    void NodeEditorShutdown();

  private:
    void init();
    void cleanUp();

    bool m_showStartup = false;
    GLFWwindow* m_window;
    std::unique_ptr<Toolbar> m_toolbar;
    std::vector<ImFont*> m_fonts;

    struct Node {
      int   id;
      float value;

      Node(const int i, const float v) : id(i), value(v) {}
    };

    struct Link {
      int id;
      int start_attr, end_attr;
    };

    struct Editor {
      ImNodesEditorContext* context = nullptr;
      std::vector<Node>     nodes;
      std::vector<Link>     links;
      int                   current_id = 0;
    };

    // Menus
    void drawTitle();
    void drawMode();
    void drawSettingsIconButton();

    // Startup
    AudioEngine* m_instance = nullptr; 
    void drawStartup();
};

#endif