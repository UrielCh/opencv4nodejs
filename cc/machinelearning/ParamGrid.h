#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/ml.hpp>

#ifndef __FF_PARAMGRID_H__
#define __FF_PARAMGRID_H__

class ParamGrid : public FF::ObjectWrap<ParamGrid, cv::ml::ParamGrid> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "ParamGrid";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  FF_ACCESSORS(minVal, FF::DoubleConverter);
  FF_ACCESSORS(maxVal, FF::DoubleConverter);
  FF_ACCESSORS(logStep, FF::DoubleConverter);
};

#endif