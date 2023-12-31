#include "FlashcardWindow.hpp"
#include "LogWindow.hpp"
#include "Cardbox.hpp"
#include <algorithm>
#include <ranges>


auto flashcardDB = imkanji::readFlashcards();

bool compareVectorAndString(const imkanji::Strings & flash, const imkanji::String & input)
{
  bool found = false;
  auto asVector = imkanji::toVector(input);
  if (asVector.empty() && flash.empty())
    return true;

  for (const auto & val: asVector)
  {
    if (imkanji::contains(flash, val))
    {
      found = true;
      break;
    }
  }

  return found;
}

imkanji::window::Flashcard::Flashcard(uint64_t cardboxLevel_, const Hide & hide_, bool kanjiFuri_, bool shuffle) :
    kanjiFuri(kanjiFuri_), hide(hide_), cardboxLevel(cardboxLevel_)
{
  if (cardboxLevel > Cardbox::instance().kanjiBoxLevels())
    usedIndices = {};
  else
  {
    auto & box = Cardbox::instance().kanjBox(cardboxLevel);
    usedIndices.reserve(box.size());
    for (auto index: box)
      usedIndices.emplace_back(index);
  }

  if (usedIndices.empty())
    return;

  if (shuffle)
  {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(usedIndices.begin(), usedIndices.end(), g);
  }

  currentFlashcard = flashcardDB.at(usedIndices.back() - 1);

  amountOfKanji = usedIndices.size();
}

imkanji::window::Flashcard::Flashcard(const std::pair<Index, Index> & fromTo_, const Hide & hide_, bool kanjiFuri_, bool shuffle) :
    kanjiFuri(kanjiFuri_), fromTo(fromTo_), hide(hide_)
{
  fromTo.second = std::min(fromTo.second, static_cast<Index>(flashcardDB.size()));
  auto range = fromTo.second - fromTo.first + 1;
  usedIndices.resize(range);
  std::generate(usedIndices.begin(), usedIndices.end(), [n = fromTo.second]() mutable
                {
                  return n--;
                });

  if (usedIndices.empty())
    return;

  if (shuffle)
  {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(usedIndices.begin(), usedIndices.end(), g);
  }

  currentFlashcard = flashcardDB.at(usedIndices.back() - 1);

  amountOfKanji = usedIndices.size();
}

void imkanji::window::Flashcard::report(const char * title, bool * p_open)
{
  if (!ImGui::Begin(title, p_open))
  {
    ImGui::End();
    return;
  }

  ImGui::Text("Report:");
  ImGui::Text("Successes: %d", static_cast<uint32_t>(successes));
  ImGui::Text("Failures: %d", static_cast<uint32_t>(failures));
  ImGui::Text("Success Rate: %.2f%%", successes / static_cast<float>(amountOfKanji) * 100.0f);

  if (Cardbox::instance().kanjiBoxLevels() > 0)
  {
    ImGui::Separator();

    ImGui::Text("Cardbox");
    for (uint64_t level = 1; level <= Cardbox::instance().kanjiBoxLevels(); ++level)
      ImGui::Text("Level %d: %d kanji left", static_cast<uint32_t>(level), static_cast<uint32_t>(Cardbox::instance().kanjBox(level).size()));
  }

  if (ImGui::Button("close"))
    *p_open = false;

  ImGui::End();
}

