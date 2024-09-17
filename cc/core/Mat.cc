#include "Mat.h"
#include "MatBindings.h"
#include "coreBindings.h"
#include "opencv_modules.h"
#include <string>

#ifdef HAVE_OPENCV_CALIB3D
#include "../calib3d/MatCalib3d.h"
#endif
#ifdef HAVE_OPENCV_IMGPROC
#include "../imgproc/MatImgproc.h"
#endif
#ifdef HAVE_OPENCV_PHOTO
#include "../photo/MatPhoto.h"
#endif
#ifdef HAVE_OPENCV_XIMGPROC
#include "../ximgproc/MatXimgproc.h"
#endif

Napi::FunctionReference Mat::constructor;

namespace FF {
/**
 * 2,3-Dimmentions Macro seters for a single Value
 */
template <typename type, int n>
static inline void matPutVal(cv::Mat mat, Napi::Value value, const cv::Vec<int, n>& idx) {
  mat.at<type>(idx) = (type)value->ToNumber(Napi::GetCurrentContext())->Value();
}

/**
 * 2,3-Dimmentions Macro seters for a Vec<2> Value
 */

template <typename type, int n>
static inline void matPutVec2(cv::Mat mat, Napi::Value vector, const cv::Vec<int, n>& idx) {
  Napi::Array vec = vector.As<Napi::Array>();
  mat.at<cv::Vec<type, 2>>(idx) = cv::Vec<type, 2>(
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(0)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(1)));
}

/**
 * 2,3-Dimmentions Macro seters for a Vec<3> Value
 */

template <typename type, int n>
static inline void matPutVec3(cv::Mat mat, Napi::Value vector, const cv::Vec<int, n>& idx) {
  Napi::Array vec = vector.As<Napi::Array>();
  mat.at<cv::Vec<type, 3>>(idx) = cv::Vec<type, 3>(
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(0)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(1)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(2)));
}

/**
 * 2,3-Dimmentions Macro seters for a Vec<4> Value
 */

template <typename type, int n>
static inline void matPutVec4(cv::Mat mat, Napi::Value vector, const cv::Vec<int, n>& idx) {
  Napi::Array vec = vector.As<Napi::Array>();
  mat.at<cv::Vec<type, 4>>(idx) = cv::Vec<type, 4>(
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(0)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(1)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(2)),
      (type)FF::DoubleConverter::unwrapUnchecked((vec).Get(3)));
}

template <typename type, int n>
static inline Napi::Value matGetVal(cv::Mat mat, cv::Vec<int, n>& idx) {
  return Napi::Number::New(env, mat.at<type>(idx));
}

template <typename type, int n>
static inline Napi::Value matGetVec2(cv::Mat mat, const cv::Vec<int, n>& idx) {
  Napi::Array vec = Napi::Array::New(env, 2);
  (vec).Set(0, Napi::Number::New(env, mat.at<cv::Vec<type, 2>>(idx)[0]));
  (vec).Set(1, Napi::Number::New(env, mat.at<cv::Vec<type, 2>>(idx)[1]));
  return vec;
}

template <typename type, int n>
static inline Napi::Value matGetVec3(cv::Mat mat, const cv::Vec<int, n>& idx) {
  Napi::Array vec = Napi::Array::New(env, 3);
  (vec).Set(0, Napi::Number::New(env, mat.at<cv::Vec<type, 3>>(idx)[0]));
  (vec).Set(1, Napi::Number::New(env, mat.at<cv::Vec<type, 3>>(idx)[1]));
  (vec).Set(2, Napi::Number::New(env, mat.at<cv::Vec<type, 3>>(idx)[2]));
  return vec;
}

template <typename type, int n>
static inline Napi::Value matGetVec4(cv::Mat mat, const cv::Vec<int, n>& idx) {
  Napi::Array vec = Napi::Array::New(env, 4);
  (vec).Set(0, Napi::Number::New(env, mat.at<cv::Vec<type, 4>>(idx)[0]));
  (vec).Set(1, Napi::Number::New(env, mat.at<cv::Vec<type, 4>>(idx)[1]));
  (vec).Set(2, Napi::Number::New(env, mat.at<cv::Vec<type, 4>>(idx)[2]));
  (vec).Set(3, Napi::Number::New(env, mat.at<cv::Vec<type, 4>>(idx)[3]));
  return vec;
}

} // namespace FF

Napi::Object Mat::Init(Napi::Object exports) {
  Napi::Env env = exports.Env();
  Napi::FunctionReference ctor = Napi::Persistent(Napi::Function::New(env, Mat::New));
  // constructor.Reset(ctor);

  // ctor->SetClassName(Napi::String::New(env, "Mat"));
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "rows"), Mat::rows_getter);
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "cols"), Mat::cols_getter);
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "type"), Mat::type_getter);
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "channels"), Mat::channels_getter);
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "dims"), Mat::dims_getter);
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "depth"), Mat::depth_getter);
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "empty"), Mat::empty_getter);
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "sizes"), Mat::GetSizes);
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "elemSize"), Mat::GetElemSize);
  // Napi::SetAccessor(ctor->InstanceTemplate(), Napi::String::New(env, "step"), Mat::GetStep);
  // // Mat static metodas
  // Napi::SetMethod(ctor, "eye", Eye);
  // Napi::SetMethod(ctor, "ones", Ones);
  // Napi::SetMethod(ctor, "zeros", Zeros);

  Napi::Function func = DefineClass(
      env,
      "Mat",
      {
        InstanceAccessor("rows", &Mat::Getrows, &Mat::Setrows),
        InstanceAccessor("cols", &Mat::Getcols, &Mat::Setcols),
        //   using InstanceMethodCallback = Napi::Value (T::*)(const CallbackInfo& info);

//        InstanceMethod("plusOne", &MyObject::PlusOne),
      });

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  // add a static method to the class
  // func.Set("hello",
  //             Napi::Function::New(env, Method));

  func.Set("flattenFloat", &Mat::FlattenFloat),
  // func.Set("flattenFloat", Napi::Function::New(Mat::FlattenFloat)),


  exports.Set("Mat", func);
  return exports;

