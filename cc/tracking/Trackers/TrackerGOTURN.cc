#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "TrackerGOTURN.h"

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)

Napi::FunctionReference TrackerGOTURN::constructor;

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)

void TrackerGOTURN::Clear(const Napi::CallbackInfo& info) {
}

void TrackerGOTURN::Init(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerGOTURN::Init");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }

  TrackerGOTURN::unwrapThis(info)->getTracker()->init(image, boundingBox);
}

void TrackerGOTURN::Update(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerGOTURN::Update");
  cv::Mat image;
  if (Mat::Converter::arg(0, &image, info)) {
    return tryCatch.reThrow();
  }

  cv::Rect rect;
  bool ret = false;

  try {
    ret = TrackerGOTURN::unwrapThis(info)->getTracker()->update(image, rect);
  } catch (std::exception& e) {
    return tryCatch.throwError(e.what());
  }

  if (ret) {
    return Rect::Converter::wrap(rect);
  } else {
    return env.Null();
  }
}

void TrackerGOTURN::GetModel(const Napi::CallbackInfo& info) {
  // TBD
}

#endif

Napi::Object TrackerGOTURN(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, TrackerGOTURN::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

#if CV_VERSION_GREATER_EQUAL(4, 5, 2)
  Napi::SetPrototypeMethod(ctor, "clear", TrackerGOTURN::Clear);
  Napi::SetPrototypeMethod(ctor, "init", TrackerGOTURN::Init);
  Napi::SetPrototypeMethod(ctor, "update", TrackerGOTURN::Update);
  Napi::SetPrototypeMethod(ctor, "getModel", TrackerGOTURN::GetModel);
#else
  Tracker::Init(ctor);
#endif
  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "TrackerGOTURN"));


  (target).Set("TrackerGOTURN", FF::getFunction(ctor));
};

void TrackerGOTURN::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "TrackerGOTURN::New");
  FF_ASSERT_CONSTRUCT_CALL();

  TrackerGOTURN* self = new TrackerGOTURN();
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  self->tracker = cv::TrackerGOTURN::create();
#else
  self->tracker = cv::TrackerGOTURN::createTracker();
#endif

  self->Wrap(info.Holder());
  return info.Holder();
};

#endif

#endif
