#include "ConfigWindow.hpp"
#include "TableWindow.hpp"
#include "Cardbox.hpp"
#include "HData.hpp"
#include "FileDialog.hpp"


auto flashcardDB_c = readFlashcards();
auto hdataDB_c = readHdata();

struct Helper
{
    Index fIndex{};
    Index hIndex{};
    std::string kanji{};
    std::string hString{};
};

void exportHtml(const char * path, const std::pair<Index, Index> & fromTo)
{
  if (path == nullptr)
    return;

  std::ofstream htmlFile{path};
  if (!htmlFile)
    return;

  const std::string header{
      "<!DOCTYPE html>\n<html>\n<head>\n<title>Sorted Kanji</title>\n<meta charset='UTF-8'>\n</head>\n<style>table, "
      "th {border:1px solid black;}</style>\n\n<body>\n<h1>Sorted Kanji</h1>\n"};
  const std::string footer{"\n</body>\n</html>"};

  htmlFile << header;

  unsigned int strokeNumber{1};

  std::vector<std::vector<Helper>> strokeMap{};
  strokeMap.resize(29);

  for (auto it = std::begin(flashcardDB_c) + fromTo.first - 1; 
       it < std::begin(flashcardDB_c) + fromTo.second; 
       ++it)
  {
    const auto & flashcard = *it;
    if (flashcard.kanji == "々")
        continue;
    const auto & h = hdataDB_c.at(flashcard.hIndex - 1).hString;
    bool level0 = true;
    uint8_t index = 0;
    uint8_t strokes{};
    for (const char c : h)
    {
        if (level0)
        {
            if (isdigit(c) == 0)
            {
                strokes += std::stoul(h.substr(0, index));
                level0 = false;
            }
        }
        else
        {
            if (isdigit(c) != 0)
            {
                strokes += std::stoul(h.substr(index));
                break;
            }
        }
        ++index;
    }
    strokeMap.at(strokes - 1).emplace_back(
        Helper
        {
            .fIndex = flashcard.fIndex,
            .hIndex = flashcard.hIndex,
            .kanji = flashcard.kanji,
            .hString = h
        });
  }

  for (const auto & kanjis : strokeMap)
  {
    if (!kanjis.empty())
    {
      htmlFile << "<h3>Stroke number " << std::to_string(strokeNumber) << "</h3>";
      htmlFile << "<table style=''>\n<tr><th align='left'>Kanji</th><th align='left'>global index</th><th "
                  "align='left'>Had. index</th><th align='left'>radical string</th></tr>\n";
    }

    strokeNumber++;
    for (const auto & kanji : kanjis)
        htmlFile << "  <tr><td>" << kanji.kanji << "</td><td>" << kanji.fIndex << "</td><td>"
                 << kanji.hIndex << "</td><td>" << kanji.hString << "</td></tr>\n";

    if (!kanjis.empty())
      htmlFile << "<p></table>\n";
  }
}

void exportLatex(const char * path, const std::pair<Index, Index> & fromTo)
{
  if (path == nullptr)
    return;

  std::ofstream texFile{path};
  if (!texFile)
    return;

  unsigned int strokeNumber{1};

  std::vector<std::vector<Helper>> strokeMap{};
  strokeMap.resize(29);

  for (auto it = std::begin(flashcardDB_c) + fromTo.first - 1; 
       it < std::begin(flashcardDB_c) + fromTo.second; 
       ++it)
  {
    const auto & flashcard = *it;
    if (flashcard.kanji == "々")
        continue;
    const auto & h = hdataDB_c.at(flashcard.hIndex - 1).hString;
    bool level0 = true;
    uint8_t index = 0;
    uint8_t strokes{};
    for (const char c : h)
    {
        if (level0)
        {
            if (isdigit(c) == 0)
            {
                strokes += std::stoul(h.substr(0, index));
                level0 = false;
            }
        }
        else
        {
            if (isdigit(c) != 0)
            {
                strokes += std::stoul(h.substr(index));
                break;
            }
        }
        ++index;
    }
    strokeMap.at(strokes - 1).emplace_back(
        Helper
        {
            .fIndex = flashcard.fIndex,
            .hIndex = flashcard.hIndex,
            .kanji = flashcard.kanji,
            .hString = h
        });
  }

  for (const auto & kanjis : strokeMap)
  {
    if (!kanjis.empty())
    {
      texFile << "\\section{stroke number " << std::to_string(strokeNumber) << "}\n";
      texFile << "  \\begin{longtable}[c]{llll}\n    \\bfseries Kanji & \\bfseries global index & \\bfseries "
                 "Had. index & \\bfseries radical string\\\\\\hline\\endhead\n";
    }

    strokeNumber++;
    for (const auto & kanji : kanjis)
        texFile << "    \\bfseries " << kanji.kanji << " & " << kanji.fIndex << " & "
                << kanji.hIndex << " & " << kanji.hString << "\\\\\n";

    if (!kanjis.empty())
      texFile << "  \\end{longtable}\n";
  }
}

