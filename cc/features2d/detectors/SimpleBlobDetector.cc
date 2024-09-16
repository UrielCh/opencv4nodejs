#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "SimpleBlobDetector.h"
#include "SimpleBlobDetectorParams.h"

Napi::FunctionReference SimpleBlobDetector::constructor;

Napi::Object SimpleBlobDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, SimpleBlobDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  SimpleBlobDetectorParams::Init(env, exports);
  FeatureDetector::Init(env, exports);
  constructor.Reset(ctor);
  ctor->SetClassName(Napi::String::New(env, "SimpleBlobDetector"));


  target.Set("SimpleBlobDetector", FF::getFunction(ctor));
};

void SimpleBlobDetector::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "SimpleBlobDetector::New");
  FF_ASSERT_CONSTRUCT_CALL();

  cv::SimpleBlobDetector::Params params;
  if (SimpleBlobDetectorParams::Converter::arg(0, &params, info)) {
    return tryCatch.reThrow();
  }

  SimpleBlobDetector* self = new SimpleBlobDetector();
  self->Wrap(info.Holder());
  self->detector = cv::SimpleBlobDetector::create(params);
  return info.Holder();
}

#endif
