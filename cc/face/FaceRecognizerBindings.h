#include "FaceRecognizer.h"

#ifndef __FF_FACERECOGNIZERBINDINGS_H_
#define __FF_FACERECOGNIZERBINDINGS_H_

namespace FaceRecognizerBindings {
struct NewWorker : public FF::SimpleWorker {
public:
  int num_components = 0;
  double threshold = DBL_MAX;

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (
        FF::IntConverter::optArg(0, &num_components, info) || FF::DoubleConverter::optArg(1, &threshold, info));
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    return FF::isArgObject(info, 0);
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    Napi::Object opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    return (
        FF::IntConverter::optProp(&num_components, "num_components", opts) || FF::DoubleConverter::optProp(&threshold, "threshold", opts));
  }
};

struct TrainWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::face::FaceRecognizer> self;
  TrainWorker(cv::Ptr<cv::face::FaceRecognizer> self) {
    this->self = self;
  }
  virtual ~TrainWorker() {
  }

  std::vector<cv::Mat> images;
  std::vector<int> labels;

  std::string executeCatchCvExceptionWorker() {
    self->train(images, labels);
    return "";
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        Mat::ArrayConverter::arg(0, &images, info) || FF::IntArrayConverter::arg(1, &labels, info));
  }
};

struct PredictWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::face::FaceRecognizer> self;
  PredictWorker(cv::Ptr<cv::face::FaceRecognizer> self) {
    this->self = self;
  }
  virtual ~PredictWorker() {
  }

  cv::Mat image;
  int label;
  double confidence;

  std::string executeCatchCvExceptionWorker() {
    self->predict(image, label, confidence);
    return "";
  }

  Napi::Value getReturnValue() {
    Napi::Object ret = Nan::New<v8::Object>();
    Nan::Set(ret, Nan::New("label").ToLocalChecked(), Nan::New(label));
    Nan::Set(ret, Nan::New("confidence").ToLocalChecked(), Nan::New(confidence));
    return ret;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        Mat::Converter::arg(0, &image, info));
  }
};

} // namespace FaceRecognizerBindings

#endif