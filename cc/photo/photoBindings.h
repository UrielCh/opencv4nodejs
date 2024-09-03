#include "CvBinding.h"
#include "photo.h"

#ifndef __FF_PHOTOBINDINGS_H_
#define __FF_PHOTOBINDINGS_H_

namespace PhotoBindings {

struct FastNlMeansDenoisingColoredWorker : public CatchCvExceptionWorker {
public:
  cv::Mat src;
  float h = 3;
  float hColor = 3;
  int templateWindowSize = 7;
  int searchWindowSize = 21;

  cv::Mat returnValue;

  virtual ~FastNlMeansDenoisingColoredWorker() {
  }

  std::string executeCatchCvExceptionWorker() {
    cv::fastNlMeansDenoisingColored(src, returnValue, h, hColor, templateWindowSize, searchWindowSize);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Mat::Converter::wrap(returnValue);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        Mat::Converter::arg(0, &src, info));
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (
        FF::FloatConverter::optArg(1, &h, info) || FF::FloatConverter::optArg(2, &hColor, info) || FF::IntConverter::optArg(3, &templateWindowSize, info) || FF::IntConverter::optArg(4, &searchWindowSize, info));
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    return FF::isArgObject(info, 1);
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    Napi::Object opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    return (
        FF::FloatConverter::optProp(&h, "h", opts) || FF::FloatConverter::optProp(&hColor, "hColor", opts) || FF::IntConverter::optProp(&templateWindowSize, "templateWindowSize", opts) || FF::IntConverter::optProp(&searchWindowSize, "searchWindowSize", opts));
  }
};

struct InpaintWorker : public CatchCvExceptionWorker {
public:
  // required function arguments
  cv::Mat src;
  cv::Mat inpaintMask;
  double inpaintRadius;
  int flags;

  // function return value
  cv::Mat dst;

  virtual ~InpaintWorker() {
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        Mat::Converter::arg(0, &src, info) || Mat::Converter::arg(1, &inpaintMask, info) || FF::DoubleConverter::arg(2, &inpaintRadius, info) || FF::IntConverter::arg(3, &flags, info));
  }

  std::string executeCatchCvExceptionWorker() {
    cv::inpaint(
        src, inpaintMask, dst,
        inpaintRadius, flags);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Mat::Converter::wrap(dst);
  }
};

class SeamlessClone : public CvClassMethodBinding<Mat> {
public:
  virtual ~SeamlessClone() {
  }

  void createBinding(std::shared_ptr<FF::Value<cv::Mat>> self) {
    auto dst = req<Mat::Converter>();
    auto mask = req<Mat::Converter>();
    auto p = req<Point2::Converter>();
    auto flags = req<FF::IntConverter>();
    auto blend = ret<Mat::Converter>("blend");

    executeBinding = [=]() {
      cv::seamlessClone(self->ref(), dst->ref(), mask->ref(), p->ref(), blend->ref(), flags->ref());
    };
  };
};

} // namespace PhotoBindings

#endif