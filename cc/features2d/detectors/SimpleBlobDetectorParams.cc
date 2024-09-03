#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "SimpleBlobDetectorParams.h"

Napi::FunctionReference SimpleBlobDetectorParams::constructor;

Napi::Object SimpleBlobDetectorParams(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, SimpleBlobDetectorParams::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "SimpleBlobDetectorParams"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString(env, "blobColor"), blobColor_getter, blobColor_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "filterByArea"), filterByArea_getter, filterByArea_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "filterByCircularity"), filterByCircularity_getter, filterByCircularity_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "filterByColor"), filterByColor_getter, filterByColor_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "filterByConvexity"), filterByConvexity_getter, filterByConvexity_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "filterByInertia"), filterByInertia_getter, filterByInertia_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "maxArea"), maxArea_getter, maxArea_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "maxCircularity"), maxCircularity_getter, maxCircularity_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "maxConvexity"), maxConvexity_getter, maxConvexity_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "maxInertiaRatio"), maxInertiaRatio_getter, maxInertiaRatio_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "maxThreshold"), maxThreshold_getter, maxThreshold_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "minArea"), minArea_getter, minArea_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "minCircularity"), minCircularity_getter, minCircularity_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "minConvexity"), minConvexity_getter, minConvexity_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "minDistBetweenBlobs"), minDistBetweenBlobs_getter, minDistBetweenBlobs_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "minInertiaRatio"), minInertiaRatio_getter, minInertiaRatio_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "minRepeatability"), minRepeatability_getter, minRepeatability_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "minThreshold"), minThreshold_getter, minThreshold_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "thresholdStep"), thresholdStep_getter, thresholdStep_setter);

  Nan::Set(target, FF::newString(env, "SimpleBlobDetectorParams"), FF::getFunction(ctor));
};

void SimpleBlobDetectorParams::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "SimpleBlobDetectorParams::New");
  FF_ASSERT_CONSTRUCT_CALL();
  SimpleBlobDetectorParams* self = new SimpleBlobDetectorParams();
  self->self = cv::SimpleBlobDetector::Params();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif
