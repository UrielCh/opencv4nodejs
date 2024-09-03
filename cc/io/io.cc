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

  FF_SET_JS_PROP(target, IMREAD_UNCHANGED, Nan::New<v8::Integer>(cv::IMREAD_UNCHANGED));
  FF_SET_JS_PROP(target, IMREAD_GRAYSCALE, Nan::New<v8::Integer>(cv::IMREAD_GRAYSCALE));
  FF_SET_JS_PROP(target, IMREAD_COLOR, Nan::New<v8::Integer>(cv::IMREAD_COLOR));
  FF_SET_JS_PROP(target, IMREAD_ANYDEPTH, Nan::New<v8::Integer>(cv::IMREAD_ANYDEPTH));
  FF_SET_JS_PROP(target, IMREAD_ANYCOLOR, Nan::New<v8::Integer>(cv::IMREAD_ANYCOLOR));
  FF_SET_JS_PROP(target, IMREAD_LOAD_GDAL, Nan::New<v8::Integer>(cv::IMREAD_LOAD_GDAL));

  FF_SET_JS_PROP(target, IMWRITE_JPEG_QUALITY, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_QUALITY));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_PROGRESSIVE, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_PROGRESSIVE));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_OPTIMIZE, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_OPTIMIZE));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_RST_INTERVAL, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_RST_INTERVAL));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_LUMA_QUALITY, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_LUMA_QUALITY));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_CHROMA_QUALITY, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_CHROMA_QUALITY));
  FF_SET_JS_PROP(target, IMWRITE_PNG_COMPRESSION, Nan::New<v8::Integer>(cv::IMWRITE_PNG_COMPRESSION));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY));
  FF_SET_JS_PROP(target, IMWRITE_PNG_BILEVEL, Nan::New<v8::Integer>(cv::IMWRITE_PNG_BILEVEL));
  FF_SET_JS_PROP(target, IMWRITE_PXM_BINARY, Nan::New<v8::Integer>(cv::IMWRITE_PXM_BINARY));
  FF_SET_JS_PROP(target, IMWRITE_WEBP_QUALITY, Nan::New<v8::Integer>(cv::IMWRITE_WEBP_QUALITY));

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_2, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_GRAYSCALE_2));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_2, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_COLOR_2));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_4, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_GRAYSCALE_4));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_4, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_COLOR_4));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_8, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_GRAYSCALE_8));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_8, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_COLOR_8));
#endif
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  FF_SET_JS_PROP(target, IMREAD_IGNORE_ORIENTATION, Nan::New<v8::Integer>(cv::IMREAD_IGNORE_ORIENTATION));
  FF_SET_JS_PROP(target, IMWRITE_PAM_TUPLETYPE, Nan::New<v8::Integer>(cv::IMWRITE_PAM_TUPLETYPE));

  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_NULL, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_NULL));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_BLACKANDWHITE, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_BLACKANDWHITE));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_GRAYSCALE, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_GRAYSCALE));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_RGB, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_RGB));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_RGB_ALPHA, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_RGB_ALPHA));
#endif
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_DEFAULT, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_DEFAULT));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_FILTERED, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_FILTERED));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_RLE, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_RLE));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_FIXED, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_FIXED));
};

void Io::Imshow(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Io::Imshow");
  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }
  if (!Mat::hasInstance(info[1])) {
    return tryCatch.throwError("expected arg1 to be an instance of Mat");
  }
  cv::imshow(FF::StringConverter::unwrapUnchecked(info[0]), Mat::Converter::unwrapUnchecked(info[1]));
}

void Io::ImshowWait(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Io::ImshowWait");
  if (!info[0]->IsString()) {
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
  if (info[0]->IsNumber()) {
    key = cv::waitKey(info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value());
  } else {
    key = cv::waitKey();
  }
  info.GetReturnValue().Set(Nan::New(key));
}

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
void Io::WaitKeyEx(const Napi::CallbackInfo& info) {
  int key;
  if (info[0]->IsNumber()) {
    key = cv::waitKeyEx(info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value());
  } else {
    key = cv::waitKeyEx();
  }
  info.GetReturnValue().Set(Nan::New(key));
}
#endif

void Io::DestroyWindow(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Io::DestroyWindow");
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
  FF::TryCatch tryCatch("Io::Imdecode");

  if (!info[0]->IsUint8Array()) {
    return tryCatch.throwError("expected arg 0 to be a Buffer of Uint8 Values");
  }

  int flags = cv::IMREAD_ANYCOLOR;
  if (FF::IntConverter::optArg(1, &flags, info)) {
    return tryCatch.reThrow();
  }

  char* data = static_cast<char*>(node::Buffer::Data(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked()));
  size_t size = node::Buffer::Length(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
  std::vector<uchar> vec(size);
  memcpy(vec.data(), data, size);

  info.GetReturnValue().Set(Mat::Converter::wrap(cv::imdecode(vec, flags)));
}

void Io::ImdecodeAsync(const Napi::CallbackInfo& info) {
  FF::TryCatch tryCatch("Io::ImdecodeAsync");

  if (!info[0]->IsUint8Array()) {
    return tryCatch.throwError("expected arg 0 to be a Buffer of Uint8 Values");
  }

  std::shared_ptr<IoBindings::ImdecodeWorker> worker = std::make_shared<IoBindings::ImdecodeWorker>();

  Napi::Function cbFunc;
  if (FF::hasArg(info, 1) && FF::IntConverterImpl::assertType(info[1])) {
    worker->flags = info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value();
    if (!info[2]->IsFunction()) {
      return tryCatch.throwError("expected argument 2 to be of type Function");
    }
    cbFunc = Napi::Function::Cast(info[2]);
  } else {
    if (!info[1]->IsFunction()) {
      return tryCatch.throwError("expected argument 1 to be of type Function");
    }
    cbFunc = Napi::Function::Cast(info[1]);
    worker->flags = cv::IMREAD_ANYCOLOR;
  }

  Napi::Object jsBuf = info[0].As<Napi::Object>();
  worker->data = static_cast<char*>(node::Buffer::Data(jsBuf));
  worker->dataSize = node::Buffer::Length(jsBuf);

  Nan::AsyncQueueWorker(new FF::AsyncWorker(
      new Nan::Callback(cbFunc),
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
