#pragma once
#include <string>
#include <optional>
#include "Imgui.hpp"
#include "FlashcardWindow.hpp"


namespace imkanji::window
{

void exportHtml(const char * path, const std::pair<Index, Index> & fromTo);
void exportLatex(const char * path, const std::pair<Index, Index> & fromTo);
void exportTable(const char * path, const std::pair<Index, Index> & fromTo);

class Config
{
public:
  void draw(const char * title, bool * p_open = nullptr);

  void refTable(Table * tableWindow_) { tableWindow = tableWindow_; }

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
  String from{"1"};
  String to{"604"};

  std::optional<Flashcard> flashcardWindow{};
  std::optional<Flashcard> wordWindow{};
  std::optional<Flashcard> exampleWindow{};
  std::optional<Flashcard> flashcardCardboxWindow{};
  std::optional<Flashcard> wordCardboxWindow{};
  std::optional<Flashcard> exampleCardboxWindow{};

  Table * tableWindow = nullptr;
};

} // namespace imkanji
