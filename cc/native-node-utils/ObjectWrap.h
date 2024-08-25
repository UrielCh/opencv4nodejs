#include "ArrayConverter.h"
#include "ArrayOfArraysConverter.h"
#include "InstanceConverter.h"
#include "TryCatch.h"
#include "utils.h"
#include <functional>

#ifndef __FF_OBJECT_WRAP_H__
#define __FF_OBJECT_WRAP_H__

namespace FF {

template <class TClass>
class ObjectWrapBase {
public:
  static TClass* unwrapClassPtrUnchecked(Napi::Value jsVal) {
    return unwrapNanObjectWrap<TClass>(jsVal);
  }

  static TClass* unwrapThis(const Napi::CallbackInfo& info) {
    return unwrapClassPtrUnchecked(info.This());
  }

  static TClass* unwrapThis(const Napi::PropertyDescriptor::GetterCallback& info) {
    return unwrapClassPtrUnchecked(info.This());
  }

  static TClass* unwrapThis(const Napi::PropertyDescriptor::SetterCallback& info) {
    return unwrapClassPtrUnchecked(info.This());
  }
};

template <class TClass, class T>
class ObjectWrapTemplate : public ObjectWrapBase<TClass> {
public:
  typedef ObjectWrapBase<TClass> super;

  T self;

  void setNativeObject(T obj) {
    self = obj;
  }

  typedef InstanceConverterImpl<TClass, T> ConverterImpl;
  typedef AbstractConverter<ConverterImpl> Converter;

  template <class CastType>
  class WithCastConverter : public AbstractConverter<InstanceConverterImpl<TClass, CastType>> {};

  template <class ElementCastType>
  class ArrayWithCastConverter : public ArrayConverterTemplate<ConverterImpl, ElementCastType> {};

  template <class ElementCastType>
  class ArrayOfArraysWithCastConverter : public ArrayOfArraysConverterTemplate<ConverterImpl, ElementCastType> {};

  typedef ArrayWithCastConverter<T> ArrayConverter;
  typedef ArrayOfArraysWithCastConverter<T> ArrayOfArraysConverter;

  template <class WorkerImpl>
  static void syncBinding(std::string name, const Napi::CallbackInfo& info) {
    auto worker = std::make_shared<WorkerImpl>();
    worker->setup(unwrapSelf(info));
    FF::executeSyncBinding(
        worker,
        std::string(TClass::getClassName()) + "::" + name,
        info);
  }

  template <class WorkerImpl>
  static void asyncBinding(std::string name, const Napi::CallbackInfo& info) {
    auto worker = std::make_shared<WorkerImpl>();
    worker->setup(unwrapSelf(info));
    FF::executeAsyncBinding(
        worker,
        std::string(TClass::getClassName()) + "::" + name + "Async",
        info);
  }

  static bool hasInstance(Napi::Value jsVal) {
    return TClass::ConverterImpl::assertType(jsVal);
  }

  static T unwrapSelf(const Napi::CallbackInfo& info) {
    return unwrapSelf(info.This());
  }

  static T unwrapSelf(const Napi::CallbackInfo& info) {
    return unwrapSelf(info.This().As<Napi::Object>());
  }

  static T unwrapSelf(const Napi::CallbackInfo& info) {
    return unwrapSelf(info.This().As<Napi::Object>());
  }

protected:
  typedef TClass ClassType;

  template <class TPropertyConverter>
  static void setter(
      const char* setterName,
      const Napi::CallbackInfo& info,
      Napi::Value value,
      void (*setProperty)(TClass*, typename TPropertyConverter::Type)) {
    FF::TryCatch tryCatch(setterName);
    typename TPropertyConverter::Type val;
    if (TPropertyConverter::unwrapTo(&val, value)) {
      return tryCatch.reThrow();
    }
    setProperty(super::unwrapThis(info.This().As<Napi::Object>()), val);
  }

  template <class TPropertyConverter>
  static Napi::Value getter(
      const Napi::CallbackInfo& info,
      typename TPropertyConverter::Type (*getProperty)(TClass*)) {
    Napi::Env env = info.Env();
    TClass* obj = super::unwrapThis(info);
    typename TPropertyConverter::Type property = getProperty(obj);
    return TPropertyConverter::wrap(env, property);
  }

  template <class ConstructorImpl>
  static void constructorBinding(const Napi::CallbackInfo& info) {
    FF::executeSyncBinding(
        std::make_shared<ConstructorImpl>(info),
        std::string(TClass::getClassName()) + "::Constructor",
        info);
  };

  class ConstructorBase : public BindingBase, public ISyncWorker {
  public:
    bool applyUnwrappers(const Napi::CallbackInfo& info) {
      if (!info.IsConstructCall()) {
        Nan::ThrowError("constructor has to be called with \"new\" keyword");
        return true;
      }
      return BindingBase::applyUnwrappers(info);
    }

    Napi::Value getReturnValue(const Napi::CallbackInfo& info) {
      TClass* self = new TClass();
      self->Wrap(info.Holder());
      self->setNativeObject(nativeObject);
      modifySelf(self);
      return info.Holder();
    }

    std::string execute() {
      try {
        nativeObject = executeBinding();
        return "";
      } catch (std::exception& e) {
        return std::string(e.what());
      }
    }

  protected:
    T nativeObject;
    std::function<T(void)> executeBinding;
    std::function<void(TClass* self)> modifySelf = [](TClass*) {};
  };

private:
  static T unwrapSelf(Napi::Object thisObj) {
    return super::unwrapClassPtrUnchecked(thisObj)->self;
  }
};

template <class TClass, class T>
class ObjectWrap : public ObjectWrapTemplate<TClass, T>, public Napi::ObjectWrap<ObjectWrap> {
public:
  void Wrap(Napi::Object object) {
    Nan::ObjectWrap::Wrap(object);
  }
};

} // namespace FF

#endif
