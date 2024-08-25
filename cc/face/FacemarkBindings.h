#include "Facemark.h"
#include "FacemarkAAMData.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

#ifndef __FF_FACEMARKBINDINGS_H_
#define __FF_FACEMARKBINDINGS_H_

namespace FacemarkBindings {

struct LoadModelWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  LoadModelWorker(cv::Ptr<cv::face::Facemark> self) {
    this->self = self;
  }

  virtual ~LoadModelWorker() {
  }

  std::string model;

  std::string executeCatchCvExceptionWorker() {
    self->loadModel(model);
    return "";
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (FF::StringConverter::arg(0, &model, info));
  }
};

struct FitWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  FitWorker(cv::Ptr<cv::face::Facemark> self) {
    this->self = self;
  }
  virtual ~FitWorker() {
  }

  cv::Mat image;
  std::vector<cv::Rect> faces;
  std::vector<std::vector<cv::Point2f>> landmarks;

  std::string executeCatchCvExceptionWorker() {
    self->fit(image, faces, landmarks);
    return "";
  }

  Napi::Value getReturnValue() {
    Napi::Value ret = Point2::ArrayOfArraysWithCastConverter<cv::Point2f>::wrap(landmarks);
    return ret;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (Mat::Converter::arg(0, &image, info) || Rect::ArrayWithCastConverter<cv::Rect>::arg(1, &faces, info));
  }
};

#if CV_VERSION_MAJOR <= 3 && CV_VERSION_MINOR < 2
struct AddTrainingSampleWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  AddTrainingSampleWorker(cv::Ptr<cv::face::Facemark> self) {
    this->self = self;
  }

  bool results;
  cv::Mat image;
  std::vector<cv::Point2f> landmarks;

  std::string executeCatchCvExceptionWorker() {
    results = self->addTrainingSample(image, landmarks);
    return "";
  }

  Napi::Value getReturnValue() {
    Napi::Value ret = Nan::New<v8::Boolean>(results);
    return ret;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (Mat::Converter::arg(0, &image, info) || Point2::ArrayWithCastConverter<cv::Point2f>::arg(1, &landmarks, info));
  }
};

struct GetDataWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  GetDataWorker(cv::Ptr<cv::face::Facemark> self) {
    this->self = self;
  }

  cv::face::FacemarkAAM::Data data;

  std::string executeCatchCvExceptionWorker() {
    self->getData(&data);
    return "";
  }

  Napi::Value getReturnValue() {
    Napi::Value ret = InstanceConverter<FacemarkAAMData, cv::face::FacemarkAAM::Data>::wrap(data);
    return ret;
  }
};

struct GetFacesWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  GetFacesWorker(cv::Ptr<cv::face::Facemark> self) {
    this->self = self;
  }

  cv::Mat image;
  std::vector<cv::Rect> faces;

  std::string executeCatchCvExceptionWorker() {
    self->getFaces(image, faces);
    return "";
  }

  Napi::Value getReturnValue() {
    Napi::Value ret =
        Rect::ArrayConverter::wrap(faces);
    return ret;
  }

  bool unwrapRequiredArgs(const Napi::CallbackInfo& info) {
    return (Mat::Converter::arg(0, &image, info));
  }
};

struct TrainingWorker : public CatchCvExceptionWorker {
public:
  cv::Ptr<cv::face::Facemark> self;
  TrainingWorker(cv::Ptr<cv::face::Facemark> self) {
    this->self = self;
  }

  std::string executeCatchCvExceptionWorker() {
    self->training();
    return "";
  }
};
#endif
} // namespace FacemarkBindings

#endif

#endif
