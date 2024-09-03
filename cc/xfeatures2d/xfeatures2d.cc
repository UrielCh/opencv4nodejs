#include "opencv_modules.h"

#ifdef HAVE_OPENCV_XFEATURES2D

#include "SIFTDetector.h"
#include "SURFDetector.h"
#include "xfeatures2d.h"

Napi::Object XFeatures2d(Napi::Env env, Napi::Object exports) {
  SIFTDetector::Init(env, exports);
  SURFDetector::Init(env, exports);
};

#endif // HAVE_OPENCV_XFEATURES2D