#pragma once
#include <string>
#include <cinttypes>
#include <vector>
#include <filesystem>
#include "glaze/glaze.hpp"
#include "Platform.hpp"


namespace imkanji
{

struct Flashcard
{
  Index fIndex{};
  Index hIndex{};
  String kanji{};
  Strings imi{};
  Strings kun{};
  Strings on{};
};

std::vector<Flashcard> readFlashcards();

}

template<>
struct glz::meta<imkanji::Flashcard>
{
  using T = imkanji::Flashcard;
  static constexpr auto value = object(
      "id", &T::fIndex, "hid", &T::hIndex, "kanji", &T::kanji, "imi", &T::imi, "kun", &T::kun, "on", &T::on);
};