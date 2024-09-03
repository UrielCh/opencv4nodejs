#include "Mat.h"
#include "macros.h"
#include <opencv2/ximgproc.hpp>

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

#ifndef __FF_SUPERPIXELLSC_H__
#define __FF_SUPERPIXELLSC_H__

class SuperpixelLSC : public FF::ObjectWrap<SuperpixelLSC, cv::Ptr<cv::ximgproc::SuperpixelLSC>> {
public:
  static Napi::FunctionReference constructor;;

  static const char* getClassName() {
    return "SuperpixelLSC";
  }

  cv::Mat image;
  cv::Mat labels;
  cv::Mat labelContourMask;
  int region_size = 10;
  double ratio = 0.075;
  int numCalculatedSuperpixels = 0;

  FF_GETTER_CUSTOM(image, Mat::Converter, image);
  FF_GETTER_CUSTOM(labels, Mat::Converter, labels);
  FF_GETTER_CUSTOM(labelContourMask, Mat::Converter, labelContourMask);
  FF_GETTER_CUSTOM(region_size, FF::IntConverter, region_size);
  FF_GETTER_CUSTOM(ratio, FF::DoubleConverter, ratio);
  FF_GETTER_CUSTOM(numCalculatedSuperpixels, FF::IntConverter, numCalculatedSuperpixels);

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);
  static void Iterate(const Napi::CallbackInfo& info);

  struct NewWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat image;
    int region_size = 10;
    float ratio = 0.075f;

    std::string executeCatchCvExceptionWorker() {
      return "";
    }

    bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
      return (
          Mat::Converter::arg(0, &image, info));
    }

    bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
      return (
          FF::IntConverter::optArg(1, &region_size, info) || FF::FloatConverter::optArg(2, &ratio, info));
    }

    bool hasOptArgsObject(const Napi::CallbackInfo& info) {
      return FF::isArgObject(info, 1);
    }

    bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
      Napi::Object opts = info[1].As<Napi::Object>();
      return (
          FF::IntConverter::optProp(&region_size, "region_size", opts) || FF::FloatConverter::optProp(&ratio, "ratio", opts));
    }
  };
};

#endif

#endif