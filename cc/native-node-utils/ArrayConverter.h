#include <napi.h>

#ifndef __FF_ARRAY_CONVERTER_H__
#define __FF_ARRAY_CONVERTER_H__

namespace FF {

template <class ElementConverterImpl, class ElementCastType>
class ArrayConverterImpl {
public:
  typedef std::vector<ElementCastType> Type;

  static std::string getTypeName() {
    return std::string("array of ") + ElementConverterImpl::getTypeName();
  }

  static bool assertType(Napi::Value& jsVal) {
    return jsVal.IsArray();
  }

  static Type unwrapUnchecked(Napi::Value& jsVal) {
    Type vec;
    unwrap(&vec, jsVal);
    return vec;
  }

  static bool unwrap(Type* vec, const Napi::Value& jsVal) {
    if (!jsVal.IsArray()) {
      return true;
    }

    Napi::Array jsArr = jsVal.As<Napi::Array>();
    Napi::Env env = jsVal.Env();
    for (uint32_t i = 0; i < jsArr.Length(); i++) {
      #ifdef NODE_ADDON_API_ENABLE_MAYBE
      // Napi::MaybeOrValue<Napi::Value> maybeElement = jsArr.Get(i);
      // if (maybeElement.IsNothing()) {
      //   throw Napi::TypeError::New(env, "Failed to get element from array");
      //   return true;
      // }
      // Napi::Value element = maybeElement.Unwrap();
      #else
      Napi::Value element = jsArr.Get(i);
      #endif
      if (!ElementConverterImpl::assertType(element)) {
        throw Napi::TypeError::New(env,
                             "expected array element at index " + std::to_string(i) + " to be of type " + ElementConverterImpl::getTypeName());
      }

      ElementCastType obj = (ElementCastType)ElementConverterImpl::unwrapUnchecked(element);
      vec->push_back(obj);
    }

    return false;
  }

  static Napi::Value wrap(Napi::Env env, Type vec) {
    Napi::Array jsArr = Napi::Array::New(env, vec.size());
    for (size_t i = 0; i < jsArr.Length(); i++) {
      jsArr.Set(i, ElementConverterImpl::wrap(vec.at(i)));
    }
    return jsArr;
  }
};

} // namespace FF
#endif
