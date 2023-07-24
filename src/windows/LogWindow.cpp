#include "LogWindow.hpp"


void Log_Window::clear()
{
    mBuf.clear();
    mLineOffsets.clear();
    mLineOffsets.push_back(0);
}

void Log_Window::addLog(const char* fmt, ...)
{
    int old_size = mBuf.size();
    va_list args;
    va_start(args, fmt);
    mBuf.appendfv(fmt, args);
    va_end(args);
    for (int new_size = mBuf.size(); old_size < new_size; old_size++)
        if (mBuf[old_size] == '\n')
            mLineOffsets.push_back(old_size + 1);
}

void Log_Window::draw(const char* title, bool* p_open)
{
    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &mAutoScroll);
        ImGui::EndPopup();
    }

    if (ImGui::Button("Options"))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
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
        const char* buf = mBuf.begin();
        const char* buf_end = mBuf.end();
 
        ImGuiListClipper clipper;
        clipper.Begin(mLineOffsets.Size);
        while (clipper.Step())
        {
            for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
            {
                const char* line_start = buf + mLineOffsets[line_no];
                const char* line_end = (line_no + 1 < mLineOffsets.Size) ? (buf + mLineOffsets[line_no + 1] - 1) : buf_end;
                ImGui::TextUnformatted(line_start, line_end);
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