//       
//       InstanceMethod("at", &At),
//       InstanceMethod("atRaw", &AtRaw),
//       InstanceMethod("set", &Set),
//       InstanceMethod("setTo", &SetTo),
//       InstanceMethod("setToAsync", &SetToAsync),
//       InstanceMethod("push_back", &PushBack),
//       InstanceMethod("push_backAsync", &PushBackAsync),
//       InstanceMethod("pushBack", &PushBack),
//       InstanceMethod("pushBackAsync", &PushBackAsync),
//       InstanceMethod("pop_back", &PopBack),
//       InstanceMethod("pop_backAsync", &PopBackAsync),
//       InstanceMethod("popBack", &PopBack),
//       InstanceMethod("popBackAsync", &PopBackAsync),
//       InstanceMethod("getData", &GetData),
//       InstanceMethod("getDataAsync", &GetDataAsync),
//       InstanceMethod("getDataAsArray", &GetDataAsArray),
//       InstanceMethod("setData", &SetData),
//       InstanceMethod("getRegion", &GetRegion),
//       InstanceMethod("row", &Row),
//       InstanceMethod("rowRange", &RowRange),
//       InstanceMethod("col", &Col),
//       InstanceMethod("colRange", &ColRange),
//       InstanceMethod("copy", &Copy),
//       InstanceMethod("copyAsync", &CopyAsync),
//       InstanceMethod("copyTo", &CopyTo),
//       InstanceMethod("copyToAsync", &CopyToAsync),
//       InstanceMethod("convertTo", &ConvertTo),
//       InstanceMethod("convertToAsync", &ConvertToAsync),
//       InstanceMethod("norm", &Norm),
//       InstanceMethod("padToSquare", &PadToSquare),
//       InstanceMethod("padToSquareAsync", &PadToSquareAsync),
//       InstanceMethod("dct", &Dct),
//       InstanceMethod("dctAsync", &DctAsync),
//       InstanceMethod("idct", &Idct),
//       InstanceMethod("idctAsync", &IdctAsync),
//       InstanceMethod("dft", &Dft),
//       InstanceMethod("dftAsync", &DftAsync),
//       InstanceMethod("idft", &Idft),
//       InstanceMethod("idftAsync", &IdftAsync),
//       InstanceMethod("normalize", &Normalize),
//       InstanceMethod("normalizeAsync", &NormalizeAsync),
//       InstanceMethod("flip", &Flip),
//       InstanceMethod("flipAsync", &FlipAsync),
//       InstanceMethod("copyMakeBorder", &CopyMakeBorder),
//       InstanceMethod("copyMakeBorderAsync", &CopyMakeBorderAsync),
//       InstanceMethod("splitChannels", &Split),
//       InstanceMethod("splitChannelsAsync", &SplitAsync),
// 
// #if CV_VERSION_GREATER_EQUAL(3, 2, 0)
//       InstanceMethod("rotate", &Rotate),
//       InstanceMethod("rotateAsync", &RotateAsync),
// #endif
// 
//       InstanceMethod("release", &Release),
// 
//       InstanceMethod("addWeighted", &AddWeighted),
//       InstanceMethod("addWeightedAsync", &AddWeightedAsync),
//       InstanceMethod("minMaxLoc", &MinMaxLoc),
//       InstanceMethod("minMaxLocAsync", &MinMaxLocAsync),
//       InstanceMethod("findNonZero", &FindNonZero),
//       InstanceMethod("findNonZeroAsync", &FindNonZeroAsync),
//       InstanceMethod("countNonZero", &CountNonZero),
//       InstanceMethod("countNonZeroAsync", &CountNonZeroAsync),
//       InstanceMethod("split", &Split),
//       InstanceMethod("splitAsync", &SplitAsync),
//       InstanceMethod("mulSpectrums", &MulSpectrums),
//       InstanceMethod("mulSpectrumsAsync", &MulSpectrumsAsync),
//       InstanceMethod("transform", &Transform),
//       InstanceMethod("transformAsync", &TransformAsync),
//       InstanceMethod("perspectiveTransform", &PerspectiveTransform),
//       InstanceMethod("perspectiveTransformAsync", &PerspectiveTransformAsync),
//       InstanceMethod("convertScaleAbs", &ConvertScaleAbs),
//       InstanceMethod("convertScaleAbsAsync", &ConvertScaleAbsAsync),
//       InstanceMethod("sum", &Sum),
//       InstanceMethod("sumAsync", &SumAsync),
//       InstanceMethod("mean", &Mean),
//       InstanceMethod("meanAsync", &MeanAsync),
//       InstanceMethod("meanStdDev", &MeanStdDev),
//       InstanceMethod("meanStdDevAsync", &MeanStdDevAsync),
//       InstanceMethod("reduce", &Reduce),
//       InstanceMethod("reduceAsync", &ReduceAsync),
//       InstanceMethod("eigen", &Eigen),
//       InstanceMethod("eigenAsync", &EigenAsync),
//       InstanceMethod("solve", &Solve),
//       InstanceMethod("solveAsync", &SolveAsync),
//       });
// 
//       // FF_PROTO_SET_MAT_OPERATIONS(ctor);
// 
//#ifdef HAVE_OPENCV_CALIB3D
//  MatCalib3d::Init(exports);
//#endif
//#ifdef HAVE_OPENCV_IMGPROC
//  MatImgproc::Init(exports);
//#endif
//#ifdef HAVE_OPENCV_PHOTO
//  MatPhoto::Init(exports);
//#endif
// #ifdef HAVE_OPENCV_XIMGPROC
//   MatXimgproc::Init(exports);
// #endif

  // exports.Set("Mat", FF::getFunction(ctor));
};

Napi::Value Mat::Getrows(const Napi::CallbackInfo& info) {
  double num = this->self.rows;
  return Napi::Number::New(info.Env(), num);
}

void Mat::Setrows(const Napi::CallbackInfo& info,
                        const Napi::Value& value) {
  Napi::Env env = info.Env();
  if (!value.IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    return;
  }
  Napi::Number num = value.As<Napi::Number>();
  this->self.rows = num.DoubleValue();
}

Napi::Value Mat::Getcols(const Napi::CallbackInfo& info) {
  double num = this->self.cols;
  return Napi::Number::New(info.Env(), num);
}

void Mat::Setcols(const Napi::CallbackInfo& info,
                        const Napi::Value& value) {
  Napi::Env env = info.Env();
  if (!value.IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    return;
  }
  Napi::Number num = value.As<Napi::Number>();
  this->self.cols = num.DoubleValue();
}


// only used in Mat::At and Mat::AtRaw
#define FF_MAT_AT(mat, val, get)                                                                                                                                                   \
  if (mat.dims > 2)                                                                                                                                                                \
    val = get(mat, info[0].ToInt32(Napi::GetCurrentContext())->Value(), info[1].ToInt32(Napi::GetCurrentContext())->Value(), info[2].ToInt32(Napi::GetCurrentContext())->Value()); \
  else                                                                                                                                                                             \
    val = get(mat, info[0].ToInt32(Napi::GetCurrentContext())->Value(), info[1].ToInt32(Napi::GetCurrentContext())->Value());

// only used in Mat::At
#define FF_MAT_AT_ARRAY(mat, val, get)               \
  {                                                  \
    std::vector<int> vec;                            \
    if (FF::IntArrayConverter::arg(0, &vec, info)) { \
      return tryCatch.reThrow();                     \
    }                                                \
    const int* idx = &vec.front();                   \
    val = get(mat, idx);                             \
  }

// only used in Mat::Set
#define FF_MAT_SET(mat, val, put)                                                                                                                                                 \
  if (mat.dims > 2)                                                                                                                                                               \
    put(mat, val, info[0].ToInt32(Napi::GetCurrentContext())->Value(), info[1].ToInt32(Napi::GetCurrentContext())->Value(), info[2].ToInt32(Napi::GetCurrentContext())->Value()); \
  else                                                                                                                                                                            \
    put(mat, val, info[0].ToInt32(Napi::GetCurrentContext())->Value(), info[1].ToInt32(Napi::GetCurrentContext())->Value());

// only used in Mat::New
#define FF_MAT_FILL(mat, vec, put)       \
  for (int r = 0; r < mat.rows; r++) {   \
    for (int c = 0; c < mat.cols; c++) { \
      put(mat, vec, r, c);               \
    }                                    \
  }

// only used in Mat::Set
#define FF_ASSERT_CHANNELS(cn, have, what)                                                        \
  if (cn != have) {                                                                               \
    return tryCatch.throwError(std::string(what) + " - expected vector with "                     \
                               + std::to_string(cn) + " channels, have " + std::to_string(have)); \
  }

