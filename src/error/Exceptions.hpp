#pragma once
#include "BaseError.hpp"
#include "Console.hpp"
#include "plog/Log.h"


#define THROW_ERROR(_RELEASE_MESSAGE_)  \
  {                                     \
    LOG_DEBUG << "raising error...";    \
    throw Error{_RELEASE_MESSAGE_, ""}; \
  }

#define THROW_ERROR_D(_RELEASE_MESSAGE_, _DEBUG_MESSAGE_) \
  {                                                       \
    LOG_DEBUG << "raising error...";                      \
    throw Error{_RELEASE_MESSAGE_, _DEBUG_MESSAGE_};      \
  }

#define THROW_FATALERROR(_RELEASE_MESSAGE_) \
  {                                         \
    LOG_DEBUG << "raising fatal error...";  \
    throw Error{_RELEASE_MESSAGE_, ""};     \
  }

#define THROW_FATALERROR_D(_RELEASE_MESSAGE_, _DEBUG_MESSAGE_) \
  {                                                            \
    LOG_DEBUG << "raising fatal error...";                     \
    throw Error{_RELEASE_MESSAGE_, _DEBUG_MESSAGE_};           \
  }

struct Error : BaseError
{
public:
  Error(std::string _releaseMessage, std::string _debugMessage = "") :
      releaseMessage{std::move(_releaseMessage)},
      debugMessage{std::move(_debugMessage)} {}

  void handle(const BaseErrorHandler & handler) const override
  {
    handler.handle(*this);
  }

  std::string releaseMessage{};
  std::string debugMessage{};
};

struct FatalError : BaseError
{
public:
  FatalError(std::string _releaseMessage, std::string _debugMessage = "") :
      releaseMessage{std::move(_releaseMessage)},
      debugMessage{std::move(_debugMessage)} {}

  void handle(const BaseErrorHandler & handler) const override
  {
    handler.handle(*this);
  }

  std::string releaseMessage{};
  std::string debugMessage{};
};
