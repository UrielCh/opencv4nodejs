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
  Napi::Maybe<Napi::Object> maybeObj = ctor.New({});
  if (maybeObj.IsNothing()) {
    // Handle the error appropriately, e.g., throw an exception or return a default object
    Napi::Error::New(ctor.Env(), "Failed to create new instance").ThrowAsJavaScriptException();
    return Napi::Object::New(ctor.Env());
  }
  return maybeObj.Unwrap();
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
  Napi::Maybe<bool> maybeHasProp = obj.HasOwnProperty(prop);
  if (maybeHasProp.IsNothing()) {
    // Handle the error appropriately, e.g., throw an exception or return a default value
    Napi::Error::New(obj.Env(), "Failed to check property").ThrowAsJavaScriptException();
    return false;
  }
  return maybeHasProp.Unwrap();
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
