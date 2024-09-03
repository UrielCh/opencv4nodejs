#include "opencv_modules.h"

#ifdef HAVE_OPENCV_OBJDETECT

#include "DetectionROI.h"

Napi::FunctionReference DetectionROI::constructor;

Napi::Object DetectionROI(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, DetectionROI::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "DetectionROI"));


  Napi::SetAccessor(instanceTemplate, FF::newString(env, "scale"), scale_getter, scale_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "locations"), locations_getter, locations_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "confidences"), confidences_getter, confidences_setter);

  (target).Set("DetectionROI", FF::getFunction(ctor));
};

void DetectionROI::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "DetectionROI::New");
  FF_ASSERT_CONSTRUCT_CALL();
  DetectionROI* self = new DetectionROI();
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif
