#include "utils.h"

#ifndef __FF_ABSTRACT_CONVERTER_H__
#define __FF_ABSTRACT_CONVERTER_H__

/**
 * @brief used by
 * - IntConverter,
 * - UintConverter,
 * - LongConverter,
 * - UlongConverter,
 * - CharConverter,
 * - UcharConverter,
 * - BoolConverter,
 * - DoubleConverter,
 * - FloatConverter,
 * - StringConverter
 */
namespace FF {

/*
ConverterImpl implements:
        static std::string getTypeName()
        static Napi::Value wrap(ConverterImpl::Type val)
        static bool unwrap(ConverterImpl::Type* pVal, Napi::Value jsVal)
        static ConverterImpl::Type unwrapUnchecked(Napi::Value jsVal)
*/
template <class ConverterImpl>
class AbstractConverter {
public:
  typedef typename ConverterImpl::Type Type;

  static bool assertType(Napi::Value jsVal) {
    return ConverterImpl::assertType(jsVal);
  }

  static Napi::Value wrap(Type val) {
    return ConverterImpl::wrap(val);
  }

  static Type unwrapUnchecked(Napi::Value jsVal) {
    return ConverterImpl::unwrapUnchecked(jsVal);
  }

  static bool unwrapTo(Type* val, Napi::Value jsVal) {
    if (ConverterImpl::unwrap(val, jsVal)) {
      Napi::Env env = jsVal.Env();
      auto msg = std::string("failed to unwrap value, expected ") + std::string(ConverterImpl::getTypeName());
      Napi::Error::New(env, msg).ThrowAsJavaScriptException();
      return true;
    }
    return false;
  }

  static bool arg(int argN, Type* val, const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    try {
      if (!hasArg(info, argN) || ConverterImpl::unwrap(val, info[argN])) {
        auto msg = std::string("expected argument ")
                                + std::to_string(argN)
                                + std::string(" to be of type ")
                                + std::string(ConverterImpl::getTypeName());
        Napi::Error::New(env, msg).ThrowAsJavaScriptException();
        return true;
      }
    } catch (const Napi::Error& e) {
      e.ThrowAsJavaScriptException();
      return true;
    }
    return false;
  }

  static bool optArg(int argN, Type* val, const Napi::CallbackInfo& info) {
    if (hasArg(info, argN) && info[argN].IsFunction()) {
      return false;
    }

    Napi::Env env = info.Env();
    try {
      if (hasArg(info, argN) && ConverterImpl::unwrap(val, info[argN])) {
        Napi::Error::New(env, Napi::String::New(env,
                                                std::string("expected argument ")
                                                    + std::to_string(argN)
                                                    + std::string(" to be of type ")
                                                    + std::string(ConverterImpl::getTypeName())))
            .ThrowAsJavaScriptException();
        return true;
      }
    } catch (const Napi::Error& e) {
      e.ThrowAsJavaScriptException();
      return true;
    }
    return false;
  }

  static bool prop(Type* val, const char* prop, Napi::Object opts) {
    if (!FF::hasOwnProperty(opts, prop)) {
      Napi::Env env = opts.Env();
      Napi::Error::New(env, Napi::String::New(env,
                                              std::string("expected object to have property: ") + std::string(prop)))
          .ThrowAsJavaScriptException();
      return true;
    }
    return AbstractConverter::optProp(val, prop, opts);
  }

  /**
   * @brief do the opt object contains the expoected property
   */
  static bool optProp(Type* val, const char* prop, Napi::Object opts) {
    Napi::Env env = opts.Env();
    try {
      if (FF::hasOwnProperty(opts, prop)
          && ConverterImpl::unwrap(val, opts.Get(prop))) {
          auto msg = std::string("expected property ") + prop + " to be of type " + ConverterImpl::getTypeName();
        Napi::Error::New(env, msg).ThrowAsJavaScriptException();
        return true;
      }
    } catch (const Napi::Error& e) {
      e.ThrowAsJavaScriptException();
      return true;
    }
    return false;
  }
};
} // namespace FF

#endif