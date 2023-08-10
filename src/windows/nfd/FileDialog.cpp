#include "FileDialog.hpp"


FileDialog::FileDialog()
{
  if (NFD_Init() != NFD_OKAY)
    throw std::runtime_error{"nfd init failed"};
}

FileDialog::~FileDialog()
{
  if (path)
    NFD_FreePathU8(path);
  if (paths)
    NFD_PathSet_Free(paths);
  for (auto help: helper)
    if (help)
      NFD_FreePathU8(help);
  NFD_Quit();
}
