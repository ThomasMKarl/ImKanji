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

void imkanji::window::Grapheme::draw(const char * title, bool * p_open)
{
  if (!ImGui::Begin(title, p_open))
  {
    ImGui::End();
    return;
  }

  pushFont(1);

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
      if (ImGui::Button(flashcard.kanji.c_str())) {}
    }
  }

  ImGui::Text("Selected:");
  for (auto & sel: selected)
  {
    if (sel.empty())
      continue;
    ImGui::SameLine();
    if (ImGui::Button(sel.c_str()))
      sel.clear();
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("1 stroke"))
  {
    for (unsigned int index = 0; index < 2; ++index)
    {
      if (index % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("2 strokes"))
  {
    for (unsigned int index = 2; index < 20; ++index)
    {
      if ((index - 2) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("3 strokes"))
  {
    for (unsigned int index = 20; index < 40; ++index)
    {
      if ((index - 20) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("4 strokes"))
  {
    for (unsigned int index = 40; index < 52; ++index)
    {
      if ((index - 40) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("5 strokes"))
  {
    for (unsigned int index = 52; index < 60; ++index)
    {
      if ((index - 52) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("6 strokes"))
  {
    for (unsigned int index = 60; index < 66; ++index)
    {
      if ((index - 60) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("7 strokes"))
  {
    for (unsigned int index = 66; index < 71; ++index)
    {
      if ((index - 66) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("8 strokes"))
  {
    for (unsigned int index = 71; index < 75; ++index)
    {
      if ((index - 71) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("9 strokes"))
  {
    for (unsigned int index = 75; index < 77; ++index)
    {
      if ((index - 75) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("10 strokes"))
  {
    for (unsigned int index = 77; index < 78; ++index)
    {
      if ((index - 77) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::Separator();
  if (ImGui::CollapsingHeader("11 strokes"))
  {
    for (unsigned int index = 78; index < 80; ++index)
    {
      if ((index - 78) % 10 != 0)
        ImGui::SameLine();
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
    }
  }

  ImGui::PopFont();

  ImGui::End();
}
