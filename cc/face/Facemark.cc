#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "Facemark.h"
#include "FacemarkBindings.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

Napi::Value Facemark::Save(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Facemark::Save");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  //info.This()->save(path.Unwrap<Facemark>());
  info.This().As<Napi::Object>().Save(path.Unwrap<Facemark>());
  //this->value_;
}

Napi::Value Facemark::Load(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Facemark::Load");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  info.This()->load(path.Unwrap<Facemark>());
}

Napi::Object Facemark::Init(Napi::Env env, Napi::Object exports) {

  Napi::Function func = DefineClass(
      env,
      "Facemark",
      {
  InstanceMethod("loadModel", &Facemark::LoadModel),
  InstanceMethod("loadModelAsync", &Facemark::LoadModelAsync),
  InstanceMethod("fit", &Facemark::Fit),
  InstanceMethod("fitAsync", &Facemark::FitAsync),
  InstanceMethod("save", &Facemark::Save),
  InstanceMethod("load", &Facemark::Load),
#if CV_VERSION_MAJOR <= 3 && CV_VERSION_MINOR < 2
  InstanceMethod("addTrainingSample", &Facemark::AddTrainingSample),
  InstanceMethod("addTrainingSampleAsync", &Facemark::AddTrainingSampleAsync),
  InstanceMethod("getData", &Facemark::GetData),
  InstanceMethod("getDataAsync", &Facemark::GetDataAsync),
  InstanceMethod("getFaces", &Facemark::GetFaces),
  InstanceMethod("getFacesAsync", &Facemark::GetFacesAsync),
  InstanceMethod("setFaceDetector", &Facemark::SetFaceDetector),
  InstanceMethod("training", &Facemark::Training),
  InstanceMethod("trainingAsync", &Facemark::TrainingAsync),
#endif
});

Napi::Value Facemark::LoadModel(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::LoadModelWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::LoadModel",
      info);
}

Napi::Value Facemark::LoadModelAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::LoadModelWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::LoadModelAsync",
      info);
}

Napi::Value Facemark::Fit(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::FitWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::Fit",
      info);
}

Napi::Value Facemark::FitAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::FitWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::FitAsync",
      info);
}

#if CV_VERSION_MAJOR <= 3 && CV_VERSION_MINOR < 2

Napi::Value Facemark::AddTrainingSample(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::AddTrainingSampleWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::AddTrainingSample",
      info);
}

Napi::Value Facemark::AddTrainingSampleAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::AddTrainingSampleWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::AddTrainingSampleAsync",
      info);
}

Napi::Value Facemark::GetData(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::GetDataWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::GetData",
      info);
}

Napi::Value Facemark::GetDataAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::GetDataWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::GetDataAsync",
      info);
}

Napi::Value Facemark::GetFaces(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::GetFacesWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::GetFaces",
      info);
}

Napi::Value Facemark::GetFacesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::GetFacesWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::GetFacesAsync",
      info);
}

Napi::Value Facemark::SetFaceDetector(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Facemark::SetFaceDetector");
  if (!info[0].IsFunction()) {
    return tryCatch.throwError("expected argument 0 to be of type");
  }
  Napi::Function cbFunc = info[0].As<Napi::Function>();
  Napi::FunctionReference* callback = new Napi::FunctionReference(cbFunc);

  bool results = Facemark::unwrapThis(info)
                     ->getFacemark()
                     ->setFaceDetector((cv::face::FN_FaceDetector)detector, callback);

  return Napi::Boolean::New(env, results);
}

Napi::Value Facemark::Training(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<FacemarkBindings::TrainingWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::Train",
      info);
}

Napi::Value Facemark::TrainingAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<FacemarkBindings::TrainingWorker>(Facemark::unwrapThis(info)->getFacemark()),
      "Facemark::TrainAsync",
      info);
}

#endif

bool Facemark::detector(cv::InputArray image, cv::OutputArray faces,
                        Napi::FunctionReference* callback) {
  Napi::HandleScope scope(env);

  cv::Mat frame = image.getMat().clone();
  Napi::Value jsMat = Mat::Converter::wrap(frame);

  Napi::Value argv[] = {jsMat};

  Napi::AsyncResource resource("opencv4nodejs:Facemark::Detector");
  Napi::Object jsObject = resource.runInAsyncScope(Napi::GetCurrentContext()->Global(), **callback, 1, argv)

                              ->ToObject(Napi::GetCurrentContext());

  std::vector<cv::Rect2d> _faces;
  Rect::ArrayConverter::unwrapTo(&_faces, jsObject);

  cv::Mat(_faces).copyTo(faces);

  return true;
}

#endif

#endif
