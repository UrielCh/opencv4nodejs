#include "FeatureDetector.h"

#ifndef __FF_FEATUREDETECTORBINDINGS_H_
#define __FF_FEATUREDETECTORBINDINGS_H_

namespace FeatureDetectorBindings {

struct DetectWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::FeatureDetector> det;

  DetectWorker(cv::Ptr<cv::FeatureDetector> _det) {
    this->det = _det;
  }

  virtual ~DetectWorker() {
  }

  cv::Mat img;
  cv::Mat mask;
  std::vector<cv::KeyPoint> kps;

  std::string executeCatchCvExceptionWorker() {
    det->detect(img, kps, mask);
    return "";
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return Mat::Converter::arg(0, &img, info);
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (
        Mat::Converter::optArg(1, &mask, info));
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return KeyPoint::ArrayConverter::wrap(kps);
  }
};

struct ComputeWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::FeatureDetector> det;

  ComputeWorker(cv::Ptr<cv::FeatureDetector> _det) {
    this->det = _det;
  }

  virtual ~ComputeWorker() {
  }

  cv::Mat img;
  std::vector<cv::KeyPoint> kps;
  cv::Mat desc;

  std::string executeCatchCvExceptionWorker() {
    det->compute(img, kps, desc);
    return "";
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        Mat::Converter::arg(0, &img, info)
        || KeyPoint::ArrayConverter::arg(1, &kps, info));
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Mat::Converter::wrap(desc);
  }
};

} // namespace FeatureDetectorBindings

#endif