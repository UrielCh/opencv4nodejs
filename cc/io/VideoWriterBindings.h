#include "VideoWriter.h"

#ifndef __FF_VIDEOWRITERBINDINGS_H_
#define __FF_VIDEOWRITERBINDINGS_H_

namespace VideoWriterBindings {

struct NewWorker : CatchCvExceptionWorker {
public:
  std::string fileName;
  int fourccCode;
  double fps;
  cv::Size2d frameSize;
  bool isColor = true;

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        FF::StringConverter::arg(0, &fileName, info) || FF::IntConverter::arg(1, &fourccCode, info) || FF::DoubleConverter::arg(2, &fps, info) || Size::Converter::arg(3, &frameSize, info));
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return FF::BoolConverter::optArg(4, &isColor, info);
  }

  std::string executeCatchCvExceptionWorker() {
    return "";
  }
};

struct GetWorker : public CatchCvExceptionWorker {
public:
  cv::VideoWriter self;

  GetWorker(cv::VideoWriter self) {
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

struct SetWorker : public CatchCvExceptionWorker {
public:
  cv::VideoWriter self;

  SetWorker(cv::VideoWriter self) {
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
    return Nan::New(ret);
  }
};

struct FourccWorker : CatchCvExceptionWorker {
public:
  std::string fourcc;

  int code;

  virtual ~FourccWorker() {
  }

  std::string executeCatchCvExceptionWorker() {
    code = cv::VideoWriter::fourcc(fourcc.at(0), fourcc.at(1), fourcc.at(2), fourcc.at(3));
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return FF::IntConverter::wrap(code);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return FF::StringConverter::arg(0, &fourcc, info);
  }
};

struct WriteWorker : CatchCvExceptionWorker {
public:
  cv::VideoWriter writer;

  WriteWorker(cv::VideoWriter writer) {
    this->writer = writer;
  }

  virtual ~WriteWorker() {
  }

  cv::Mat frame;

  std::string executeCatchCvExceptionWorker() {
    writer.write(frame);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return FF::BoolConverter::wrap(true);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return Mat::Converter::arg(0, &frame, info);
  }
};

} // namespace VideoWriterBindings

#endif