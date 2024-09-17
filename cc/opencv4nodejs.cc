// #include "ExternalMemTracking.h"
#include "opencv_modules.h"
#include <napi.h>
//#include <uv.h>

#include "core/core.h"
  
//  #ifdef HAVE_OPENCV_HIGHGUI
//  #include "highgui/highgui.h"
//  #endif
//  #ifdef HAVE_OPENCV_CALIB3D
//  #include "calib3d/calib3d.h"
//  #endif
//  #ifdef HAVE_OPENCV_DNN
//  #include "dnn/dnn.h"
//  #endif
//  #ifdef HAVE_OPENCV_FACE
//  #include "face/face.h"
//  #endif
//  #ifdef HAVE_OPENCV_FEATURES2D
//  #include "features2d/features2d.h"
//  #endif
//  #ifdef HAVE_OPENCV_IMGPROC
//  #include "imgproc/imgproc.h"
//  #endif
//  #ifdef HAVE_IO
//  #include "io/io.h"
//  #endif
//  #ifdef HAVE_OPENCV_ML
//  #include "machinelearning/machinelearning.h"
//  #endif
//  #ifdef HAVE_OPENCV_OBJDETECT
//  #include "objdetect/objdetect.h"
//  #endif
//  #ifdef HAVE_OPENCV_PHOTO
//  #include "photo/photo.h"
//  #endif
//  #ifdef HAVE_OPENCV_TEXT
//  #include "text/text.h"
//  #endif
//  #ifdef HAVE_OPENCV_TRACKING
//  #include "tracking/tracking.h"
//  #endif
//  #ifdef HAVE_OPENCV_VIDEO
//  #include "video/video.h"
//  #endif
//  #ifdef HAVE_OPENCV_XFEATURES2D
//  #include "xfeatures2d/xfeatures2d.h"
//  #endif
//  #ifdef HAVE_OPENCV_XIMGPROC
//  #include "ximgproc/ximgproc.h"
//  #endif
//  #ifdef HAVE_OPENCV_IMG_HASH
//  #include "img_hash/img_hash.h"
//  #endif

int customCvErrorHandler(int status, const char* func_name, const char* err_msg, const char* file_name, int line, void* userdata) {
  std::string msg = "OpenCV Error: (" + std::string(err_msg) + ")"
                    + " in " + std::string(func_name)
                    + ", in file " + std::string(file_name)
                    + ", line " + std::to_string(line)
                    + ", status " + std::to_string(status);

  throw std::runtime_error(msg);
  return 0;
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
  // can be disabled by defining env variable: OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING
  // ExternalMemTracking::Init(env, exports);

  // override cv error handler to prevent printing cv errors and throw std::exception
  // instead, which can be catched and forwarded to node process
  // cv::redirectError(customCvErrorHandler);

  // hand craft version object { major: number; minor: number; revision: number;}
  Napi::Object version = Napi::Object::New(env);
  version.Set("major", Napi::Number::New(env, CV_VERSION_MAJOR));
  version.Set("minor", Napi::Number::New(env, CV_VERSION_MINOR));
  version.Set("revision", Napi::Number::New(env, CV_VERSION_REVISION));
  // attache the newly created version object
  exports.Set("version", version);

  // hand craft modules Object containing available modules {modulename: true; ...}
  Napi::Object modules = Napi::Object::New(env);
  // attache the newly created modules object
  exports.Set("modules", modules);
  exports.Set("xmodules", modules);

  modules.Set("core", Napi::Boolean::New(env, true));
  Core::Init(exports);

// #ifdef HAVE_OPENCV_HIGHGUI
//   modules.Set("highgui", Napi::Boolean::New(env, true));
//   Highgui::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_CALIB3D
//   modules.Set(FF::newString(env, "calib3d"), Napi::Boolean::New(env, true));
//   Calib3d::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_DNN
//   modules.Set("dnn", Napi::Boolean::New(env, true));
//   Dnn::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_FACE
//   modules.Set("face", Napi::Boolean::New(env, true));
//   Face::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_FEATURES2D
//   modules.Set(FF::newString(env, "features2d"), Napi::Boolean::New(env, true));
//   Features2d::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_IMGPROC
//   modules.Set("imgproc", Napi::Boolean::New(env, true));
//   Imgproc::Init(env, exports);
// #endif
// #ifdef HAVE_IO
//   modules.Set("io", Napi::Boolean::New(env, true));
//   Io::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_ML
//   modules.Set("ml", Napi::Boolean::New(env, true));
//   MachineLearning::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_OBJDETECT
//   modules.Set("objdetect", Napi::Boolean::New(env, true));
//   Objdetect::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_PHOTO
//   modules.Set("photo", Napi::Boolean::New(env, true));
//   Photo::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_TEXT
//   modules.Set("text", Napi::Boolean::New(env, true));
//   Text::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_TRACKING
//   modules.Set("tracking", Napi::Boolean::New(env, true));
//   Tracking::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_VIDEO
//   modules.Set("video", Napi::Boolean::New(env, true));
//   Video::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_XFEATURES2D
//   modules.Set(FF::newString(env, "xfeatures2d"), Napi::Boolean::New(env, true));
//   XFeatures2d::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_XIMGPROC
//   modules.Set("ximgproc", Napi::Boolean::New(env, true));
//   XImgproc::Init(env, exports);
// #endif
// #ifdef HAVE_OPENCV_IMG_HASH
//   modules.Set(FF::newString(env, "img_hash"), Napi::Boolean::New(env, true));
//   ImgHash::Init(env, exports);
// #endif
  return exports;
};

#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(opencv4nodejs, init)
#else
NODE_API_MODULE(opencv4nodejs, init)
#endif