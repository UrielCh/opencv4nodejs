#include "CascadeClassifier.h"

#ifndef __FF_CASCADECLASSIFIERBINDINGS_H_
#define __FF_CASCADECLASSIFIERBINDINGS_H_

namespace CascadeClassifierBindings {

struct NewWorker : CatchCvExceptionWorker {
public:
  std::string xmlFilePath;

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return FF::StringConverter::arg(0, &xmlFilePath, info);
  }

  std::string executeCatchCvExceptionWorker() {
    return "";
  }
};

struct DetectMultiScaleWorker : CatchCvExceptionWorker {
public:
  cv::CascadeClassifier classifier;
  bool isGpu;

  virtual ~DetectMultiScaleWorker() {
  }

  DetectMultiScaleWorker(cv::CascadeClassifier classifier, bool isGpu = false) {
    this->classifier = classifier;
    this->isGpu = isGpu;
  }

  cv::Mat img;
  double scaleFactor = 1.1;
  uint minNeighbors = 3;
  uint flags = 0;
  cv::Size2d minSize;
  cv::Size2d maxSize;

  std::vector<cv::Rect> objectRects;
  std::vector<int> numDetections;

  std::string executeCatchCvExceptionWorker() {
    if (isGpu) {
      cv::UMat oclMat = img.getUMat(cv::ACCESS_READ);
      classifier.detectMultiScale(oclMat, objectRects, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize);
    } else {
      classifier.detectMultiScale(img, objectRects, numDetections, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize);
    }
    return "";
  }

  Napi::Value getReturnValue() {
    if (isGpu) {
      return Rect::ArrayWithCastConverter<cv::Rect>::wrap(objectRects);
    } else {
      Napi::Object ret = Nan::New<v8::Object>();
      Nan::Set(ret, FF::newString(env, "objects"), Rect::ArrayWithCastConverter<cv::Rect>::wrap(objectRects));
      Nan::Set(ret, FF::newString(env, "numDetections"), FF::IntArrayConverter::wrap(numDetections));
      return ret;
    }
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return Mat::Converter::arg(0, &img, info);
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (
        FF::DoubleConverter::optArg(1, &scaleFactor, info) || FF::UintConverter::optArg(2, &minNeighbors, info) || FF::UintConverter::optArg(3, &flags, info) || Size::Converter::optArg(4, &minSize, info) || Size::Converter::optArg(5, &maxSize, info));
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    return FF::isArgObject(info, 1);
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    Napi::Object opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    return (
        FF::DoubleConverter::optProp(&scaleFactor, "scaleFactor", opts) || FF::UintConverter::optProp(&minNeighbors, "minNeighbors", opts) || FF::UintConverter::optProp(&flags, "flags", opts) || Size::Converter::optProp(&minSize, "minSize", opts) || Size::Converter::optProp(&maxSize, "maxSize", opts));
  }
};

struct DetectMultiScaleWithRejectLevelsWorker : public DetectMultiScaleWorker {
public:
  DetectMultiScaleWithRejectLevelsWorker(cv::CascadeClassifier classifier, bool isGpu = false)
      : DetectMultiScaleWorker(classifier, isGpu) {
  }

  std::vector<int> rejectLevels;
  std::vector<double> levelWeights;

  std::string executeCatchCvExceptionWorker() {
    if (isGpu) {
      cv::UMat oclMat = img.getUMat(cv::ACCESS_READ);
      classifier.detectMultiScale(oclMat, objectRects, rejectLevels, levelWeights, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize, true);
    } else {
      classifier.detectMultiScale(img, objectRects, rejectLevels, levelWeights, scaleFactor, (int)minNeighbors, (int)flags, minSize, maxSize, true);
    }
    return "";
  }

  Napi::Value getReturnValue() {
    Napi::Object ret = Nan::New<v8::Object>();
    Nan::Set(ret, FF::newString(env, "objects"), Rect::ArrayWithCastConverter<cv::Rect>::wrap(objectRects));
    Nan::Set(ret, FF::newString(env, "rejectLevels"), FF::IntArrayConverter::wrap(rejectLevels));
    Nan::Set(ret, FF::newString(env, "levelWeights"), FF::DoubleArrayConverter::wrap(levelWeights));
    return ret;
  }
};

} // namespace CascadeClassifierBindings

#endif