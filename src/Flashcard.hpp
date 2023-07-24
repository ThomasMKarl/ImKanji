#pragma once
#include <string>
#include <cinttypes>
#include <vector>
#include <filesystem>
#include "glaze/glaze.hpp"
#include "Platform.hpp"


struct Flashcard
{
    Index fIndex{};
    Index hIndex{};
    String kanji{};
    Strings imi{};
    Strings kun{};
    Strings on{};
};

template<>
struct glz::meta<Flashcard>
{
    using T = Flashcard;
    static constexpr auto value = object(
        "id", &T::fIndex,
        "hid", &T::hIndex,
        "kanji", &T::kanji,
        "imi", &T::imi,
        "kun", &T::kun,
        "on", &T::on
    );
};

std::vector<Flashcard> readFlashcards();
