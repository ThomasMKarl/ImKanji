#include "GraphemeWindow.hpp"
#include "HData.hpp"
#include "Flashcard.hpp"


auto hdataDB = imkanji::readHdata();
auto flashcardDB_gr = imkanji::readFlashcards();

constexpr auto numberOfGraphemes = 80ULL;

// clang-format off
constexpr std::array<const char *, numberOfGraphemes> graphemeList{
    "一", "丨", "イ", "ニ", "冫", "孑", "阝", "力", "又", "匕", "亠", "十", "ト", "イ", "勹", "儿",
    "厶", "厂", "⻌", "冂", "氵", "土", "扌", "口", "女", "巾", "犭", "弓", "彳", "夕", "彡", "艹",
    "宀", "大", "小", "山", "寸", "工", "ヨ", "尸", "木", "日", "月", "火", "ネ", "王", "牛", "方",
    "攵", "斤", "心", "戈", "石", "立", "目", "禾", "ネ", "田", "皿", "疒", "糸", "米", "舟", "虫",
    "耳", "⺮", "言", "貝", "車", "⻊", "酉", "金", "住", "雨", "門", "頁", "食", "馬", "魚", "鳥"};
// clang-format on

constexpr std::array<std::pair<unsigned int, unsigned int>, 11ULL> beginEnd{
  std::make_pair<unsigned int, unsigned int>(0, 2),
  std::make_pair<unsigned int, unsigned int>(2, 20),
  std::make_pair<unsigned int, unsigned int>(20, 40),
  std::make_pair<unsigned int, unsigned int>(40, 52),
  std::make_pair<unsigned int, unsigned int>(52, 60),
  std::make_pair<unsigned int, unsigned int>(60, 66),
  std::make_pair<unsigned int, unsigned int>(66, 71),
  std::make_pair<unsigned int, unsigned int>(71, 75),
  std::make_pair<unsigned int, unsigned int>(75, 77),
  std::make_pair<unsigned int, unsigned int>(77, 78),
  std::make_pair<unsigned int, unsigned int>(78, 80)
};

void imkanji::window::Grapheme::draw(const char * title, bool * p_open)
{
  if (!ImGui::Begin(title, p_open))
  {
    ImGui::End();
    return;
  }

  ImGui::Text("Found:");
  for (const auto & flashcard: flashcardDB_gr)
  {
    bool match = true;
    bool allEmpty = true;
    const auto & radicals = hdataDB.at(flashcard.hIndex).radicals;
    for (const auto & sel: selected)
    {
      if (sel.empty())
        continue;
      allEmpty = false;
      bool found = std::find_if(std::begin(radicals), std::end(radicals), [sel](const auto & in)
                                {
                                  return sel == graphemeList.at(in - 1);
                                }) != std::end(radicals);
      if (!found)
      {
        match = false;
        break;
      }
    }

    if (match && !allEmpty)
    {
      ImGui::SameLine();
      pushFont(2);
      if (ImGui::Button(flashcard.kanji.c_str())) {}
      ImGui::PopFont();
    }
  }

  ImGui::Text("Selected:");
  for (auto & sel: selected)
  {
    if (sel.empty())
      continue;
    ImGui::SameLine();
    pushFont(2);
    if (ImGui::Button(sel.c_str()))
      sel.clear();
    ImGui::PopFont();
  }

  for (unsigned int strokeNum = 1; strokeNum <= beginEnd.size(); ++strokeNum)
    table(strokeNum);

  ImGui::End();
}

void imkanji::window::Grapheme::table(unsigned int strokeNum)
{
  ImGui::Separator();
  if (ImGui::CollapsingHeader((std::to_string(strokeNum) + " strokes").c_str()))
  {
    for (unsigned int index = beginEnd[strokeNum - 1].first; index < beginEnd[strokeNum - 1].second; ++index)
    {
      if ((index - beginEnd[strokeNum - 1].first) % 10 != 0)
        ImGui::SameLine();
      pushFont(2);
      if (ImGui::Button(graphemeList[index]))
      {
        for (auto & sel: selected)
        {
          if (sel == graphemeList[index])
            sel.clear();
          if (sel.empty())
          {
            sel = graphemeList[index];
            break;
          }
        }
      }
      ImGui::PopFont();
    }
  }
}
