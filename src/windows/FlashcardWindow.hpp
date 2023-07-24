#pragma once
#include <algorithm>
#include <random>
#include "Imgui.hpp"
#include "Platform.hpp"
#include "Flashcard.hpp"
#include "Observer.hpp"
#include "TableWindow.hpp"


struct Hide
{
    bool hideImi{};
    bool hideKun{};
    bool hideOn{};
};

class Flashcard_Window : public Observer<Table_Window>
{
public:
    Flashcard_Window(uint64_t cardboxLevel, const Hide & hide_, bool kanjiFuri_, bool shuffle);
    Flashcard_Window(const std::pair<Index, Index> & fromTo_, const Hide & hide_, bool kanjiFuri_, bool shuffle);
    void report(const char* title, bool* p_open = nullptr);
    void draw(const char* title, bool* p_open = nullptr);
    void prefill();
    bool compareFlashcards() const;

    void fieldChanged(Table_Window & source, const std::string & fieldName) override
    {
        if (fieldName == "selected")
            inputKanji = source.getSelected();
    }

private:
    bool showReport{};

    bool success{};
    bool submitted{};

    bool kanjiFuri{};
    std::pair<Index, Index> fromTo{};
    Hide hide{};

    uint64_t amountOfKanji{0};
    uint64_t successes{0};
    uint64_t failures{0};
    uint64_t cardboxLevel{0};
    Flashcard currentFlashcard{};

    String inputKanji{};
    String inputImi{};
    String inputKun{};
    String inputOn{};

    std::vector<Index> usedIndices{};
};
