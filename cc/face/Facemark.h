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

class Facemark : public FF::ObjectWrapBase<Facemark>, public Napi::ObjectWrap {
public:
  virtual cv::Ptr<cv::face::Facemark> getFacemark() = 0;
  virtual void save(std::string) = 0;
  virtual void load(std::string) = 0;

  static void Init(Napi::FunctionReference);

  static void AddTrainingSample(const Napi::CallbackInfo& info);
  static void AddTrainingSampleAsync(const Napi::CallbackInfo& info);
  static void LoadModel(const Napi::CallbackInfo& info);
  static void LoadModelAsync(const Napi::CallbackInfo& info);
  static void GetData(const Napi::CallbackInfo& info);
  static void GetDataAsync(const Napi::CallbackInfo& info);
  static void GetFaces(const Napi::CallbackInfo& info);
  static void GetFacesAsync(const Napi::CallbackInfo& info);
  static void SetFaceDetector(const Napi::CallbackInfo& info);
  static void Training(const Napi::CallbackInfo& info);
  static void TrainingAsync(const Napi::CallbackInfo& info);
  static void Fit(const Napi::CallbackInfo& info);
  static void FitAsync(const Napi::CallbackInfo& info);
  static void Save(const Napi::CallbackInfo& info);
  static void Load(const Napi::CallbackInfo& info);

  static bool detector(cv::InputArray image, cv::OutputArray faces,
                       Napi::FunctionReference* callback);
};

#endif

#endif
