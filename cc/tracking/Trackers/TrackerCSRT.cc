#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerCSRT.h"
#include "TrackerCSRTParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)

Napi::FunctionReference TrackerCSRT::constructor;

Napi::Object TrackerCSRT(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrackerCSRT::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Tracker::Init(ctor);
  TrackerCSRTParams::Init(env, exports);

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerCSRT"));


  (target).Set("TrackerCSRT", FF::getFunction(ctor));
};

void TrackerCSRT::New(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerCSRT::New");
  FF_ASSERT_CONSTRUCT_CALL();

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerCSRT::Params params;
#else
  cv::TrackerCSRT::Params params;
#endif
  if (TrackerCSRTParams::Converter::optArg(0, &params, info)) {
    return tryCatch.reThrow();
  }

  TrackerCSRT* self = new TrackerCSRT();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerCSRT::create(params);
#else
  self->tracker = cv::TrackerCSRT::create(params);
#endif
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif

#endif
