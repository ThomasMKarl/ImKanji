#include "Cardbox.hpp"


std::unique_ptr<imkanji::Cardbox> imkanji::Cardbox::singleton{};

imkanji::Cardbox & imkanji::Cardbox::instance(const char * path)
{
  if (static_cast<bool>(singleton))
    return *singleton.get();
  singleton = std::unique_ptr<Cardbox>(new Cardbox{path});
  return *singleton.get();
}

std::set<imkanji::Index> & imkanji::Cardbox::kanjBox(uint64_t level)
{
  return content.kanjiBox.at(level - 1);
}

std::set<imkanji::Index> & imkanji::Cardbox::exampleBox(uint64_t level)
{
  return content.exampleBox.at(level - 1);
}

std::set<imkanji::Index> & imkanji::Cardbox::wordBox(uint64_t level)
{
  return content.wordBox.at(level - 1);
}

void imkanji::Cardbox::write() const
{
  auto error = glz::write_file(content, fspath.string(), String{});
  if (error)
    throw std::runtime_error{"cannot write " + fspath.string()};
}

imkanji::Cardbox::Cardbox(const char * path)
{
  if (path == nullptr)
    return;

  fspath = std::filesystem::absolute(makeUtf8Path(path));
  if (!std::filesystem::exists(fspath))
    throw std::runtime_error(fspath.string() + " does not exist");

  std::ifstream file(fspath.c_str());
  if (!file)
    throw std::runtime_error{"cannot open " + fspath.string()};

  String fileContent{};
  while (file.good())
  {
    String line{};
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
