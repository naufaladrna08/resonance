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
    void createButton(const char* icon, const char* label, bool showLabel = true, std::function<void()> callback = nullptr);
    void createTimeBar();
};

#endif