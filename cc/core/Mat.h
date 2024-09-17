// #include "CatchCvExceptionWorker.h"
// #include "ExternalMemTracking.h"
#include "NativeNodeUtils.h"
// #include "Point2.h"
// #include "Rect.h"
// #include "RotatedRect.h"
// #include "Vec.h"
// #include "coreUtils.h"
#include "macros.h"
#include "Converters.h"
#include "matUtils.h"

#ifndef __FF_MAT_H__
#define __FF_MAT_H__

// #define NN_HEADER_ACC(ff_property_name) \
//   static ff_property_converter::Type getProperty_##ff_property_name(ClassType* self) {     \
//     return self->ff_access_property_expr;                                                  \
//   }                                                                                        \
//   static Napi::Value ff_property_name##_getter(const Napi::CallbackInfo& info) {           \
//     return getter<ff_property_converter>(info, getProperty_##ff_property_name);            \
//   }
// 
//                 FF::ObjectWrap<Mat, cv::Mat>
class Mat: public Napi::ObjectWrap<Mat> {
public:
  static Napi::FunctionReference constructor;
  Mat(const Napi::CallbackInfo& info);
  // static Napi::Value New(const Napi::CallbackInfo& info);

  static const char* getClassName() {
    return "Mat";
  }

  cv::Mat self;

  static Napi::Object Init(Napi::Object exports);

  Napi::Value Getrows(const Napi::CallbackInfo& info);
  void Setrows(const Napi::CallbackInfo& info, const Napi::Value& value);

  Napi::Value Getcols(const Napi::CallbackInfo& info);
  void Setcols(const Napi::CallbackInfo& info, const Napi::Value& value);

  Napi::Value Gettype(const Napi::CallbackInfo& info);


  // FF_GETTER_CUSTOM(rows, FF::IntConverter, self.rows);
  // FF_GETTER_CUSTOM(cols, FF::IntConverter, self.cols);
  // FF_GETTER_CUSTOM(type, FF::IntConverter, self.type());
  // FF_GETTER_CUSTOM(channels, FF::IntConverter, self.channels());
  // FF_GETTER_CUSTOM(dims, FF::IntConverter, self.dims);
  // FF_GETTER_CUSTOM(depth, FF::IntConverter, self.depth());
  // FF_GETTER_CUSTOM(empty, FF::IntConverter, self.empty());

  // Napi::Value GetElemSize(const Napi::CallbackInfo& info) {
  //   return (int)Mat::unwrapSelf(info).elemSize();
  // };
// 
  // Napi::Value GetStep(const Napi::CallbackInfo& info) {
  //   return (int)Mat::unwrapSelf(info).step.operator size_t();
  // };

  // Napi::Value GetSizes(const Napi::CallbackInfo& info) {
  //   cv::Mat m = Mat::unwrapSelf(info);
  //   std::vector<int> sizes;
  //   for (int s = 0; s < m.dims; s++) {
  //     sizes.push_back(m.size[s]);
  //   }
  //   return FF::IntArrayConverter::wrap(sizes);
  // };

  // FF_INIT_MAT_OPERATIONS();

  // static Napi::Value Dot(const Napi::CallbackInfo& info) {
  //   FF_OPERATOR_RET_SCALAR(&cv::Mat::dot, FF_APPLY_CLASS_FUNC, Mat, "Dot");
  // }

