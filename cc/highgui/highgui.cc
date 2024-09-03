#include "opencv_modules.h"

#ifdef HAVE_OPENCV_HIGHGUI

#include "highgui.h"
#include "highguiBindings.h"
#include "highguiConstants.h"
#include "macros.h"
#include "opencv2/core.hpp"

Napi::Object Highgui(Napi::Env env, Napi::Object exports) {
  HighguiConstants::Init(env, exports);

  exports.Set("setWindowProperty", Napi::Function::New(env, Highgui::setWindowProperty));
  exports.Set("getWindowProperty", Napi::Function::New(env, Highgui::getWindowProperty));
  exports.Set("setWindowTitle", Napi::Function::New(env, Highgui::setWindowTitle));
  exports.Set("moveWindow", Napi::Function::New(env, Highgui::moveWindow));
  exports.Set("namedWindow", Napi::Function::New(env, Highgui::namedWindow));
  exports.Set("resizeWindow", Napi::Function::New(env, Highgui::resizeWindow));
  exports.Set("startWindowThread", Napi::Function::New(env, Highgui::startWindowThread));
};

void Highgui::setWindowProperty(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch(env, "Highgui::setWindowProperty");
  int prop_id;
  double prop_value;
  if (!info[0].IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }
  if (!info[1].IsNumber()) {
    return tryCatch.throwError("expected arg1 (prop_id) to be a number");
  }
  if (!info[2].IsNumber()) {
    return tryCatch.throwError("expected arg2 (prop_value) to be a number");
  }
  if (FF::IntConverter::arg(1, &prop_id, info) || FF::DoubleConverter::arg(2, &prop_value, info)) {
    return tryCatch.reThrow();
  }
  cv::setWindowProperty(FF::StringConverter::unwrapUnchecked(info[0]), prop_id, prop_value);
}

// void Io::MoveWindow(const Napi::CallbackInfo& info) {
// 	FF::TryCatch tryCatch(env, "Io::MoveWindow");
// 	std::string winName;
// 	int x, y;
// 	if (FF::StringConverter::arg(0, &winName, info) || FF::IntConverter::arg(1, &x, info) || FF::IntConverter::arg(2, &y, info)) {
// 		return tryCatch.reThrow();
// 	}
// 	cv::moveWindow(winName, x, y);
// }

void Highgui::moveWindow(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch(env, "Highgui::moveWindow");
  std::string winName;
  int x;
  int y;
  if (!info[0].IsString()) {
    return tryCatch.throwError("expected arg0 (winName) to be the window name");
  }
  if (!info[1].IsNumber()) {
    return tryCatch.throwError("expected arg1 (x) to be a number");
  }
  if (!info[2].IsNumber()) {
    return tryCatch.throwError("expected arg2 (y) to be a number");
  }
  FF::StringConverter::arg(0, &winName, info);
  FF::IntConverter::arg(2, &x, info);
  FF::IntConverter::arg(3, &y, info);
  cv::moveWindow(FF::StringConverter::unwrapUnchecked(info[0]), x, y);
}

void Highgui::setWindowTitle(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "Highgui::setWindowTitle");
  if (!info[0].IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }

  if (!info[1].IsString()) {
    return tryCatch.throwError("expected arg1 to be the new window title");
  }
  cv::setWindowTitle(FF::StringConverter::unwrapUnchecked(info[0]), FF::StringConverter::unwrapUnchecked(info[1]));
}

void Highgui::getWindowProperty(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "Highgui::getWindowProperty");
  int prop_id;

  if (!info[0].IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }
  if (!info[1].IsNumber()) {
    return tryCatch.throwError("expected arg1 (prop_id) to be a number");
  }
  FF::IntConverter::arg(1, &prop_id, info);
  info.GetReturnValue().Set(Nan::New(cv::getWindowProperty(FF::StringConverter::unwrapUnchecked(info[0]), prop_id)));
}

void Highgui::namedWindow(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "Highgui::namedWindow");

  std::string winName;
  int flags = cv::WINDOW_AUTOSIZE;

  if (!info[0].IsString()) {
    return tryCatch.throwError("expected arg0 (winName) to be the window name");
  }
  FF::IntConverter::optArg(1, &flags, info);
  FF::StringConverter::arg(0, &winName, info);
  cv::namedWindow(FF::StringConverter::unwrapUnchecked(info[0]), flags);
}

void Highgui::resizeWindow(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "Highgui::resizeWindow");
  int width;
  int height;

  if (!info[0].IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }

  if (!info[1].IsNumber()) {
    return tryCatch.throwError("expected arg1 (width) to be a number");
  }

  if (!info[2].IsNumber()) {
    return tryCatch.throwError("expected arg2 (height) to be a number");
  }

  FF::IntConverter::arg(1, &width, info);
  FF::IntConverter::arg(2, &height, info);
  cv::resizeWindow(FF::StringConverter::unwrapUnchecked(info[0]), width, height);
}

void Highgui::startWindowThread(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();  
  FF::TryCatch tryCatch(env, "Highgui::startWindowThread");
  int retval = cv::startWindowThread();
  info.GetReturnValue().Set(Nan::New(retval));
}

#endif
