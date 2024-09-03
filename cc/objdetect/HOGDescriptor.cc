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


  Napi::SetAccessor(instanceTemplate, FF::newString(env, "winSize"), winSize_getter, winSize_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "blockSize"), blockSize_getter, blockSize_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "blockStride"), blockStride_getter, blockStride_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "cellSize"), cellSize_getter, cellSize_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "nbins"), nbins_getter, nbins_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "derivAperture"), derivAperture_getter, derivAperture_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "histogramNormType"), histogramNormType_getter, histogramNormType_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "nlevels"), nlevels_getter, nlevels_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "winSigma"), winSigma_getter, winSigma_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "L2HysThreshold"), L2HysThreshold_getter, L2HysThreshold_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "gammaCorrection"), gammaCorrection_getter, gammaCorrection_setter);
  Napi::SetAccessor(instanceTemplate, FF::newString(env, "signedGradient"), signedGradient_getter, signedGradient_setter);

  Napi::SetMethod(ctor, "getDaimlerPeopleDetector", GetDaimlerPeopleDetector);
  Napi::SetMethod(ctor, "getDefaultPeopleDetector", GetDefaultPeopleDetector);

  InstanceMethod("compute", &Compute),
  InstanceMethod("computeAsync", &ComputeAsync),
  InstanceMethod("computeGradient", &ComputeGradient),
  InstanceMethod("computeGradientAsync", &ComputeGradientAsync),
  InstanceMethod("detect", &Detect),
  InstanceMethod("detectAsync", &DetectAsync),
  InstanceMethod("detectROI", &DetectROI),
  InstanceMethod("detectROIAsync", &DetectROIAsync),
  InstanceMethod("detectMultiScale", &DetectMultiScale),
  InstanceMethod("detectMultiScaleAsync", &DetectMultiScaleAsync),
  InstanceMethod("detectMultiScaleROI", &DetectMultiScaleROI),
  InstanceMethod("detectMultiScaleROIAsync", &DetectMultiScaleROIAsync),
  InstanceMethod("groupRectangles", &GroupRectangles),
  InstanceMethod("groupRectanglesAsync", &GroupRectanglesAsync),
  InstanceMethod("checkDetectorSize", &CheckDetectorSize),
  InstanceMethod("setSVMDetector", &SetSVMDetector),
  InstanceMethod("save", &Save),
  InstanceMethod("load", &Load),

  (target).Set("HOGDescriptor", FF::getFunction(ctor));
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  HistogramNormType::Init(env, exports);
#endif
};

void HOGDescriptor::New(const Napi::CallbackInfo& info) {
  constructorBinding<Constructor>(info);
}

void HOGDescriptor::GetDaimlerPeopleDetector(const Napi::CallbackInfo& info) {
  std::vector<float> detector = cv::HOGDescriptor::getDaimlerPeopleDetector();
  return FF::FloatArrayConverter::wrap(detector);
}

void HOGDescriptor::GetDefaultPeopleDetector(const Napi::CallbackInfo& info) {
  std::vector<float> detector = cv::HOGDescriptor::getDefaultPeopleDetector();
  return FF::FloatArrayConverter::wrap(detector);
}

void HOGDescriptor::CheckDetectorSize(const Napi::CallbackInfo& info) {
  return Napi::New(env, HOGDescriptor::unwrapSelf(info)->checkDetectorSize());
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
