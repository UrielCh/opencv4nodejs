#include "Facemark.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

#ifndef __FF_FACEMARKAAM_H__
#define __FF_FACEMARKAAM_H__

class FacemarkAAM : public Facemark {
public:
  cv::Ptr<cv::face::Facemark> facemark;

  void save(std::string path) {
    facemark->save(path);
  }

  void load(std::string path) {
    cv::Algorithm::load<cv::face::FacemarkAAM>(path);
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  cv::Ptr<cv::face::Facemark> getFacemark() {
    return facemark;
  }
};

#endif

#endif
