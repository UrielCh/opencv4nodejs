#include "opencv_modules.h"

#ifdef HAVE_OPENCV_TEXT

#include "text.h"
#include "textBindings.h"

Napi::Object Text(Napi::Env env, Napi::Object exports) {
  OCRHMMDecoder::Init(env, exports);
  OCRHMMClassifier::Init(env, exports);
  exports.Set("loadOCRHMMClassifierNM", Napi::Function::New(env, Text::LoadOCRHMMClassifierNM));
  exports.Set("loadOCRHMMClassifierNMAsync", Napi::Function::New(env, Text::LoadOCRHMMClassifierNMAsync));
#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  exports.Set("loadOCRHMMClassifierCNN", Napi::Function::New(env, Text::LoadOCRHMMClassifierCNN));
  exports.Set("loadOCRHMMClassifierCNNAsync", Napi::Function::New(env, Text::LoadOCRHMMClassifierCNNAsync));
  exports.Set("createOCRHMMTransitionsTable", Napi::Function::New(env, Text::CreateOCRHMMTransitionsTable));
  exports.Set("createOCRHMMTransitionsTableAsync", Napi::Function::New(env, Text::CreateOCRHMMTransitionsTableAsync));
#endif
}

void Text::LoadOCRHMMClassifierNM(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<TextBindings::LoadOCRHMMClassifierNMWorker>(),
      "Text::LoadOCRHMMClassifierNM",
      info);
}

void Text::LoadOCRHMMClassifierNMAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<TextBindings::LoadOCRHMMClassifierNMWorker>(),
      "Text::LoadOCRHMMClassifierNMAsync",
      info);
}

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)

void Text::LoadOCRHMMClassifierCNN(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<TextBindings::LoadOCRHMMClassifierCNNWorker>(),
      "Text::LoadOCRHMMClassifierCNN",
      info);
}

void Text::LoadOCRHMMClassifierCNNAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<TextBindings::LoadOCRHMMClassifierCNNWorker>(),
      "Text::LoadOCRHMMClassifierCNNAsync",
      info);
}

void Text::CreateOCRHMMTransitionsTable(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<TextBindings::CreateOCRHMMTransitionsTableWorker>(),
      "Text::CreateOCRHMMTransitionsTable",
      info);
}

void Text::CreateOCRHMMTransitionsTableAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<TextBindings::CreateOCRHMMTransitionsTableWorker>(),
      "Text::CreateOCRHMMTransitionsTableAsync",
      info);
}
#endif

#endif
