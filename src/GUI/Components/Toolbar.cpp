#include <GUI/Components/Toolbar.h>

Toolbar::Toolbar() {

}

Toolbar::~Toolbar() {

}

void Toolbar::render() {

  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
  this->createProjectMenu();
  this->createPlaybackMenu();
  this->createTimeBar();
  ImGui::PopStyleVar();
}


void Toolbar::createProjectMenu() {
  static bool projectMenuOpened = true;
  if (ImGui::Begin("Project Menu", &projectMenuOpened, m_windowFlags)) {
    createButton(ICON_LC_FILE, "New",  false, "Create new audio project", nullptr);
    createButton(ICON_LC_FOLDER, "Open", false, "Open existing Resonance project", nullptr);
    createButton(ICON_LC_SAVE, "Save", false, "Save project", nullptr);
    createButton(ICON_LC_SAVE, "Save As", false, "Save project as", nullptr);

    ImGui::NewLine();

    createButton(ICON_LC_UNDO, "Undo",  false, "Undo last action", nullptr);
    createButton(ICON_LC_REDO, "Redo", false, "Redo", nullptr);
    createButton(ICON_LC_COPY, "Copy", false, "Copy selection", nullptr);
    createButton(ICON_LC_SCISSORS, "Cut", false, "Cut selection", nullptr);
    createButton(ICON_LC_SKIP_BACK, "Undo", false, nullptr);
    createButton(ICON_LC_SKIP_FORWARD, "Redo", false, nullptr);

    ImGui::End();
  }
}

void Toolbar::createPlaybackMenu() {
  static bool playbackMenuOpened = true;
  if (ImGui::Begin("Playback Menu", &playbackMenuOpened, m_windowFlags)) {
    createButton(ICON_LC_SKIP_BACK, "Skip back", false, "Skip back", nullptr, ImVec2(72, 72));
    createButton(ICON_LC_SKIP_FORWARD, "Skip forward", false, "Skip forward", nullptr, ImVec2(72, 72)); 
    createButton(ICON_LC_PLAY, "Play", false, "Play/pause track", nullptr, ImVec2(72, 72));
    createButton(ICON_LC_CIRCLE, "Play", false, "Toggle record", nullptr, ImVec2(72, 72), ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
  
    ImGui::End();
  }
}

void Toolbar::createTimeBar() {
  ImGuiStyle& style = ImGui::GetStyle();

  static int currentTempo = 130;
  static bool isDraggingTempo = false;
  static bool isTempoEditing = false;

  ImVec2 cursorStartPos = ImGui::GetCursorPos();

  static bool timebarOpened = true;
  
  if (ImGui::Begin("Time bar", &timebarOpened, m_windowFlags)) {
    // Colors for custom UI
    ImVec4 bgColor = ImVec4(0.1f, 0.1f, 0.15f, 1.0f); // Dark background
    ImVec4 borderColor = ImVec4(0.2f, 0.2f, 0.3f, 1.0f); // Border color
    ImVec4 accentColor = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Text color

    // Draw a rounded rectangle container
    ImVec2 containerSize(250, 72); // Width and height of container
    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 10, ImGui::GetCursorPosY()));
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 p0 = ImGui::GetCursorScreenPos();
    ImVec2 p1 = ImVec2(p0.x + containerSize.x, p0.y + containerSize.y);

    ImGui::SameLine();
    draw_list->AddRectFilled(p0, p1, ImGui::GetColorU32(bgColor), 10.0f); // Rounded rectangle
    draw_list->AddRect(p0, p1, ImGui::GetColorU32(borderColor), 10.0f);   // Border

    // Start overlaying text inside the rectangle
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 16);

    // First row: Timing "3.1" with a small label
    ImGui::BeginGroup();
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]); // Optional: Use a bold or larger font
    ImGui::TextColored(accentColor, "3.1");
    ImGui::PopFont();
    ImGui::Text("MAX"); // Small label below
    ImGui::EndGroup();

    ImGui::SameLine(0, 50); // Add spacing between items
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 16);

    // Second column: Tempo "130"
    ImGui::BeginGroup();
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    if (!isTempoEditing) {
      ImGui::TextColored(accentColor, "%d", currentTempo);
    } else {
      ImGui::PushItemWidth(48);
      ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 16);
      ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
      if (ImGui::InputInt("##Tempo", &currentTempo, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue)) {
        isTempoEditing = false;
      }
      ImGui::PopStyleVar();
      ImGui::PopItemWidth();
    }
    ImGui::PopFont();
    ImGui::Text("TEMPO");
    ImGui::EndGroup();

    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip("Drag to change tempo");
      if (isTempoEditing) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);
      } else {
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
      }

      if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        isDraggingTempo = true;
      }
    }

    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
      isTempoEditing = true;
    }

    if (isDraggingTempo) {
      currentTempo -= (int)ImGui::GetIO().MouseDelta.y;

      // Optional: Clamp the tempo to a specific range
      currentTempo = (currentTempo < 20) ? 20 : (currentTempo > 300 ? 300 : currentTempo);

      // Stop dragging when mouse button is released
      if (!ImGui::IsMouseDown(0))  {
        isDraggingTempo = false; // Reset dragging flag
      }
    }

    ImGui::SameLine(0, 50); // Add spacing between items
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 16);

    // Third column: Bars "4/4" and Key "Cmaj"
    ImGui::BeginGroup();
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    ImGui::TextColored(accentColor, "4/4");
    ImGui::PopFont();
    ImGui::Text("Cmaj");
    ImGui::EndGroup();

    // Restore original padding
    
    ImGui::End();
  }

}

void Toolbar::createButton(const char* icon, const char* label, bool showLabel, const char* hoverText, std::function<void()> callback, ImVec2 customSize, ImVec4 customColor) {
  char buffer[256];
  if (showLabel) {
    sprintf(buffer, "%s %s", icon, label);
  } else {
    sprintf(buffer, "%s", icon);
  }

  if (ImGui::Button(buffer, customSize)) {
    if (callback) {
      callback();
    }
  }

  if (ImGui::IsItemHovered()) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    if (hoverText != nullptr) ImGui::SetTooltip("%s", hoverText);
  }

  ImGui::SameLine();
}
