#include "FaceRecognizer.h"

#ifndef __FF_FISHERFACERECOGNIZER_H__
#define __FF_FISHERFACERECOGNIZER_H__

class FisherFaceRecognizer : public FaceRecognizer {
public:
  cv::Ptr<cv::face::FaceRecognizer> faceRecognizer;

  void save(std::string path) {
    faceRecognizer->save(path);
  }

  void load(std::string path) {
#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
    faceRecognizer = cv::Algorithm::load<cv::face::FisherFaceRecognizer>(path);
#else
    faceRecognizer->load(path);
#endif
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  static Napi::FunctionReference constructor;
  ;

  cv::Ptr<cv::face::FaceRecognizer> getFaceRecognizer() {
    return faceRecognizer;
  }
};

#endif