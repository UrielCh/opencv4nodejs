#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "BFMatcher.h"
#include "DescriptorMatch.h"
#include "KeyPoint.h"
#include "KeyPointMatch.h"
#include "descriptorMatching.h"
#include "descriptorMatchingKnn.h"
#include "detectors/AGASTDetector.h"
#include "detectors/AKAZEDetector.h"
#include "detectors/BRISKDetector.h"
#include "detectors/FASTDetector.h"
#include "detectors/GFTTDetector.h"
#include "detectors/KAZEDetector.h"
#include "detectors/MSERDetector.h"
#include "detectors/ORBDetector.h"
#include "detectors/SimpleBlobDetector.h"
#include "features2d.h"

Napi::Object Features2d(Napi::Env env, Napi::Object exports) {
  KeyPoint::Init(env, exports);
  KeyPointMatch::Init(env, exports);
  DescriptorMatch::Init(env, exports);
  DescriptorMatching::Init(env, exports);
  DescriptorMatchingKnn::Init(env, exports);
  AGASTDetector::Init(env, exports);
  AKAZEDetector::Init(env, exports);
  BRISKDetector::Init(env, exports);
  BFMatcher::Init(env, exports);
  FASTDetector::Init(env, exports);
  GFTTDetector::Init(env, exports);
  KAZEDetector::Init(env, exports);
  MSERDetector::Init(env, exports);
  ORBDetector::Init(env, exports);
  SimpleBlobDetector::Init(env, exports);

  Napi::Object agastTypes = Napi::Object::New(env);
  FF_SET_JS_PROP(agastTypes, AGAST_5_8, Napi::Number::New(env, cv::AgastFeatureDetector::AGAST_5_8));
  FF_SET_JS_PROP(agastTypes, AGAST_7_12d, Napi::Number::New(env, cv::AgastFeatureDetector::AGAST_7_12d));
  FF_SET_JS_PROP(agastTypes, AGAST_7_12s, Napi::Number::New(env, cv::AgastFeatureDetector::AGAST_7_12s));
  FF_SET_JS_PROP(agastTypes, OAST_9_16, Napi::Number::New(env, cv::AgastFeatureDetector::OAST_9_16));
  FF_SET_JS_PROP(agastTypes, THRESHOLD, Napi::Number::New(env, cv::AgastFeatureDetector::THRESHOLD));
  FF_SET_JS_PROP(agastTypes, NONMAX_SUPPRESSION, Napi::Number::New(env, cv::AgastFeatureDetector::NONMAX_SUPPRESSION));
  FF_SET_JS_PROP(exports, "AGAST", agastTypes);

  Napi::Object akazeTypes = Napi::Object::New(env);
  FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_KAZE, Napi::Number::New(env, cv::AKAZE::DESCRIPTOR_KAZE));
  FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_KAZE, Napi::Number::New(env, cv::AKAZE::DESCRIPTOR_KAZE));
  FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_MLDB_UPRIGHT, Napi::Number::New(env, cv::AKAZE::DESCRIPTOR_MLDB_UPRIGHT));
  FF_SET_JS_PROP(akazeTypes, DESCRIPTOR_MLDB, Napi::Number::New(env, cv::AKAZE::DESCRIPTOR_MLDB));
  FF_SET_JS_PROP(exports, "AKAZE", akazeTypes);

  Napi::Object kazeTypes = Napi::Object::New(env);
  FF_SET_JS_PROP(kazeTypes, DIFF_PM_G1, Napi::Number::New(env, cv::KAZE::DIFF_PM_G1));
  FF_SET_JS_PROP(kazeTypes, DIFF_PM_G2, Napi::Number::New(env, cv::KAZE::DIFF_PM_G2));
  FF_SET_JS_PROP(kazeTypes, DIFF_WEICKERT, Napi::Number::New(env, cv::KAZE::DIFF_WEICKERT));
  FF_SET_JS_PROP(kazeTypes, DIFF_CHARBONNIER, Napi::Number::New(env, cv::KAZE::DIFF_CHARBONNIER));
  FF_SET_JS_PROP(exports, "KAZE", kazeTypes);

  Napi::Object fastTypes = Napi::Object::New(env);
  FF_SET_JS_PROP(fastTypes, TYPE_5_8, Napi::Number::New(env, cv::FastFeatureDetector::TYPE_5_8));
  FF_SET_JS_PROP(fastTypes, TYPE_7_12, Napi::Number::New(env, cv::FastFeatureDetector::TYPE_7_12));
  FF_SET_JS_PROP(fastTypes, TYPE_9_16, Napi::Number::New(env, cv::FastFeatureDetector::TYPE_9_16));
  FF_SET_JS_PROP(fastTypes, THRESHOLD, Napi::Number::New(env, cv::FastFeatureDetector::THRESHOLD));
  FF_SET_JS_PROP(fastTypes, NONMAX_SUPPRESSION, Napi::Number::New(env, cv::FastFeatureDetector::NONMAX_SUPPRESSION));
  FF_SET_JS_PROP(exports, "FAST", fastTypes);

  Napi::Object orbTypes = Napi::Object::New(env);
  FF_SET_JS_PROP(orbTypes, HARRIS_SCORE, Napi::Number::New(env, cv::ORB::HARRIS_SCORE));
  FF_SET_JS_PROP(orbTypes, FAST_SCORE, Napi::Number::New(env, cv::ORB::FAST_SCORE));
  FF_SET_JS_PROP(orbTypes, kBytes, Napi::Number::New(env, cv::ORB::kBytes));
  FF_SET_JS_PROP(exports, "ORB", orbTypes);

  exports.Set("drawKeyPoints", Napi::Function::New(env, Features2d::DrawKeyPoints));
  exports.Set("drawMatches", Napi::Function::New(env, Features2d::DrawMatches));
};

// export function drawKeyPoints(img: Mat, keyPoints: KeyPoint[]): Mat;
Napi::Value Features2d::DrawKeyPoints(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Features2d::DrawKeyPoints");

  cv::Mat img;
  std::vector<cv::KeyPoint> kps;
  if (
      Mat::Converter::arg(0, &img, info) || KeyPoint::ArrayConverter::arg(1, &kps, info)) {
    return tryCatch.reThrow();
  }

  cv::Mat drawMat;
  cv::drawKeypoints(img, kps, drawMat);
  return Mat::Converter::wrap(drawMat);
}

Napi::Value Features2d::DrawMatches(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Features2d::DrawMatches");

  cv::Mat img1, img2;
  std::vector<cv::KeyPoint> kps1, kps2;
  std::vector<cv::DMatch> dMatches;
  if (
      Mat::Converter::arg(0, &img1, info) || Mat::Converter::arg(1, &img2, info) || KeyPoint::ArrayConverter::arg(2, &kps1, info) || KeyPoint::ArrayConverter::arg(3, &kps2, info) || DescriptorMatch::ArrayConverter::arg(4, &dMatches, info)) {
    return tryCatch.reThrow();
  }

  cv::Mat drawMat;
  cv::drawMatches(img1, kps1, img2, kps2, dMatches, drawMat);
  return Mat::Converter::wrap(drawMat);
}

#endif
