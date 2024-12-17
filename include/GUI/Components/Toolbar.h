#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <imgui.h>
#include <GUI/IconsLucide.h>
#include <stdio.h>
#include <functional>

class Toolbar {
  public:
    Toolbar();
    ~Toolbar();

    void render();

  private:
    const ImGuiWindowFlags m_windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
    
    // Parts
    void createProjectMenu();
    void createPlaybackMenu();
    void createTimeBar();
    
    // Helpers
    void createButton(
      const char* icon, 
      const char* label, 
      bool showLabel = true, 
      const char* hoverText = nullptr, 
      std::function<void()> callback = nullptr,
      ImVec2 customSize = ImVec2(0, 0),
      ImVec4 customColor = ImVec4(0, 0, 0, 0)
    );
};

#endif