#pragma once
#include "Imgui.hpp"
#include "Platform.hpp"
#include "plog/Log.h"


#define IIMLOG(_MESSAGE_, ...)                                                       \
  {                                                                                  \
    imkanji::String fullMess{imkanji::String{"INFO: "} + __PRETTY_FUNCTION__ + " " + \
                             __FILE__ + ":" + std::to_string(__LINE__) + "\n\t" +    \
                             _MESSAGE_ + "\n"};                                      \
    fullMess = imkanji::makeString(fullMess.c_str(), __VA_ARGS__);                   \
    PLOGI << imkanji::makeString(_MESSAGE_, __VA_ARGS__) << "\n";                    \
    imkanji::window::Log::instance().addLog(fullMess.c_str(), "");                   \
  }

#define WIMLOG(_MESSAGE_, ...)                                                          \
  {                                                                                     \
    imkanji::String fullMess{imkanji::String{"WARNING: "} + __PRETTY_FUNCTION__ + " " + \
                             __FILE__ + ":" + std::to_string(__LINE__) + "\n\t" +       \
                             _MESSAGE_ + "\n"};                                         \
    fullMess = imkanji::makeString(fullMess.c_str(), __VA_ARGS__);                      \
    PLOGW << imkanji::makeString(_MESSAGE_, __VA_ARGS__);                               \
    imkanji::Log::instance().addLog(fullMess.c_str(), "");                              \
  }

#define EIMLOG(_MESSAGE_, ...)                                                        \
  {                                                                                   \
    imkanji::String fullMess{imkanji::String{"ERROR: "} + __PRETTY_FUNCTION__ + " " + \
                             __FILE__ + ":" + std::to_string(__LINE__) + "\n\t" +     \
                             _MESSAGE_ + "\n"};                                       \
    fullMess = imkanji::makeString(fullMess.c_str(), __VA_ARGS__);                    \
    PLOGE << imkanji::makeString(_MESSAGE_, __VA_ARGS__);                             \
    imkanji::window::Log::instance().addLog(fullMess.c_str(), "");                    \
  }

namespace imkanji::window
{

struct Log
{
public:
  static Log & instance()
  {
    static Log * inst = new Log{};
    return *inst;
  }

  void clear();

  template<typename... Ts>
  void addLog(const StringView & fmt, Ts... args)
  {
    uint32_t begin = mBuf.size();
    mBuf.append(makeString(fmt, args...));
    const uint32_t end = mBuf.size();

    for (auto index = begin; index < end; ++index)
    {
      if (mBuf[index] == '\n')
      {
        auto numChars = index - begin;
        mLines.emplace_back(StringView{mBuf.c_str() + begin, numChars});
        begin = index + 1;
      }
    }
  }

  void draw(const char * title, bool * p_open = nullptr);

  Log(const Log &) = delete;
  Log(Log &&) = delete;
  Log & operator=(const Log &) = delete;
  Log & operator=(Log &&) = delete;

private:
  Log() { clear(); }

  bool mAutoScroll = true;
  String mBuf{};
  StringViews mLines{};
};

} // namespace imkanji::window
