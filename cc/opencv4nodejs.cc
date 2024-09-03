#include "ExternalMemTracking.h"
#include "opencv_modules.h"
#include <node.h>

#include "core/core.h"

#ifdef HAVE_OPENCV_HIGHGUI
#include "highgui/highgui.h"
#endif
#ifdef HAVE_OPENCV_CALIB3D
#include "calib3d/calib3d.h"
#endif
#ifdef HAVE_OPENCV_DNN
#include "dnn/dnn.h"
#endif
#ifdef HAVE_OPENCV_FACE
#include "face/face.h"
#endif
#ifdef HAVE_OPENCV_FEATURES2D
#include "features2d/features2d.h"
#endif
#ifdef HAVE_OPENCV_IMGPROC
#include "imgproc/imgproc.h"
#endif
#ifdef HAVE_IO
#include "io/io.h"
#endif
#ifdef HAVE_OPENCV_ML
#include "machinelearning/machinelearning.h"
#endif
#ifdef HAVE_OPENCV_OBJDETECT
#include "objdetect/objdetect.h"
#endif
#ifdef HAVE_OPENCV_PHOTO
#include "photo/photo.h"
#endif
#ifdef HAVE_OPENCV_TEXT
#include "text/text.h"
#endif
#ifdef HAVE_OPENCV_TRACKING
#include "tracking/tracking.h"
#endif
#ifdef HAVE_OPENCV_VIDEO
#include "video/video.h"
#endif
#ifdef HAVE_OPENCV_XFEATURES2D
#include "xfeatures2d/xfeatures2d.h"
#endif
#ifdef HAVE_OPENCV_XIMGPROC
#include "ximgproc/ximgproc.h"
#endif
#ifdef HAVE_OPENCV_IMG_HASH
#include "img_hash/img_hash.h"
#endif

int customCvErrorHandler(int status, const char* func_name, const char* err_msg, const char* file_name, int line, void* userdata) {
  std::string msg = "OpenCV Error: (" + std::string(err_msg) + ")"
                    + " in " + std::string(func_name)
                    + ", in file " + std::string(file_name)
                    + ", line " + std::to_string(line)
                    + ", status " + std::to_string(status);

  throw std::runtime_error(msg);
  return 0;
}

NAN_MODULE_INIT(init) {
  // can be disabled by defining env variable: OPENCV4NODEJS_DISABLE_EXTERNAL_MEM_TRACKING
  ExternalMemTracking::Init(env, exports);

  // override cv error handler to prevent printing cv errors and throw std::exception
  // instead, which can be catched and forwarded to node process
  cv::redirectError(customCvErrorHandler);

  // hand craft version object { major: number; minor: number; revision: number;}
  Napi::Object version = Napi::Object::New(env);
  Nan::Set(version, FF::newString(env, "major"), Nan::New(CV_VERSION_MAJOR));
  Nan::Set(version, FF::newString(env, "minor"), Nan::New(CV_VERSION_MINOR));
  Nan::Set(version, FF::newString(env, "revision"), Nan::New(CV_VERSION_REVISION));
  // attache the newly created version object
  Nan::Set(target, FF::newString(env, "version"), version);

  // hand craft modules Object containing available modules {modulename: true; ...}
  Napi::Object modules = Napi::Object::New(env);
  // attache the newly created modules object
  Nan::Set(target, FF::newString(env, "modules"), modules);
  Nan::Set(target, FF::newString(env, "xmodules"), modules);

  Nan::Set(modules, FF::newString(env, "core"), Nan::New(true));
  Core::Init(env, exports);

#ifdef HAVE_OPENCV_HIGHGUI
  Nan::Set(modules, FF::newString(env, "highgui"), Nan::New(true));
  Highgui::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_CALIB3D
  Nan::Set(modules, FF::newString(env, "calib3d"), Nan::New(true));
  Calib3d::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_DNN
  Nan::Set(modules, FF::newString(env, "dnn"), Nan::New(true));
  Dnn::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_FACE
  Nan::Set(modules, FF::newString(env, "face"), Nan::New(true));
  Face::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_FEATURES2D
  Nan::Set(modules, FF::newString(env, "features2d"), Nan::New(true));
  Features2d::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_IMGPROC
  Nan::Set(modules, FF::newString(env, "imgproc"), Nan::New(true));
  Imgproc::Init(env, exports);
#endif
#ifdef HAVE_IO
  Nan::Set(modules, FF::newString(env, "io"), Nan::New(true));
  Io::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_ML
  Nan::Set(modules, FF::newString(env, "ml"), Nan::New(true));
  MachineLearning::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_OBJDETECT
  Nan::Set(modules, FF::newString(env, "objdetect"), Nan::New(true));
  Objdetect::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_PHOTO
  Nan::Set(modules, FF::newString(env, "photo"), Nan::New(true));
  Photo::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_TEXT
  Nan::Set(modules, FF::newString(env, "text"), Nan::New(true));
  Text::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_TRACKING
  Nan::Set(modules, FF::newString(env, "tracking"), Nan::New(true));
  Tracking::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_VIDEO
  Nan::Set(modules, FF::newString(env, "video"), Nan::New(true));
  Video::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_XFEATURES2D
  Nan::Set(modules, FF::newString(env, "xfeatures2d"), Nan::New(true));
  XFeatures2d::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_XIMGPROC
  Nan::Set(modules, FF::newString(env, "ximgproc"), Nan::New(true));
  XImgproc::Init(env, exports);
#endif
#ifdef HAVE_OPENCV_IMG_HASH
  Nan::Set(modules, FF::newString(env, "img_hash"), Nan::New(true));
  ImgHash::Init(env, exports);
#endif
};

#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(opencv4nodejs, init)
#else
NODE_MODULE(opencv4nodejs, init)
#endif