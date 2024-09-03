#include "CatchCvExceptionWorker.h"
#include "CvBinding.h"
#include "DetectionROI.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"
#include "Size.h"
#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>

#ifndef __FF_HOGDESCRIPTOR_H__
#define __FF_HOGDESCRIPTOR_H__

class HOGDescriptor : public FF::ObjectWrap<HOGDescriptor, std::shared_ptr<cv::HOGDescriptor>> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "HOGDescriptor";
  }

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  class HistogramNormType : public FF::EnumWrap<HistogramNormType> {
  public:
    typedef cv::HOGDescriptor::HistogramNormType Type;

    static const char* getClassName() {
      return "HOGHistogramNormType";
    }

    static std::vector<Type> getEnumValues() {
      return {Type::L2Hys};
    }

    static std::vector<const char*> getEnumMappings() {
      return {"L2Hys"};
    }
  };
#endif

  FF_ACCESSORS_PTR(winSize, Size::Converter);
  FF_ACCESSORS_PTR(blockSize, Size::Converter);
  FF_ACCESSORS_PTR(blockStride, Size::Converter);
  FF_ACCESSORS_PTR(cellSize, Size::Converter);
  FF_ACCESSORS_PTR(nbins, FF::IntConverter);
  FF_ACCESSORS_PTR(derivAperture, FF::IntConverter);
  FF_ACCESSORS_PTR(winSigma, FF::DoubleConverter);
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  FF_ACCESSORS_PTR(histogramNormType, HistogramNormType::Converter);
#else
  FF_ACCESSORS_PTR(histogramNormType, FF::IntConverter);
#endif
  FF_ACCESSORS_PTR(L2HysThreshold, FF::DoubleConverter);
  FF_ACCESSORS_PTR(gammaCorrection, FF::BoolConverter);
  FF_ACCESSORS_PTR(nlevels, FF::IntConverter);
  FF_ACCESSORS_PTR(signedGradient, FF::BoolConverter);

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  static void New(const Napi::CallbackInfo& info);
  static void GetDaimlerPeopleDetector(const Napi::CallbackInfo& info);
  static void GetDefaultPeopleDetector(const Napi::CallbackInfo& info);
  static void CheckDetectorSize(const Napi::CallbackInfo& info);
  static void SetSVMDetector(const Napi::CallbackInfo& info);
  static void Save(const Napi::CallbackInfo& info);
  static void Load(const Napi::CallbackInfo& info);
  static void Compute(const Napi::CallbackInfo& info);
  static void ComputeAsync(const Napi::CallbackInfo& info);
  static void ComputeGradient(const Napi::CallbackInfo& info);
  static void ComputeGradientAsync(const Napi::CallbackInfo& info);
  static void Detect(const Napi::CallbackInfo& info);
  static void DetectAsync(const Napi::CallbackInfo& info);
  static void DetectROI(const Napi::CallbackInfo& info);
  static void DetectROIAsync(const Napi::CallbackInfo& info);
  static void DetectMultiScale(const Napi::CallbackInfo& info);
  static void DetectMultiScaleAsync(const Napi::CallbackInfo& info);
  static void DetectMultiScaleROI(const Napi::CallbackInfo& info);
  static void DetectMultiScaleROIAsync(const Napi::CallbackInfo& info);
  static void GroupRectangles(const Napi::CallbackInfo& info);
  static void GroupRectanglesAsync(const Napi::CallbackInfo& info);

  class Constructor : public ConstructorBase {
  public:
    virtual ~Constructor() {
    }

    Constructor(const Napi::CallbackInfo& info) {
      auto winSize = opt<Size::Converter>("winSize", cv::Size2d(64, 128));
      auto blockSize = opt<Size::Converter>("blockSize", cv::Size2d(16, 16));
      auto blockStride = opt<Size::Converter>("blockStride", cv::Size2d(8, 8));
      auto cellSize = opt<Size::Converter>("cellSize", cv::Size2d(8, 8));
      auto nbins = opt<FF::IntConverter>("nbins", 9);
      auto derivAperture = opt<FF::IntConverter>("derivAperture", 1);
      auto winSigma = opt<FF::DoubleConverter>("winSigma", -1);
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
      auto histogramNormType = opt<HOGDescriptor::HistogramNormType::Converter>("histogramNormType", cv::HOGDescriptor::L2Hys);
#else
      auto histogramNormType = opt<FF::IntConverter>("histogramNormType", cv::HOGDescriptor::L2Hys);
#endif
      auto L2HysThreshold = opt<FF::DoubleConverter>("L2HysThreshold", 0.2);
      auto gammaCorrection = opt<FF::BoolConverter>("gammaCorrection", false);
      auto nlevels = opt<FF::IntConverter>("nlevels", cv::HOGDescriptor::DEFAULT_NLEVELS);
      auto signedGradient = opt<FF::BoolConverter>("signedGradient", false);

      executeBinding = [=]() {
        return std::make_shared<cv::HOGDescriptor>(
            winSize->ref(),
            blockSize->ref(),
            blockStride->ref(),
            cellSize->ref(),
            nbins->ref(),
            derivAperture->ref(),
            winSigma->ref(),
            histogramNormType->ref(),
            L2HysThreshold->ref(),
            gammaCorrection->ref(),
            nlevels->ref(),
            signedGradient->ref());
      };
    };
  };
};

#endif