#define FF_MAT_APPLY_TYPED_OPERATOR(mat, arg, type, ITERATOR, OPERATOR)       \
  {                                                                           \
    switch (type) {                                                           \
    case CV_8UC1:                                                             \
      ITERATOR(mat, arg, OPERATOR##Val<uchar>)                                \
      break;                                                                  \
    case CV_8UC2:                                                             \
      ITERATOR(mat, arg, OPERATOR##Vec2<uchar>)                               \
      break;                                                                  \
    case CV_8UC3:                                                             \
      ITERATOR(mat, arg, OPERATOR##Vec3<uchar>)                               \
      break;                                                                  \
    case CV_8UC4:                                                             \
      ITERATOR(mat, arg, OPERATOR##Vec4<uchar>)                               \
      break;                                                                  \
    case CV_8SC1:                                                             \
      ITERATOR(mat, arg, OPERATOR##Val<char>)                                 \
      break;                                                                  \
    case CV_8SC2:                                                             \
      ITERATOR(mat, arg, OPERATOR##Vec2<char>)                                \
      break;                                                                  \
    case CV_8SC3:                                                             \
      ITERATOR(mat, arg, OPERATOR##Vec3<char>)                                \
      break;                                                                  \
    case CV_8SC4:                                                             \
      ITERATOR(mat, arg, OPERATOR##Vec4<char>)                                \
      break;                                                                  \
    case CV_16UC1:                                                            \
      ITERATOR(mat, arg, OPERATOR##Val<ushort>)                               \
      break;                                                                  \
    case CV_16UC2:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec2<ushort>)                              \
      break;                                                                  \
    case CV_16UC3:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec3<ushort>)                              \
      break;                                                                  \
    case CV_16UC4:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec4<ushort>)                              \
      break;                                                                  \
    case CV_16SC1:                                                            \
      ITERATOR(mat, arg, OPERATOR##Val<short>)                                \
      break;                                                                  \
    case CV_16SC2:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec2<short>)                               \
      break;                                                                  \
    case CV_16SC3:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec3<short>)                               \
      break;                                                                  \
    case CV_16SC4:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec4<short>)                               \
      break;                                                                  \
    case CV_32SC1:                                                            \
      ITERATOR(mat, arg, OPERATOR##Val<int>)                                  \
      break;                                                                  \
    case CV_32SC2:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec2<int>)                                 \
      break;                                                                  \
    case CV_32SC3:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec3<int>)                                 \
      break;                                                                  \
    case CV_32SC4:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec4<int>)                                 \
      break;                                                                  \
    case CV_32FC1:                                                            \
      ITERATOR(mat, arg, OPERATOR##Val<float>)                                \
      break;                                                                  \
    case CV_32FC2:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec2<float>)                               \
      break;                                                                  \
    case CV_32FC3:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec3<float>)                               \
      break;                                                                  \
    case CV_32FC4:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec4<float>)                               \
      break;                                                                  \
    case CV_64FC1:                                                            \
      ITERATOR(mat, arg, OPERATOR##Val<double>)                               \
      break;                                                                  \
    case CV_64FC2:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec2<double>)                              \
      break;                                                                  \
    case CV_64FC3:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec3<double>)                              \
      break;                                                                  \
    case CV_64FC4:                                                            \
      ITERATOR(mat, arg, OPERATOR##Vec4<double>)                              \
      break;                                                                  \
    default:                                                                  \
      return tryCatch.throwError("invalid matType: " + std::to_string(type)); \
      break;                                                                  \
    }                                                                         \
  }

// only used in Mat::New
#define FF_MAT_FROM_JS_ARRAY_2D(mat, rowArray, put)             \
  for (int r = 0; r < mat.rows; r++) {                          \
    Napi::Array colArray = (rowArray).Get(r.As<Napi::Array>()); \
    for (int c = 0; c < mat.cols; c++) {                        \
      put(mat, (colArray).Get(c), r, c);                        \
    }                                                           \
  }

#define FF_MAT_FROM_JS_ARRAY_3D(mat, rowArray, put)                        \
  {                                                                        \
    cv::MatSize sizes = mat.size;                                          \
    cv::Vec3i cur = cv::Vec3b(0, 0, 0);                                    \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {                        \
      Napi::Array colArray1 = (rowArray).Get(cur[0].As<Napi::Array>());    \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {                      \
        Napi::Array colArray2 = (colArray1).Get(cur[1].As<Napi::Array>()); \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {                    \
          put(mat, (colArray2).Get(cur[2]), cur);                          \
        }                                                                  \
      }                                                                    \
    }                                                                      \
  }

// std::cout << "loop line " << cur[0] << "/" << sizes[1] << std::endl;
// std::cout << "loop cell " << cur[0] << "/" << sizes[0] << ", " << cur[1] << "/" << sizes[1] << std::endl;
// std::cout << "loop cell " << cur[0] << "/" << sizes[0] << ", " << cur[1] << "/" << sizes[1] << ", " << cur[2] << "/" << sizes[2]<< std::endl;
// std::cout << "loop pos " << cur[0] << ", " << cur[1] << ", " << cur[2] << ", " << cur[3] << std::endl;

#define FF_MAT_FROM_JS_ARRAY_4D(mat, rowArray, put)                          \
  {                                                                          \
    cv::MatSize sizes = mat.size;                                            \
    cv::Vec4i cur = cv::Vec4i(0, 0, 0, 0);                                   \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {                          \
      Napi::Array colArray1 = (rowArray).Get(cur[0].As<Napi::Array>());      \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {                        \
        Napi::Array colArray2 = (colArray1).Get(cur[1].As<Napi::Array>());   \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {                      \
          Napi::Array colArray3 = (colArray2).Get(cur[2].As<Napi::Array>()); \
          for (cur[3] = 0; cur[3] < sizes[3]; cur[3]++) {                    \
            put(mat, (colArray3).Get(cur[3]), cur);                          \
          }                                                                  \
        }                                                                    \
      }                                                                      \
    }                                                                        \
  }

#define FF_MAT_FROM_JS_ARRAY_5D(mat, rowArray, put)                            \
  {                                                                            \
    cv::MatSize sizes = mat.size;                                              \
    cv::Vec4i cur = cv::Vec5b(0, 0, 0, 0, 0);                                  \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {                            \
      Napi::Array colArray1 = (rowArray).Get(cur[0].As<Napi::Array>());        \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {                          \
        Napi::Array colArray2 = (colArray1).Get(cur[1].As<Napi::Array>());     \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {                        \
          Napi::Array colArray3 = (colArray2).Get(cur[2].As<Napi::Array>());   \
          for (cur[3] = 0; cur[3] < sizes[3]; cur[3]++) {                      \
            Napi::Array colArray4 = (colArray3).Get(cur[3].As<Napi::Array>()); \
            for (cur[4] = 0; cur[4] < sizes[4]; cur[4]++) {                    \
              put(mat, (colArray4).Get(cur[4]), cur);                          \
            }                                                                  \
          }                                                                    \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }


Napi::Value Mat::New(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  //FF::TryCatch tryCatch(env, "Mat::New");
  //FF_ASSERT_CONSTRUCT_CALL();
  //Mat* self = new Mat();
  ///* from channels
  // * constructor(channels: Mat[]);
  // */
  //// prepare debug for next big release
  ////  std::cout << "New Mat: args: " << info.Length() << std::endl;
  //if (info.Length() == 1 && info[0].IsArray()) {
  //  Napi::Array jsChannelMats = info[0].As<Napi::Array>();
  //  std::vector<cv::Mat> channels;
  //  for (uint i = 0; i < jsChannelMats->Length(); i++) {
  //    Napi::Object jsChannelMat = (jsChannelMats).Get(i.To<Napi::Object>());
  //    if (!Napi::New(env, Mat::constructor)->HasInstance(jsChannelMat)) {
  //      return tryCatch.throwError("expected channel " + std::to_string(i) + " to be an instance of Mat");
  //    }
  //    cv::Mat channelMat = Mat::Converter::unwrapUnchecked(jsChannelMat);
  //    channels.push_back(channelMat);
  //    if (i > 0) {
  //      if (channels.at(i - 1).rows != channelMat.rows) {
  //        return tryCatch.throwError("Mat::New - rows mismatch " + std::to_string(channels.at(i - 1).rows) + ", have " + std::to_string(channelMat.rows) + " at channel " + std::to_string(i));
  //      }
  //      if (channels.at(i - 1).cols != channelMat.cols) {
  //        return tryCatch.throwError("Mat::New - cols mismatch " + std::to_string(channels.at(i - 1).cols) + ", have " + std::to_string(channelMat.rows) + " at channel " + std::to_string(i));
  //      }
  //    }
  //  }
  //  cv::Mat mat;
  //  cv::merge(channels, mat);
  //  self->setNativeObject(mat);
  //}
  ///* data array, type
  // * constructor(dataArray: number[][], type: number);
  // * constructor(dataArray: number[][][], type: number);
  // */
  //else if (info.Length() == 2 && info[0].IsArray() && info[1].IsNumber()) {
  //  // get Type
  //  int type = info[1].ToInt32(Napi::GetCurrentContext())->Value();
  //  // get channel count
  //  int channel = (type >> CV_CN_SHIFT) + 1;
//
  //  // check data concistency
  //  Napi::Array rowArray0 = info[0].As<Napi::Array>();
  //  int dim = 1;
  //  while ((rowArray0).Get(0)->IsArray()) {
  //    dim = dim + 1;
  //    rowArray0 = (rowArray0).Get(0.As < Napi::Array > ());
  //  }
  //  // if multishanel drop one dimmention
  //  if (channel > 1)
  //    dim--;
  //  // std::cout << "Create a Mat of " << dim << " dimentions eatch item has " << channel << " channel(s)." << std::endl;
//
  //  // reset row0
  //  rowArray0 = info[0].As<Napi::Array>();
  //  if (dim == 1) {
  //    // tak first argument as dim array;
  //    std::vector<int> sizes(rowArray0->Length());
  //    for (int i = 0; i < (int)rowArray0->Length(); i++) {
  //      sizes[i] = (int)FF::DoubleConverter::unwrapUnchecked((rowArray0).Get(i));
  //    }
  //    cv::Mat mat = cv::Mat(sizes, type);
  //    self->setNativeObject(mat);
  //    // return tryCatch.throwError("Mat::New - Mat must have at least 2 Dimentions");
  //  } else if (dim == 2) {
  //    long rows = rowArray0->Length();
  //    long numCols = -1;
  //    for (long i = 0; i < rows; i++) {
  //      if (!(rowArray0).Get(i)->IsArray())
  //        return tryCatch.throwError("Column should be an array, at column: " + std::to_string(i));
  //      Napi::Array colArray = (rowArray0).Get(i.As<Napi::Array>());
  //      if (numCols == -1)
  //        numCols = colArray->Length();
  //      else if (numCols != colArray->Length())
  //        return tryCatch.throwError("Mat cols must be of uniform length, at column: " + std::to_string(i));
  //    }
  //    // 	Mat (int rows, int cols, int type)
  //    cv::Mat mat = cv::Mat(rows, numCols, type);
  //    FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray0, type, FF_MAT_FROM_JS_ARRAY_2D, FF::matPut);
  //    self->setNativeObject(mat);
  //  } else if (dim == 3) {
  //    std::vector<int> sizes = {(int)rowArray0->Length(), -1, -1};
  //    for (int i = 0; i < sizes[0]; i++) {
  //      if (!(rowArray0).Get(i)->IsArray())
  //        return tryCatch.throwError("Column should be an array, at column: " + std::to_string(i));
  //      Napi::Array rowArray1 = (rowArray0).Get(i.As<Napi::Array>());
  //      if (sizes[1] == -1)
  //        sizes[1] = rowArray1->Length();
  //      else if (sizes[1] != (int)rowArray1->Length())
  //        return tryCatch.throwError("Mat cols must be of uniform length, at column: " + std::to_string(i));
  //      for (int j = 0; j < sizes[1]; j++) {
  //        if (!(rowArray1).Get(j)->IsArray())
  //          return tryCatch.throwError("Column should be an array, at column: " + std::to_string(i) + ", " + std::to_string(j));
  //        Napi::Array rowArray2 = (rowArray1).Get(j.As<Napi::Array>());
  //        if (sizes[2] == -1)
  //          sizes[2] = rowArray2->Length();
  //        else if (sizes[2] != (int)rowArray2->Length())
  //          return tryCatch.throwError("Mat cols must be of uniform length, at column: " + std::to_string(i) + ", " + std::to_string(j));
  //      }
  //    }
  //    // Mat (const std::vector< int > &sizes, int type)
  //    cv::Mat mat = cv::Mat(sizes, type);
  //    FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray0, type, FF_MAT_FROM_JS_ARRAY_3D, FF::matPut);
  //    self->setNativeObject(mat);
  //  } else if (dim == 4) {
  //    std::vector<int> sizes = {(int)rowArray0->Length(), -1, -1, -1};
  //    std::vector<Napi::Array> arrs(4);
  //    cv::Vec3i cur = cv::Vec3i(0, 0, 0);
//
  //    arrs[0] = rowArray0;
  //    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {
  //      if (!(arrs[0]).Get(cur[0])->IsArray())
  //        return tryCatch.throwError("All array in dimension 1 should be array, at position: " + std::to_string(cur[0]));
  //      arrs[1] = (arrs[0]).Get(cur[0].As<Napi::Array>());
  //      if (sizes[1] == -1)
  //        sizes[1] = arrs[1]->Length();
  //      else if (sizes[1] != (int)arrs[1]->Length())
  //        return tryCatch.throwError("Mat cols must be of uniform length, at column: " + std::to_string(cur[0]) + " find " + std::to_string(arrs[1]->Length()) + " expecting " + std::to_string(sizes[1]));
  //      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {
  //        if (!(arrs[1]).Get(cur[1])->IsArray())
  //          return tryCatch.throwError("All array in dimension 2 should be array, at position:" + std::to_string(cur[0]) + ", " + std::to_string(cur[1]));
  //        arrs[2] = (arrs[1]).Get(cur[1].As<Napi::Array>());
  //        if (sizes[2] == -1)
  //          sizes[2] = arrs[2]->Length();
  //        else if (sizes[2] != (int)arrs[2]->Length())
  //          return tryCatch.throwError("Mat cols must be of uniform length, at column: " + std::to_string(cur[0]) + ", " + std::to_string(cur[1]) + " find " + std::to_string(arrs[2]->Length()) + " expecting " + std::to_string(sizes[2]));
  //        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {
  //          if (!(arrs[2]).Get(cur[2])->IsArray())
  //            return tryCatch.throwError("All array in dimension 3 should be array, at position: " + std::to_string(cur[0]) + ", " + std::to_string(cur[1]) + "," + std::to_string(cur[2]));
  //          arrs[3] = (arrs[2]).Get(cur[2].As<Napi::Array>());
  //          if (sizes[3] == -1)
  //            sizes[3] = arrs[3]->Length();
  //          else if (sizes[3] != (int)arrs[3]->Length())
  //            return tryCatch.throwError("Mat cols must be of uniform length, at column: " + std::to_string(cur[0]) + ", " + std::to_string(cur[1]) + ", " + std::to_string(cur[2]) + " find " + std::to_string(arrs[3]->Length()) + " expecting " + std::to_string(sizes[3]));
  //        }
  //      }
  //    }
  //    // Mat (const std::vector< int > &sizes, int type)
  //    cv::Mat mat = cv::Mat(sizes, type);
  //    FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray0, type, FF_MAT_FROM_JS_ARRAY_4D, FF::matPut);
  //    self->setNativeObject(mat);
  //  } else {
  //    return tryCatch.throwError("Mat::New - Support only 4 Dimmention provided payload contains " + std::to_string(dim));
  //  }
  //}
  ///* row, col, type
  // * constructor(rows: number, cols: number, type: number, fillValue?: number | number[]);
  // * constructor(rows: number, cols: number, type: number, data: Buffer, step?: number);
  // */
  //else if (info[0].IsNumber() && info[1].IsNumber() && info[2].IsNumber()) {
  //  int type = info[2].ToInt32(Napi::GetCurrentContext())->Value();
  //  if (info.Length() == 3 || info[3].IsArray() || info[3].IsNumber()) {
//
  //    cv::Mat mat(info[0].ToInt32(Napi::GetCurrentContext())->Value(), info[1].ToInt32(Napi::GetCurrentContext())->Value(), type);
//
  //    /* fill vector */
  //    // TODO by Vec
  //    if (info[3].IsArray()) {
  //      Napi::Array vec = info[3].As<Napi::Array>();
  //      if (mat.channels() != (long)vec->Length()) {
  //        return tryCatch.throwError(
  //            std::string("Mat::New - number of channels (") + std::to_string(mat.channels())
  //            + std::string(") do not match fill vector length ") + std::to_string(vec->Length()));
  //      }
  //      FF_MAT_APPLY_TYPED_OPERATOR(mat, vec, type, FF_MAT_FILL, FF::matPut);
  //    }
  //    if (info[3].IsNumber()) {
  //      FF_MAT_APPLY_TYPED_OPERATOR(mat, info[3], type, FF_MAT_FILL, FF::matPut);
  //    }
  //    self->setNativeObject(mat);
  //  } else if (info[3].IsObject()) {
  //    char* data = static_cast<char*>(info[3].ToObject(Napi::GetCurrentContext(.As<Napi::Buffer<char>>().Data())));
  //    if (info[4].IsNumber()) {
  //      int step = info[4].ToInt32(Napi::GetCurrentContext())->Value();
  //      cv::Mat mat(
  //          info[0].ToInt32(Napi::GetCurrentContext())->Value(),
  //          info[1].ToInt32(Napi::GetCurrentContext())->Value(),
  //          type,
  //          data,
  //          step);
  //      self->setNativeObject(mat);
  //    } else {
  //      cv::Mat mat(
  //          info[0].ToInt32(Napi::GetCurrentContext())->Value(),
  //          info[1].ToInt32(Napi::GetCurrentContext())->Value(),
  //          type,
  //          data);
  //      self->setNativeObject(mat);
  //    }
  //  }
  //}
  ///* raw data, row, col, type
  // * constructor(data: Buffer, rows: number, cols: number, type?: number);
  // */
  //else if (info.Length() == 4 && info[1].IsNumber() && info[2].IsNumber() && info[3].IsNumber()) {
  //  int type = info[3].ToInt32(Napi::GetCurrentContext())->Value();
  //  char* data = static_cast<char*>(info[0].ToObject(Napi::GetCurrentContext(.As<Napi::Buffer<char>>().Data())));
  //  cv::Mat mat(info[1].ToInt32(Napi::GetCurrentContext())->Value(), info[2].ToInt32(Napi::GetCurrentContext())->Value(), type);
  //  size_t size = mat.rows * mat.cols * mat.elemSize();
  //  memcpy(mat.data, data, size);
  //  self->setNativeObject(mat);
  //}
  //self->Wrap(info.Holder());
//
  //// if ExternalMemTracking is disabled, the following instruction will be a no op
  //// notes: I *think* New should be called in JS thread where cv::mat has been created async,
  //// so a good place to rationalise memory
  //ExternalMemTracking::onMatAllocated();
// return info.Holder();
  return env.Undefined();
}

Napi::Value Mat::Eye(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::Eye");
  // int rows, cols, type;
  // if (
  //     FF::IntConverter::arg(0, &rows, info) || FF::IntConverter::arg(1, &cols, info) || FF::IntConverter::arg(2, &type, info)) {
  //   return tryCatch.reThrow();
  // }
  // return Mat::Converter::wrap(cv::Mat::eye(cv::Size(cols, rows), type));
  return env.Undefined();
}

Napi::Value Mat::Ones(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::Ones");
  // int rows, cols, type;
  // if (
  //     FF::IntConverter::arg(0, &rows, info) || FF::IntConverter::arg(1, &cols, info) || FF::IntConverter::arg(2, &type, info)) {
  //   return tryCatch.reThrow();
  // }
  // return Mat::Converter::wrap(cv::Mat::ones(cv::Size(cols, rows), type));
  return env.Undefined();
}

Napi::Value Mat::Zeros(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::Zero");
  // int rows, cols, type;
  // if (
  //     FF::IntConverter::arg(0, &rows, info) || FF::IntConverter::arg(1, &cols, info) || FF::IntConverter::arg(2, &type, info)) {
  //   return tryCatch.reThrow();
  // }
  // return Mat::Converter::wrap(cv::Mat::zeros(cv::Size(cols, rows), type));
  return env.Undefined();
}

Napi::Value Mat::FlattenFloat(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::FlattenFloat");
  // int rows, cols;
  //if (
  //    FF::IntConverter::arg(0, &rows, info) || FF::IntConverter::arg(1, &cols, info)) {
  //  return tryCatch.reThrow();
  //}

  //cv::Mat matSelf = Mat::unwrapSelf(info);
  //cv::Mat mat2D(rows, cols, CV_32F, matSelf.ptr<float>());
  //return Mat::Converter::wrap(mat2D);
  return env.Undefined();
}

Napi::Value Mat::At(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::At");
  // cv::Mat matSelf = Mat::unwrapSelf(info);
  // Napi::Value val;
  // Napi::Value jsVal;
  // if (info[0].IsArray()) {
  //   if ((long)info[0].As<Napi::Array>()->Length() != matSelf.dims) {
  //     tryCatch.throwError("expected array length to be equal to the dims, get " + std::to_string((long)info[0].As<Napi::Array>()->Length()) + " expecting " + std::to_string(matSelf.dims));
  //   }
  //   FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT_ARRAY, FF::matGet);
  // } else {
  //   FF_ASSERT_INDEX_RANGE(info[0].ToInt32(Napi::GetCurrentContext())->Value(), matSelf.size[0] - 1, "Mat::At row");
  //   FF_ASSERT_INDEX_RANGE(info[1].ToInt32(Napi::GetCurrentContext())->Value(), matSelf.size[1] - 1, "Mat::At col");
  //   FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
  // }
// 
  // if (val->IsArray()) {
  //   Napi::Array vec = val.As<Napi::Array>();
  //   Napi::Value jsVec;
  //   if (vec->Length() == 2) {
  //     jsVec = Vec2::Converter::wrap(cv::Vec2d(FF::DoubleConverter::unwrapUnchecked((vec).Get(0)), FF::DoubleConverter::unwrapUnchecked((vec).Get(1))));
  //   } else if (vec->Length() == 3) {
  //     jsVec = Vec3::Converter::wrap(cv::Vec3d(FF::DoubleConverter::unwrapUnchecked((vec).Get(0)), FF::DoubleConverter::unwrapUnchecked((vec).Get(1)), FF::DoubleConverter::unwrapUnchecked((vec).Get(2))));
  //   } else {
  //     jsVec = Vec4::Converter::wrap(cv::Vec4d(FF::DoubleConverter::unwrapUnchecked((vec).Get(0)), FF::DoubleConverter::unwrapUnchecked((vec).Get(1)), FF::DoubleConverter::unwrapUnchecked((vec).Get(2)), FF::DoubleConverter::unwrapUnchecked((vec).Get(3))));
  //   }
  //   jsVal = jsVec;
  // } else {
  //   //  std::string str;
  //   //  if (matSelf.dims == 4) {
  //   //    auto sizes = matSelf.size;
  //   //    std::vector<Napi::Array> arrs(4);
  //   //    // cv::Vec4i
  //   //    // cv::Vec<int, 4> cur = cv::Vec4i(0, 0, 0, 0);
  //   //    std::vector<int> cur(4);
  //   //    //  = cv::Vec4i(0, 0, 0, 0);
  //   //    str += "Iter ";
  //   //    str += std::to_string(sizes[0]);
  //   //    str += "\n";
  //   //    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {
  //   //      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {
  //   //        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {
  //   //          for (cur[3] = 0; cur[3] < sizes[3]; cur[3]++) {
  //   //            int* ptr = (int*)cur.data();
  //   //            //cv::Vec4i a;
  //   //            // Point b;
  //   //         		// , 0, Napi::New(env, mat.at< cv::Vec<type, 4> >(idx)[0]));
  //   //            auto value = matSelf.at< cv::Vec<double, 4> >(ptr);
  //   //            str += std::to_string(value[0]);
  //   //            str += ", ";
  //   //            // Mat((int)sizes.size(), (int*)sizes.begin(), traits::Type<_Tp>::value, (uchar*)list.begin()).copyTo(*this);
  //   //          }
  //   //          str += "\n";
  //   //        }
  //   //      }
  //   //    }
  //   //  }
  //   // tryCatch.throwError(str);
  //   jsVal = val.As<Napi::Value>();
  // }
  // return jsVal;
  return env.Undefined();
}

Napi::Value Mat::AtRaw(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::AtRaw");
  // cv::Mat matSelf = Mat::unwrapSelf(info);
  // FF_ASSERT_INDEX_RANGE(info[0].ToInt32(Napi::GetCurrentContext())->Value(), matSelf.size[0] - 1, "Mat::At row");
  // FF_ASSERT_INDEX_RANGE(info[1].ToInt32(Napi::GetCurrentContext())->Value(), matSelf.size[1] - 1, "Mat::At col");
  // Napi::Value val;
  // FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
  // return val;
  return env.Undefined();
}

Napi::Value Mat::Set(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  //FF::TryCatch tryCatch(env, "Mat::Set");
  //cv::Mat matSelf = Mat::unwrapSelf(info);
  //FF_ASSERT_INDEX_RANGE(info[0].ToInt32(Napi::GetCurrentContext())->Value(), matSelf.size[0] - 1, "Mat::At row");
  //FF_ASSERT_INDEX_RANGE(info[1].ToInt32(Napi::GetCurrentContext())->Value(), matSelf.size[1] - 1, "Mat::At col");
//
  //int cn = matSelf.channels();
  //if (info[2].IsArray()) {
  //  Napi::Array vec = info[2].As<Napi::Array>();
  //  FF_ASSERT_CHANNELS(cn, (long)vec->Length(), "Mat::Set");
  //  FF_MAT_APPLY_TYPED_OPERATOR(matSelf, vec, matSelf.type(), FF_MAT_SET, FF::matPut);
  //} else if (Vec2::hasInstance(info[2])) {
  //  FF_ASSERT_CHANNELS(cn, 2, "Mat::Set");
  //  FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<2>(Vec2::Converter::unwrapUnchecked(info[2])), matSelf.type(), FF_MAT_SET, FF::matPut);
  //} else if (Vec3::hasInstance(info[2])) {
  //  FF_ASSERT_CHANNELS(cn, 3, "Mat::Set");
  //  FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<3>(Vec3::Converter::unwrapUnchecked(info[2])), matSelf.type(), FF_MAT_SET, FF::matPut);
  //} else if (Vec4::hasInstance(info[2])) {
  //  FF_ASSERT_CHANNELS(cn, 4, "Mat::Set");
  //  FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<4>(Vec4::Converter::unwrapUnchecked(info[2])), matSelf.type(), FF_MAT_SET, FF::matPut);
  //} else if (info[2].IsNumber()) {
  //  FF_MAT_APPLY_TYPED_OPERATOR(matSelf, info[2], matSelf.type(), FF_MAT_SET, FF::matPut);
  //} else {
  //  return tryCatch.throwError("unexpected argument 2");
  //}
  return env.Undefined();
}

Napi::Value Mat::SetTo(const Napi::CallbackInfo& info) {
  //FF::executeSyncBinding(
  //    std::make_shared<MatBindings::SetToWorker>(Mat::unwrapSelf(info)),
  //    "Mat::SetTo",
  //    info);
  return info.Env().Undefined();
}

Napi::Value Mat::SetToAsync(const Napi::CallbackInfo& info) {
  //FF::executeAsyncBinding(
  //    std::make_shared<MatBindings::SetToWorker>(Mat::unwrapSelf(info)),
  //    "Mat::SetToAsync",
  //    info);
  return info.Env().Undefined();
}

#define FF_JS_ARRAY_FROM_MAT_2D(mat, rowArray, get)         \
  for (int r = 0; r < mat.rows; r++) {                      \
    Napi::Array colArray = Napi::Array::New(env, mat.cols); \
    for (int c = 0; c < mat.cols; c++) {                    \
      (colArray).Set(c, get(mat, r, c));                    \
    }                                                       \
    (rowArray).Set(r, colArray);                            \
  }

#define FF_JS_ARRAY_FROM_MAT_3D(mat, rowArray, get)                \
  for (int r = 0; r < mat.size[0]; r++) {                          \
    Napi::Array colArray = Napi::Array::New(env, mat.size[1]);     \
    for (int c = 0; c < mat.size[1]; c++) {                        \
      Napi::Array depthArray = Napi::Array::New(env, mat.size[2]); \
      for (int z = 0; z < mat.size[2]; z++) {                      \
        (depthArray).Set(z, get(mat, r, c, z));                    \
      }                                                            \
      (colArray).Set(c, depthArray);                               \
    }                                                              \
    (rowArray).Set(r, colArray);                                   \
  }

#define FF_JS_ARRAY_FROM_MAT_4D(mat, rowArray, get)             \
  {                                                             \
    cv::MatSize sizes = mat.size;                               \
    cv::Vec4i cur = cv::Vec4i(0, 0, 0, 0);                      \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {             \
      Napi::Array array1 = Napi::Array::New(env, sizes[1]);     \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {           \
        Napi::Array array2 = Napi::Array::New(env, sizes[2]);   \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {         \
          Napi::Array array3 = Napi::Array::New(env, sizes[3]); \
          for (cur[3] = 0; cur[3] < sizes[3]; cur[3]++) {       \
            (array3).Set(cur[3], get(mat, cur));                \
          }                                                     \
          (array2).Set(cur[2], array3);                         \
        }                                                       \
        (array1).Set(cur[1], array2);                           \
      }                                                         \
      (rowArray).Set(cur[0], array1);                           \
    }                                                           \
  }

#define FF_JS_ARRAY_FROM_MAT_5D(mat, rowArray, get)               \
  {                                                               \
    cv::MatSize sizes = mat.size;                                 \
    cv::Vec4i cur = cv::Vec5i(0, 0, 0, 0, 0);                     \
    for (cur[0] = 0; cur[0] < sizes[0]; cur[0]++) {               \
      Napi::Array array1 = Napi::Array::New(env, sizes[1]);       \
      for (cur[1] = 0; cur[1] < sizes[1]; cur[1]++) {             \
        Napi::Array array2 = Napi::Array::New(env, sizes[2]);     \
        for (cur[2] = 0; cur[2] < sizes[2]; cur[2]++) {           \
          Napi::Array array3 = Napi::Array::New(env, sizes[3]);   \
          for (cur[3] = 0; cur[3] < sizes[3]; cur[3]++) {         \
            Napi::Array array4 = Napi::Array::New(env, sizes[4]); \
            for (cur[4] = 0; cur[4] < sizes[4]; cur[4]++) {       \
              (array4).Set(cur[4], get(mat, cur));                \
            }                                                     \
            (array3).Set(cur[3], array3);                         \
          }                                                       \
          (array2).Set(cur[2], array3);                           \
        }                                                         \
        (array1).Set(cur[1], array2);                             \
      }                                                           \
      (rowArray).Set(cur[0], array1);                             \
    }                                                             \
  }


Napi::Value Mat::GetDataAsArray(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::GetDataAsArray");
  // cv::Mat mat = Mat::unwrapSelf(info);
  // Napi::Array rowArray = Napi::Array::New(env, mat.size[0]);
// 
  // switch (mat.dims) {
  // case 2:
  //   FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT_2D, FF::matGet);
  //   break;
  // case 3:
  //   FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT_3D, FF::matGet);
  //   break;
  // case 4:
  //   FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT_4D, FF::matGet);
  //   break;
  //   // case 5:  FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT_5D, FF::matGet);  break;
  // default:
  //   return tryCatch.throwError("not implemented yet - mat dims:" + std::to_string(mat.dims));
  // }
  // return rowArray;
  return env.Undefined();
}


Napi::Value Mat::SetData(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::SetData");
  // cv::Mat mat = Mat::unwrapSelf(info);
  // char* data = static_cast<char*>(info[0].ToObject(Napi::GetCurrentContext(.As<Napi::Buffer<char>>().Data())));
  // size_t size = mat.rows * mat.cols * mat.elemSize();
  // memcpy(mat.data, data, size);
  // return Mat::Converter::wrap(mat);
  return env.Undefined();
}


Napi::Value Mat::GetRegion(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::GetRegion");
  // cv::Rect2d rect;
  // if (Rect::Converter::arg(0, &rect, info)) {
  //   return tryCatch.reThrow();
  // }
  // // FF::TryCatch tryCatch do not work here
  // try {
  //   return Mat::Converter::wrap(Mat::unwrapSelf(info)(rect));
  // } catch (const std::exception& e) {
  //   return tryCatch.throwError(e.what());
  // }
  return env.Undefined();
}

Napi::Value Mat::Norm(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::Norm");
  // bool withSrc2 = FF::hasArg(info, 0) && Mat::hasInstance(info[0]);
  // uint i = withSrc2 ? 1 : 0;
  // double norm;
// 
  // // optional args
  // bool hasOptArgsObj = FF::isArgObject(info, i);
  // Napi::Object optArgs = hasOptArgsObj ? info[i].ToObject(Napi::GetCurrentContext()) : Napi::Object::New(env);
// 
  // uint normType = cv::NORM_L2;
  // cv::Mat mask = cv::noArray().getMat();
// 
  // if (
  //     (hasOptArgsObj && (FF::UintConverter::optProp(&normType, "normType", optArgs) || Mat::Converter::optProp(&mask, "mask", optArgs))) || (FF::UintConverter::optArg(i, &normType, info) || Mat::Converter::optArg(i + 1, &mask, info))) {
  //   return tryCatch.reThrow();
  // }
// 
  // if (withSrc2) {
  //   cv::Mat src2;
  //   if (Mat::Converter::arg(0, &src2, info)) {
  //     return tryCatch.reThrow();
  //   }
  //   norm = cv::norm(Mat::unwrapSelf(info), src2, (int)normType, mask);
  // } else {
  //   norm = cv::norm(Mat::unwrapSelf(info), (int)normType, mask);
  // }
  // return norm;
  return env.Undefined();
}

// The method makes a new header for the specified matrix row and returns it. This is an O(1)
// operation, regardless of the matrix size. The underlying data of the new matrix is shared with the
// original matrix.

Napi::Value Mat::Row(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::Row");
  // int row;
  // if (FF::IntConverter::arg(0, &row, info)) {
  //   return tryCatch.reThrow();
  // }
  // return Mat::Converter::wrap(Mat::unwrapSelf(info).row(row));
  return env.Undefined();
}

// The method makes a new header for the specified matrix column and returns it. This is an O(1)
// operation, regardless of the matrix size. The underlying data of the new matrix is shared with the
// original matrix. See also the Mat::row description.
Napi::Value Mat::Col(const Napi::CallbackInfo& info) {
  // Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::Col");
  // int col;
  // if (FF::IntConverter::arg(0, &col, info)) {
  //   return tryCatch.reThrow();
  // }
  // return Mat::Converter::wrap(Mat::unwrapSelf(info).col(col));
  return info.Env().Undefined();
}

// The method makes a new header for the specified row span of the matrix. Similarly to Mat::row and
// Mat::col , this is an O(1) operation.
Napi::Value Mat::RowRange(const Napi::CallbackInfo& info) {
  // Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::RowRange");
  // int start, end;
  // if (FF::IntConverter::arg(0, &start, info) || FF::IntConverter::arg(1, &end, info)) {
  //   return tryCatch.reThrow();
  // }
  // return Mat::Converter::wrap(Mat::unwrapSelf(info).rowRange(start, end));
  return info.Env().Undefined();
}

// The method makes a new header for the specified column span of the matrix. Similarly to Mat::row and
// Mat::col , this is an O(1) operation.
Napi::Value Mat::ColRange(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  // FF::TryCatch tryCatch(env, "Mat::ColRange");
  // int start, end;
  // if (FF::IntConverter::arg(0, &start, info) || FF::IntConverter::arg(1, &end, info)) {
  //   return tryCatch.reThrow();
  // }
  // return Mat::Converter::wrap(Mat::unwrapSelf(info).colRange(start, end));
  return env.Undefined();
}

Napi::Value Mat::Release(const Napi::CallbackInfo& info) {
  // must get pointer to the original; else we are just getting a COPY and then releasing that!
  // Mat::unwrapThis(info)->self.release();
  return info.Env().Undefined();
}

Napi::Value Mat::PushBack(const Napi::CallbackInfo& info) {
  //Mat::syncBinding<MatBindings::PushBack>("PushBack", info);
  return info.Env().Undefined();
}

Napi::Value Mat::PushBackAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<MatBindings::PushBack>("PushBack", info);
  return info.Env().Undefined();
}

Napi::Value Mat::PopBack(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<MatBindings::PopBack>("PopBack", info);
  return info.Env().Undefined();
}

Napi::Value Mat::PopBackAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<MatBindings::PopBack>("PopBack", info);
  return info.Env().Undefined();
}

Napi::Value Mat::GetData(const Napi::CallbackInfo& info) {
  // FF::executeSyncBinding(
  //     std::make_shared<MatBindings::GetDataWorker>(Mat::unwrapSelf(info)),
  //     "Mat::GetData",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::GetDataAsync(const Napi::CallbackInfo& info) {
  //FF::executeAsyncBinding(
  //    std::make_shared<MatBindings::GetDataWorker>(Mat::unwrapSelf(info)),
  //    "Mat::GetDataAsync",
  //    info);
  return info.Env().Undefined();
}

Napi::Value Mat::Copy(const Napi::CallbackInfo& info) {
  //Mat::syncBinding<MatBindings::Copy>("Copy", info);
  return info.Env().Undefined();
}

Napi::Value Mat::CopyAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<MatBindings::Copy>("Copy", info);
  return info.Env().Undefined();
}

