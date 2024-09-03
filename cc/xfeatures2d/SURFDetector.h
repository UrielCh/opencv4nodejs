#include "CvBinding.h"
#include "features2d/FeatureDetector.h"
#include "macros.h"
#include <opencv2/xfeatures2d.hpp>

#ifndef __FF_SURFDETECTOR_H__
#define __FF_SURFDETECTOR_H__

class SURFDetector final : public FeatureDetector, public FF::ObjectWrapTemplate<SURFDetector, cv::Ptr<cv::xfeatures2d::SURF>> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "SURFDetector";
  }

  cv::Ptr<cv::FeatureDetector> getDetector(void) {
    return self;
  }

  void Wrap(Napi::Object object) {
    FeatureDetector::Wrap(object);
  }

  FF_GETTER_CUSTOM(hessianThreshold, FF::DoubleConverter, self->getHessianThreshold());
  FF_GETTER_CUSTOM(nOctaves, FF::IntConverter, self->getNOctaves());
  FF_GETTER_CUSTOM(nOctaveLayers, FF::IntConverter, self->getNOctaveLayers());
  FF_GETTER_CUSTOM(extended, FF::BoolConverter, self->getExtended());
  FF_GETTER_CUSTOM(upright, FF::BoolConverter, self->getUpright());

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);

  class Constructor : public ConstructorBase {
  public:
    Constructor(const Napi::CallbackInfo& info) {
      auto hessianThreshold = opt<FF::DoubleConverter>("hessianThreshold", 100);
      auto nOctaves = opt<FF::IntConverter>("nOctaves", 4);
      auto nOctaveLayers = opt<FF::DoubleConverter>("nOctaveLayers", 3);
      auto extended = opt<FF::BoolConverter>("extended", false);
      auto upright = opt<FF::BoolConverter>("upright", false);

      executeBinding = [=]() {
        return cv::xfeatures2d::SURF::create(
            hessianThreshold->ref(),
            nOctaves->ref(),
            nOctaveLayers->ref(),
            extended->ref(),
            upright->ref());
      };
    };

    virtual ~Constructor() {
    }
  };
};

#endif