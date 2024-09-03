#include "opencv_modules.h"

#ifdef HAVE_IO

#include "io.h"
#include "ioBindings.h"
#include "ioConstants.h"

Napi::Object Io(Napi::Env env, Napi::Object exports) {
  IoConstants::Init(env, exports);
  VideoCapture::Init(env, exports);
  VideoWriter::Init(env, exports);

  exports.Set("imread", Napi::Function::New(env, Io::Imread));
  exports.Set("imshow", Napi::Function::New(env, Io::Imshow));
  exports.Set("imshowWait", Napi::Function::New(env, Io::ImshowWait));
  exports.Set("imwrite", Napi::Function::New(env, Io::Imwrite));
  exports.Set("waitKey", Napi::Function::New(env, Io::WaitKey));
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  exports.Set("waitKeyEx", Napi::Function::New(env, Io::WaitKeyEx));
#endif
  exports.Set("imencode", Napi::Function::New(env, Io::Imencode));
  exports.Set("imdecode", Napi::Function::New(env, Io::Imdecode));
  exports.Set("destroyWindow", Napi::Function::New(env, Io::DestroyWindow));
  exports.Set("destroyAllWindows", Napi::Function::New(env, Io::DestroyAllWindows));

  exports.Set("imreadAsync", Napi::Function::New(env, Io::ImreadAsync));
  exports.Set("imwriteAsync", Napi::Function::New(env, Io::ImwriteAsync));
  exports.Set("imencodeAsync", Napi::Function::New(env, Io::ImencodeAsync));
  exports.Set("imdecodeAsync", Napi::Function::New(env, Io::ImdecodeAsync));

  FF_SET_JS_PROP(target, IMREAD_UNCHANGED, Napi::Number::New(env, cv::IMREAD_UNCHANGED));
  FF_SET_JS_PROP(target, IMREAD_GRAYSCALE, Napi::Number::New(env, cv::IMREAD_GRAYSCALE));
  FF_SET_JS_PROP(target, IMREAD_COLOR, Napi::Number::New(env, cv::IMREAD_COLOR));
  FF_SET_JS_PROP(target, IMREAD_ANYDEPTH, Napi::Number::New(env, cv::IMREAD_ANYDEPTH));
  FF_SET_JS_PROP(target, IMREAD_ANYCOLOR, Napi::Number::New(env, cv::IMREAD_ANYCOLOR));
  FF_SET_JS_PROP(target, IMREAD_LOAD_GDAL, Napi::Number::New(env, cv::IMREAD_LOAD_GDAL));

  FF_SET_JS_PROP(target, IMWRITE_JPEG_QUALITY, Napi::Number::New(env, cv::IMWRITE_JPEG_QUALITY));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_PROGRESSIVE, Napi::Number::New(env, cv::IMWRITE_JPEG_PROGRESSIVE));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_OPTIMIZE, Napi::Number::New(env, cv::IMWRITE_JPEG_OPTIMIZE));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_RST_INTERVAL, Napi::Number::New(env, cv::IMWRITE_JPEG_RST_INTERVAL));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_LUMA_QUALITY, Napi::Number::New(env, cv::IMWRITE_JPEG_LUMA_QUALITY));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_CHROMA_QUALITY, Napi::Number::New(env, cv::IMWRITE_JPEG_CHROMA_QUALITY));
  FF_SET_JS_PROP(target, IMWRITE_PNG_COMPRESSION, Napi::Number::New(env, cv::IMWRITE_PNG_COMPRESSION));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY, Napi::Number::New(env, cv::IMWRITE_PNG_STRATEGY));
  FF_SET_JS_PROP(target, IMWRITE_PNG_BILEVEL, Napi::Number::New(env, cv::IMWRITE_PNG_BILEVEL));
  FF_SET_JS_PROP(target, IMWRITE_PXM_BINARY, Napi::Number::New(env, cv::IMWRITE_PXM_BINARY));
  FF_SET_JS_PROP(target, IMWRITE_WEBP_QUALITY, Napi::Number::New(env, cv::IMWRITE_WEBP_QUALITY));

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_2, Napi::Number::New(env, cv::IMREAD_REDUCED_GRAYSCALE_2));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_2, Napi::Number::New(env, cv::IMREAD_REDUCED_COLOR_2));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_4, Napi::Number::New(env, cv::IMREAD_REDUCED_GRAYSCALE_4));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_4, Napi::Number::New(env, cv::IMREAD_REDUCED_COLOR_4));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_8, Napi::Number::New(env, cv::IMREAD_REDUCED_GRAYSCALE_8));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_8, Napi::Number::New(env, cv::IMREAD_REDUCED_COLOR_8));
#endif
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  FF_SET_JS_PROP(target, IMREAD_IGNORE_ORIENTATION, Napi::Number::New(env, cv::IMREAD_IGNORE_ORIENTATION));
  FF_SET_JS_PROP(target, IMWRITE_PAM_TUPLETYPE, Napi::Number::New(env, cv::IMWRITE_PAM_TUPLETYPE));

  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_NULL, Napi::Number::New(env, cv::IMWRITE_PAM_FORMAT_NULL));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_BLACKANDWHITE, Napi::Number::New(env, cv::IMWRITE_PAM_FORMAT_BLACKANDWHITE));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_GRAYSCALE, Napi::Number::New(env, cv::IMWRITE_PAM_FORMAT_GRAYSCALE));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA, Napi::Number::New(env, cv::IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_RGB, Napi::Number::New(env, cv::IMWRITE_PAM_FORMAT_RGB));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_RGB_ALPHA, Napi::Number::New(env, cv::IMWRITE_PAM_FORMAT_RGB_ALPHA));
