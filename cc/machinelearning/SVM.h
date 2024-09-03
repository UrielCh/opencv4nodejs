#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "ParamGrid.h"
#include "TrainData.h"
#include "macros.h"
#include <opencv2/ml.hpp>

#ifndef __FF_SVM_H__
#define __FF_SVM_H__

class SVM : public FF::ObjectWrap<SVM, cv::Ptr<cv::ml::SVM>> {
public:
  static Napi::FunctionReference constructor;;

  static const char* getClassName() {
    return "SVM";
  }

  void setParams(Napi::Object params);

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  FF_GETTER_CUSTOM(c, FF::DoubleConverter, self->getC());
  FF_GETTER_CUSTOM(coef0, FF::DoubleConverter, self->getCoef0());
  FF_GETTER_CUSTOM(degree, FF::DoubleConverter, self->getDegree());
  FF_GETTER_CUSTOM(gamma, FF::DoubleConverter, self->getGamma());
  FF_GETTER_CUSTOM(nu, FF::DoubleConverter, self->getNu());
  FF_GETTER_CUSTOM(p, FF::DoubleConverter, self->getP());
  FF_GETTER_CUSTOM(kernelType, FF::IntConverter, self->getKernelType());
  FF_GETTER_CUSTOM(varCount, FF::IntConverter, self->getVarCount());
  FF_GETTER_CUSTOM(isTrained, FF::BoolConverter, self->isTrained());
  FF_GETTER_CUSTOM(classWeights, Mat::Converter, self->getClassWeights());

  // TODO custom kernel

  static void New(const Napi::CallbackInfo& info);
  static void SetParams(const Napi::CallbackInfo& info);
  static void Predict(const Napi::CallbackInfo& info);
  static void GetSupportVectors(const Napi::CallbackInfo& info);
  static void GetUncompressedSupportVectors(const Napi::CallbackInfo& info);
  static void GetDecisionFunction(const Napi::CallbackInfo& info);
  static void CalcError(const Napi::CallbackInfo& info);
  static void Save(const Napi::CallbackInfo& info);
  static void Load(const Napi::CallbackInfo& info);
  static void Train(const Napi::CallbackInfo& info);
  static void TrainAsync(const Napi::CallbackInfo& info);
  static void TrainAuto(const Napi::CallbackInfo& info);
  static void TrainAutoAsync(const Napi::CallbackInfo& info);
};

#endif