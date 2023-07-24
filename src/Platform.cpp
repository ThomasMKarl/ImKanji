#include "Platform.hpp"


std::string_view trim(const std::string_view & in)
{
    String whitespaces = "\n\r\t ";
    auto begin = in.find_first_not_of(whitespaces);
    auto end = in.find_last_not_of(whitespaces);
    return std::string_view{in.data() + begin, end - begin};
}

std::string_view trim(const std::string & in)
{
    String whitespaces = "\n\r\t ";
    auto begin = in.find_first_not_of(whitespaces);
    auto end = in.find_last_not_of(whitespaces);
    return std::string_view{in.data() + begin, end - begin};
}

std::vector<std::string_view> split(const std::string & val, char delim, bool trimspace)
{
    std::string d{delim};
    std::vector<std::string_view> res{};
    if (val.empty())
        return res;

    std::size_t begin = 0;
    auto found = 0ULL;
    while (begin < val.size())
    {
        found = val.find_first_of(delim, begin);
        if(found == std::string::npos)
            found = val.size();
        if (trimspace)
            res.emplace_back(trim(std::string_view{val.data() + begin, found - begin}));
        else
            res.emplace_back(std::string_view{val.data() + begin, found - begin});
        begin = found + 1;
    }

    return res;
}

Strings convert(const std::vector<std::string_view> & in)
{
    Strings res{};
    res.reserve(in.size());
    for (const auto & view : in)
      res.emplace_back(view);
    return res;
}

std::vector<std::string_view> toVectorView(const std::string & in)
{
    return split(in, ',', true);
}

Strings toVector(const std::string & in)
{
    return convert(split(in, ',', true));
}

String toString(const Strings & in)
{
    String res{};
    if (in.empty())
        return res;

    for (const auto & s : in)
        res.append(s + ", ");
    res.pop_back();
    res.pop_back();
    return res;
}

std::filesystem::path makeUtf8Path(const char * path)
{
    return std::filesystem::path((const char8_t*)path);
}
