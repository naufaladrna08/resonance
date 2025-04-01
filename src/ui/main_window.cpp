#include <ui/main_window.h>

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

  // Color palette
  ImVec4 background = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);  // Classic Win95 gray
  ImVec4 dark_gray = ImVec4(0.63f, 0.63f, 0.63f, 1.00f);   // Win95 dark elements
  ImVec4 medium_gray = ImVec4(0.75f, 0.75f, 0.75f, 1.00f); // Win95 button gray
  ImVec4 light_gray = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);  // Win95 light elements
  ImVec4 black = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);       // High-contrast borders
  ImVec4 highlight_blue = ImVec4(0.00f, 0.47f, 0.84f, 1.00f); // Win95 accent color

  colors[ImGuiCol_Text] = black;
  colors[ImGuiCol_TextDisabled] = medium_gray;
  colors[ImGuiCol_WindowBg] = background;
  colors[ImGuiCol_ChildBg] = background;
  colors[ImGuiCol_PopupBg] = background;
  colors[ImGuiCol_Border] = black;
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

  // Buttons
  colors[ImGuiCol_Button] = light_gray;
  colors[ImGuiCol_ButtonHovered] = medium_gray;
  colors[ImGuiCol_ButtonActive] = dark_gray;

  // Frame elements
  colors[ImGuiCol_FrameBg] = light_gray;
  colors[ImGuiCol_FrameBgHovered] = medium_gray;
  colors[ImGuiCol_FrameBgActive] = dark_gray;

  // Headers
  colors[ImGuiCol_Header] = highlight_blue;
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.35f, 0.63f, 1.00f);
  colors[ImGuiCol_HeaderActive] = dark_gray;

  // Title
  colors[ImGuiCol_TitleBg] = dark_gray;
  colors[ImGuiCol_TitleBgActive] = dark_gray;
  colors[ImGuiCol_TitleBgCollapsed] = dark_gray;

  // Scrollbars
  colors[ImGuiCol_ScrollbarBg] = light_gray;
  colors[ImGuiCol_ScrollbarGrab] = medium_gray;
  colors[ImGuiCol_ScrollbarGrabHovered] = dark_gray;
  colors[ImGuiCol_ScrollbarGrabActive] = black;

  // Sliders
  colors[ImGuiCol_SliderGrab] = medium_gray;
  colors[ImGuiCol_SliderGrabActive] = dark_gray;

  // Checkbox/mark
  colors[ImGuiCol_CheckMark] = black;

  // Tabs
  colors[ImGuiCol_Tab] = light_gray;
  colors[ImGuiCol_TabHovered] = medium_gray;
  colors[ImGuiCol_TabActive] = dark_gray;
  colors[ImGuiCol_TabUnfocused] = light_gray;
  colors[ImGuiCol_TabUnfocusedActive] = medium_gray;

  // Menubar
  colors[ImGuiCol_MenuBarBg] = light_gray;

  // Separators
  colors[ImGuiCol_Separator] = black;
  colors[ImGuiCol_SeparatorHovered] = medium_gray;
  colors[ImGuiCol_SeparatorActive] = dark_gray;

  // Resize grips
  colors[ImGuiCol_ResizeGrip] = medium_gray;
  colors[ImGuiCol_ResizeGripHovered] = dark_gray;
  colors[ImGuiCol_ResizeGripActive] = black;

  colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.42f, 1.00f);    // Dark blue background
  colors[ImGuiCol_TitleBgPattern] = ImVec4(0.00f, 0.74f, 0.83f, 0.5f); // Cyan pattern

  // Custom window shadow (neo-brutalism style)
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);


  ImGuiStyle& style = ImGui::GetStyle();
  style.WindowPadding = ImVec2(8, 8);
  style.FramePadding = ImVec2(8, 4);
  style.ItemSpacing = ImVec2(8, 4);
  style.ItemInnerSpacing = ImVec2(4, 4);
  style.TouchExtraPadding = ImVec2(0, 0);
  style.IndentSpacing = 12.0f;

  // Borders
  style.WindowBorderSize = 2.0f;
  style.ChildBorderSize = 2.0f;
  style.PopupBorderSize = 2.0f;
  style.FrameBorderSize = 2.0f;
  style.TabBorderSize = 2.0f;

  // Rounding
  style.WindowRounding = 0.0f;  // Square windows
  style.ChildRounding = 0.0f;
  style.FrameRounding = 2.0f;   // Slight neo-brutalism curve
  style.PopupRounding = 0.0f;
  style.ScrollbarRounding = 0.0f;
  style.GrabRounding = 0.0f;
  style.TabRounding = 0.0f;

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
  ImGui::SetNextWindowPos({viewport->Pos.x, viewport->Pos.y + 16});
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

  ImGui::Begin("DockSpace", nullptr, 
    ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | 
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
    ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_MenuBarGradient
  );
    createMenu();
    
    ImGui::PopStyleVar(4);

    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);
    createMenu();

    ImGui::PushFont(m_fonts[2]);
    
    if (m_showStartup) {
      drawStartup();
    } else {
      // Show the node editor
      NodeEditorShow();
    }

    ImGui::PopFont();
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
  // ImGui::PushStyleColor(ImGuiCol_MenuBarBgColor1, ImVec4(0.133f, 0.133f, 0.133f, 1.0f));
  // ImGui::PushStyleColor(ImGuiCol_MenuBarBgColor2, ImVec4(0.318f, 0.200f, 0.200f, 1.0f));

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

  ImGui::PopStyleVar(2);
  // ImGui::PopStyleColor(2);
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

void MainWindow::showStartup(AudioEngine** instance) {
  this->m_showStartup = true;
  this->m_instance = *instance;
}

void MainWindow::drawStartup() {
  ImGui::OpenPopup("Audio Engine Configuration");

  if (ImGui::BeginPopupModal("Audio Engine Configuration", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

    std::vector<std::string> bufferSizes = m_instance->queryBufferSizes();
    std::vector<std::string> sampleRates = m_instance->querySampleRates();
    static int selectedBufferSize = 0;
    static int selectedSampleRate = 0;

    ImGui::Text("Buffer Size");
    ImGui::ComboVec("##BufferSize", &selectedBufferSize, bufferSizes, bufferSizes.size());
    ImGui::Text("Sample Rate");
    ImGui::ComboVec("##SampleRate", &selectedSampleRate, sampleRates, sampleRates.size());

    if (ImGui::Button("OK")) {
      m_instance->setBufferSize(std::stoi(bufferSizes[selectedBufferSize]));
      m_instance->setSampleRate(std::stoi(sampleRates[selectedSampleRate]));
      m_instance->start();

      m_showStartup = false;
      ImGui::CloseCurrentPopup();
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel")) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
}