#include "OCRHMMClassifier.h"

#ifndef __FF_OCRHMMCLASSIFIERBINDINGS_H_
#define __FF_OCRHMMCLASSIFIERBINDINGS_H_

namespace OCRHMMClassifierBindings {

struct EvalWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::text::OCRHMMDecoder::ClassifierCallback> classifier;

  EvalWorker(cv::Ptr<cv::text::OCRHMMDecoder::ClassifierCallback> classifier) {
    this->classifier = classifier;
  }

  virtual ~EvalWorker() {
  }

  cv::Mat img;
  std::vector<int> clazz;
  std::vector<double> confidence;

  std::string executeCatchCvExceptionWorker() {
    classifier->eval(img, clazz, confidence);
    return "";
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    Napi::Object ret = Napi::Object::New(env);
    Nan::Set(ret, FF::newString(env, "classes"), FF::IntArrayConverter::wrap(clazz));
    Nan::Set(ret, FF::newString(env, "confidences"), FF::DoubleArrayConverter::wrap(confidence));
    return ret;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return Mat::Converter::arg(0, &img, info);
  }
};

} // namespace OCRHMMClassifierBindings

#endif