#include "MainWindow.hpp"
#include "LogWindow.hpp"
#include "MainMenuBar.hpp"
#include "ConfigWindow.hpp"
#include "TableWindow.hpp"
#include "GraphemeWindow.hpp"


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void setStyleLightDefault()
{
    ImGui::StyleColorsLight();
}

void setStyleDarkDefault()
{
    ImGui::StyleColorsDark();
}

void setStyleClassicDefault()
{
    ImGui::StyleColorsClassic();
}

void setCustomStyle()
{
    setStyleLightDefault();

    ImGuiStyle * style = &ImGui::GetStyle();

    const auto pink = ImVec4(1.0f, 37.0f/255.0f, 223.0f/255.0f, 1.0f);
    const auto lightpink = ImVec4(1.0f, 140.0f/255.0f, 1.0f, 1.0f);
    const auto grey = ImVec4(0.0f, 0.0f, 0.0f, 100.0f/255.0f);
    const auto lightgrey = ImVec4(0.0f, 0.0f, 0.0f, 50.0f/255.0f);

    // style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style->Colors[ImGuiCol_FrameBgHovered] = lightgrey;
    style->Colors[ImGuiCol_FrameBgActive] = grey;
    // style->Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style->Colors[ImGuiCol_CheckMark] = lightpink;
    style->Colors[ImGuiCol_SliderGrab] = grey;
    style->Colors[ImGuiCol_SliderGrabActive] = grey;
    style->Colors[ImGuiCol_Button] = grey;
    style->Colors[ImGuiCol_ButtonHovered] = lightpink;
    style->Colors[ImGuiCol_ButtonActive] = pink;
    style->Colors[ImGuiCol_Header] = grey;
    style->Colors[ImGuiCol_HeaderHovered] = lightpink;
    style->Colors[ImGuiCol_HeaderActive] = lightpink;
    style->Colors[ImGuiCol_Separator] = grey;
    style->Colors[ImGuiCol_SeparatorHovered] = lightpink;
    style->Colors[ImGuiCol_SeparatorActive] = pink;
    style->Colors[ImGuiCol_ResizeGrip] = grey;
    style->Colors[ImGuiCol_ResizeGripHovered] = lightpink;
    style->Colors[ImGuiCol_ResizeGripActive] = pink;
    style->Colors[ImGuiCol_Tab] = lightpink;
    style->Colors[ImGuiCol_TabHovered] = pink;
    style->Colors[ImGuiCol_TabActive] = pink;
    // style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_DragDropTarget] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    // style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
}

Main_Window Main_Window::create(const std::pair<uint32_t, uint32_t> & size, const char * name, GLFWmonitor * monitor, GLFWwindow * share)
{
    Main_Window res{};
    res.setupBeforeWindow();
    res.mMainWindow = glfwCreateWindow(size.first, size.second, name, monitor, share);
    if (res.mMainWindow == nullptr)
        throw std::runtime_error{"cannot create window"};
    res.setupAfterWindow();
    return res;
}

Main_Window Main_Window::createMax(const char * name)
{
    Main_Window res{};
    res.setupBeforeWindow();
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    auto monitor = glfwGetPrimaryMonitor();
    auto vmode = glfwGetVideoMode(monitor);
    res.mMainWindow = glfwCreateWindow(vmode->width, vmode->height, name, nullptr, nullptr);
    if (res.mMainWindow == nullptr)
        throw std::runtime_error{"cannot create window"};
    glfwSetWindowMonitor(res.mMainWindow, nullptr, 0, 0, vmode->width, vmode->height, vmode->refreshRate);
    res.setupAfterWindow();
    return res;
}

ImFont & Main_Window::addFont(const char * path, float size)
{
    auto font = ImGui::GetIO().Fonts->AddFontFromFileTTF(path, size, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    if (font == nullptr)
        throw std::runtime_error{"adding font failed"};
    return *font;
}

void Main_Window::renderLoop()
{
    auto background = StbImage{"resources/background.png"};
    if (background.isEmpty())
    {
        PLOGE << "cannot load background\n";
        throw std::runtime_error{"cannot load background"};
    }
    auto backgroundTex = background.addTexture();

    auto icon = StbImage{"resources/kanji.png"};
    setAsIcon(icon);
    icon.clear();

    auto mainMenuBar = Main_MenuBar{};
    auto tableWindow = Table_Window{};
    auto graphemeWindow = Grapheme_Window{};
    auto configWindow = Config_Window{};
    configWindow.refTable(&tableWindow);
    while (!glfwWindowShouldClose(mMainWindow))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();
        mainMenuBar.draw();
        configWindow.draw("Configuration");
        tableWindow.draw("Kanji Table");
        graphemeWindow.draw("Grapheme Table");
        Log_Window::instance().draw("Logging");

        auto drawList = ImGui::GetBackgroundDrawList();
        drawList->AddImage((void*)(intptr_t)backgroundTex, {0, 0}, {static_cast<float>(background.width()), static_cast<float>(background.height())});

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(mMainWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mMainWindow);
    }
}

Main_Window::~Main_Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mMainWindow);
    glfwTerminate();
}

void Main_Window::setupBeforeWindow()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        throw std::runtime_error{"initializing glfw failed"};

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void Main_Window::setupAfterWindow()
{
    glfwMakeContextCurrent(mMainWindow);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(mMainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}
