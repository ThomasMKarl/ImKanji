#pragma once
#include <vector>
#include "Observer.hpp"


namespace imkanji::window
{

template<typename T>
class Observable
{
public:
  void notify(T & source, const String & name)
  {
    for (auto obs: observers)
      obs->fieldChanged(source, name);
  }

  void subscribe(Observer<T> * f)
  {
    observers.push_back(f);
  }

  void unsubscribe(Observer<T> * f)
  {
    observers.erase(std::remove(std::begin(observers), std::end(observers), f), std::end(observers));
  }

private:
  std::vector<Observer<T> *> observers{};
};

} // namespace imkanji::window
