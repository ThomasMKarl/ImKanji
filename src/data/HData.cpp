#include "HData.hpp"


std::vector<imkanji::HData> imkanji::readHdata()
{
  std::vector<HData> ret{};
  auto path = std::filesystem::absolute(makeUtf8Path("resources/hdata.json"));
  if (!std::filesystem::exists(path))
    throw std::runtime_error(path.string() + " does not exist");

  std::ifstream file(path.c_str());
  if (!file)
    throw std::runtime_error{"cannot open " + path.string()};

  String content{};
  while (file.good())
  {
    String line{};
    std::getline(file, line);
    content.append(std::move(line));
  }

  auto error = glz::read_json(ret, content);
  if (error)
    throw std::runtime_error{"cannot load " + path.string() + " (error " + glz::format_error(error, content) + ")"};

  return ret;
}