Napi::Value Mat::CopyTo(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<MatBindings::CopyTo>("CopyTo", info);
  return info.Env().Undefined();
}

Napi::Value Mat::CopyToAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<MatBindings::CopyTo>("CopyTo", info);
  return info.Env().Undefined();
}

Napi::Value Mat::ConvertTo(const Napi::CallbackInfo& info) {
  //Mat::syncBinding<MatBindings::ConvertTo>("ConvertTo", info);
  return info.Env().Undefined();
}

Napi::Value Mat::ConvertToAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<MatBindings::ConvertTo>("ConvertTo", info);
}

Napi::Value Mat::PadToSquare(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<MatBindings::PadToSquare>("PadToSquare", info);
}

Napi::Value Mat::PadToSquareAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<MatBindings::PadToSquare>("PadToSquare", info);
}

Napi::Value Mat::Dct(const Napi::CallbackInfo& info) {
  // FF::executeSyncBinding(
  //     std::make_shared<MatBindings::DCTWorker>(Mat::unwrapSelf(info)),
  //     "Mat::Dct",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::DctAsync(const Napi::CallbackInfo& info) {
  // FF::executeAsyncBinding(
  //     std::make_shared<MatBindings::DCTWorker>(Mat::unwrapSelf(info)),
  //     "Mat::DctAsync",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::Idct(const Napi::CallbackInfo& info) {
  //FF::executeSyncBinding(
  //    std::make_shared<MatBindings::DCTWorker>(Mat::unwrapSelf(info)),
  //    "Mat::Idct",
  //    info);
  return info.Env().Undefined();
}

