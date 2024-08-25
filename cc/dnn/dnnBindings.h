#include "dnn.h"

#ifndef __FF_DNNBINDINGS_H_
#define __FF_DNNBINDINGS_H_

namespace DnnBindings {

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
struct ReadNetFromDarknetWorker : public CatchCvExceptionWorker {
public:
  std::string cfgFile;
  std::string darknetModelFile = "";

  cv::dnn::Net net;

  virtual ~ReadNetFromDarknetWorker() {
  }

  std::string executeCatchCvExceptionWorker() {
    net = cv::dnn::readNetFromDarknet(cfgFile, darknetModelFile);
    if (net.empty()) {
      return std::string("failed to cfgFile: " + cfgFile + ", darknetModelFile: " + darknetModelFile).data();
    }
    return "";
  }

  Napi::Value getReturnValue() {
    return Net::Converter::wrap(net);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (FF::StringConverter::arg(0, &cfgFile, info));
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (FF::StringConverter::optArg(1, &darknetModelFile, info));
  }
};
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 2)

struct ReadNetWorker : public CatchCvExceptionWorker {
public:
  std::string model;
  std::string config = "";
  std::string framework = "";

  cv::dnn::Net net;

  virtual ~ReadNetWorker() {
  }

  std::string executeCatchCvExceptionWorker() {
    net = cv::dnn::readNet(model, config, framework);
    if (net.empty()) {
      return std::string("failed to load network model: " + model).data();
    }
    return "";
  }

  Napi::Value getReturnValue() {
    return Net::Converter::wrap(net);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return FF::StringConverter::arg(0, &model, info);
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (FF::StringConverter::optArg(1, &config, info) || FF::StringConverter::optArg(2, &framework, info));
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    return FF::isArgObject(info, 1);
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    Napi::Object opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    return (
        FF::StringConverter::optProp(&config, "config", opts) || FF::StringConverter::optProp(&framework, "framework", opts));
  }
};
#endif

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
struct ReadNetFromONNXWorker : public CatchCvExceptionWorker {
public:
  std::string onnxFile;

  cv::dnn::Net net;

  virtual ~ReadNetFromONNXWorker() {
  }

  std::string executeCatchCvExceptionWorker() {
    net = cv::dnn::readNetFromONNX(onnxFile);
    if (net.empty()) {
      return std::string("failed to load network model: " + onnxFile).data();
    }
    return "";
  }

  Napi::Value getReturnValue() {
    return Net::Converter::wrap(net);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return FF::StringConverter::arg(0, &onnxFile, info);
  }
};
#endif

struct ReadNetFromTensorflowWorker : public CatchCvExceptionWorker {
public:
  std::string modelFile;
  std::string configFile = "";

  cv::dnn::Net net;

  virtual ~ReadNetFromTensorflowWorker() {
  }

  std::string executeCatchCvExceptionWorker() {
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
    net = cv::dnn::readNetFromTensorflow(modelFile, configFile);
#else
    net = cv::dnn::readNetFromTensorflow(modelFile);
#endif
    if (net.empty()) {
      return std::string("failed to load net: " + modelFile + "failed to load config: " + configFile).data();
    }
    return "";
  }

  Napi::Value getReturnValue() {
    return Net::Converter::wrap(net);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (FF::StringConverter::arg(0, &modelFile, info));
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (FF::StringConverter::optArg(1, &configFile, info));
  }
};

struct ReadNetFromCaffeWorker : public CatchCvExceptionWorker {
public:
  std::string prototxt;
  std::string modelFile = "";

  cv::dnn::Net net;

  virtual ~ReadNetFromCaffeWorker() {
  }

  std::string executeCatchCvExceptionWorker() {
    net = cv::dnn::readNetFromCaffe(prototxt, modelFile);
    if (net.empty()) {
      return std::string("failed to prototxt: " + prototxt + ", modelFile: " + modelFile).data();
    }
    return "";
  }

