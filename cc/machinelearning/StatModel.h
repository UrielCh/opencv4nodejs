#include "macros.h"
#include <opencv2/ml.hpp>

#ifndef __FF_STATMODEL_H__
#define __FF_STATMODEL_H__

class StatModel : public Napi::ObjectWrap<StatModel> {
public:
  cv::Ptr<cv::ml::SVM> svm;

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  StatModel(const Napi::CallbackInfo& info);

  static Napi::FunctionReference constructor;
};

#endif