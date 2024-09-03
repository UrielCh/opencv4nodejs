#include "opencv_modules.h"

#ifdef HAVE_OPENCV_DNN

#include "macros.h"
#include "opencv2/core.hpp"

#include "Net.h"
#include "NetBindings.h"

Napi::FunctionReference Net::constructor;

Napi::Object Net(Napi::Env env, Napi::Object exports) {
  Napi::FunctionReference ctor = Nan::New<v8::FunctionTemplate>(Net::New);
  Net::constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Net").ToLocalChecked());

  // setInput(blob: Mat, name?: string, scalefactor?: number, mean?: number): void;
  // setInput(blob: Mat, inputName?: string): void;
  Nan::SetPrototypeMethod(ctor, "setInput", SetInput);
  Nan::SetPrototypeMethod(ctor, "setInputAsync", SetInputAsync);
  // forward(inputName?: string): Mat;
  Nan::SetPrototypeMethod(ctor, "forward", Forward);
  Nan::SetPrototypeMethod(ctor, "forwardAsync", ForwardAsync);
  // getLayerNames(): string[];
  Nan::SetPrototypeMethod(ctor, "getLayerNames", GetLayerNames);
  Nan::SetPrototypeMethod(ctor, "getLayerNamesAsync", GetLayerNamesAsync);
  // getUnconnectedOutLayers(): number[];
  Nan::SetPrototypeMethod(ctor, "getUnconnectedOutLayers", GetUnconnectedOutLayers);
  Nan::SetPrototypeMethod(ctor, "getUnconnectedOutLayersAsync", GetUnconnectedOutLayersAsync);
  // dump(): string;
  Nan::SetPrototypeMethod(ctor, "dump", Dump);
  // setPreferableBackend(backendId: number): void;
  Nan::SetPrototypeMethod(ctor, "setPreferableBackend", SetPreferableBackend);
  // setPreferableTarget(targetId: number): void;
  Nan::SetPrototypeMethod(ctor, "setPreferableTarget", SetPreferableTarget);
  // getPerfProfile(): {	retval: number, timings: number[] };
  Nan::SetPrototypeMethod(ctor, "getPerfProfile", GetPerfProfile);

  target.Set("Net", FF::getFunction(ctor));
};

void Net::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "Net::New");
  FF_ASSERT_CONSTRUCT_CALL();
  Net* self = new Net();
  self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
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
  info.GetReturnValue().Set(FF::newString(self.dump()));
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

  info.GetReturnValue().Set(obj);
}

#endif
