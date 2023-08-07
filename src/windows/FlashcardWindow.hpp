#pragma once
#include <algorithm>
#include <random>
#include "Imgui.hpp"
#include "Platform.hpp"
#include "Flashcard.hpp"
#include "Observer.hpp"
#include "TableWindow.hpp"


namespace imkanji::window
{

struct Hide
{
  bool hideImi{};
  bool hideKun{};
  bool hideOn{};
};

class Flashcard : public Observer<Table>
{
public:
  Flashcard(uint64_t cardboxLevel, const Hide & hide_, bool kanjiFuri_, bool shuffle);
  Flashcard(const std::pair<Index, Index> & fromTo_, const Hide & hide_, bool kanjiFuri_, bool shuffle);
  void report(const char * title, bool * p_open = nullptr);
  void draw(const char * title, bool * p_open = nullptr);
  void prefill();
  bool compareFlashcards() const;
  void fieldChanged(Table & source, const String & fieldName) override;
  void clear();
  void fillAll();

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
  imkanji::Flashcard currentFlashcard{};

  String inputKanji{};
  String inputImi{};
  String inputKun{};
  String inputOn{};

  std::vector<Index> usedIndices{};
};

} // namespace imkanji::window
