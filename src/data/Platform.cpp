#include "Platform.hpp"


imkanji::StringView imkanji::trim(const StringView & in)
{
  String whitespaces = "\n\r\t ";
  auto begin = in.find_first_not_of(whitespaces);
  auto end = in.find_last_not_of(whitespaces);
  return StringView{in.data() + begin, end - begin};
}

imkanji::StringView imkanji::trim(const String & in)
{
  String whitespaces = "\n\r\t ";
  auto begin = in.find_first_not_of(whitespaces);
  auto end = in.find_last_not_of(whitespaces);
  return StringView{in.data() + begin, end - begin};
}

imkanji::StringViews imkanji::split(const String & val, char delim, bool trimspace)
{
  String d{delim};
  StringViews res{};
  if (val.empty())
    return res;

  std::size_t begin = 0;
  auto found = 0ULL;
  while (begin < val.size())
  {
    found = val.find_first_of(delim, begin);
    if (found == String::npos)
      found = val.size();
    if (trimspace)
      res.emplace_back(trim(StringView{val.data() + begin, found - begin}));
    else
      res.emplace_back(StringView{val.data() + begin, found - begin});
    begin = found + 1;
  }

  return res;
}

imkanji::Strings imkanji::convert(const StringViews & in)
{
  Strings res{};
  res.reserve(in.size());
  for (const auto & view: in)
    res.emplace_back(view);
  return res;
}

imkanji::StringViews imkanji::toVectorView(const String & in)
{
  return split(in, ',', true);
}

imkanji::Strings imkanji::toVector(const String & in)
{
  return convert(split(in, ',', true));
}

imkanji::String imkanji::toString(const Strings & in)
{
  String res{};
  if (in.empty())
    return res;

  for (const auto & s: in)
    res.append(s + ", ");
  res.pop_back();
  res.pop_back();
  return res;
}

std::filesystem::path imkanji::makeUtf8Path(const StringView & path)
{
  return std::filesystem::path(reinterpret_cast<const char8_t *>(path.data()));
}

uint64_t imkanji::replace(String & in, const StringView & toReplace, const StringView & replace)
{
  uint64_t count{0};
  for (std::string::size_type pos{};
       in.npos != (pos = in.find(toReplace.data(), pos, toReplace.length()));
       pos += replace.length(), ++count)
    in.replace(pos, toReplace.length(), replace.data(), replace.length());
  return count;
}