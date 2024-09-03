#include "VideoCapture.h"

#ifndef __FF_VIDEOCAPTUREBINDINGS_H_
#define __FF_VIDEOCAPTUREBINDINGS_H_

namespace VideoCaptureBindings {

struct GetWorker : public CatchCvExceptionWorker {
public:
  cv::VideoCapture self;

  GetWorker(cv::VideoCapture self) {
    this->self = self;
  }

  virtual ~GetWorker() {
  }

  int prop;
  double val;

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        FF::IntConverter::arg(0, &prop, info));
  }

  std::string executeCatchCvExceptionWorker() {
    val = self.get(prop);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return FF::DoubleConverter::wrap(val);
  }
};

struct ReadWorker : public CatchCvExceptionWorker {
public:
  cv::VideoCapture self;

  ReadWorker(cv::VideoCapture self) {
    this->self = self;
  }

  virtual ~ReadWorker() {
  }

  cv::Mat frame;

  std::string executeCatchCvExceptionWorker() {
    self.read(frame);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Mat::Converter::wrap(frame);
  }
};

struct SetWorker : public CatchCvExceptionWorker {
public:
  cv::VideoCapture self;

  SetWorker(cv::VideoCapture self) {
    this->self = self;
  }

  virtual ~SetWorker() {
  }

  // required fn args
  int prop;
  double value;
  bool ret;

  std::string executeCatchCvExceptionWorker() {
    ret = this->self.set(prop, value);
    return "";
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        FF::IntConverter::arg(0, &prop, info) || FF::DoubleConverter::arg(1, &value, info));
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Napi::New(env, ret);
  }
};

} // namespace VideoCaptureBindings

#endif