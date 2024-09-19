#include <iostream>
#include <memory>
#include <napi.h>

#ifndef __FF_UTILS_H__
#define __FF_UTILS_H__

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

namespace FF {

static inline Napi::Function getFunction(Napi::FunctionReference fnTempl) {
  return fnTempl.Value();
}

static inline Napi::Object newInstance(Napi::FunctionReference ctor) {
  // can be Napi::MaybeOrValue<Napi::Object> or Napi::Maybe<Napi::Object>
#ifdef NODE_ADDON_API_ENABLE_MAYBE
  auto maybeObj = ctor.New({});
  if (maybeObj.IsNothing()) // maybeObj.IsNull() ||
  {
    // Handle the error appropriately, e.g., throw an exception or return a default object
    throw Napi::Error::New(ctor.Env(), "Failed to create new instance");
    // return Napi::Object::New(ctor.Env());
  }
  return maybeObj.Unwrap();
#else
  return ctor.New({});
#endif
}

static inline bool hasArg(const Napi::CallbackInfo& info, int argN) {
  return static_cast<size_t>(argN) < info.Length();
}

static inline bool isArgObject(const Napi::CallbackInfo& info, int argN) {
  return FF::hasArg(info, argN) && info[argN].IsObject() && !info[argN].IsArray() && !info[argN].IsFunction();
}

static inline Napi::String newString(Napi::Env env, std::string str) {
  return Napi::String::New(env, str);
}

static inline bool hasOwnProperty(Napi::Object obj, const char* prop) {
  // Napi::Maybe<bool> maybeHasProp = obj.HasOwnProperty(prop);
#ifdef NODE_ADDON_API_ENABLE_MAYBE
  auto maybeHasProp = obj.HasOwnProperty(prop);
  if (maybeHasProp.IsNothing()) {
    // Handle the error appropriately, e.g., throw an exception or return a default value
    throw Napi::Error::New(obj.Env(), "Failed to check property");
    return false;
  }
  return true;
#else
  return obj.HasOwnProperty(prop);
#endif
}

template <class TClass>
static inline TClass* unwrapNanObjectWrap(Napi::Object jsObj) {
  return Napi::ObjectWrap<TClass>::Unwrap(jsObj);
}

template <class TClass>
static inline TClass* unwrapNanObjectWrap(Napi::Value jsVal) {
  return unwrapNanObjectWrap<TClass>(jsVal.As<Napi::Object>());
}

} // namespace FF

#endif