Napi::Value Mat::IdctAsync(const Napi::CallbackInfo& info) {
  // FF::executeAsyncBinding(
  //     std::make_shared<MatBindings::DCTWorker>(Mat::unwrapSelf(info)),
  //     "Mat::IdctAsync",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::Dft(const Napi::CallbackInfo& info) {
  // FF::executeSyncBinding(
  //     std::make_shared<MatBindings::DFTWorker>(Mat::unwrapSelf(info)),
  //     "Mat::Dft",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::DftAsync(const Napi::CallbackInfo& info) {
  // FF::executeAsyncBinding(
  //     std::make_shared<MatBindings::DFTWorker>(Mat::unwrapSelf(info)),
  //     "Mat::DftAsync",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::Idft(const Napi::CallbackInfo& info) {
  // FF::executeSyncBinding(
  //     std::make_shared<MatBindings::DFTWorker>(Mat::unwrapSelf(info)),
  //     "Mat::Idft",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::IdftAsync(const Napi::CallbackInfo& info) {
  //FF::executeAsyncBinding(
  //    std::make_shared<MatBindings::DFTWorker>(Mat::unwrapSelf(info)),
  //    "Mat::IdftAsync",
  //    info);
  return info.Env().Undefined();
}

Napi::Value Mat::Flip(const Napi::CallbackInfo& info) {
  // FF::executeSyncBinding(
  //     std::make_shared<MatBindings::FlipWorker>(Mat::unwrapSelf(info)),
  //     "Mat::Flip",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::FlipAsync(const Napi::CallbackInfo& info) {
  // FF::executeAsyncBinding(
  //     std::make_shared<MatBindings::FlipWorker>(Mat::unwrapSelf(info)),
  //     "Mat::FlipAsync",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::CopyMakeBorder(const Napi::CallbackInfo& info) {
  // FF::executeSyncBinding(
  //     std::make_shared<MatBindings::CopyMakeBorderWorker>(Mat::unwrapSelf(info)),
  //     "Mat::CopyMakeBorder",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::CopyMakeBorderAsync(const Napi::CallbackInfo& info) {
  // FF::executeAsyncBinding(
  //     std::make_shared<MatBindings::CopyMakeBorderWorker>(Mat::unwrapSelf(info)),
  //     "Mat::CopyMakeBorderAsync",
  //     info);
  return info.Env().Undefined();
}

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
Napi::Value Mat::Rotate(const Napi::CallbackInfo& info) {
  // FF::executeSyncBinding(
  //     std::make_shared<MatBindings::RotateWorker>(Mat::unwrapSelf(info)),
  //     "Mat::Rotate",
  //     info);
  return info.Env().Undefined();
}

