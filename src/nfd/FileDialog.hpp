#pragma once
#include <filesystem>
#include <string>
#include <stdexcept>
#include <vector>
#include "nfd.h"


class FileDialog
{
public:
    template<uint64_t N>
    static std::string openFile(const nfdu8filteritem_t (&filter)[N], const char * defaultPath = nullptr)
    {
        std::string result{};
        FileDialog ret{};
        auto res = NFD_OpenDialogU8(&ret.path, filter, N, reinterpret_cast<const nfdu8char_t *>(defaultPath));
        if (res == NFD_OKAY && ret.path != nullptr)
            return reinterpret_cast<char*>(ret.path);
        if (res == NFD_ERROR)
            throw std::runtime_error{"error in file dialog"};
        return result;
    }

    template<uint64_t N>
    static std::vector<std::string> openFileMulti(const nfdu8filteritem_t (&filter)[N], const char * defaultPath = nullptr)
    {
        std::vector<std::string> result{};
        FileDialog ret{};

        auto res = NFD_OpenDialogMultipleU8(&ret.paths, filter, N, reinterpret_cast<const nfdu8char_t *>(defaultPath));

        if (res == NFD_CANCEL)
            return result;

        if (res == NFD_ERROR || ret.paths == nullptr)
            throw std::runtime_error{"error in file dialog"};

        nfdpathsetsize_t count;
        if (NFD_PathSet_GetCount(ret.paths, &count) != NFD_OKAY)
            throw std::runtime_error{"error in file dialog"};

        result.reserve(count);
        ret.helper.resize(count);
        for (nfdpathsetsize_t index = 0; index < count; ++index)
        {
            auto innerRes = NFD_PathSet_GetPathU8(ret.paths, index, &ret.helper[index]);
            if (innerRes != NFD_OKAY || ret.helper[index] == nullptr)
                throw std::runtime_error{"error in file dialog"};
            result.emplace_back(reinterpret_cast<char*>(ret.helper[index]));
        }

        return result;
    }

    template<uint64_t N>
    static std::string openFolder(const nfdu8filteritem_t (&filter)[N], const char * defaultPath = nullptr)
    {
        std::string result{};
        FileDialog ret{};
        auto res = NFD_PickFolderU8(&ret.path, filter, N, reinterpret_cast<const nfdu8char_t *>(defaultPath));
        if (res == NFD_OKAY && ret.path != nullptr)
            return reinterpret_cast<char*>(ret.path);
        if (res == NFD_ERROR)
            throw std::runtime_error{"error in file dialog"};
    }

    template<uint64_t N>
    static std::pair<std::string, uint8_t> saveFile(const nfdu8filteritem_t (&filter)[N], 
                                                    const char * defaultPath = nullptr,
                                                    const char * defaultName = nullptr)
    {
        std::pair<std::string, uint8_t> result{};
        FileDialog ret{};
        nfdfilteritem_t filterItem[2] = {{"Source code", "c,cpp,cc"}, {"Header", "h,hpp"}};
        auto res = NFD_SaveDialogU8(&ret.path, &result.second, filterItem, 2, /*defaultPath*/nullptr, nullptr/*defaultName*/);
        if (res == NFD_OKAY && ret.path != nullptr)
        {
            result.first = reinterpret_cast<char*>(ret.path);
            return result;
        }
        if (res == NFD_ERROR)
            throw std::runtime_error{std::string{"error in file dialog: "} + NFD_GetError()};
        return result;
    }

    ~FileDialog();
    FileDialog(const FileDialog&) = delete;
    FileDialog(FileDialog&&) = delete;
    FileDialog & operator=(const FileDialog&) = delete;
    FileDialog & operator=(FileDialog&&) = delete;

private:
    FileDialog();

    nfdu8char_t * path = nullptr;
    nfdpathset_t** paths = nullptr;
    std::vector<nfdu8char_t *> helper{};
};
