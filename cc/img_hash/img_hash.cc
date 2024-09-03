#include "opencv_modules.h"

#ifdef HAVE_OPENCV_IMG_HASH

#include "PHash.h"
#include "img_hash.h"

Napi::Object ImgHash(Napi::Env env, Napi::Object exports) {
  PHash::Init(env, exports);
};

#endif