  Napi::Value getReturnValue() {
    return Net::Converter::wrap(net);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        FF::StringConverter::arg(0, &prototxt, info));
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (FF::StringConverter::optArg(1, &modelFile, info));
  }
};

struct BlobFromImageWorker : public CatchCvExceptionWorker {
public:
  bool isSingleImage;

  BlobFromImageWorker(bool isSingleImage = true) {
    this->isSingleImage = isSingleImage;
  }

  virtual ~BlobFromImageWorker() {
  }

  cv::Mat image;
  std::vector<cv::Mat> images;

  double scalefactor = 1.0;
  cv::Size2d size = cv::Size2d();
  cv::Vec3d mean = cv::Vec3d();
  bool swapRB = true;
  bool crop = true;
  int ddepth = CV_32F;
  cv::Mat returnValue;

  std::string executeCatchCvExceptionWorker() {
#if CV_VERSION_GREATER_EQUAL(3, 4, 0) && CV_VERSION_REVISION > 2
    if (isSingleImage) {
      returnValue = cv::dnn::blobFromImage(image, scalefactor, size, mean, swapRB, crop, ddepth);
    } else {
      returnValue = cv::dnn::blobFromImages(images, scalefactor, size, mean, swapRB, crop, ddepth);
    }
#else
    if (isSingleImage) {
      returnValue = cv::dnn::blobFromImage(image, scalefactor, size, mean, swapRB);
    } else {
      returnValue = cv::dnn::blobFromImages(images, scalefactor, size, mean, swapRB);
    }
#endif
    return "";
  }

  Napi::Value getReturnValue() {
    return Mat::Converter::wrap(returnValue);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        (isSingleImage && Mat::Converter::arg(0, &image, info)) || (!isSingleImage && Mat::ArrayConverter::arg(0, &images, info)));
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (
        FF::DoubleConverter::optArg(1, &scalefactor, info) || Size::Converter::optArg(2, &size, info) || Vec3::Converter::optArg(3, &mean, info) || FF::BoolConverter::optArg(4, &swapRB, info) || FF::BoolConverter::optArg(5, &crop, info) || FF::IntConverter::optArg(6, &ddepth, info));
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    return FF::isArgObject(info, 1);
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    Napi::Object opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    return (
        FF::DoubleConverter::optProp(&scalefactor, "scalefactor", opts) || FF::BoolConverter::optProp(&swapRB, "swapRB", opts) || Size::Converter::optProp(&size, "size", opts) || Vec3::Converter::optProp(&mean, "mean", opts) || FF::BoolConverter::optProp(&crop, "crop", opts) || FF::IntConverter::optProp(&ddepth, "ddepth", opts));
  }
};

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
struct NMSBoxes : public CatchCvExceptionWorker {
public:
  std::vector<cv::Rect> bboxes;
  std::vector<float> scores;
  float score_threshold;
  float nms_threshold;
  std::vector<int> indices;
  float eta = 1.0f;
  int top_k = 0;

  virtual ~NMSBoxes() {
  }

  std::string executeCatchCvExceptionWorker() {
    cv::dnn::NMSBoxes(bboxes, scores, score_threshold, nms_threshold, indices);
    return "";
  }

  Napi::Value getReturnValue() {
    return FF::IntArrayConverter::wrap(indices);
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (
        Rect::ArrayWithCastConverter<cv::Rect>::arg(0, &bboxes, info) || FF::FloatArrayConverter::arg(1, &scores, info) || FF::FloatConverter::arg(2, &score_threshold, info) || FF::FloatConverter::arg(3, &nms_threshold, info));
  }

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return FF::FloatConverter::optArg(4, &eta, info) || FF::IntConverter::optArg(5, &top_k, info);
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    return FF::isArgObject(info, 4);
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    Napi::Object opts = info[4]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    return (
        FF::FloatConverter::optProp(&eta, "eta", opts) || FF::IntConverter::optProp(&top_k, "topK", opts));
  }
};
#endif
} // namespace DnnBindings

#endif
