#include "opencv_modules.h"

#ifdef HAVE_OPENCV_OBJDETECT

#include "DetectionROI.h"

Nan::Persistent<v8::FunctionTemplate> DetectionROI::constructor;

NAN_MODULE_INIT(DetectionROI::Init) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(DetectionROI::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "DetectionROI"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString(env, "scale"), scale_getter, scale_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "locations"), locations_getter, locations_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "confidences"), confidences_getter, confidences_setter);

  Nan::Set(target, FF::newString(env, "DetectionROI"), FF::getFunction(ctor));
};

NAN_METHOD(DetectionROI::New) {
  FF::TryCatch tryCatch("DetectionROI::New");
  FF_ASSERT_CONSTRUCT_CALL();
  DetectionROI* self = new DetectionROI();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif
