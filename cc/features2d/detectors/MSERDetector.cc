#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "MSERDetector.h"
#include "Point.h"
#include "Rect.h"

Napi::FunctionReference MSERDetector::constructor;

Napi::Object MSERDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, MSERDetector::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Napi::String::New(env, "MSERDetector"));


  Napi::SetPrototypeMethod(ctor, "detectRegions", MSERDetector::DetectRegions);
  Napi::SetPrototypeMethod(ctor, "detectRegionsAsync", MSERDetector::DetectRegionsAsync);

  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "delta"), delta_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "minArea"), minArea_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "maxArea"), maxArea_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "maxVariation"), maxVariation_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "minDiversity"), minDiversity_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "maxEvolution"), maxEvolution_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "areaThreshold"), areaThreshold_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "minMargin"), minMargin_getter);
  Napi::SetAccessor(instanceTemplate, Napi::String::New(env, "edgeBlurSize"), edgeBlurSize_getter);

  target.Set("MSERDetector", FF::getFunction(ctor));
};

void MSERDetector::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "MSERDetector::New");
  FF_ASSERT_CONSTRUCT_CALL();
  MSERDetector::NewWorker worker;

  if (worker.applyUnwrappers(info)) {
    return tryCatch.reThrow();
  }

  MSERDetector* self = new MSERDetector();
  self->Wrap(info.Holder());
  self->delta = worker.delta;
  self->minArea = worker.minArea;
  self->maxArea = worker.maxArea;
  self->maxVariation = worker.maxVariation;
  self->minDiversity = worker.minDiversity;
  self->maxEvolution = worker.maxEvolution;
  self->areaThreshold = worker.areaThreshold;
  self->minMargin = worker.minMargin;
  self->edgeBlurSize = worker.edgeBlurSize;
  self->self = cv::MSER::create(worker.delta, worker.minArea, worker.maxArea, worker.maxVariation,
                                worker.minDiversity, worker.maxEvolution, worker.areaThreshold, worker.minMargin, worker.edgeBlurSize);
  return info.Holder();
}

struct DetectRegionsWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::MSER> det;

  DetectRegionsWorker(cv::Ptr<cv::MSER> det) {
    this->det = det;
  }

  virtual ~DetectRegionsWorker() {
  }

  cv::Mat img;
  std::vector<std::vector<cv::Point>> regions;
  std::vector<cv::Rect> mser_bbox;

  std::string executeCatchCvExceptionWorker() {
    det->detectRegions(img, regions, mser_bbox);
    return "";
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    // we only need input image
    return Mat::Converter::arg(0, &img, info);
  }

  Napi::Value getReturnValue(const Napi::Env& env) {
    Napi::Object ret = Napi::Object::New(env);
    (ret).Set("msers", Point2::ArrayOfArraysWithCastConverter<cv::Point2i>::wrap(regions));
    (ret).Set("bboxes", Rect::ArrayWithCastConverter<cv::Rect>::wrap(mser_bbox));
    return ret;
  }
};

void MSERDetector::DetectRegions(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<DetectRegionsWorker>(MSERDetector::unwrapSelf(info)),
      "MSERDetector::DetectRegions",
      info);
}

void MSERDetector::DetectRegionsAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<DetectRegionsWorker>(MSERDetector::unwrapSelf(info)),
      "MSERDetector::DetectRegionsAsync",
      info);
}

#endif
