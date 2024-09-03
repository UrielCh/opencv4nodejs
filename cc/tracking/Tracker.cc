#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TRACKING

#include "Tracker.h"

void Tracker::Init(Napi::FunctionReference ctor) {
  Nan::SetPrototypeMethod(ctor, "clear", Tracker::Clear);
  Nan::SetPrototypeMethod(ctor, "init", Tracker::Init);
  Nan::SetPrototypeMethod(ctor, "update", Tracker::Update);
  Nan::SetPrototypeMethod(ctor, "getModel", Tracker::GetModel);
};

void Tracker::Clear(const Napi::CallbackInfo& info) {
  Tracker::unwrapThis(info)->getTracker()->clear();
}

void Tracker::Init(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Tracker::Init");
  cv::Mat image;
  cv::Rect2d boundingBox;
  if (
      Mat::Converter::arg(0, &image, info) || Rect::Converter::arg(1, &boundingBox, info)) {
    return tryCatch.reThrow();
  }

  bool ret = Tracker::unwrapThis(info)->getTracker()->init(image, boundingBox);
  info.GetReturnValue().Set(Nan::New(ret));
}

void Tracker::Update(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Tracker::Update");
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
    info.GetReturnValue().Set(Rect::Converter::wrap(rect));
  } else {
    info.GetReturnValue().Set(Nan::Null());
  }
}

void Tracker::GetModel(const Napi::CallbackInfo& info) {
  // TBD
}

#endif