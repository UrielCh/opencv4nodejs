#include "coreConstants.h"

#define FF_SET_JS_PROP(obj, prop, val) (obj).Set(#prop, val)

#define FF_SET_CV_CONSTANT(obj, cvConstant) \
  FF_SET_JS_PROP(obj, cvConstant, Napi::Number::New(env, cvConstant));

#define FF_SET_CONST_WITH_VALUE(obj, constant, val) \
  FF_SET_JS_PROP(obj, constant, val);

#define FF_SET_CV_CONSTSTR(obj, constant, cvConstant) \
  FF_SET_JS_PROP(obj, constant, Napi::String::New(env, cvConstant));

#define CV_VERSION_GREATER_EQUAL(major, minor, revision)         \
  (                                                              \
      CV_VERSION_MAJOR > major                                   \
      || (CV_VERSION_MAJOR == major && CV_VERSION_MINOR > minor) \
      || (CV_VERSION_MAJOR == major && CV_VERSION_MINOR == minor && CV_VERSION_REVISION >= revision))

using namespace cv;

void CoreConstants::Init(Napi::Object exports) {
  Napi::Env env = exports.Env();
  FF_SET_CV_CONSTANT(exports, NORM_INF);
  FF_SET_CV_CONSTANT(exports, NORM_L1);
  FF_SET_CV_CONSTANT(exports, NORM_L2);
  FF_SET_CV_CONSTANT(exports, NORM_L2SQR);
  FF_SET_CV_CONSTANT(exports, NORM_HAMMING);
  FF_SET_CV_CONSTANT(exports, NORM_HAMMING2);
  FF_SET_CV_CONSTANT(exports, NORM_TYPE_MASK);
  FF_SET_CV_CONSTANT(exports, NORM_RELATIVE);
  FF_SET_CV_CONSTANT(exports, NORM_MINMAX);

  FF_SET_CV_CONSTANT(exports, KMEANS_RANDOM_CENTERS);
  FF_SET_CV_CONSTANT(exports, KMEANS_PP_CENTERS);
  FF_SET_CV_CONSTANT(exports, KMEANS_USE_INITIAL_LABELS);

  Napi::Object termCriteriaTypes = Napi::Object::New(env);
  FF_SET_JS_PROP(termCriteriaTypes, COUNT, Napi::Number::New(env, cv::TermCriteria::COUNT));
  FF_SET_JS_PROP(termCriteriaTypes, MAX_ITER, Napi::Number::New(env, cv::TermCriteria::MAX_ITER));
  FF_SET_JS_PROP(termCriteriaTypes, EPS, Napi::Number::New(env, cv::TermCriteria::EPS));
  exports.Set("termCriteria", termCriteriaTypes);

  Napi::Object haarCascades = Napi::Object::New(env);
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_EYE, "./haarcascade_eye.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_EYE_TREE_EYEGLASSES, "./haarcascade_eye_tree_eyeglasses.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_FRONTALCATFACE, "./haarcascade_frontalcatface.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_FRONTALCATFACE_EXTENDED, "./haarcascade_frontalcatface_extended.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_FRONTALFACE_ALT, "./haarcascade_frontalface_alt.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_FRONTALFACE_ALT2, "./haarcascade_frontalface_alt2.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_FRONTALFACE_ALT_TREE, "./haarcascade_frontalface_alt_tree.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_FRONTALFACE_DEFAULT, "./haarcascade_frontalface_default.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_FULLBODY, "./haarcascade_fullbody.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_LEFTEYE_2SPLITS, "./haarcascade_lefteye_2splits.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_LICENCE_PLATE_RUS_16STAGES, "./haarcascade_licence_plate_rus_16stages.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_LOWERBODY, "./haarcascade_lowerbody.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_PROFILEFACE, "./haarcascade_profileface.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_RIGHTEYE_2SPLITS, "./haarcascade_righteye_2splits.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_RUSSIAN_PLATE_NUMBER, "./haarcascade_russian_plate_number.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_SMILE, "./haarcascade_smile.xml");
  FF_SET_CV_CONSTSTR(haarCascades, HAAR_UPPERBODY, "./haarcascade_upperbody.xml");
  exports.Set("haarCascades", haarCascades);

  Napi::Object lbpCascades = Napi::Object::New(env);
  FF_SET_CV_CONSTSTR(lbpCascades, LBP_FRONTALCATFACE, "./lbpcascade_frontalcatface.xml");
  FF_SET_CV_CONSTSTR(lbpCascades, LBP_FRONTALFACE, "./lbpcascade_frontalface.xml");
  FF_SET_CV_CONSTSTR(lbpCascades, LBP_FRONTALFACE_IMPROVED, "./lbpcascade_frontalface_improved.xml");
  FF_SET_CV_CONSTSTR(lbpCascades, LBP_PROFILEFACE, "./lbpcascade_profileface.xml");
  FF_SET_CV_CONSTSTR(lbpCascades, LBP_SILVERWARE, "./lbpcascade_silverware.xml");
  lbpCascades.Set("lbpCascades", lbpCascades);

  FF_SET_CV_CONSTANT(exports, REDUCE_SUM);
  FF_SET_CV_CONSTANT(exports, REDUCE_AVG);
  FF_SET_CV_CONSTANT(exports, REDUCE_MAX);
  FF_SET_CV_CONSTANT(exports, REDUCE_MIN);

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  FF_SET_CV_CONSTANT(exports, ROTATE_90_CLOCKWISE);
  FF_SET_CV_CONSTANT(exports, ROTATE_180);
  FF_SET_CV_CONSTANT(exports, ROTATE_90_COUNTERCLOCKWISE);
#endif

  FF_SET_CV_CONSTANT(exports, DECOMP_LU);
  FF_SET_CV_CONSTANT(exports, DECOMP_CHOLESKY);
  FF_SET_CV_CONSTANT(exports, DECOMP_EIG);
  FF_SET_CV_CONSTANT(exports, DECOMP_SVD);
  FF_SET_CV_CONSTANT(exports, DECOMP_QR);
  FF_SET_CV_CONSTANT(exports, DECOMP_NORMAL);

  FF_SET_CV_CONSTANT(exports, BORDER_CONSTANT);
  FF_SET_CV_CONSTANT(exports, BORDER_REPLICATE);
  FF_SET_CV_CONSTANT(exports, BORDER_REFLECT);
  FF_SET_CV_CONSTANT(exports, BORDER_WRAP);
  FF_SET_CV_CONSTANT(exports, BORDER_REFLECT_101);
  FF_SET_CV_CONSTANT(exports, BORDER_TRANSPARENT);
  FF_SET_CV_CONSTANT(exports, BORDER_ISOLATED);
  FF_SET_CV_CONSTANT(exports, BORDER_DEFAULT);
}
