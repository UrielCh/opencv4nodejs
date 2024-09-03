#include "opencv_modules.h"

#ifdef HAVE_OPENCV_VIDEO

#include "BackgroundSubtractor.h"
#include "Mat.h"

void BackgroundSubtractor::Init(Napi::FunctionReference ctor) {
  Nan::SetPrototypeMethod(ctor, "apply", BackgroundSubtractor::Apply);
};

void BackgroundSubtractor::Apply(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "BackgroundSubtractor::Apply");
  cv::Mat frame;
  double learningRate = -1;
  if (
      Mat::Converter::arg(0, &frame, info) || FF::DoubleConverter::optArg(1, &learningRate, info)) {
    return tryCatch.reThrow();
  }

  BackgroundSubtractor* self = BackgroundSubtractor::unwrapThis(info);
  self->getSubtractor()->apply(frame, self->fgMask, learningRate);
  info.GetReturnValue().Set(Mat::Converter::wrap(self->fgMask));
}

#endif