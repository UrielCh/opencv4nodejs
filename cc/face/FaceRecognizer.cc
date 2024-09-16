#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "FaceRecognizer.h"
#include "FaceRecognizerBindings.h"

void FaceRecognizer::Init(Napi::Env env, Napi::Object exports) {
  InstanceMethod("train", &Train),
  InstanceMethod("trainAsync", &TrainAsync),
  InstanceMethod("predict", &Predict),
  InstanceMethod("predictAsync", &PredictAsync),
  InstanceMethod("save", &Save),
  InstanceMethod("load", &Load),
};

void FaceRecognizer::Save(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch(env, "FaceRecognizer::Save");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  info.This())->save(path.Unwrap<FaceRecognizer>();
}

void FaceRecognizer::Load(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "FaceRecognizer::Load");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  info.This())->load(path.Unwrap<FaceRecognizer>();
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