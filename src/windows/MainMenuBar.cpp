#include "MainMenuBar.hpp"

#include "Platform.hpp"


void Main_MenuBar::draw()
{
    if (!ImGui::BeginMainMenuBar())
        return;

    if constexpr (isDebug())
    {
        if (ImGui::BeginMenu("Debugging"))
        {
            ImGui::MenuItem("Debug Log", nullptr, &mShowLogging);
            ImGui::MenuItem("Metrics", nullptr, &mShowMetrics);
            ImGui::MenuItem("Build Info", nullptr, &mShowBuildInfo);
            ImGui::EndMenu();
        }
    }

    if (ImGui::BeginMenu("Style"))
    {
        ImGui::MenuItem("Editor", nullptr, &mShowStyleEditor);
        ImGui::EndMenu();
    }

    if (mShowMetrics)
        ImGui::ShowMetricsWindow(&mShowMetrics);

    if (mShowBuildInfo)
        ImGui::ShowAboutWindow(&mShowBuildInfo);

    if (mShowLogging)
        ImGui::ShowDebugLogWindow(&mShowLogging);

    if (mShowStyleEditor)
    {
        ImGui::Begin("Style Editor", &mShowStyleEditor);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }

    ImGui::EndMainMenuBar();
}
