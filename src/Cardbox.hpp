#pragma once
#include <vector>
#include <set>
#include <memory>
#include "glaze/glaze.hpp"
#include "Platform.hpp"


constexpr uint64_t numberOfCardboxLevels = 5;

struct CardboxContent
{
    std::vector<std::set<Index>> kanjiBox{};
    std::vector<std::set<Index>> exampleBox{};
    std::vector<std::set<Index>> wordBox{};  
};

template<>
struct glz::meta<CardboxContent>
{
    using T = CardboxContent;
    static constexpr auto value = object(
        "kanjiBox", &T::kanjiBox,
        "exampleBox", &T::exampleBox,
        "wordBox", &T::wordBox
    );
};

class Cardbox
{
public:
    static Cardbox & instance(const char * path = nullptr);

    uint64_t kanjiBoxLevels() { return content.kanjiBox.size(); }
    uint64_t exampleBoxLevels() { return content.exampleBox.size(); }
    uint64_t wordBoxLevels() { return content.wordBox.size(); }
    std::set<Index> & kanjBox(uint64_t level);
    std::set<Index> & exampleBox(uint64_t level);
    std::set<Index> & wordBox(uint64_t level);

    void write() const;

    Cardbox(const Cardbox &) = delete;
    Cardbox & operator=(const Cardbox &) = delete;
    Cardbox(Cardbox &&) = delete;
    Cardbox & operator=(Cardbox &&) = delete;
    ~Cardbox() { write(); }

private:
    Cardbox(const char * path);

    std::filesystem::path fspath{};
    CardboxContent content{};
    static std::unique_ptr<Cardbox> singleton;
};