#include "Cardbox.hpp"


std::unique_ptr<Cardbox> Cardbox::singleton{};

Cardbox & Cardbox::instance(const char * path)
{
    if (static_cast<bool>(singleton))
        return *singleton.get();
    singleton = std::unique_ptr<Cardbox>(new Cardbox{path});
    return *singleton.get();
}

std::set<Index> & Cardbox::kanjBox(uint64_t level)
{
    return content.kanjiBox.at(level - 1);
}

std::set<Index> & Cardbox::exampleBox(uint64_t level)
{
    return content.exampleBox.at(level - 1);
}

std::set<Index> & Cardbox::wordBox(uint64_t level)
{
    return content.wordBox.at(level - 1);
}

void Cardbox::write() const
{
    auto error = glz::write_file(content, fspath.string());
    if (error)
        throw std::runtime_error{"cannot write " + fspath.string()};
}

Cardbox::Cardbox(const char * path)
{
    if (path == nullptr)
        return;

    fspath = std::filesystem::absolute(makeUtf8Path(path));
    if (!std::filesystem::exists(fspath))
        throw std::runtime_error(fspath.string() + " does not exist");

    std::ifstream file(fspath.c_str());
    if (!file)
        throw std::runtime_error{"cannot open " + fspath.string()};

    std::string fileContent{};
    while (file.good())
    {
        std::string line{};
        std::getline(file, line);
        fileContent.append(std::move(line));
    }

    CardboxContent ret{};
    auto error = glz::read_json(ret, fileContent);
    if (error)
        throw std::runtime_error{"cannot load " + fspath.string() + " (error " + glz::format_error(error, fileContent) + ")"};

    ret.exampleBox.resize(numberOfCardboxLevels);
    ret.kanjiBox.resize(numberOfCardboxLevels);
    ret.wordBox.resize(numberOfCardboxLevels);

    std::swap(content, ret);
}
