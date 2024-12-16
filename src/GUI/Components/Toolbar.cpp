#include <GUI/Components/Toolbar.h>

Toolbar::Toolbar() {

}

Toolbar::~Toolbar() {

}

void Toolbar::render() {
  ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + 38));
	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, 50));
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGuiWindowFlags window_flags = 0 
		| ImGuiWindowFlags_NoTitleBar 
		| ImGuiWindowFlags_NoResize 
		| ImGuiWindowFlags_NoMove 
		| ImGuiWindowFlags_NoScrollbar;

  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.14f, 0.14f, 0.14f, 1.0f));
	ImGui::Begin("TOOLBAR", NULL, window_flags);
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 8));
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 8));
  ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(8, 8));
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

    createButton(ICON_LC_FILE, "New",  false, nullptr);
    createButton(ICON_LC_FOLDER, "Open", false, nullptr);
    createButton(ICON_LC_SAVE, "Save", false, nullptr);
    createButton(ICON_LC_SAVE, "Save As", false, nullptr);
    createButton(ICON_LC_SKIP_BACK, "Undo", false, nullptr);
    createButton(ICON_LC_SKIP_FORWARD, "Redo", false, nullptr);

  ImGui::PopStyleVar(4);
  ImGui::PopStyleColor();

  this->createTimeBar();
  
	ImGui::End();
}

void Toolbar::createButton(const char* icon, const char* label, bool showLabel, std::function<void()> callback) {
  char buffer[256];
  if (showLabel) {
    sprintf(buffer, "%s %s", icon, label);
  } else {
    sprintf(buffer, "%s", icon);
  }
  
  if (ImGui::Button(buffer)) {
    if (callback) {
      callback();
    }
  }

  ImGui::SameLine();
}

void Toolbar::createTimeBar() {
  ImGuiStyle& style = ImGui::GetStyle();

  // Save the current style
  ImVec2 originalFramePadding = style.FramePadding;

  // Modify style temporarily (optional for smaller padding)
  style.FramePadding = ImVec2(5.0f, 5.0f);

  // Colors for custom UI
  ImVec4 bgColor = ImVec4(0.1f, 0.1f, 0.15f, 1.0f); // Dark background
  ImVec4 borderColor = ImVec4(0.2f, 0.2f, 0.3f, 1.0f); // Border color
  ImVec4 accentColor = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Text color

  // Draw a rounded rectangle container
  ImVec2 containerSize(250, 60); // Width and height of container
  ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 10, ImGui::GetCursorPosY() - 10));
  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  ImVec2 p0 = ImGui::GetCursorScreenPos();
  ImVec2 p1 = ImVec2(p0.x + containerSize.x, p0.y + containerSize.y);

  ImGui::SameLine();
  draw_list->AddRectFilled(p0, p1, ImGui::GetColorU32(bgColor), 10.0f); // Rounded rectangle
  draw_list->AddRect(p0, p1, ImGui::GetColorU32(borderColor), 10.0f);   // Border

  // Start overlaying text inside the rectangle
  ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20);
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);

  // First row: Timing "3.1" with a small label
  ImGui::BeginGroup();
  ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]); // Optional: Use a bold or larger font
  ImGui::TextColored(accentColor, "3.1");
  ImGui::PopFont();
  ImGui::Text("MAX"); // Small label below
  ImGui::EndGroup();

  ImGui::SameLine(0, 50); // Add spacing between items
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);

  // Second column: Tempo "130"
  ImGui::BeginGroup();
  ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
  ImGui::TextColored(accentColor, "130");
  ImGui::PopFont();
  ImGui::Text("TEMPO");
  ImGui::EndGroup();

  ImGui::SameLine(0, 50); // Add spacing between items
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);

  // Third column: Bars "4/4" and Key "Cmaj"
  ImGui::BeginGroup();
  ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
  ImGui::TextColored(accentColor, "4/4");
  ImGui::PopFont();
  ImGui::Text("Cmaj");
  ImGui::EndGroup();

  // Restore original padding
  style.FramePadding = originalFramePadding;
}