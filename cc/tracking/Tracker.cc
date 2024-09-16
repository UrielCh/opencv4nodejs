#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "Tracker.h"

void Tracker::Init(Napi::Env env, Napi::Object exports) {
  Napi::SetPrototypeMethod(ctor, "clear", Tracker::Clear);
  Napi::SetPrototypeMethod(ctor, "init", Tracker::Init);
  Napi::SetPrototypeMethod(ctor, "update", Tracker::Update);
  Napi::SetPrototypeMethod(ctor, "getModel", Tracker::GetModel);
};

void Tracker::Clear(const Napi::CallbackInfo& info) {
  Tracker::unwrapThis(info)->getTracker()->clear();
}

Napi : Value Tracker::Init(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Tracker::Init");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }

  bool ret = Tracker::unwrapThis(info)->getTracker()->init(image, boundingBox);
  return Napi::New(env, ret);
}

Napi : Value Tracker::Update(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Tracker::Update");
  cv::Mat image;
  if (Mat::Converter::arg(0, &image, info)) {
    return tryCatch.reThrow();
  }

  cv::Rect2d rect;
  bool ret = false;

  try {
    ret = Tracker::unwrapThis(info)->getTracker()->update(image, rect);
  } catch (std::exception& e) {
    return tryCatch.throwError(e.what());
  }

  if (ret) {
    return Rect::Converter::wrap(rect);
  } else {
    return env.Null();
  }
}

void Tracker::GetModel(const Napi::CallbackInfo& info) {
  // TBD
}

#endif