#include "opencv_modules.h"

#ifdef HAVE_OPENCV_PHOTO

#include "photo.h"
#include "photoBindings.h"
#include "photoConstants.h"

Napi::Object Photo(Napi::Env env, Napi::Object exports) {
  PhotoConstants::Init(env, exports);
  exports.Set("fastNlMeansDenoisingColored", Napi::Function::New(env, Photo::FastNlMeansDenoisingColored));
  exports.Set("fastNlMeansDenoisingColoredAsync", Napi::Function::New(env, Photo::FastNlMeansDenoisingColoredAsync));
  exports.Set("inpaint", Napi::Function::New(env, Photo::Inpaint));
  exports.Set("inpaintAsync", Napi::Function::New(env, Photo::InpaintAsync));
  exports.Set("seamlessClone", Napi::Function::New(env, Photo::SeamlessClone));
  exports.Set("seamlessCloneAsync", Napi::Function::New(env, Photo::SeamlessCloneAsync));
};

void Photo::FastNlMeansDenoisingColored(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<PhotoBindings::FastNlMeansDenoisingColoredWorker>(),
      "Photo::FastNlMeansDenoisingColored",
      info);
}

void Photo::FastNlMeansDenoisingColoredAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<PhotoBindings::FastNlMeansDenoisingColoredWorker>(),
      "Photo::FastNlMeansDenoisingColoredAsync",
      info);
}

void Photo::Inpaint(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<PhotoBindings::InpaintWorker>(),
      "Photo::Inpaint",
      info);
}

void Photo::InpaintAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<PhotoBindings::InpaintWorker>(),
      "Photo::InpaintAsync",
      info);
}

void Photo::SeamlessClone(const Napi::CallbackInfo& info) {
  FF::syncBinding<PhotoBindings::SeamlessClone>("Photo", "SeamlessClone", info);
}

void Photo::SeamlessCloneAsync(const Napi::CallbackInfo& info) {
  FF::asyncBinding<PhotoBindings::SeamlessClone>("Photo", "SeamlessClone", info);
}

#endif
