#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/features2d.hpp>

#ifndef __FF_DESCRIPTORMATCH_H__
#define __FF_DESCRIPTORMATCH_H__

class DescriptorMatch : public FF::ObjectWrap<DescriptorMatch, cv::DMatch> {
public:
  static Napi::FunctionReference constructor;

  static const char* getClassName() {
    return "DescriptorMatch";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);


  // static FF::IntConverter::Type getProperty_queryIdx(ClassType* self) { return self->self.queryIdx; }
  // static Napi::Value queryIdx_getter(const Napi::CallbackInfo& info) { return getter<FF::IntConverter>(info, getProperty_queryIdx); };
  // static void setProperty_queryIdx(ClassType* self, FF::IntConverter::Type val) { self->self.queryIdx = val; }
  // static void queryIdx_setter(const Napi::CallbackInfo& info, const Napi::Value& value) { setter<FF::IntConverter>("queryIdx", info, value, setProperty_queryIdx); }

  FF_ACCESSORS(queryIdx, FF::IntConverter);
  FF_ACCESSORS(trainIdx, FF::IntConverter);
  FF_ACCESSORS(distance, FF::FloatConverter);
};

#endif