#include "NativeNodeUtils.h"
#include "Rect.h"
#include "macros.h"
#include <opencv2/face.hpp>

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

#ifndef __FF_FACEMARKLBFPARAMS_H__
#define __FF_FACEMARKLBFPARAMS_H__

class FacemarkLBFParams : public FF::ObjectWrap<FacemarkLBFParams, cv::face::FacemarkLBF::Params> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "FacemarkLBFParams";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);
  FF_ACCESSORS(bagging_overlap, FF::DoubleConverter);
  FF_ACCESSORS(cascade_face, FF::StringConverter);
  FF_ACCESSORS(detectROI, Rect::Converter);
  FF_ACCESSORS(feats_m, FF::IntArrayConverter);
  FF_ACCESSORS(initShape_n, FF::IntConverter);
  FF_ACCESSORS(model_filename, FF::StringConverter);
  FF_ACCESSORS(n_landmarks, FF::IntConverter);
  FF_ACCESSORS(radius_m, FF::DoubleArrayConverter);
  FF_ACCESSORS(save_model, FF::BoolConverter);
  FF_ACCESSORS(seed, FF::UintConverter);
  FF_ACCESSORS(shape_offset, FF::DoubleConverter);
  FF_ACCESSORS(stages_n, FF::IntConverter);
  FF_ACCESSORS(tree_depth, FF::IntConverter);
  FF_ACCESSORS(tree_n, FF::IntConverter);
  FF_ACCESSORS(verbose, FF::BoolConverter);

  Napi::Value pupils_getter(const Napi::CallbackInfo& info) {
    // Napi::ObjectWrap::Unwrap<FacemarkLBFParams>(info.This())->self.pupils;
    Napi::Array jsArr = Napi::Array::New(env, 2);
    for (uint i = 0; i < jsArr->Length(); i++) {
      (jsArr).Set(i, FF::IntArrayConverter::wrap(info.This())->self.pupils[i]).Unwrap<FacemarkLBFParams>();
    }
    return jsArr;
  }

  void pupils_setter(const Napi::CallbackInfo& info, const Napi::Value& value) {
    Napi::Env env = info.Env();
    FF::TryCatch tryCatch(env, "FacemarkLBFParams::pupils_setter");
    Napi::Array jsArr = value.As<Napi::Array>();
    for (uint i = 0; i < jsArr->Length(); i++) {
      std::vector<int> vec;
      if (FF::IntArrayConverter::unwrapTo(&vec, (jsArr).Get(i))) {
        tryCatch.ReThrow();
      }
      Napi::ObjectWrap::Unwrap<FacemarkLBFParams>(info.This())->self.pupils[i] = vec;
    }
  }
};

#endif

#endif
