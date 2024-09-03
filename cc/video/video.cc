#include "opencv_modules.h"

#ifdef HAVE_OPENCV_VIDEO

#include "BackgroundSubtractorKNN.h"
#include "BackgroundSubtractorMOG2.h"
#include "video.h"

Napi::Object Video(Napi::Env env, Napi::Object exports) {
  BackgroundSubtractorMOG2::Init(env, exports);
  BackgroundSubtractorKNN::Init(env, exports);
};

#endif