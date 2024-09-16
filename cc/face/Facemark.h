#include "Mat.h"
#include "NativeNodeUtils.h"
#include "Point.h"
#include "Rect.h"
#include "macros.h"
#include <iostream>
#include <opencv2/face.hpp>

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

#ifndef __FF_FACEMARK_H__
#define __FF_FACEMARK_H__

class Facemark : public FF::ObjectWrapBase<Facemark>, public Napi::ObjectWrap<Facemark> {
public:
  virtual cv::Ptr<cv::face::Facemark> getFacemark() = 0;
  virtual Napi::Value save(std::string) = 0;
  virtual Napi::Value load(std::string) = 0;

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static Napi::Value AddTrainingSample(const Napi::CallbackInfo& info);
  static Napi::Value AddTrainingSampleAsync(const Napi::CallbackInfo& info);
  static Napi::Value LoadModel(const Napi::CallbackInfo& info);
  static Napi::Value LoadModelAsync(const Napi::CallbackInfo& info);
  static Napi::Value GetData(const Napi::CallbackInfo& info);
  static Napi::Value GetDataAsync(const Napi::CallbackInfo& info);
  static Napi::Value GetFaces(const Napi::CallbackInfo& info);
  static Napi::Value GetFacesAsync(const Napi::CallbackInfo& info);
  static Napi::Value SetFaceDetector(const Napi::CallbackInfo& info);
  static Napi::Value Training(const Napi::CallbackInfo& info);
  static Napi::Value TrainingAsync(const Napi::CallbackInfo& info);
  static Napi::Value Fit(const Napi::CallbackInfo& info);
  static Napi::Value FitAsync(const Napi::CallbackInfo& info);
  static Napi::Value Save(const Napi::CallbackInfo& info);
  static Napi::Value Load(const Napi::CallbackInfo& info);

  static bool detector(cv::InputArray image, cv::OutputArray faces,
                       Napi::FunctionReference* callback);
};

#endif

#endif
