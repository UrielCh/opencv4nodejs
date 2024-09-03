#include "CatchCvExceptionWorker.h"
#include "ExternalMemTracking.h"
#include "NativeNodeUtils.h"
#include "Point2.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "Vec.h"
#include "coreUtils.h"
#include "macros.h"
#include "matUtils.h"

#ifndef __FF_MAT_H__
#define __FF_MAT_H__

class Mat : public FF::ObjectWrap<Mat, cv::Mat> {
public:
  static Napi::FunctionReference constructor;
  ;

  static const char* getClassName() {
    return "Mat";
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  FF_GETTER_CUSTOM(rows, FF::IntConverter, self.rows);
  FF_GETTER_CUSTOM(cols, FF::IntConverter, self.cols);
  FF_GETTER_CUSTOM(type, FF::IntConverter, self.type());
  FF_GETTER_CUSTOM(channels, FF::IntConverter, self.channels());
  FF_GETTER_CUSTOM(dims, FF::IntConverter, self.dims);
  FF_GETTER_CUSTOM(depth, FF::IntConverter, self.depth());
  FF_GETTER_CUSTOM(empty, FF::IntConverter, self.empty());

  Napi::Value GetElemSize(const Napi::CallbackInfo& info) {
    return (int)Mat::unwrapSelf(info).elemSize();
  };

  Napi::Value GetStep(const Napi::CallbackInfo& info) {
    return (int)Mat::unwrapSelf(info).step.operator size_t();
  };

  Napi::Value GetSizes(const Napi::CallbackInfo& info) {
    cv::Mat m = Mat::unwrapSelf(info);
    std::vector<int> sizes;
    for (int s = 0; s < m.dims; s++) {
      sizes.push_back(m.size[s]);
    }
    return FF::IntArrayConverter::wrap(sizes);
  };

  FF_INIT_MAT_OPERATIONS();

  static Napi::Value Dot(const Napi::CallbackInfo& info) {
    FF_OPERATOR_RET_SCALAR(&cv::Mat::dot, FF_APPLY_CLASS_FUNC, Mat, "Dot");
  }

  static void New(const Napi::CallbackInfo& info);
  static void Eye(const Napi::CallbackInfo& info);
  static void Ones(const Napi::CallbackInfo& info);
  static void Zeros(const Napi::CallbackInfo& info);
  static void FlattenFloat(const Napi::CallbackInfo& info);
  static void At(const Napi::CallbackInfo& info);
  static void AtRaw(const Napi::CallbackInfo& info);
  static void Set(const Napi::CallbackInfo& info);
  static void SetTo(const Napi::CallbackInfo& info);
  static void SetToAsync(const Napi::CallbackInfo& info);
  static void GetDataAsArray(const Napi::CallbackInfo& info);
  static void SetData(const Napi::CallbackInfo& info);
  static void GetRegion(const Napi::CallbackInfo& info);
  static void Norm(const Napi::CallbackInfo& info);
  static void Row(const Napi::CallbackInfo& info);
  static void RowRange(const Napi::CallbackInfo& info);
  static void Col(const Napi::CallbackInfo& info);
  static void ColRange(const Napi::CallbackInfo& info);
  static void Release(const Napi::CallbackInfo& info);
  static void PushBack(const Napi::CallbackInfo& info);
  static void PushBackAsync(const Napi::CallbackInfo& info);
  static void PopBack(const Napi::CallbackInfo& info);
  static void PopBackAsync(const Napi::CallbackInfo& info);
  static void GetData(const Napi::CallbackInfo& info);
  static void GetDataAsync(const Napi::CallbackInfo& info);
  static void Copy(const Napi::CallbackInfo& info);
  static void CopyAsync(const Napi::CallbackInfo& info);
  static void CopyTo(const Napi::CallbackInfo& info);
  static void CopyToAsync(const Napi::CallbackInfo& info);
  static void ConvertTo(const Napi::CallbackInfo& info);
  static void ConvertToAsync(const Napi::CallbackInfo& info);
  static void PadToSquare(const Napi::CallbackInfo& info);
  static void PadToSquareAsync(const Napi::CallbackInfo& info);
  static void Dct(const Napi::CallbackInfo& info);
  static void DctAsync(const Napi::CallbackInfo& info);
  static void Idct(const Napi::CallbackInfo& info);
  static void IdctAsync(const Napi::CallbackInfo& info);
  static void Dft(const Napi::CallbackInfo& info);
  static void DftAsync(const Napi::CallbackInfo& info);
  static void Idft(const Napi::CallbackInfo& info);
  static void IdftAsync(const Napi::CallbackInfo& info);
  static void Flip(const Napi::CallbackInfo& info);
  static void FlipAsync(const Napi::CallbackInfo& info);
  static void CopyMakeBorder(const Napi::CallbackInfo& info);
  static void CopyMakeBorderAsync(const Napi::CallbackInfo& info);

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static void Rotate(const Napi::CallbackInfo& info);
  static void RotateAsync(const Napi::CallbackInfo& info);
#endif

  static void AddWeighted(const Napi::CallbackInfo& info);
  static void AddWeightedAsync(const Napi::CallbackInfo& info);
  static void MinMaxLoc(const Napi::CallbackInfo& info);
  static void MinMaxLocAsync(const Napi::CallbackInfo& info);
  static void FindNonZero(const Napi::CallbackInfo& info);
  static void FindNonZeroAsync(const Napi::CallbackInfo& info);
  static void CountNonZero(const Napi::CallbackInfo& info);
  static void CountNonZeroAsync(const Napi::CallbackInfo& info);
  static void Normalize(const Napi::CallbackInfo& info);
  static void NormalizeAsync(const Napi::CallbackInfo& info);
  static void Split(const Napi::CallbackInfo& info);
  static void SplitAsync(const Napi::CallbackInfo& info);
  static void MulSpectrums(const Napi::CallbackInfo& info);
  static void MulSpectrumsAsync(const Napi::CallbackInfo& info);
  static void Transform(const Napi::CallbackInfo& info);
  static void TransformAsync(const Napi::CallbackInfo& info);
  static void PerspectiveTransform(const Napi::CallbackInfo& info);
  static void PerspectiveTransformAsync(const Napi::CallbackInfo& info);
  static void Sum(const Napi::CallbackInfo& info);
  static void SumAsync(const Napi::CallbackInfo& info);
  static void ConvertScaleAbs(const Napi::CallbackInfo& info);
  static void ConvertScaleAbsAsync(const Napi::CallbackInfo& info);
  static void Mean(const Napi::CallbackInfo& info);
  static void MeanAsync(const Napi::CallbackInfo& info);
  static void MeanStdDev(const Napi::CallbackInfo& info);
  static void MeanStdDevAsync(const Napi::CallbackInfo& info);
  static void Reduce(const Napi::CallbackInfo& info);
  static void ReduceAsync(const Napi::CallbackInfo& info);
  static void Eigen(const Napi::CallbackInfo& info);
  static void EigenAsync(const Napi::CallbackInfo& info);
  static void Solve(const Napi::CallbackInfo& info);
  static void SolveAsync(const Napi::CallbackInfo& info);
};

#endif
