#include "opencv_modules.h"

#ifdef HAVE_OPENCV_PHOTO

#include "MatPhoto.h"
#include "photoBindings.h"

void MatPhoto::Init(Napi::FunctionReference ctor) {
  Nan::SetPrototypeMethod(ctor, "seamlessClone", SeamlessClone);
  Nan::SetPrototypeMethod(ctor, "seamlessCloneAsync", SeamlessCloneAsync);
};

void MatPhoto::SeamlessClone(const Napi::CallbackInfo& info) {
  Mat::syncBinding<PhotoBindings::SeamlessClone>("SeamlessClone", info);
}

void MatPhoto::SeamlessCloneAsync(const Napi::CallbackInfo& info) {
  Mat::asyncBinding<PhotoBindings::SeamlessClone>("SeamlessClone", info);
}

#endif