#endif
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_DEFAULT, Napi::Number::New(env, cv::IMWRITE_PNG_STRATEGY_DEFAULT));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_FILTERED, Napi::Number::New(env, cv::IMWRITE_PNG_STRATEGY_FILTERED));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY, Napi::Number::New(env, cv::IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_RLE, Napi::Number::New(env, cv::IMWRITE_PNG_STRATEGY_RLE));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_FIXED, Napi::Number::New(env, cv::IMWRITE_PNG_STRATEGY_FIXED));
};

void Io::Imshow(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Io::Imshow");
  if (!info[0].IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }
  if (!Mat::hasInstance(info[1])) {
    return tryCatch.throwError("expected arg1 to be an instance of Mat");
  }
  cv::imshow(FF::StringConverter::unwrapUnchecked(info[0]), Mat::Converter::unwrapUnchecked(info[1]));
}

void Io::ImshowWait(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Io::ImshowWait");
  if (!info[0].IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }
  if (!Mat::hasInstance(info[1])) {
    return tryCatch.throwError("expected arg1 to be an instance of Mat");
  }
  cv::imshow(FF::StringConverter::unwrapUnchecked(info[0]), Mat::Converter::unwrapUnchecked(info[1]));
  cv::waitKey();
}

void Io::WaitKey(const Napi::CallbackInfo& info) {
  int key;
  if (info[0].IsNumber()) {
    key = cv::waitKey(info[0].ToNumber(Napi::GetCurrentContext())->Value());
  } else {
    key = cv::waitKey();
  }
  return Napi::New(env, key);
}

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
void Io::WaitKeyEx(const Napi::CallbackInfo& info) {
  int key;
  if (info[0].IsNumber()) {
    key = cv::waitKeyEx(info[0].ToNumber(Napi::GetCurrentContext())->Value());
  } else {
    key = cv::waitKeyEx();
  }
  return Napi::New(env, key);
}
#endif

void Io::DestroyWindow(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Io::DestroyWindow");
  std::string winName;
  if (FF::StringConverter::arg(0, &winName, info)) {
    return tryCatch.reThrow();
  }
  cv::destroyWindow(winName);
}

void Io::DestroyAllWindows(const Napi::CallbackInfo& info) {
  cv::destroyAllWindows();
}

void Io::Imdecode(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Io::Imdecode");

  if (!info[0].IsUint8Array()) {
    return tryCatch.throwError("expected arg 0 to be a Buffer of Uint8 Values");
  }

  int flags = cv::IMREAD_ANYCOLOR;
  if (FF::IntConverter::optArg(1, &flags, info)) {
    return tryCatch.reThrow();
  }

  char* data = static_cast<char*>(info[0].ToObject(Napi::GetCurrentContext(.As<Napi::Buffer<char>>().Data())));
  size_t size = info[0].ToObject(Napi::GetCurrentContext(.As<Napi::Buffer<char>>().Length()));
  std::vector<uchar> vec(size);
  memcpy(vec.data(), data, size);

  return Mat::Converter::wrap(cv::imdecode(vec, flags));
}

void Io::ImdecodeAsync(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  FF::TryCatch tryCatch(env, "Io::ImdecodeAsync");

  if (!info[0].IsUint8Array()) {
    return tryCatch.throwError("expected arg 0 to be a Buffer of Uint8 Values");
  }

  std::shared_ptr<IoBindings::ImdecodeWorker> worker = std::make_shared<IoBindings::ImdecodeWorker>();

  Napi::Function cbFunc;
  if (FF::hasArg(info, 1) && FF::IntConverterImpl::assertType(info[1])) {
    worker->flags = info[1].ToInt32(Napi::GetCurrentContext())->Value();
    if (!info[2].IsFunction()) {
      return tryCatch.throwError("expected argument 2 to be of type Function");
    }
    cbFunc = info[2].As<Napi::Function>();
  } else {
    if (!info[1].IsFunction()) {
      return tryCatch.throwError("expected argument 1 to be of type Function");
    }
    cbFunc = info[1].As<Napi::Function>();
    worker->flags = cv::IMREAD_ANYCOLOR;
  }

  Napi::Object jsBuf = info[0].As<Napi::Object>();
  worker->data = static_cast<char*>(jsBuf.As<Napi::Buffer<char>>().Data());
  worker->dataSize = jsBuf.As<Napi::Buffer<char>>().Length();

  Napi::AsyncQueueWorker(new FF::AsyncWorker(
      new Napi::FunctionReference(cbFunc),
      worker));
}

void Io::Imread(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<IoBindings::ImreadWorker>(),
      "Io::Imread",
      info);
}

void Io::ImreadAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<IoBindings::ImreadWorker>(),
      "Io::ImreadAsync",
      info);
}

void Io::Imwrite(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<IoBindings::ImwriteWorker>(),
      "Io::Imwrite",
      info);
}

void Io::ImwriteAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<IoBindings::ImwriteWorker>(),
      "Io::ImwriteAsync",
      info);
}

void Io::Imencode(const Napi::CallbackInfo& info) {
  FF::executeSyncBinding(
      std::make_shared<IoBindings::ImencodeWorker>(),
      "Io::Imencode",
      info);
}

void Io::ImencodeAsync(const Napi::CallbackInfo& info) {
  FF::executeAsyncBinding(
      std::make_shared<IoBindings::ImencodeWorker>(),
      "Io::ImencodeAsync",
      info);
}

#endif
