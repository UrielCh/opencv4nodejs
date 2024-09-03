#include "CatchCvExceptionWorker.h"
#include "Mat.h"
#include "NativeNodeUtils.h"
#include "macros.h"
#include <opencv2/face.hpp>

#ifndef __FF_FACERECOGNIZER_H__
#define __FF_FACERECOGNIZER_H__

class FaceRecognizer : public FF::ObjectWrapBase<FaceRecognizer>, public Napi::ObjectWrap {
public:
  virtual cv::Ptr<cv::face::FaceRecognizer> getFaceRecognizer() = 0;
  virtual void save(std::string) = 0;
  virtual void load(std::string) = 0;

  static void Init(Napi::FunctionReference);

  static void Save(const Napi::CallbackInfo& info);
  static void Load(const Napi::CallbackInfo& info);
  static void Train(const Napi::CallbackInfo& info);
  static void TrainAsync(const Napi::CallbackInfo& info);
  static void Predict(const Napi::CallbackInfo& info);
  static void PredictAsync(const Napi::CallbackInfo& info);
};

#endif