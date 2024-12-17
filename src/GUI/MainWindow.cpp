#include <GUI/MainWindow.h>

MainWindow::MainWindow(GLFWwindow* window)
  : m_window(window) {
  init();
}

MainWindow::~MainWindow() {
  cleanUp();
}

void MainWindow::init() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  this->NodeEditorInitialize();
  ImGui_ImplGlfw_InitForOpenGL(m_window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  ImGui::StyleColorsLight();

  // ImGui Flags
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImVec4* colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
  colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_DockingPreview]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_DockingEmptyBg]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

  ImGuiStyle& style = ImGui::GetStyle();
  style.WindowPadding                     = ImVec2(8.00f, 8.00f);
  style.FramePadding                      = ImVec2(4.00f, 8.00f);
  style.CellPadding                       = ImVec2(6.00f, 6.00f);
  style.ItemSpacing                       = ImVec2(6.00f, 6.00f);
  style.ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
  style.TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
  style.IndentSpacing                     = 25;
  style.ScrollbarSize                     = 15;
  style.GrabMinSize                       = 10;
  style.WindowBorderSize                  = 1;
  style.ChildBorderSize                   = 1;
  style.PopupBorderSize                   = 1;
  style.FrameBorderSize                   = 1;
  style.TabBorderSize                     = 1;
  style.WindowRounding                    = 7;
  style.ChildRounding                     = 4;
  style.FrameRounding                     = 3;
  style.PopupRounding                     = 4;
  style.ScrollbarRounding                 = 9;
  style.GrabRounding                      = 3;
  style.LogSliderDeadzone                 = 4;
  style.TabRounding                       = 4;

  // Font
  ImFont* font_basicNormal = io.Fonts->AddFontFromFileTTF("resources/fonts/Lato-Bold.ttf", 16.0f);
  ImFont* font_basiBold = io.Fonts->AddFontFromFileTTF("resources/fonts/Lato-Black.ttf", 16.0f);

  // merge in icons from Font Awesome
  static const ImWchar icons_ranges[] = { ICON_MIN_LC, ICON_MAX_LC, 0 };
  ImFontConfig icons_config; 
  icons_config.MergeMode = true; 
  icons_config.PixelSnapH = true;
  icons_config.GlyphMinAdvanceX = 13;
  ImFont* font_icon = io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_LC, 16.0f, &icons_config, icons_ranges);

  // Create toolbar
  m_toolbar = std::make_unique<Toolbar>();

  // Set the font
  io.FontDefault = font_basicNormal;
  m_fonts.push_back(font_basicNormal);
  m_fonts.push_back(font_basiBold);
  m_fonts.push_back(font_icon);
}

void MainWindow::cleanUp() {
  this->NodeEditorShutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void MainWindow::render() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos({viewport->Pos.x, viewport->Pos.y + 24});
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

  ImGuiWindowFlags dockspaceFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
  dockspaceFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  dockspaceFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  ImGui::Begin("DockSpace", nullptr, dockspaceFlags);
    ImGui::PopStyleVar(4);

    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);
    createMenu();

    ImGui::PushFont(m_fonts[2]);
    m_toolbar->render();
    ImGui::PopFont();

    this->NodeEditorShow();
    ImGui::ShowDemoWindow();
  
  ImGui::End();    

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainWindow::NodeEditorInitialize() {
  ImNodes::CreateContext();
  ImNodes::SetNodeGridSpacePos(1, ImVec2(200.0f, 200.0f));
}

void MainWindow::NodeEditorShow() {
  ImGui::Begin("Guitar Effects");
    ImNodes::BeginNodeEditor();

      ImNodes::BeginNode(0);
        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("Guitar Input");
        ImNodes::EndNodeTitleBar();

        ImNodes::BeginOutputAttribute(2);
        ImGui::Indent(40);
        ImGui::Text("Output");
        ImNodes::EndOutputAttribute();
      ImNodes::EndNode();

      ImNodes::BeginNode(1);
        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted("Chorus");
        ImNodes::EndNodeTitleBar();


        ImNodes::BeginInputAttribute(2);
        ImGui::Text("input");
        ImNodes::EndInputAttribute();

        ImNodes::BeginOutputAttribute(3);
        ImGui::Indent(40);
        ImGui::Text("output");
        ImNodes::EndOutputAttribute();

      ImNodes::EndNode();
    ImNodes::EndNodeEditor();
  ImGui::End();
}

void MainWindow::NodeEditorShutdown() {
  ImNodes::DestroyContext();
}

void MainWindow::createMenu() {
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 12));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
  ImGui::PushStyleColor(ImGuiCol_MenuBarBgColor1, ImVec4(0.133f, 0.133f, 0.133f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_MenuBarBgColor2, ImVec4(0.318f, 0.200f, 0.200f, 1.0f));

  // Begin the menu bar
  if (ImGui::BeginMainMenuBar(true)) {
    drawTitle();

    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Open", "Ctrl + O")) { /* Handle open */ }
      if (ImGui::MenuItem("Save", "Ctrl + S")) { /* Handle save */ }
      if (ImGui::MenuItem("Save as", "Ctrl + Shift + S")) { /* Handle save */ }
      if (ImGui::MenuItem("Open Workspace from File", "Ctrl + Shift + S")) { /* Handle save */ }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo")) { /* Handle undo */ }
      if (ImGui::MenuItem("Redo")) { /* Handle redo */ }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View")) {
      if (ImGui::MenuItem("Show Toolbar")) { /* Handle show toolbar */ }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Tracks")) {
      if (ImGui::MenuItem("Add Track")) { /* Handle add track */ }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Plugins")) {
      if (ImGui::MenuItem("Add Plugin")) { /* Handle add plugin */ }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window")) {
      if (ImGui::MenuItem("Show Node Editor")) { /* Handle show node editor */ }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Help")) {
      if (ImGui::MenuItem("About")) { /* Handle about */ }
      ImGui::EndMenu();
    }

    // Space between
    drawMode();
    drawSettingsIconButton();

    // End the menu bar
    ImGui::EndMainMenuBar();
  }

  ImGui::PopStyleColor(2);
  ImGui::PopStyleVar(2);
}

void MainWindow::drawTitle() {
  ImGui::Spacing();
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
  ImGui::PushFont(m_fonts[2]);
  ImGui::Text(ICON_LC_MUSIC);
  ImGui::PopFont();
  ImGui::Spacing();

  ImGui::SetCursorPosY(ImGui::GetCursorPosY());
  ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
  ImGui::Text("Resonance");
  ImGui::PopFont();
  ImGui::Spacing();
}

void MainWindow::drawMode() {
  ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
  ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("NORMAL MODE").x - 38);
  ImGui::Text("NORMAL MODE");
  ImGui::PopFont();

  if (ImGui::IsItemHovered()) {
    ImGui::SetTooltip("When in normal mode, you can use this like a normal DAW.");
  }
}

void MainWindow::drawSettingsIconButton() {
  ImGui::SameLine(ImGui::GetWindowWidth() - 32);

  ImGui::PushFont(m_fonts[2]);
  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 16));
  ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
  
  if (ImGui::Button(ICON_LC_COG)) {
    // Handle settings
  }

  if (ImGui::IsItemHovered()) {
    ImGui::SetTooltip("Settings");
    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
  }

  ImGui::PopFont();
  ImGui::PopStyleColor(3);
  ImGui::PopStyleVar(2);
}
