#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "Facemark.h"
#include "FacemarkBindings.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

void Facemark::Save(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Facemark::Save");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  Nan::ObjectWrap::Unwrap<Facemark>(info.This())->save(path);
}

void Facemark::Load(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Facemark::Load");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  Nan::ObjectWrap::Unwrap<Facemark>(info.This())->load(path);
}

void Facemark::Init(Napi::FunctionReference ctor) {
  Nan::SetPrototypeMethod(ctor, "loadModel", LoadModel);
  Nan::SetPrototypeMethod(ctor, "loadModelAsync", LoadModelAsync);
  Nan::SetPrototypeMethod(ctor, "fit", Fit);
  Nan::SetPrototypeMethod(ctor, "fitAsync", FitAsync);
  Nan::SetPrototypeMethod(ctor, "save", Save);
  Nan::SetPrototypeMethod(ctor, "load", Load);
#if CV_VERSION_MAJOR <= 3 && CV_VERSION_MINOR < 2
  Nan::SetPrototypeMethod(ctor, "addTrainingSample", AddTrainingSample);
  Nan::SetPrototypeMethod(ctor, "addTrainingSampleAsync", AddTrainingSampleAsync);
  Nan::SetPrototypeMethod(ctor, "getData", GetData);
  Nan::SetPrototypeMethod(ctor, "getDataAsync", GetDataAsync);
  Nan::SetPrototypeMethod(ctor, "getFaces", GetFaces);
  Nan::SetPrototypeMethod(ctor, "getFacesAsync", GetFacesAsync);
  Nan::SetPrototypeMethod(ctor, "setFaceDetector", SetFaceDetector);
  Nan::SetPrototypeMethod(ctor, "training", Training);
  Nan::SetPrototypeMethod(ctor, "trainingAsync", TrainingAsync);
#endif
};

void Facemark::LoadModel(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::LoadModelWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::LoadModel",
      info);
}

void Facemark::LoadModelAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::LoadModelWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::LoadModelAsync",
      info);
}

void Facemark::Fit(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::FitWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::Fit",
      info);
}

void Facemark::FitAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::FitWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::FitAsync",
      info);
}

#if CV_VERSION_MAJOR <= 3 && CV_VERSION_MINOR < 2

void Facemark::AddTrainingSample(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::AddTrainingSampleWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::AddTrainingSample",
      info);
}

void Facemark::AddTrainingSampleAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::AddTrainingSampleWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::AddTrainingSampleAsync",
      info);
}

void Facemark::GetData(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::GetDataWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::GetData",
      info);
}

void Facemark::GetDataAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::GetDataWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::GetDataAsync",
      info);
}

void Facemark::GetFaces(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::GetFacesWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::GetFaces",
      info);
}

void Facemark::GetFacesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::GetFacesWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::GetFacesAsync",
      info);
}

void Facemark::SetFaceDetector(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Facemark::SetFaceDetector");
  if (!info[0]->IsFunction()) {
    return tryCatch.throwError("expected argument 0 to be of type");
  }
  Napi::Function cbFunc = Napi::Function::Cast(info[0]);
  Nan::Callback* callback = new Nan::Callback(cbFunc);

  bool results = Facemark::unwrapThis(info)
                     ->getFacemark()
                     ->setFaceDetector((cv::face::FN_FaceDetector)detector, callback);

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(results));
}

void Facemark::Training(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::TrainingWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::Train",
      info);
}

void Facemark::TrainingAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::TrainingWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::TrainAsync",
      info);
}

#endif

bool Facemark::detector(cv::InputArray image, cv::OutputArray faces,
                        Nan::Callback* callback) {
  Nan::HandleScope scope;

  cv::Mat frame = image.getMat().clone();
  Napi::Value jsMat = Mat::Converter::wrap(frame);

  Napi::Value argv[] = {jsMat};

  Nan::AsyncResource resource("opencv4nodejs:Facemark::Detector");
  Napi::Object jsObject = resource.runInAsyncScope(Nan::GetCurrentContext()->Global(), **callback, 1, argv)
                              .ToLocalChecked()
                              ->ToObject(Nan::GetCurrentContext())
                              .ToLocalChecked();

  std::vector<cv::Rect2d> _faces;
  Rect::ArrayConverter::unwrapTo(&_faces, jsObject);

  cv::Mat(_faces).copyTo(faces);

  return true;
}

#endif

#endif
