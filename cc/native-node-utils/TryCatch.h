#include "Converters.h"
#include "utils.h"

#ifndef __FF_TRY_CATCH_H__
#define __FF_TRY_CATCH_H__

namespace FF {

class TryCatch {
public:
  // errorPrefix can be used to prefix errors in a method binding with the method name
  std::string errorPrefix;
  Napi::Env env;
  Napi::EscapableHandleScope scope;

  TryCatch(Napi::Env env, std::string errorPrefix)
      : env(env), errorPrefix(errorPrefix), scope(env) {};

  std::string getCaughtErrorMessageUnchecked() {
    return Exception().Message(); //  .ToString().Utf8Value();
  }

  std::string extendWithPrefix(std::string errorMessage) {
    if (!errorPrefix.empty()) {
      return errorPrefix + std::string(" - ") + errorMessage;
    }
    return errorMessage;
  }

  void throwError(Napi::Value message) {
    Napi::Maybe<Napi::String> maybeString = message.ToString();
    if (maybeString.IsNothing()) {
      Napi::Error::New(env, "Failed to convert message to string").ThrowAsJavaScriptException();
      return;
    }
    std::string errorMessage = maybeString.Unwrap().Utf8Value();
    Napi::Error::New(env, errorMessage).ThrowAsJavaScriptException();
  }

  void throwError(std::string errorMessage) {
    throwError(Napi::String::New(env, extendWithPrefix(errorMessage)));
  }

  void reThrow() {
    throwError(Napi::String::New(env, extendWithPrefix(getCaughtErrorMessageUnchecked())));
  }

private:
  Napi::Error Exception() {
    return Napi::Error::New(env, "An error occurred");
  }
};

} // namespace FF

#endif