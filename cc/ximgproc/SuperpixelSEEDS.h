#include "Mat.h"
#include "macros.h"
#include <opencv2/ximgproc.hpp>

#ifndef __FF_SUPERPIXELSEEDS_H__
#define __FF_SUPERPIXELSEEDS_H__

class SuperpixelSEEDS : public FF::ObjectWrap<SuperpixelSEEDS, cv::Ptr<cv::ximgproc::SuperpixelSEEDS>> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "SuperpixelSEEDS";
  }

  cv::Mat image;
  cv::Mat labels;
  cv::Mat labelContourMask;
  int num_superpixels;
  int num_levels;
  int prior = 2;
  int histogram_bins = 5;
  bool double_step = false;
  int numCalculatedSuperpixels = 0;

  FF_GETTER_CUSTOM(image, Mat::Converter, image);
  FF_GETTER_CUSTOM(labels, Mat::Converter, labels);
  FF_GETTER_CUSTOM(labelContourMask, Mat::Converter, labelContourMask);
  FF_GETTER_CUSTOM(num_superpixels, FF::IntConverter, num_superpixels);
  FF_GETTER_CUSTOM(num_levels, FF::IntConverter, num_levels);
  FF_GETTER_CUSTOM(prior, FF::IntConverter, prior);
  FF_GETTER_CUSTOM(histogram_bins, FF::IntConverter, histogram_bins);
  FF_GETTER_CUSTOM(double_step, FF::BoolConverter, double_step);
  FF_GETTER_CUSTOM(numCalculatedSuperpixels, FF::IntConverter, numCalculatedSuperpixels);

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static void New(const Napi::CallbackInfo& info);
  static void Iterate(const Napi::CallbackInfo& info);

  struct NewWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat img;
    int num_superpixels;
    int num_levels;
    int histogram_bins = 5;
    int prior = 2;
    bool double_step = false;

    std::string executeCatchCvExceptionWorker() {
      return "";
    }

    bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
      return (
          Mat::Converter::arg(0, &img, info) || FF::IntConverter::arg(1, &num_superpixels, info) || FF::IntConverter::arg(2, &num_levels, info));
    }

    bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
      return (
          FF::IntConverter::optArg(3, &histogram_bins, info) || FF::IntConverter::optArg(4, &prior, info) || FF::BoolConverter::optArg(5, &double_step, info));
    }

    bool hasOptArgsObject(const Napi::CallbackInfo& info) {
      return FF::isArgObject(info, 3);
    }

    bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
      Napi::Object opts = info[3].As<Napi::Object>();
      return (
          FF::IntConverter::optProp(&histogram_bins, "histogram_bins", opts) || FF::IntConverter::optProp(&prior, "prior", opts) || FF::BoolConverter::optProp(&double_step, "double_step", opts));
    }
  };
};

#endif