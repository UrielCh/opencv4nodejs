#include "opencv_modules.h"

#ifdef HAVE_OPENCV_DNN

#include "dnn.h"
#include "dnnBindings.h"
#include "macros.h"
#include "opencv2/core.hpp"

#define FF_CONST_TYPE(CONST, VALUE) \
  Nan::Set(target, Nan::New<v8::String>(#CONST).ToLocalChecked(), Nan::New<v8::Integer>(VALUE));

Napi::Object Dnn(Napi::Env env, Napi::Object exports) {

#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  FF_CONST_TYPE(DNN_BACKEND_OPENCV, cv::dnn::DNN_BACKEND_OPENCV)
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 1)
  FF_CONST_TYPE(DNN_BACKEND_INFERENCE_ENGINE, cv::dnn::DNN_BACKEND_INFERENCE_ENGINE)
#endif

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  FF_CONST_TYPE(DNN_BACKEND_HALIDE, cv::dnn::DNN_BACKEND_HALIDE)
#endif

#if CV_VERSION_GREATER_EQUAL(4, 2, 0)
  FF_CONST_TYPE(DNN_BACKEND_CUDA, cv::dnn::DNN_BACKEND_CUDA)
#endif

  FF_CONST_TYPE(DNN_TARGET_CPU, cv::dnn::DNN_TARGET_CPU)

#if CV_VERSION_GREATER_EQUAL(3, 3, 0)
  FF_CONST_TYPE(DNN_TARGET_OPENCL, cv::dnn::DNN_TARGET_OPENCL)
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  FF_CONST_TYPE(DNN_TARGET_OPENCL_FP16, cv::dnn::DNN_TARGET_OPENCL_FP16)
  FF_CONST_TYPE(DNN_TARGET_MYRIAD, cv::dnn::DNN_TARGET_MYRIAD)
#endif

#if CV_VERSION_GREATER_EQUAL(4, 2, 0)
  FF_CONST_TYPE(DNN_TARGET_CUDA, cv::dnn::DNN_TARGET_CUDA)
  FF_CONST_TYPE(DNN_TARGET_CUDA_FP16, cv::dnn::DNN_TARGET_CUDA_FP16)
#endif

#if CV_VERSION_GREATER_EQUAL(4, 5, 1)
  FF_CONST_TYPE(DNN_TARGET_HDDL, cv::dnn::DNN_TARGET_HDDL)
#endif

#if CV_VERSION_GREATER_EQUAL(4, 8, 0)
  FF_CONST_TYPE(DNN_BACKEND_WEBNN, cv::dnn::DNN_BACKEND_WEBNN)
#endif

  Net::Init(env, exports);

  exports.Set("readNetFromTensorflow", Napi::Function::New(env, Dnn::ReadNetFromTensorflow));
  exports.Set("readNetFromTensorflowAsync", Napi::Function::New(env, Dnn::ReadNetFromTensorflowAsync));
  exports.Set("readNetFromCaffe", Napi::Function::New(env, Dnn::ReadNetFromCaffe));
  exports.Set("readNetFromCaffeAsync", Napi::Function::New(env, Dnn::ReadNetFromCaffeAsync));
  exports.Set("blobFromImage", Napi::Function::New(env, Dnn::BlobFromImage));
  exports.Set("blobFromImageAsync", Napi::Function::New(env, Dnn::BlobFromImageAsync));
  exports.Set("blobFromImages", Napi::Function::New(env, Dnn::BlobFromImages));
  exports.Set("blobFromImagesAsync", Napi::Function::New(env, Dnn::BlobFromImagesAsync));
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  exports.Set("readNetFromDarknet", Napi::Function::New(env, Dnn::ReadNetFromDarknet));
  exports.Set("readNetFromDarknetAsync", Napi::Function::New(env, Dnn::ReadNetFromDarknetAsync));
  exports.Set("NMSBoxes", Napi::Function::New(env, Dnn::NMSBoxes));
#endif
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  exports.Set("readNetFromONNX", Napi::Function::New(env, Dnn::ReadNetFromONNX));
  exports.Set("readNetFromONNXAsync", Napi::Function::New(env, Dnn::ReadNetFromONNXAsync));
#endif
#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
  exports.Set("readNet", Napi::Function::New(env, Dnn::ReadNet));
  exports.Set("readNetAsync", Napi::Function::New(env, Dnn::ReadNetAsync));
#endif
};

void Dnn::ReadNetFromTensorflow(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetFromTensorflowWorker>(), "ReadNetFromTensorflow", info);
}

void Dnn::ReadNetFromTensorflowAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetFromTensorflowWorker>(), "ReadNetFromTensorflowAsync", info);
}

void Dnn::ReadNetFromCaffe(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetFromCaffeWorker>(), "ReadNetFromCaffe", info);
}

void Dnn::ReadNetFromCaffeAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetFromCaffeWorker>(), "ReadNetFromCaffeAsync", info);
}

void Dnn::BlobFromImage(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::BlobFromImageWorker>(true), "BlobFromImage", info);
}

void Dnn::BlobFromImageAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::BlobFromImageWorker>(true), "BlobFromImageAsync", info);
}

void Dnn::BlobFromImages(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::BlobFromImageWorker>(false), "BlobFromImages", info);
}

void Dnn::BlobFromImagesAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::BlobFromImageWorker>(false), "BlobFromImagesAsync", info);
}

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
void Dnn::ReadNetFromDarknet(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetFromDarknetWorker>(), "ReadNetFromDarknet", info);
}

void Dnn::ReadNetFromDarknetAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetFromDarknetWorker>(), "ReadNetFromDarknetAsync", info);
}

void Dnn::NMSBoxes(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::NMSBoxes>(), "NMSBoxes", info);
}
#endif

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
void Dnn::ReadNetFromONNX(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetFromONNXWorker>(), "ReadNetFromONNX", info);
}

void Dnn::ReadNetFromONNXAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetFromONNXWorker>(), "ReadNetFromONNXAsync", info);
}
#endif

#if CV_VERSION_GREATER_EQUAL(3, 4, 2)
void Dnn::ReadNet(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(std::make_shared<DnnBindings::ReadNetWorker>(), "ReadNet", info);
}

void Dnn::ReadNetAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(std::make_shared<DnnBindings::ReadNetWorker>(), "ReadNetAsync", info);
}
#endif

#endif
