#include "CmdConfig.hpp"
#include "ArgParse.hpp"


argparse::ArgumentParser getFromCmd(int argc, const char ** argv)
{
  argparse::ArgumentParser program(argv[0], "1.0", argparse::default_arguments::none, true);

  program.add_argument("--version")
      .help("shows version information and exits")
      .action([=](const std::string & s)
              {
                std::cout << "ImKanji - Kanji Training in ImGui\n";
                exit(0);
              })
      .default_value(false)
      .implicit_value(true);

  program.add_argument("--noGui")
      .help("starts program without gui")
      .default_value(false)
      .implicit_value(true);

  program.add_argument("-h", "--help")
      .help("shows help message and exits")
      .action([=](const std::string & s)
              {
                std::cout << "\n\n############ HELP ############\n\n"
                          << program.help().str() << "\n##############################\n";
                exit(0);
              })
      .default_value(false)
      .implicit_value(true);

  try
  {
    program.parse_args(argc, argv);
  }
  catch(const std::runtime_error& e)
  {
    std::cout << "\n\n############ HELP ############\n\n"
              << e.what()
              << "\n"
              << program.help().str() << "\n\n##############################\n";
    throw std::runtime_error{"invalid arguments"};
  }

  return program;
}


imkanji::CmdConfig globalInstance = imkanji::CmdConfig::defaulting();

imkanji::CmdConfig & imkanji::CmdConfig::init(int argc, const char ** argv)
{
  auto parser = getFromCmd(argc, argv);

  globalInstance = CmdConfig{};
  globalInstance.mNoGui = parser["--noGui"] == true;

  return globalInstance;
}

imkanji::CmdConfig & imkanji::CmdConfig::instance()
{
  return globalInstance;
}
