#include "ImgHashBase.h"

#ifndef __FF_IMGHASHBASEBINDINGS_H_
#define __FF_IMGHASHBASEBINDINGS_H_

namespace ImgHashBaseBindings {

struct CompareWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::img_hash::ImgHashBase> self;

  CompareWorker(cv::Ptr<cv::img_hash::ImgHashBase> self) {
    this->self = self;
  }

  std::vector<uchar> hashOne;
  std::vector<uchar> hashTwo;
  double returnValue;

  std::string executeCatchCvExceptionWorker() {
    returnValue = self->compare(hashOne, hashTwo);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    Napi::Value ret = FF::DoubleConverter::wrap(returnValue);
    return ret;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (FF::UcharArrayConverter::arg(0, &hashOne, info) || FF::UcharArrayConverter::arg(1, &hashTwo, info));
  }

  virtual ~CompareWorker() {
  }
};

struct ComputeWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::img_hash::ImgHashBase> self;

  ComputeWorker(cv::Ptr<cv::img_hash::ImgHashBase> self) {
    this->self = self;
  }

  cv::Mat inputArr;
  std::vector<uchar> outputArr;

  std::string executeCatchCvExceptionWorker() {
    self->compute(inputArr, outputArr);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    Napi::Value ret = FF::UcharArrayConverter::wrap(outputArr);
    return ret;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (Mat::Converter::arg(0, &inputArr, info));
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (FF::UcharArrayConverter::optArg(1, &outputArr, info));
  }

  virtual ~ComputeWorker() {
  }
};

} // namespace ImgHashBaseBindings

#endif
