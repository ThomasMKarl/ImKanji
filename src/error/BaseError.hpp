#pragma once
#include <cassert>


template<typename... ETs> struct ErrorHandler;

template<typename ET, typename... ETs>
struct ErrorHandler<ET, ETs...> : ErrorHandler<ETs...>
{
  using ErrorHandler<ETs...>::handle;
  virtual void handle(const ET &) const
  {
    assert(false);
  }
};

template<typename ET>
struct ErrorHandler<ET>
{
  virtual void handle(const ET &) const
  {
    assert(false);
  }
};

struct BaseError;
struct FatalError;
struct Error;

using BaseErrorHandler = ErrorHandler<Error, FatalError>;

class GlobalErrorHandler : public BaseErrorHandler
{
public:
  static const GlobalErrorHandler & instance()
  {
    static GlobalErrorHandler single{};
    return single;
  }

  GlobalErrorHandler(const GlobalErrorHandler &) = delete;
  GlobalErrorHandler(GlobalErrorHandler &&) = delete;

  void handle(const Error &) const override;
  void handle(const FatalError &) const override;

private:
  GlobalErrorHandler(){};
};

struct BaseError
{
  virtual void handle(const BaseErrorHandler &) const = 0;
};
