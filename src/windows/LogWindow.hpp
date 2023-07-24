#pragma once
#include "Imgui.hpp"
#include "plog/Log.h"


#define IIMLOG(_MESSAGE_, ...)                                                                                                                     \
{                                                                                                                                                  \
    String fullMess{std::string{"INFO: "} + __PRETTY_FUNCTION__ + " " + __FILE__ + ":" + std::to_string(__LINE__) + "\n\t" + _MESSAGE_ + "\n"};    \
    fullMess = makeString(fullMess.c_str(), __VA_ARGS__);                                                                                          \
    PLOGI << makeString(_MESSAGE_, __VA_ARGS__) << "\n";                                                                                           \
    Log_Window::instance().addLog("%s", fullMess.c_str());                                                                                         \
}

#define WIMLOG(_MESSAGE_, ...)                                                                                                                     \
{                                                                                                                                                  \
    String fullMess{std::string{"WARNING: "} + __PRETTY_FUNCTION__ + " " + __FILE__ + ":" + std::to_string(__LINE__) + "\n\t" + _MESSAGE_ + "\n"}; \
    PLOGW << makeString(fullMess.c_str(), __VA_ARGS__);                                                                                            \
    Log_Window::instance().addLog(fullMess.c_str(), __VA_ARGS__);                                                                                  \
}

#define EIMLOG(_MESSAGE_, ...)                                                                                                                     \
{                                                                                                                                                  \
    String fullMess{std::string{"ERROR: "} + __PRETTY_FUNCTION__ + " " + __FILE__ + ":" + std::to_string(__LINE__) + "\n\t" + _MESSAGE_ + "\n"};   \
    PLOGE << makeString(fullMess.c_str(), __VA_ARGS__);                                                                                            \
    Log_Window::instance().addLog(fullMess.c_str(), __VA_ARGS__);                                                                                  \
}

struct Log_Window
{
public:
    static Log_Window & instance()
    {
        static Log_Window * inst = new Log_Window{};
        return *inst;
    }

    void clear();

    void addLog(const char* fmt, ...) IM_FMTARGS(2);

    void draw(const char* title, bool* p_open = nullptr);

    Log_Window(const Log_Window&) = delete;
    Log_Window(Log_Window&&) = delete;
    Log_Window& operator=(const Log_Window&) = delete;
    Log_Window& operator=(Log_Window&&) = delete;

private:
    Log_Window() { clear(); }

    ImGuiTextBuffer mBuf{};
    ImVector<uint8_t> mLineOffsets{};
    bool mAutoScroll = true;
};
