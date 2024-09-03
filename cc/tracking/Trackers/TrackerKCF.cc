#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerKCF.h"
#include "TrackerKCFParams.h"

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

Napi::FunctionReference TrackerKCF::constructor;

Napi::Object TrackerKCF(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrackerKCF::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  Tracker::Init(ctor);
  TrackerKCFParams::Init(env, exports);

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerKCF"));


  (target).Set("TrackerKCF", FF::getFunction(ctor));
};

void TrackerKCF::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerKCF::New");
  FF_ASSERT_CONSTRUCT_CALL();

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  cv::legacy::TrackerKCF::Params params;
#else
  cv::TrackerKCF::Params params;
#endif
  if (TrackerKCFParams::Converter::optArg(0, &params, info)) {
    return tryCatch.reThrow();
  }

  TrackerKCF* self = new TrackerKCF();
#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  self->tracker = cv::legacy::TrackerKCF::create(params);
#elif CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerKCF::create(params);
#else
  self->tracker = cv::TrackerKCF::createTracker(params);
#endif
  self->Wrap(info.Holder());
  return info.Holder();
};

#endif

#endif
