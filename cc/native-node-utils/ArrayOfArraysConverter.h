#include "ArrayConverter.h"

#ifndef __FF_ARRAY_OF_ARRAYS_CONVERTER_H__
#define __FF_ARRAY_OF_ARRAYS_CONVERTER_H__

namespace FF {

template <class ElementConverterImpl, class ElementCastType>
class ArrayOfArraysConverterImpl : private ArrayConverterImpl<ElementConverterImpl, ElementCastType> {
public:
  typedef std::vector<std::vector<ElementCastType>> Type;
  typedef ArrayConverterImpl<ElementConverterImpl, ElementCastType> super;

  static std::string getTypeName() {
    return std::string("array of arrays of ") + ElementConverterImpl::getTypeName();
  }

  static bool assertType(Napi::Value& jsVal) {
    return jsVal.IsArray();
  }

  static Type unwrapUnchecked(Napi::Value& jsVal) {
    Type vecOfVecs;
    unwrap(&vecOfVecs, jsVal);
    return vecOfVecs;
  }

  static bool unwrap(Type* vecOfVecs, Napi::Value& jsVal) {
    if (!jsVal.IsArray()) {
      return true;
    }

    Napi::Array jsArr = jsVal.As<Napi::Array>();
    Napi::Env env = jsVal.Env();
    for (uint32_t i = 0; i < jsArr.Length(); i++) {
      std::vector<ElementCastType> vec;
      Napi::HandleScope scope(env);
      // Napi::Value element = jsArr.Get(i);
      Napi::MaybeOrValue<Napi::Value> maybeElement = jsArr.Get(i);
      if (maybeElement.IsEmpty()) {
        // Handle the error case
        Napi::Error::New(env, "Element is empty").ThrowAsJavaScriptException();
        return env.Null();
      }
      Napi::Value element = maybeElement.Unwrap();
      if (super::unwrap(&vec, element)) {
        Napi::Error::New(env, "Error unwrapping element").ThrowAsJavaScriptException();
        return true;
      }
      vecOfVecs->push_back(vec);
    }
    return false;
  }

  static Napi::Value wrap(Type vec) {
    Napi::Env env = Napi::Env::GetCurrent();
    Napi::Array jsArr = Napi::Array::New(env, vec.size());
    for (uint i = 0; i < jsArr.Length(); i++) {
      jsArr.Set(i, super::wrap(vec.at(i)));
    }
    return jsArr;
  }
};

} // namespace FF

#endif
