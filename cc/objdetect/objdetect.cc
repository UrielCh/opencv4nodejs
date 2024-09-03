#include "opencv_modules.h"

#ifdef HAVE_OPENCV_OBJDETECT

#include "CascadeClassifier.h"
#include "DetectionROI.h"
#include "HOGDescriptor.h"
#include "objdetect.h"

Napi::Object Objdetect(Napi::Env env, Napi::Object exports) {
  CascadeClassifier::Init(env, exports);
  HOGDescriptor::Init(env, exports);
  DetectionROI::Init(env, exports);
};

#endif