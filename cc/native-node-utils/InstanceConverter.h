#include "AbstractConverter.h"
#include "UnwrapperBase.h"
#include "utils.h"

#ifndef __FF_INSTANCE_CONVERTER_H__
#define __FF_INSTANCE_CONVERTER_H__

namespace FF {

template <class TClass, class T>
class InstanceConverterImpl : public UnwrapperBase<InstanceConverterImpl<TClass, T>, T> {
public:
  typedef T Type;

  static std::string getTypeName() {
    return TClass::getClassName();
  }

  static bool assertType(Napi::Env& env, Napi::Value& jsVal) {
    return !jsVal.IsNull() && !jsVal.IsUndefined() && Napi::Object::New(env, TClass::constructor)->HasInstance(jsVal);
  }

  static T unwrapUnchecked(Napi::Value jsVal) {
    return unwrapNanObjectWrap<TClass>(jsVal)->self;
  }

  static Napi::Value wrap(Napi::Env& env, T val) {
    Napi::Object jsObj = FF::newInstance(Napi::Object::New(env, TClass::constructor));
    unwrapNanObjectWrap<TClass>(jsObj)->setNativeObject(val);
    return jsObj;
  }
};

} // namespace FF

#endif