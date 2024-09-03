#include "opencv_modules.h"

#ifdef HAVE_OPENCV_DNN

#include "macros.h"
#include "opencv2/core.hpp"

#include "Net.h"
#include "NetBindings.h"

Napi::FunctionReference Net::constructor;

Napi::Object Net(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, Net::New));
  Net::constructor.Reset(ctor);

  ctor->SetClassName(Napi::String::New(env, "Net"));

  // setInput(blob: Mat, name?: string, scalefactor?: number, mean?: number): void;
  // setInput(blob: Mat, inputName?: string): void;
  InstanceMethod("setInput", &SetInput),
  InstanceMethod("setInputAsync", &SetInputAsync),
  // forward(inputName?: string): Mat;
  InstanceMethod("forward", &Forward),
  InstanceMethod("forwardAsync", &ForwardAsync),
  // getLayerNames(): string[];
  InstanceMethod("getLayerNames", &GetLayerNames),
  InstanceMethod("getLayerNamesAsync", &GetLayerNamesAsync),
  // getUnconnectedOutLayers(): number[];
  InstanceMethod("getUnconnectedOutLayers", &GetUnconnectedOutLayers),
  InstanceMethod("getUnconnectedOutLayersAsync", &GetUnconnectedOutLayersAsync),
  // dump(): string;
  InstanceMethod("dump", &Dump),
  // setPreferableBackend(backendId: number): void;
  InstanceMethod("setPreferableBackend", &SetPreferableBackend),
  // setPreferableTarget(targetId: number): void;
  InstanceMethod("setPreferableTarget", &SetPreferableTarget),
  // getPerfProfile(): {	retval: number, timings: number[] };
  InstanceMethod("getPerfProfile", &GetPerfProfile),

  target.Set("Net", FF::getFunction(ctor));
};

void Net::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Net::New");
  FF_ASSERT_CONSTRUCT_CALL();
  Net* self = new Net();
  self->Wrap(info.Holder());
  return info.Holder();
}

void Net::SetInput(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<NetBindings::SetInputWorker>(Net::unwrapSelf(info)),
      "Net::SetInput",
      info);
}

void Net::SetInputAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<NetBindings::SetInputWorker>(Net::unwrapSelf(info)),
      "Net::SetInputAsync",
      info);
}

void Net::Forward(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<NetBindings::ForwardWorker>(Net::unwrapSelf(info)),
      "Net::Forward",
      info);
}

void Net::ForwardAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<NetBindings::ForwardWorker>(Net::unwrapSelf(info)),
      "Net::ForwardAsync",
      info);
}

void Net::GetLayerNames(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<NetBindings::GetLayerNamesWorker>(Net::unwrapSelf(info)),
      "Net::GetLayerNames",
      info);
}

void Net::GetLayerNamesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<NetBindings::GetLayerNamesWorker>(Net::unwrapSelf(info)),
      "Net::GetLayerNamesAsync",
      info);
}

void Net::GetUnconnectedOutLayers(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<NetBindings::GetUnconnectedOutLayersWorker>(Net::unwrapSelf(info)),
      "Net::GetUnconnectedOutLayers",
      info);
}

void Net::GetUnconnectedOutLayersAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<NetBindings::GetUnconnectedOutLayersWorker>(Net::unwrapSelf(info)),
      "Net::GetUnconnectedOutLayersAsync",
      info);
}

void Net::Dump(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Core::Dump");
  cv::dnn::Net self = Net::unwrapSelf(info);
  return FF::newString(self.dump());
}

void Net::SetPreferableBackend(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Core::SetPreferableBackend");
  cv::dnn::Net self = Net::unwrapSelf(info);
  int backendId;
  if (FF::IntConverter::arg(0, &backendId, info)) {
    return tryCatch.reThrow();
  }
  self.setPreferableBackend(backendId);
}

void Net::SetPreferableTarget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Core::SetPreferableTarget");
  cv::dnn::Net self = Net::unwrapSelf(info);
  int targetId;
  if (FF::IntConverter::arg(0, &targetId, info)) {
    return tryCatch.reThrow();
  }
  self.setPreferableTarget(targetId);
}

// ret {	retval: number, timings: number[] }

void Net::GetPerfProfile(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Core::GetPerfProfile");
  cv::dnn::Net self = Net::unwrapSelf(info);

  // int64 cv::dnn::Net::getPerfProfile	(	std::vector< double > & 	timings	)
  std::vector<double> layersTimes;
  int64 time = self.getPerfProfile(layersTimes);

  Napi::Object obj = Napi::Object::New(env);

  obj.Set("retval", FF::DoubleConverter::wrap(time));
  obj.Set("timings", FF::DoubleArrayConverter::wrap(layersTimes));

  return obj;
}

#endif