void imkanji::window::Flashcard::draw(const char * title, bool * p_open)
{
  if (showReport)
  {
    report(title, p_open);
    return;
  }

  if (usedIndices.empty())
    return;

  if (!ImGui::Begin(title, p_open))
  {
    ImGui::End();
    return;
  }

  prefill();

  ImGui::Text("Flashcard Id: %d", currentFlashcard.fIndex);
  ImGui::Text("Hadamitzky Id: %d", currentFlashcard.hIndex);
  auto done = amountOfKanji - usedIndices.size();
  ImGui::Text("Done: %d of %d (%.2f%%)", static_cast<uint32_t>(done), static_cast<uint32_t>(amountOfKanji), done / static_cast<float>(amountOfKanji) * 100.0f);

  auto & levelOne = Cardbox::instance().kanjBox(1);
  auto foundIt = std::find(std::begin(levelOne), std::end(levelOne), currentFlashcard.fIndex);
  bool found = foundIt != std::end(levelOne);

  pushFont(3);
  scaleFont(5.0f);
  ImGui::InputText("##kanji", &inputKanji);
  ImGui::PopFont();
  ImGui::PopItemWidth();

  pushFont(0);

  ImGui::SameLine();
  ImGui::Text("Kanji");

  if (!hide.hideImi)
  {
    ImGui::InputText("##imi", &inputImi);
    ImGui::SameLine();
    ImGui::Text("Imi");
  }

  if (!hide.hideKun)
  {
    pushFont(2);
    ImGui::InputText("##kun", &inputKun);
    ImGui::PopFont();
    ImGui::SameLine();
    ImGui::Text("Kun");
  }

  if (!hide.hideOn)
  {
    pushFont(2);
    ImGui::InputText("##on", &inputOn);
    ImGui::PopFont();
    ImGui::SameLine();
    ImGui::Text("On");
  }

  if (!submitted && ImGui::Button("submit"))
  {
    submitted = true;
    success = compareFlashcards();
    if (success)
    {
      ++successes;
      if (cardboxLevel > 0)
      {
        if (cardboxLevel + 1 <= Cardbox::instance().kanjiBoxLevels())
          Cardbox::instance().kanjBox(cardboxLevel + 1).emplace(currentFlashcard.fIndex);
        std::erase_if(Cardbox::instance().kanjBox(cardboxLevel), [this](auto const & in)
                      {
                        return in == currentFlashcard.fIndex;
                      });
      }
    }
    else
    {
      ++failures;
      fillAll();
    }
  }

  if (submitted && ImGui::Button("continue"))
  {
    submitted = false;
    usedIndices.pop_back();
    if (usedIndices.empty())
      showReport = true;
    else
      currentFlashcard = flashcardDB.at(usedIndices.back() - 1);
    clear();
  }

  ImGui::SameLine();

  if (cardboxLevel == 0)
  {
    if (found && ImGui::Button("remove from cardbox"))
      levelOne.erase(foundIt);
    if (!found && ImGui::Button("add to cardbox"))
      levelOne.emplace(currentFlashcard.fIndex);
  }

  ImGui::SameLine();

  if (submitted)
  {
    if (success)
      Text(1, 1, green, "Success!");
    else
      Text(1, 1, red, "Failure!");
  }

  ImGui::PopFont();

  ImGui::End();
}

void imkanji::window::Flashcard::prefill()
{
  if (kanjiFuri)
  {
    inputKanji = currentFlashcard.kanji;
    if (hide.hideImi)
      inputImi = toString(currentFlashcard.imi);
    if (hide.hideKun)
      inputKun = toString(currentFlashcard.kun);
    if (hide.hideOn)
      inputOn = toString(currentFlashcard.on);
  }
  else
  {
    inputImi = toString(currentFlashcard.imi);
    inputKun = toString(currentFlashcard.kun);
    inputOn = toString(currentFlashcard.on);
  }
}

bool imkanji::window::Flashcard::compareFlashcards() const
{
  if (currentFlashcard.kanji != inputKanji)
    return false;

  auto res = compareVectorAndString(currentFlashcard.imi, inputImi);
  if (!res && !hide.hideImi)
    return false;

  res = compareVectorAndString(currentFlashcard.kun, inputKun);
  if (!res && !hide.hideKun)
    return false;

  res = compareVectorAndString(currentFlashcard.on, inputOn);
  if (!res && !hide.hideOn)
    return false;

  return true;
}

void imkanji::window::Flashcard::fieldChanged(Table & source, const String & fieldName)
{
  if (fieldName == "selected")
    inputKanji = source.getSelected();
}

void imkanji::window::Flashcard::clear()
{
  inputKanji.clear();
  inputImi.clear();
  inputKun.clear();
  inputOn.clear();
}

void imkanji::window::Flashcard::fillAll()
{
  inputKanji = currentFlashcard.kanji;
  inputImi = toString(currentFlashcard.imi);
  inputKun = toString(currentFlashcard.kun);
  inputOn = toString(currentFlashcard.on);
}
