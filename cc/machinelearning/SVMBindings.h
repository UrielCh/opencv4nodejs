#include "SVM.h"

#ifndef __FF_SVMBINDINGS_H_
#define __FF_SVMBINDINGS_H_

namespace SVMBindings {

struct TrainFromTrainDataWorker : CatchCvExceptionWorker {
public:
  cv::Ptr<cv::ml::SVM> svm;

  virtual ~TrainFromTrainDataWorker() {
  }

  TrainFromTrainDataWorker(cv::Ptr<cv::ml::SVM> svm) {
    this->svm = svm;
  }

  cv::Ptr<cv::ml::TrainData> trainData;
  uint flags;

  bool ret;

  std::string executeCatchCvExceptionWorker() {
    ret = svm->train(trainData, (int)flags);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Napi::New(env, ret);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return TrainData::Converter::arg(0, &trainData, info);
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return FF::UintConverter::optArg(1, &flags, info);
  }
};

struct TrainFromMatWorker : CatchCvExceptionWorker {
public:
  cv::Ptr<cv::ml::SVM> svm;

  virtual ~TrainFromMatWorker() {
  }

  TrainFromMatWorker(cv::Ptr<cv::ml::SVM> svm) {
    this->svm = svm;
  }

  cv::Mat samples;
  uint layout;
  cv::Mat responses;

  bool ret;

  std::string executeCatchCvExceptionWorker() {
    ret = svm->train(samples, (int)layout, responses);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Napi::New(env, ret);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        Mat::Converter::arg(0, &samples, info) || FF::UintConverter::arg(1, &layout, info) || Mat::Converter::arg(2, &responses, info));
  }
};

struct TrainAutoWorker : CatchCvExceptionWorker {
public:
  cv::Ptr<cv::ml::SVM> svm;

  virtual ~TrainAutoWorker() {
  }

  TrainAutoWorker(cv::Ptr<cv::ml::SVM> svm) {
    this->svm = svm;
  }

  cv::Ptr<cv::ml::TrainData> trainData;
  uint kFold = 10;
  cv::ml::ParamGrid cGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::C);
  cv::ml::ParamGrid gammaGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::GAMMA);
  cv::ml::ParamGrid pGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::P);
  cv::ml::ParamGrid nuGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::NU);
  cv::ml::ParamGrid coeffGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::COEF);
  cv::ml::ParamGrid degreeGrid = cv::ml::SVM::getDefaultGrid(cv::ml::SVM::DEGREE);
  bool balanced = false;

  bool ret;

  std::string executeCatchCvExceptionWorker() {
    ret = svm->trainAuto(trainData, (int)kFold, cGrid, gammaGrid, pGrid, nuGrid, coeffGrid, degreeGrid, balanced);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    return Napi::New(env, ret);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return TrainData::Converter::arg(0, &trainData, info);
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (
        FF::UintConverter::optArg(1, &kFold, info) || ParamGrid::Converter::optArg(2, &cGrid, info) || ParamGrid::Converter::optArg(3, &gammaGrid, info) || ParamGrid::Converter::optArg(4, &pGrid, info) || ParamGrid::Converter::optArg(5, &nuGrid, info) || ParamGrid::Converter::optArg(6, &coeffGrid, info) || ParamGrid::Converter::optArg(7, &degreeGrid, info) || FF::BoolConverter::optArg(8, &balanced, info));
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    return FF::isArgObject(info, 1);
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    Napi::Object opts = info[1].As<Napi::Object>();
    return (
        FF::UintConverter::optProp(&kFold, "kFold", opts) || ParamGrid::Converter::optProp(&cGrid, "cGrid", opts) || ParamGrid::Converter::optProp(&gammaGrid, "gammaGrid", opts) || ParamGrid::Converter::optProp(&pGrid, "pGrid", opts) || ParamGrid::Converter::optProp(&nuGrid, "nuGrid", opts) || ParamGrid::Converter::optProp(&coeffGrid, "coeffGrid", opts) || ParamGrid::Converter::optProp(&degreeGrid, "degreeGrid", opts) || FF::BoolConverter::optProp(&balanced, "balanced", opts));
  }
};

} // namespace SVMBindings

#endif