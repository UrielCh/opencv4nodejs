#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "MSERDetector.h"
#include "Point.h"
#include "Rect.h"

Nan::Persistent<v8::FunctionTemplate> MSERDetector::constructor;

Napi::Object MSERDetector(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(MSERDetector::New);
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
  ctor->SetClassName(Nan::New("MSERDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(ctor, "detectRegions", MSERDetector::DetectRegions);
  Nan::SetPrototypeMethod(ctor, "detectRegionsAsync", MSERDetector::DetectRegionsAsync);

  Nan::SetAccessor(instanceTemplate, Nan::New("delta").ToLocalChecked(), delta_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("minArea").ToLocalChecked(), minArea_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("maxArea").ToLocalChecked(), maxArea_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("maxVariation").ToLocalChecked(), maxVariation_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("minDiversity").ToLocalChecked(), minDiversity_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("maxEvolution").ToLocalChecked(), maxEvolution_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("areaThreshold").ToLocalChecked(), areaThreshold_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("minMargin").ToLocalChecked(), minMargin_getter);
  Nan::SetAccessor(instanceTemplate, Nan::New("edgeBlurSize").ToLocalChecked(), edgeBlurSize_getter);

  Nan::Set(target, Nan::New("MSERDetector").ToLocalChecked(), FF::getFunction(ctor));
};

void MSERDetector::New(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("MSERDetector::New");
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
  info.GetReturnValue().Set(info.Holder());
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
    Nan::Set(ret, FF::newString(env, "msers"), Point2::ArrayOfArraysWithCastConverter<cv::Point2i>::wrap(regions));
    Nan::Set(ret, FF::newString(env, "bboxes"), Rect::ArrayWithCastConverter<cv::Rect>::wrap(mser_bbox));
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
