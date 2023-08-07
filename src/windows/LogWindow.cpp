#include "LogWindow.hpp"


void imkanji::window::Log::clear()
{
  mBuf.clear();
  mLines.clear();
}

void imkanji::window::Log::draw(const char * title, bool * p_open)
{
  if (!ImGui::Begin(title, p_open))
  {
    ImGui::End();
    return;
  }

  ImGui::Checkbox("Auto-scroll", &mAutoScroll);
  bool toBeCleared = ImGui::Button("Clear");
  ImGui::SameLine();
  bool toBeCopied = ImGui::Button("Copy");

  ImGui::Separator();

  if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar))
  {
    if (toBeCleared)
      clear();
    if (toBeCopied)
      ImGui::LogToClipboard();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

    ImGuiListClipper clipper{};
    clipper.Begin(mLines.size());
    while (clipper.Step())
    {
      for (uint32_t lineNum = clipper.DisplayStart; lineNum < static_cast<uint32_t>(clipper.DisplayEnd); ++lineNum)
      {
        const auto & line = mLines.at(lineNum);
        ImGui::TextUnformatted(line.data(), line.data() + line.length());
      }
    }
    clipper.End();

    ImGui::PopStyleVar();

    if (mAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
      ImGui::SetScrollHereY(1.0f);
  }
  ImGui::EndChild();
  ImGui::End();
}