void exportTable(const char * path, const std::pair<Index, Index> & fromTo)
{
    if (path == nullptr)
        return;
    
    if (strcmp(path, "") == 0)
        return;

    if (path[0] == '.')
        return;

    const char * dot = strchr(path, '.');
    if (dot == nullptr)
        return;

    if (strcmp(dot, ".tex") == 0)
        exportLatex(path, fromTo);
    else if (strcmp(dot, ".html") == 0)
        exportHtml(path, fromTo);
}

Index toIndex(std::string & val)
{
    uint8_t counter = 0;
    for (const auto & c : val)
    {
        if (!isdigit(c))
        {
            val = val.substr(0, counter);
            break;
        }
        ++counter;
    }

    if (val.empty())
      return 0;

    return std::min(static_cast<Index>(540), static_cast<Index>(std::stoul(val)));
}

bool check(const std::pair<Index, Index> & range)
{
    if (range.first == 0)
        return false;
    if (range.second == 0)
        return false;
    if (range.first > range.second)
        return false;
    return true;
}

void Config_Window::draw(const char* title, bool* p_open)
{
    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }

    auto fromTo = std::make_pair(toIndex(from), toIndex(to));

    pushFont(1);

    if (ImGui::RadioButton("振り仮名 - 漢字", !kanjiFuri))
        kanjiFuri = false;
    ImGui::SameLine();
    if (ImGui::RadioButton("漢字 - 振り仮名", kanjiFuri))
        kanjiFuri = true;
        
    ImGui::PopFont();
            
    if (ImGui::Checkbox("Hide Imi", &hide.hideImi))
    {
        if (hide.hideKun && hide.hideOn)
            hide.hideImi = false;
    }
    ImGui::SameLine();
    ImGui::Checkbox("Shuffle", &shuffle);
    if (ImGui::Checkbox("Hide Kun", &hide.hideKun))
    {
        if (hide.hideImi && hide.hideOn)
            hide.hideKun = false;   
    }
    if (ImGui::Checkbox("Hide On", &hide.hideOn))
    {
        if (hide.hideKun && hide.hideImi)
            hide.hideOn = false;
    }
    
    if (ImGui::Button("export"))
    {
        nfdu8filteritem_t filter[] = {{"LaTeX include", "tex"}, {"web page", "html"}};
        auto path = FileDialog::saveFile(filter,
                                         nullptr,
                                         (std::string("kanji_sorted_") + std::to_string(fromTo.first) + "-" + std::to_string(fromTo.second)).c_str());
        if (!path.first.empty())
            exportTable(path.first.c_str(), fromTo);
    }

    ImGui::InputText("##from", &from);
    ImGui::SameLine();
    ImGui::Text("from");

    ImGui::InputText("##to", &to);
    ImGui::SameLine();
    ImGui::Text("to");

    for (uint8_t index = 1; index <= numberOfCardboxLevels; ++index)
    {
        if (ImGui::Button(std::to_string(index).c_str()))
        {
            trainingFlashcards = true;
            if (flashcardWindow.has_value() && tableWindow != nullptr)
                tableWindow->unsubscribe(&(flashcardWindow.value()));
            flashcardWindow = Flashcard_Window{index, hide, kanjiFuri, shuffle};
            if (tableWindow != nullptr)
                tableWindow->subscribe(&(flashcardWindow.value()));
        }
        ImGui::SameLine();
    }
    if (ImGui::Button("train kanji") && check(fromTo))
    {
        trainingFlashcards = true;
        if (flashcardWindow.has_value() && tableWindow != nullptr)
            tableWindow->unsubscribe(&(flashcardWindow.value()));
        flashcardWindow = Flashcard_Window{fromTo, hide, kanjiFuri, shuffle};
        if (tableWindow != nullptr)
            tableWindow->subscribe(&(flashcardWindow.value()));
    }

    for (uint8_t index = 1; index <= numberOfCardboxLevels; ++index)
    {
        ImGui::Button(std::to_string(index).c_str());
        ImGui::SameLine();
    }
    ImGui::Button("train examples");
            
    for (uint8_t index = 1; index <= numberOfCardboxLevels; ++index)
    {
        ImGui::Button(std::to_string(index).c_str());
        ImGui::SameLine();
    }
    ImGui::Button("train words");

    if (flashcardWindow.has_value())
    {
        if (trainingFlashcards)
            flashcardWindow.value().draw("Flashcard", &trainingFlashcards);
        else
        {
            if (tableWindow != nullptr)
                tableWindow->unsubscribe(&(flashcardWindow.value()));
            flashcardWindow.reset();
        }
    }

    ImGui::End();
}
