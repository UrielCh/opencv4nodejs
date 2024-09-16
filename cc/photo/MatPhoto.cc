#include "opencv_modules.h"

#ifdef HAVE_OPENCV_PHOTO

#include "MatPhoto.h"
#include "photoBindings.h"

void MatPhoto::Init(Napi::Env env, Napi::Object exports) {
  InstanceMethod("seamlessClone", &SeamlessClone),
  InstanceMethod("seamlessCloneAsync", &SeamlessCloneAsync),
};

void MatPhoto::SeamlessClone(const Napi::CallbackInfo& info) {
  Mat::syncBinding<PhotoBindings::SeamlessClone>("SeamlessClone", info);
}

void MatPhoto::SeamlessCloneAsync(const Napi::CallbackInfo& info) {
  Mat::asyncBinding<PhotoBindings::SeamlessClone>("SeamlessClone", info);
}

#endif