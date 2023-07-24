#pragma once
#include "Imgui.hpp"
#include <string>
#include <optional>
#include "FlashcardWindow.hpp"


void exportHtml(const char * path, const std::pair<Index, Index> & fromTo);
void exportLatex(const char * path, const std::pair<Index, Index> & fromTo);
void exportTable(const char * path, const std::pair<Index, Index> & fromTo);

Index toIndex(std::string & val);

bool check(const std::pair<Index, Index> & range);

class Config_Window
{
public:
    void draw(const char* title, bool* p_open = nullptr);

    void refTable(Table_Window * tableWindow_) { tableWindow = tableWindow_; }

    void refGraphemes() {}

private:
    bool trainingFlashcards{};
    bool trainingWords{};
    bool trainingExamples{};
    bool flashcardCardboxOpen{};
    bool wordCardboxOpen{};
    bool exampleCardboxOpen{};

    bool shuffle{true};
    bool kanjiFuri{true};
    Hide hide{};
    std::string from{"1"};
    std::string to{"604"};

    std::optional<Flashcard_Window> flashcardWindow{};
    std::optional<Flashcard_Window> wordWindow{};
    std::optional<Flashcard_Window> exampleWindow{};
    std::optional<Flashcard_Window> flashcardCardboxWindow{};
    std::optional<Flashcard_Window> wordCardboxWindow{};
    std::optional<Flashcard_Window> exampleCardboxWindow{};

    Table_Window * tableWindow = nullptr;
};
