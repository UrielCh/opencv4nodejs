#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/features2d.hpp>

#ifndef __FF_DESCRIPTORMATCH_H__
#define __FF_DESCRIPTORMATCH_H__

class DescriptorMatch : public FF::ObjectWrap<DescriptorMatch, cv::DMatch> {
public:
  static Napi::FunctionReference constructor;;

  static const char* getClassName() {
    return "DescriptorMatch";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  FF_ACCESSORS(queryIdx, FF::IntConverter);
  FF_ACCESSORS(trainIdx, FF::IntConverter);
  FF_ACCESSORS(distance, FF::FloatConverter);
};

#endif