Napi::Value Mat::RotateAsync(const Napi::CallbackInfo& info) {
  //FF::executeAsyncBinding(
  //    std::make_shared<MatBindings::RotateWorker>(Mat::unwrapSelf(info)),
  //    "Mat::RotateAsync",
  //    info);
  return info.Env().Undefined();
}
#endif

Napi::Value Mat::AddWeighted(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::AddWeighted>("AddWeighted", info);
  return info.Env().Undefined();
}

Napi::Value Mat::AddWeightedAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::AddWeighted>("AddWeighted", info);
  return info.Env().Undefined();
}

Napi::Value Mat::MinMaxLoc(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::MinMaxLoc>("MinMaxLoc", info);
  return info.Env().Undefined();
}

Napi::Value Mat::MinMaxLocAsync(const Napi::CallbackInfo& info) {
  return info.Env().Undefined();
  // Mat::asyncBinding<CoreBindings::MinMaxLoc>("MinMaxLoc", info);
}

Napi::Value Mat::FindNonZero(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::FindNonZero>("FindNonZero", info);
  return info.Env().Undefined();
}

Napi::Value Mat::FindNonZeroAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::FindNonZero>("FindNonZero", info);
  return info.Env().Undefined();
}

Napi::Value Mat::CountNonZero(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::CountNonZero>("CountNonZero", info);
  return info.Env().Undefined();
}

