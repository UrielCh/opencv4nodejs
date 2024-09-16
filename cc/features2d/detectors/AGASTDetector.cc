#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "AGASTDetector.h"

Napi::FunctionReference AGASTDetector::constructor;

Napi::Object AGASTDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, AGASTDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(env, exports);
  constructor.Reset(ctor);
  ctor->SetClassName(Napi::String::New(env, "AGASTDetector"));


  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "threshold"), threshold_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "nonmaxSuppression"), nonmaxSuppression_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "type"), type_getter);

  target.Set("AGASTDetector", FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  DetectorType::Init(env, exports);
#endif
};

struct NewWorker : CatchCvExceptionWorker {
public:
  int threshold = 10;
  bool nonmaxSuppression = true;
  int type = cv::AgastFeatureDetector::OAST_9_16;

  bool unwrapOptionalArgs(const Napi::CallbackInfo& info) {
    return (
        FF::IntConverter::optArg(0, &threshold, info) || FF::BoolConverter::optArg(1, &nonmaxSuppression, info) || FF::IntConverter::optArg(2, &type, info));
  }

  bool hasOptArgsObject(const Napi::CallbackInfo& info) {
    return FF::isArgObject(info, 0);
  }

  bool unwrapOptionalArgsFromOpts(const Napi::CallbackInfo& info) {
    Napi::Object opts = info[0].As<Napi::Object>();
    return (
        FF::IntConverter::optProp(&threshold, "threshold", opts) || FF::BoolConverter::optProp(&nonmaxSuppression, "nonmaxSuppression", opts) || FF::IntConverter::optProp(&type, "type", opts));
  }

  std::string executeCatchCvExceptionWorker() {
    return "";
  }
};

void AGASTDetector::New(const Napi::CallbackInfo& info) {
  NewBinding().construct(info);
}

#endif
