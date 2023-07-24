#pragma once
#include "Imgui.hpp"
#include <array>
#include "Observable.hpp"
#include "Platform.hpp"


class Table_Window : public Observable<Table_Window>
{
public:
    void draw(const char* title, bool* p_open = nullptr);

    const std::string & getSelected() const { return selected; }

private:
    std::string selected{};
};