Napi::Value Mat::CountNonZeroAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::CountNonZero>("CountNonZero", info);
  return info.Env().Undefined();
}

Napi::Value Mat::Normalize(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::Normalize>("Normalize", info);
  return info.Env().Undefined();
}

Napi::Value Mat::NormalizeAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::Normalize>("Normalize", info);
  return info.Env().Undefined();
}

Napi::Value Mat::Split(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::Split>("Split", info);
  return info.Env().Undefined();
}

Napi::Value Mat::SplitAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::Split>("Split", info);
  return info.Env().Undefined();
}

Napi::Value Mat::MulSpectrums(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::MulSpectrums>("MulSpectrums", info);
  return info.Env().Undefined();
}

Napi::Value Mat::MulSpectrumsAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::MulSpectrums>("MulSpectrums", info);
  return info.Env().Undefined();
}

Napi::Value Mat::Transform(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::Transform>("Transform", info);
  return info.Env().Undefined();
}

Napi::Value Mat::TransformAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::Transform>("Transform", info);
  return info.Env().Undefined();
}

Napi::Value Mat::PerspectiveTransform(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::PerspectiveTransform>("PerspectiveTransform", info);
  return info.Env().Undefined();
}

Napi::Value Mat::PerspectiveTransformAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::PerspectiveTransform>("PerspectiveTransform", info);
  return info.Env().Undefined();
}

Napi::Value Mat::Sum(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::Sum>("Sum", info);
  return info.Env().Undefined();
}

Napi::Value Mat::SumAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::Sum>("Sum", info);
  return info.Env().Undefined();
}

Napi::Value Mat::ConvertScaleAbs(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::ConvertScaleAbs>("ConvertScaleAbs", info);
  return info.Env().Undefined();
}

Napi::Value Mat::ConvertScaleAbsAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::ConvertScaleAbs>("ConvertScaleAbs", info);
  return info.Env().Undefined();
}

Napi::Value Mat::Mean(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::Mean>("Mean", info);
  return info.Env().Undefined();
}

Napi::Value Mat::MeanAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::Mean>("Mean", info);
  return info.Env().Undefined();
}

Napi::Value Mat::MeanStdDev(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::MeanStdDev>("MeanStdDev", info);
  return info.Env().Undefined();
}

Napi::Value Mat::MeanStdDevAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::MeanStdDev>("MeanStdDev", info);
  return info.Env().Undefined();
}

Napi::Value Mat::Reduce(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::Reduce>("Reduce", info);
  return info.Env().Undefined();
}

Napi::Value Mat::ReduceAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::Reduce>("Reduce", info);
  return info.Env().Undefined();
}

Napi::Value Mat::Eigen(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::Eigen>("Eigen", info);
  return info.Env().Undefined();
}

Napi::Value Mat::EigenAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::Eigen>("Eigen", info);
  return info.Env().Undefined();
}

Napi::Value Mat::Solve(const Napi::CallbackInfo& info) {
  // Mat::syncBinding<CoreBindings::Solve>("Solve", info);
  return info.Env().Undefined();
}

Napi::Value Mat::SolveAsync(const Napi::CallbackInfo& info) {
  // Mat::asyncBinding<CoreBindings::Solve>("Solve", info);
  return info.Env().Undefined();
}
