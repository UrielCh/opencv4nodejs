#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerTLD.h"

Napi::FunctionReference TrackerTLD::constructor;

Napi::Object TrackerTLD(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrackerTLD::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Tracker::Init(ctor);

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerTLD"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::Set(target, FF::newString(env, "TrackerTLD"), FF::getFunction(ctor));
};

void TrackerTLD::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerTLD::New");
  FF_ASSERT_CONSTRUCT_CALL();

  TrackerTLD* self = new TrackerTLD();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerTLD::create();
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerTLD::create();
#else
  self->tracker = cv::TrackerTLD::createTracker();
#endif
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
};

#endif
