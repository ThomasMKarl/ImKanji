#pragma once


namespace imkanji
{

class CmdConfig
{
public:
  static CmdConfig & init(int argc, const char ** argv);
  static CmdConfig & instance();
  static CmdConfig defaulting() { return CmdConfig{}; }

  bool noGui() const { return mNoGui; }

  CmdConfig(const CmdConfig &) = delete;
  CmdConfig & operator=(const CmdConfig &) = delete;

private:
  CmdConfig() = default;
  CmdConfig(CmdConfig &&) = default;
  CmdConfig & operator=(CmdConfig &&) = default;

  bool mNoGui{};
};

} // namespace imkanji