  static Napi::Value Eye(const Napi::CallbackInfo& info);
  static Napi::Value Ones(const Napi::CallbackInfo& info);
  static Napi::Value Zeros(const Napi::CallbackInfo& info);
  static Napi::Value FlattenFloat(const Napi::CallbackInfo& info);
  static Napi::Value At(const Napi::CallbackInfo& info);
  static Napi::Value AtRaw(const Napi::CallbackInfo& info);
  static Napi::Value Set(const Napi::CallbackInfo& info);
  static Napi::Value SetTo(const Napi::CallbackInfo& info);
  static Napi::Value SetToAsync(const Napi::CallbackInfo& info);
  static Napi::Value GetDataAsArray(const Napi::CallbackInfo& info);
  static Napi::Value SetData(const Napi::CallbackInfo& info);
  static Napi::Value GetRegion(const Napi::CallbackInfo& info);
  static Napi::Value Norm(const Napi::CallbackInfo& info);
  static Napi::Value Row(const Napi::CallbackInfo& info);
  static Napi::Value RowRange(const Napi::CallbackInfo& info);
  static Napi::Value Col(const Napi::CallbackInfo& info);
  static Napi::Value ColRange(const Napi::CallbackInfo& info);
  static Napi::Value Release(const Napi::CallbackInfo& info);
  static Napi::Value PushBack(const Napi::CallbackInfo& info);
  static Napi::Value PushBackAsync(const Napi::CallbackInfo& info);
  static Napi::Value PopBack(const Napi::CallbackInfo& info);
  static Napi::Value PopBackAsync(const Napi::CallbackInfo& info);
  static Napi::Value GetData(const Napi::CallbackInfo& info);
  static Napi::Value GetDataAsync(const Napi::CallbackInfo& info);
  static Napi::Value Copy(const Napi::CallbackInfo& info);
  static Napi::Value CopyAsync(const Napi::CallbackInfo& info);
  static Napi::Value CopyTo(const Napi::CallbackInfo& info);
  static Napi::Value CopyToAsync(const Napi::CallbackInfo& info);
  static Napi::Value ConvertTo(const Napi::CallbackInfo& info);
  static Napi::Value ConvertToAsync(const Napi::CallbackInfo& info);
  static Napi::Value PadToSquare(const Napi::CallbackInfo& info);
  static Napi::Value PadToSquareAsync(const Napi::CallbackInfo& info);
  static Napi::Value Dct(const Napi::CallbackInfo& info);
  static Napi::Value DctAsync(const Napi::CallbackInfo& info);
  static Napi::Value Idct(const Napi::CallbackInfo& info);
  static Napi::Value IdctAsync(const Napi::CallbackInfo& info);
  static Napi::Value Dft(const Napi::CallbackInfo& info);
  static Napi::Value DftAsync(const Napi::CallbackInfo& info);
  static Napi::Value Idft(const Napi::CallbackInfo& info);
  static Napi::Value IdftAsync(const Napi::CallbackInfo& info);
  static Napi::Value Flip(const Napi::CallbackInfo& info);
  static Napi::Value FlipAsync(const Napi::CallbackInfo& info);
  static Napi::Value CopyMakeBorder(const Napi::CallbackInfo& info);
  static Napi::Value CopyMakeBorderAsync(const Napi::CallbackInfo& info);

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static Napi::Value Rotate(const Napi::CallbackInfo& info);
  static Napi::Value RotateAsync(const Napi::CallbackInfo& info);
#endif

  static Napi::Value AddWeighted(const Napi::CallbackInfo& info);
  static Napi::Value AddWeightedAsync(const Napi::CallbackInfo& info);
  static Napi::Value MinMaxLoc(const Napi::CallbackInfo& info);
  static Napi::Value MinMaxLocAsync(const Napi::CallbackInfo& info);
  static Napi::Value FindNonZero(const Napi::CallbackInfo& info);
  static Napi::Value FindNonZeroAsync(const Napi::CallbackInfo& info);
  static Napi::Value CountNonZero(const Napi::CallbackInfo& info);
  static Napi::Value CountNonZeroAsync(const Napi::CallbackInfo& info);
  static Napi::Value Normalize(const Napi::CallbackInfo& info);
  static Napi::Value NormalizeAsync(const Napi::CallbackInfo& info);
  static Napi::Value Split(const Napi::CallbackInfo& info);
  static Napi::Value SplitAsync(const Napi::CallbackInfo& info);
  static Napi::Value MulSpectrums(const Napi::CallbackInfo& info);
  static Napi::Value MulSpectrumsAsync(const Napi::CallbackInfo& info);
  static Napi::Value Transform(const Napi::CallbackInfo& info);
  static Napi::Value TransformAsync(const Napi::CallbackInfo& info);
  static Napi::Value PerspectiveTransform(const Napi::CallbackInfo& info);
  static Napi::Value PerspectiveTransformAsync(const Napi::CallbackInfo& info);
  static Napi::Value Sum(const Napi::CallbackInfo& info);
  static Napi::Value SumAsync(const Napi::CallbackInfo& info);
  static Napi::Value ConvertScaleAbs(const Napi::CallbackInfo& info);
  static Napi::Value ConvertScaleAbsAsync(const Napi::CallbackInfo& info);
  static Napi::Value Mean(const Napi::CallbackInfo& info);
  static Napi::Value MeanAsync(const Napi::CallbackInfo& info);
  static Napi::Value MeanStdDev(const Napi::CallbackInfo& info);
  static Napi::Value MeanStdDevAsync(const Napi::CallbackInfo& info);
  static Napi::Value Reduce(const Napi::CallbackInfo& info);
  static Napi::Value ReduceAsync(const Napi::CallbackInfo& info);
  static Napi::Value Eigen(const Napi::CallbackInfo& info);
  static Napi::Value EigenAsync(const Napi::CallbackInfo& info);
  static Napi::Value Solve(const Napi::CallbackInfo& info);
  static Napi::Value SolveAsync(const Napi::CallbackInfo& info);
};

#endif
