#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FaceRecognizer.h"
#include "FaceRecognizerBindings.h"

void FaceRecognizer::Init(Napi::FunctionReference ctor) {
  Nan::SetPrototypeMethod(ctor, "train", Train);
  Nan::SetPrototypeMethod(ctor, "trainAsync", TrainAsync);
  Nan::SetPrototypeMethod(ctor, "predict", Predict);
  Nan::SetPrototypeMethod(ctor, "predictAsync", PredictAsync);
  Nan::SetPrototypeMethod(ctor, "save", Save);
  Nan::SetPrototypeMethod(ctor, "load", Load);
};

void FaceRecognizer::Save(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch(env, "FaceRecognizer::Save");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  Nan::ObjectWrap::Unwrap<FaceRecognizer>(info.This())->save(path);
}

void FaceRecognizer::Load(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "FaceRecognizer::Load");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  Nan::ObjectWrap::Unwrap<FaceRecognizer>(info.This())->load(path);
}

void FaceRecognizer::Train(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FaceRecognizerBindings::TrainWorker>(FaceRecognizer::unwrapThis(info)->getFaceRecognizer()),
      "FaceRecognizer::Train",
      info);
}

void FaceRecognizer::TrainAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FaceRecognizerBindings::TrainWorker>(FaceRecognizer::unwrapThis(info)->getFaceRecognizer()),
      "FaceRecognizer::TrainAsync",
      info);
}

void FaceRecognizer::Predict(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FaceRecognizerBindings::PredictWorker>(FaceRecognizer::unwrapThis(info)->getFaceRecognizer()),
      "FaceRecognizer::Predict",
      info);
}

void FaceRecognizer::PredictAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FaceRecognizerBindings::PredictWorker>(FaceRecognizer::unwrapThis(info)->getFaceRecognizer()),
      "FaceRecognizer::PredictAsync",
      info);
}

#endif