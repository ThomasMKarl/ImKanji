#pragma once
#include <array>
#include "Imgui.hpp"
#include "Observable.hpp"
#include "Platform.hpp"


namespace imkanji::window
{

class Table : public Observable<Table>
{
public:
  void draw(const char * title, bool * p_open = nullptr);

  const String & getSelected() const { return selected; }

private:
  void table(unsigned int number, unsigned int step, std::string & selected) const;
  String selected{};
};

} // namespace imkanji::window
