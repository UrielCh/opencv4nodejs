#include "opencv_modules.h"

#ifdef HAVE_OPENCV_OBJDETECT

#include "HOGDescriptor.h"
#include "HOGDescriptorBindings.h"

Napi::FunctionReference HOGDescriptor::constructor;

Napi::Object HOGDescriptor(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, HOGDescriptor::New));
  v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  ctor->SetClassName(FF::newString(env, "HOGDescriptor"));
  instanceTemplate->SetInternalFieldCount(1);

  Nan::SetAccessor(instanceTemplate, FF::newString(env, "winSize"), winSize_getter, winSize_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "blockSize"), blockSize_getter, blockSize_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "blockStride"), blockStride_getter, blockStride_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "cellSize"), cellSize_getter, cellSize_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "nbins"), nbins_getter, nbins_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "derivAperture"), derivAperture_getter, derivAperture_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "histogramNormType"), histogramNormType_getter, histogramNormType_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "nlevels"), nlevels_getter, nlevels_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "winSigma"), winSigma_getter, winSigma_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "L2HysThreshold"), L2HysThreshold_getter, L2HysThreshold_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "gammaCorrection"), gammaCorrection_getter, gammaCorrection_setter);
  Nan::SetAccessor(instanceTemplate, FF::newString(env, "signedGradient"), signedGradient_getter, signedGradient_setter);

  Nan::SetMethod(ctor, "getDaimlerPeopleDetector", GetDaimlerPeopleDetector);
  Nan::SetMethod(ctor, "getDefaultPeopleDetector", GetDefaultPeopleDetector);

  Nan::SetPrototypeMethod(ctor, "compute", Compute);
  Nan::SetPrototypeMethod(ctor, "computeAsync", ComputeAsync);
  Nan::SetPrototypeMethod(ctor, "computeGradient", ComputeGradient);
  Nan::SetPrototypeMethod(ctor, "computeGradientAsync", ComputeGradientAsync);
  Nan::SetPrototypeMethod(ctor, "detect", Detect);
  Nan::SetPrototypeMethod(ctor, "detectAsync", DetectAsync);
  Nan::SetPrototypeMethod(ctor, "detectROI", DetectROI);
  Nan::SetPrototypeMethod(ctor, "detectROIAsync", DetectROIAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScale", DetectMultiScale);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleAsync", DetectMultiScaleAsync);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleROI", DetectMultiScaleROI);
  Nan::SetPrototypeMethod(ctor, "detectMultiScaleROIAsync", DetectMultiScaleROIAsync);
  Nan::SetPrototypeMethod(ctor, "groupRectangles", GroupRectangles);
  Nan::SetPrototypeMethod(ctor, "groupRectanglesAsync", GroupRectanglesAsync);
  Nan::SetPrototypeMethod(ctor, "checkDetectorSize", CheckDetectorSize);
  Nan::SetPrototypeMethod(ctor, "setSVMDetector", SetSVMDetector);
  Nan::SetPrototypeMethod(ctor, "save", Save);
  Nan::SetPrototypeMethod(ctor, "load", Load);

  Nan::Set(target, FF::newString(env, "HOGDescriptor"), FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  HistogramNormType::Init(env, exports);
#endif
};

void HOGDescriptor::New(const Napi::CallbackInfo& info) {
  constructorBinding<Constructor>(info);
}

void HOGDescriptor::GetDaimlerPeopleDetector(const Napi::CallbackInfo& info) {
  std::vector<float> detector = cv::HOGDescriptor::getDaimlerPeopleDetector();
  info.GetReturnValue().Set(FF::FloatArrayConverter::wrap(detector));
}

void HOGDescriptor::GetDefaultPeopleDetector(const Napi::CallbackInfo& info) {
  std::vector<float> detector = cv::HOGDescriptor::getDefaultPeopleDetector();
  info.GetReturnValue().Set(FF::FloatArrayConverter::wrap(detector));
}

void HOGDescriptor::CheckDetectorSize(const Napi::CallbackInfo& info) {
  info.GetReturnValue().Set(Nan::New(HOGDescriptor::unwrapSelf(info)->checkDetectorSize()));
}

void HOGDescriptor::SetSVMDetector(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "HOGDescriptor::SetSVMDetector");
  std::vector<float> detector;
  if (!FF::hasArg(info, 0) || FF::FloatArrayConverter::unwrapTo(&detector, info[0])) {
    return tryCatch.throwError("expected detector to be an Array of type Number");
  }
  HOGDescriptor::unwrapSelf(info)->setSVMDetector(detector);
}

void HOGDescriptor::Save(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "HOGDescriptor::Save");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  HOGDescriptor::unwrapSelf(info)->save(path);
}

void HOGDescriptor::Load(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "HOGDescriptor::Load");

  std::string path;
  if (FF::StringConverter::arg(0, &path, info)) {
    return tryCatch.reThrow();
  }
  HOGDescriptor::unwrapSelf(info)->load(path);
}

void HOGDescriptor::Compute(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<HOGDescriptorBindings::ComputeWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::Compute",
      info);
}

void HOGDescriptor::ComputeAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<HOGDescriptorBindings::ComputeWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::ComputeAsync",
      info);
}

void HOGDescriptor::ComputeGradient(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<HOGDescriptorBindings::ComputeGradientWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::ComputeGradient",
      info);
}

void HOGDescriptor::ComputeGradientAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<HOGDescriptorBindings::ComputeGradientWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::ComputeGradientAsync",
      info);
}

void HOGDescriptor::Detect(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<HOGDescriptorBindings::DetectWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::Detect",
      info);
}

void HOGDescriptor::DetectAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<HOGDescriptorBindings::DetectWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::DetectAsync",
      info);
}

void HOGDescriptor::DetectROI(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<HOGDescriptorBindings::DetectROIWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::DetectROI",
      info);
}

void HOGDescriptor::DetectROIAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<HOGDescriptorBindings::DetectROIWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::DetectROIAsync",
      info);
}

void HOGDescriptor::DetectMultiScale(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<HOGDescriptorBindings::DetectMultiScaleWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::DetectMultiScale",
      info);
}

void HOGDescriptor::DetectMultiScaleAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<HOGDescriptorBindings::DetectMultiScaleWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::DetectMultiScaleAsync",
      info);
}

void HOGDescriptor::DetectMultiScaleROI(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<HOGDescriptorBindings::DetectMultiScaleROIWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::DetectMultiScaleROI",
      info);
}

void HOGDescriptor::DetectMultiScaleROIAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<HOGDescriptorBindings::DetectMultiScaleROIWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::DetectMultiScaleROIAsync",
      info);
}

void HOGDescriptor::GroupRectangles(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<HOGDescriptorBindings::GroupRectanglesWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::GroupRectangles",
      info);
}

void HOGDescriptor::GroupRectanglesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<HOGDescriptorBindings::GroupRectanglesWorker>(HOGDescriptor::unwrapSelf(info)),
      "HOGDescriptor::GroupRectanglesAsync",
      info);
}

#endif
