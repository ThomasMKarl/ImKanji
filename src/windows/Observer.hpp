#pragma once
#include <Platform.hpp>


namespace imkanji::window
{

template<typename T>
struct Observer
{
  virtual void fieldChanged(T & source, const String & fieldName) = 0;
};

} // namespace imkanji::window
