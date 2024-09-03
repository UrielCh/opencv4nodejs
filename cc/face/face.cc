#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FACE

#include "EigenFaceRecognizer.h"
#include "FisherFaceRecognizer.h"
#include "LBPHFaceRecognizer.h"
#include "face.h"

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
#include "FacemarkAAM.h"
#include "FacemarkAAMData.h"
#include "FacemarkAAMParams.h"
#include "FacemarkLBF.h"
#include "FacemarkLBFParams.h"
#endif

Napi::Object Face(Napi::Env env, Napi::Object exports) {
  EigenFaceRecognizer::Init(env, exports);
  FisherFaceRecognizer::Init(env, exports);
  LBPHFaceRecognizer::Init(env, exports);
#if CV_VERSION_GREATER_EQUAL(3, 4, 0)
  FacemarkAAM::Init(env, exports);
  FacemarkAAMData::Init(env, exports);
  FacemarkAAMParams::Init(env, exports);
  FacemarkLBF::Init(env, exports);
  FacemarkLBFParams::Init(env, exports);
#endif
};

#endif
